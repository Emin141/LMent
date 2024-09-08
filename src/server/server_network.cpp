#include "server/server_network.h"
#include "common/game_started_message.h"
#include "common/message_type.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */
void ServerNetwork::set_port(int port) { port_ = port; }
/* -------------------------------------------------------------------------- */
void ServerNetwork::set_player_count(int playerCount) {
  playerCount_ = playerCount;
}
/* -------------------------------------------------------------------------- */
void ServerNetwork::listen_for_connections() {
  if (socketListener_.listen(port_) != sf::Socket::Done) {
    spdlog::error("Failed to listen on port {}.", port_);
  }
  socketListener_.setBlocking(false);

  int acceptedPlayersCount{0};
  uint8_t acceptedPlayerId{0};
  while (acceptedPlayersCount < playerCount_) {
    // Accept connections.
    auto newSocket{std::make_unique<sf::TcpSocket>()};
    if (socketListener_.accept(*newSocket) == sf::Socket::Done) {
      newSocket->setBlocking(false);
      spdlog::info("Accepted player from {}. Assigning player ID {}",
                   newSocket->getRemoteAddress().toString(), acceptedPlayerId);
      sockets_[acceptedPlayerId] = std::move(newSocket);
      acceptedPlayerId++;
      acceptedPlayersCount++; // Check later if all players are connected.
    }

    // Check for disconnections using explicit iterator.
    for (auto it = sockets_.begin(); it != sockets_.end();) {
      sf::Packet dummyPacket;
      if (it->second->receive(dummyPacket) == sf::Socket::Disconnected) {
        spdlog::warn("Player {} has disconnected. Connection is not saved.",
                     it->first);
        it = sockets_.erase(it); // Erase and get the next valid iterator
        acceptedPlayersCount--;
      } else {
        ++it; // Move to the next element
      }
    }

    // Avoid busy waiting.
    sf::sleep(sf::milliseconds(100));
  }

  spdlog::info(
      "Server has accepted sufficient number of players to start the match.");

  for (const auto &[playerId, socket] : sockets_) {
    playerAddresses_[playerId] = socket->getRemoteAddress();
  }

  broadcast(MessageType::GameStarted);
}
/* -------------------------------------------------------------------------- */
void ServerNetwork::broadcast(MessageType messageType) {
  switch (messageType) {
  case MessageType::GameStarted: {
    broadcast_game_started();
    break;
  }
  case MessageType::PlayerDisconnected: {
    spdlog::warn("Handling for disconnected players not implemented yet");
    break;
  }
  case MessageType::Update: {
    spdlog::warn("No game state update implementation done on server yet.");
    break;
  }
  default:
    spdlog::warn("No implementation for broadcast of message type {}",
                 static_cast<uint16_t>(messageType));
  }
}
/* -------------------------------------------------------------------------- */
void ServerNetwork::broadcast_game_started() {
  for (const auto &[playerId, socket] : sockets_) {
    sf::Packet sendPacket;
    sendPacket << MessageType::GameStarted;

    GameStartedMessage message;
    message.thisPlayerId = playerId;
    message.initialPlayerInfoList.reserve(playerCount_);

    // TODO dummy stuff, add actual info.
    for (uint8_t i{0}; i < playerCount_; ++i) {
      GameStartedMessage::InitialPlayerInfo initialPlayerInfo;
      initialPlayerInfo.id = i;
      initialPlayerInfo.position = i * 2 + 42;
      message.initialPlayerInfoList.emplace_back(initialPlayerInfo);
    }

    sendPacket << message;

    if (sockets_[playerId]->send(sendPacket) != sf::Socket::Done) {
      spdlog::error("Failed to send GameStarted message to player {} at {}.",
                    playerId,
                    sockets_[playerId]->getRemoteAddress().toString());
    }
  }
}
/* -------------------------------------------------------------------------- */