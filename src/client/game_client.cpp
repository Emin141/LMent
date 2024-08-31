#include "client/game_client.h"
#include "spdlog/spdlog.h"
/* -------------------------------------------------------------------------- */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
  window_.setFramerateLimit(60);
}
/* -------------------------------------------------------------------------- */
void GameClient::run() {
  spdlog::info("Running client.");

  while (isRunning_) {
    sf::Clock dtClock;

    poll_events();
    update();
    draw();

    spdlog::info("Frame time: {}ms", dtClock.restart().asMilliseconds());
  }

  exit();
}
/* -------------------------------------------------------------------------- */
void GameClient::update() {
  // TODO add logic code.
}
/* -------------------------------------------------------------------------- */
void GameClient::exit() { Game::exit(); }
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