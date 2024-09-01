#include "server/game_server.h"
#include "common/defines.h"
#include "common/misc_util.h"
#include "spdlog/spdlog.h"
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */
GameServer::GameServer() : Game::Game() {
  if (!initialize_network()) {
    exit();
  }
}
/* -------------------------------------------------------------------------- */
void GameServer::run() {
  spdlog::info("Running server.");

  float deltaTime{1.0f / 60};
  while (isRunning_) {
    sf::Clock dtClock;

    update(deltaTime);

    deltaTime = dtClock.restart().asSeconds();
  }

  exit();
}
/* -------------------------------------------------------------------------- */
void GameServer::update(float deltaTime) {}
/* -------------------------------------------------------------------------- */
void GameServer::exit() { Game::exit(); }
/* -------------------------------------------------------------------------- */
bool GameServer::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");
  std::string inputLine;
  std::printf("Player count (2 - 4): ");
  if (std::getline(std::cin, inputLine)) {
    std::stringstream lineStream{inputLine};
    lineStream >> maxNumberOfPlayers_;
    util::clamp<int>(maxNumberOfPlayers_, MIN_NUMBER_OF_PLAYERS,
                     MAX_NUMBER_OF_PLAYERS);
  } else {
    spdlog::error("Failed to read number of players.");
    return false;
  }

  std::printf("Listen on port (40000 - 60000): ");
  if (std::getline(std::cin, inputLine)) {
    std::stringstream lineStream{inputLine};
    lineStream >> port_;
    util::clamp<int>(port_, 40000, 60000);
    if (socketListener_.listen(port_) != sf::Socket::Done) {
      spdlog::error("Failed to listen on port {}.", port_);
    }
  } else {
    spdlog::error("Failed to read port number.");
    return false;
  }

  while (currentNumberOfPlayers_ < maxNumberOfPlayers_) {
    if (socketListener_.accept(sockets_[currentNumberOfPlayers_]) !=
        sf::Socket::Done) {
      spdlog::error(
          "Failed to accept player {} from address {}.",
          currentNumberOfPlayers_,
          sockets_[currentNumberOfPlayers_].getRemoteAddress().toString());
    }

    spdlog::info(
        "Accepted player {} from {}.", currentNumberOfPlayers_,
        sockets_[currentNumberOfPlayers_].getRemoteAddress().toString());
    currentNumberOfPlayers_++;
  }

  spdlog::info(
      "Server has accepted sufficient number of players to start the match.");
  return true;
}
/* -------------------------------------------------------------------------- */
