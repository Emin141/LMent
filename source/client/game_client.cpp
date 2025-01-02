#include "client/game_client.h"

#include <lz4.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <fstream>
#include <sstream>

#include "client/ui/widgets/user_interface.h"
#include "common/defines.h"
#include "spdlog/spdlog.h"
/* ------------------------------------------------------------------------------------------------------------------ */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]), "ELEMENT", sf::Style::Fullscreen),
      userInterface_(window_.getSize()) {
  window_.setVisible(false);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::run() {
  spdlog::info("Running client.");

  window_.setVisible(true);

  float deltaTime{1.0f / 60};
  while (isRunning_) {
    sf::Clock dtClock;

    poll_events();
    update(deltaTime);  // TODO I will need dt for animations probably?
    draw();

    deltaTime = dtClock.restart().asSeconds();
  }
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void GameClient::update(float deltaTime) {
  if (isRunning_) {
    // TODO Update the current scene.
  } else {
    // TODO if isRunning is false, that means we have to save the game (if there is anything to save).
  }
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void GameClient::abort() {
  Game::abort();
}
/* ------------------------------------------------------------------------------------------------------------------
 */
bool GameClient::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");

  network_.set_ip_address("127.0.0.1");
  network_.set_port(DEFAULT_PORT);

  network_.connect();

  return true;
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void GameClient::poll_events() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed: {
        isRunning_ = false;
        break;
      }
      case sf::Event::KeyReleased: {
        if (event.key.code == sf::Keyboard::Escape) {
          isRunning_ = false;
        }
        break;
      }
      default: {
        userInterface_.handle_input(event);
        break;
      }
    }
  }
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void GameClient::draw() {
  window_.clear();
  window_.draw(userInterface_);
  // window.draw(gameObjects_); ...
  window_.display();
}
/* ------------------------------------------------------------------------------------------------------------------
 */