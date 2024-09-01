#include "client/game_client.h"
#include "common/defines.h"
#include "common/game_started_message.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
  window_.setVisible(false);
  if (!initialize_network()) {
    abort();
  }

  window_.setVisible(true);
  window_.setFramerateLimit(60);
}
/* -------------------------------------------------------------------------- */
void GameClient::run() {
  spdlog::info("Running client.");

  float deltaTime{1.0f / 60};
  while (isRunning_) {
    sf::Clock dtClock;

    poll_events();
    update(deltaTime);
    draw();

    deltaTime = dtClock.restart().asSeconds();
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::update(float deltaTime) {
  // TODO add logic code.
}
/* -------------------------------------------------------------------------- */
void GameClient::abort() { Game::abort(); }
/* -------------------------------------------------------------------------- */
bool GameClient::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");

  network_.set_ip_address("127.0.0.1");
  network_.set_port(DEFAULT_PORT);

  network_.connect();

  return true;
}
/* -------------------------------------------------------------------------- */
void GameClient::poll_events() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      // TODO Create event handling
      isRunning_ = false;
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::draw() {
  window_.clear();
  // TODO Call draw on all drawable objects.
  window_.display();
}
/* -------------------------------------------------------------------------- */