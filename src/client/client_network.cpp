#include "client/client_network.h"
#include "common/game_started_message.h"
#include "common/message_type.h"
#include "spdlog/spdlog.h"
/* -------------------------------------------------------------------------- */
void ClientNetwork::connect() {
  if (socket_.connect(serverAddress_, serverPort_, sf::Time(sf::seconds(10))) !=
      sf::Socket::Done) {
    spdlog::error("Failed to connect to server at {}:{} after 10 seconds.",
                  serverAddress_.toString(), serverPort_);
    abort();
  }

  spdlog::info("Client has connected to server at {}:{}.",
               serverAddress_.toString(), serverPort_);

  spdlog::info("Waiting for host to start the match.");
  sf::Packet receivedPacket{};
  if (socket_.receive(receivedPacket) != sf::Socket::Done) {
    spdlog::error("Failed to receive GameStarted message from server.");
    abort();
  }

  MessageType messageType{};
  receivedPacket >> messageType;
  if (messageType != MessageType::GameStarted) {
    spdlog::critical("Message received from server was not GameStarted.");
    abort();
  }

  GameStartedMessage message;
  receivedPacket >> message;

  spdlog::info("Received GameStarted message as playerId:{}, playerCount:{}.",
               message.thisPlayerId, message.initialPlayerInfoList.size());

  for (const auto &playerInfo : message.initialPlayerInfoList) {
    spdlog::debug("Player {} is at {}.", playerInfo.id, playerInfo.position);
  }
}
/* -------------------------------------------------------------------------- */
void ClientNetwork::set_ip_address(const sf::IpAddress &serverAddress) {
  serverAddress_ = serverAddress;
}
/* -------------------------------------------------------------------------- */
void ClientNetwork::set_port(int serverPort) { serverPort_ = serverPort; }
/* -------------------------------------------------------------------------- */