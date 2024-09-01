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
    abort();
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
}
/* -------------------------------------------------------------------------- */
void GameServer::update(float deltaTime) {}
/* -------------------------------------------------------------------------- */
void GameServer::abort() { Game::abort(); }
/* -------------------------------------------------------------------------- */
bool GameServer::initialize_network() {
  // TODO temporary, the port and player count should be specified in the GUI
  spdlog::info("Initializing network.");

  network_.set_max_number_of_players(MIN_NUMBER_OF_PLAYERS);
  network_.set_port(DEFAULT_PORT);

  network_.listen_for_connections();

  return true;
}
/* -------------------------------------------------------------------------- */
