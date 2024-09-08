#include "client/game_client.h"
#include "common/defines.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
/* -------------------------------------------------------------------------- */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
  window_.setVisible(false);
}
/* -------------------------------------------------------------------------- */
void GameClient::run() {
  spdlog::info("Running client.");

  float deltaTime{1.0f / 60};
  while (isRunning_) {
    sf::Clock dtClock;

    poll_events();
    update(deltaTime); // TODO Do I even need this?
    draw();

    deltaTime = dtClock.restart().asSeconds();
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::update(float deltaTime) {
  // TODO Remove this. This should be called in a connect to host screen.
  if (!network_.connected()) {
    if (!initialize_network()) {
      abort();
    }
    window_.setVisible(true);
    window_.setFramerateLimit(60);
  }

  network_.check_connection();
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
  // TODO Create event handling
  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed: {
      isRunning_ = false;
      break;
    }
    default:
      break;
    }
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::draw() {
  window_.clear();
  // TODO Call draw on all drawable objects.
  window_.display();
}
/* -------------------------------------------------------------------------- */