#include "server/server_network.h"
#include "common/game_started_message.h"
#include "spdlog/spdlog.h"
/* -------------------------------------------------------------------------- */
void ServerNetwork::set_port(int port) { port_ = port; }
/* -------------------------------------------------------------------------- */
void ServerNetwork::set_max_number_of_players(int playerCount) {
  playerCount_ = playerCount;
}
/* -------------------------------------------------------------------------- */
void ServerNetwork::listen_for_connections() {
  if (socketListener_.listen(port_) != sf::Socket::Done) {
    spdlog::error("Failed to listen on port {}.", port_);
  }

  int acceptedPlayersCount_{0};
  while (acceptedPlayersCount_ < playerCount_) {
    if (socketListener_.accept(sockets_[acceptedPlayersCount_]) !=
        sf::Socket::Done) {
      spdlog::error(
          "Failed to accept player {} from address {}.", acceptedPlayersCount_,
          sockets_[acceptedPlayersCount_].getRemoteAddress().toString());
    } else {
      spdlog::info(
          "Accepted player {} from {}.", acceptedPlayersCount_,
          sockets_[acceptedPlayersCount_].getRemoteAddress().toString());
      acceptedPlayersCount_++;
    }
  }

  spdlog::info(
      "Server has accepted sufficient number of players to start the match.");

  //! FIXME: The game should now check if all of the players are still
  //! connected.

  std::vector<std::thread> gameStartedSender;
  for (int i{0}; i < playerCount_; ++i) {
    gameStartedSender.emplace_back(
        [this, i]() -> void { send_game_started(i); });
  }

  for (auto &thread : gameStartedSender) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}
/* -------------------------------------------------------------------------- */
void ServerNetwork::send_game_started(uint8_t playerId) {
  GameStartedMessage message;
  message.thisPlayerId = playerId;
  message.initialPlayerInfoList.reserve(playerCount_);

  for (uint8_t i{0}; i < playerCount_; ++i) {
    GameStartedMessage::InitialPlayerInfo initialPlayerInfo;
    initialPlayerInfo.id = i;
    initialPlayerInfo.position = i * 2 + 42;
    message.initialPlayerInfoList.emplace_back(initialPlayerInfo);
  }

  sf::Packet sendPacket;
  sendPacket << message;
  if (sockets_[playerId].send(sendPacket) != sf::Socket::Done) {
    spdlog::error("Failed to send GameStarted message to player {} at {}.",
                  playerId, sockets_[playerId].getRemoteAddress().toString());
  }
}
/* -------------------------------------------------------------------------- */