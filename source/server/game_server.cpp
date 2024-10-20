#include "server/game_server.h"
#include "common/defines.h"
#include "spdlog/spdlog.h"
#include <SFML/System.hpp>
/* -------------------------------------------------------------------------- */
GameServer::GameServer() : Game::Game() {}
/* -------------------------------------------------------------------------- */
void GameServer::init(int playerCount, int port) {
  if (!initialize_network(playerCount, port)) {
    abort();
  }
}
/* ---------------------------------------------------------------- */
void GameServer::run() {
  spdlog::info("Running server.");

  while (isRunning_) {
    update(0.0f); // Server does not need time delta.
  }
}
/* -------------------------------------------------------------------------- */
void GameServer::update(float deltaTime) {}
/* -------------------------------------------------------------------------- */
void GameServer::abort() { Game::abort(); }
/* -------------------------------------------------------------------------- */
bool GameServer::initialize_network(int playerCount, int port) {
  // TODO temporary, the port and player count should be specified in the GUI
  spdlog::info("Initializing network.");

  network_.set_player_count(MIN_NUMBER_OF_PLAYERS);
  network_.set_port(DEFAULT_PORT);

  network_.listen_for_connections();

  return true;
}
/* -------------------------------------------------------------------------- */
