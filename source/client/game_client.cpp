#include "client/game_client.h"
#include "client/ui/button.h"
#include "client/ui/user_interface.h"
#include "client/ui/image_widget.h"
#include "common/defines.h"
#include "spdlog/spdlog.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <memory>
/* ------------------------------------------------------------------------------------------------------------------ */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(sf::VideoMode::getFullscreenModes()[0]), "LMent", sf::Style::Fullscreen),
      userInterface_(window_.getSize()) {
  window_.setVisible(false);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::run() {
  spdlog::info("Running client.");

  // !TEST CODE BEGIN
  sf::Texture* backgroundTexture = new sf::Texture();
  backgroundTexture->loadFromFile("assets/background.png");
  auto backgroundPtr =
      std::make_unique<ImageWidget>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window_.getSize()), backgroundTexture,
                                    sf::IntRect(0, 0, window_.getSize().x, window_.getSize().y), nullptr);

  sf::Texture* gameTexture = new sf::Texture();
  gameTexture->loadFromFile("assets/game_texture.png");
  auto joinGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 450.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, nullptr);
  auto& joinGameButton = *joinGameButtonPtr;
  joinGameButton.bind_clicked_callback([]() { spdlog::info("Join game clicked!"); });
  joinGameButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  joinGameButton.set_state(Button::State::Normal);

  auto hostGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 600.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, nullptr);
  auto& hostGameButton = *hostGameButtonPtr;
  hostGameButton.bind_clicked_callback([]() { spdlog::info("Host game clicked!"); });
  hostGameButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  hostGameButton.set_state(Button::State::Normal);

  auto optionsButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 750.0f},
                                                   sf::Vector2f{320.0f, 100.f}, gameTexture, nullptr);
  auto& optionsButton = *optionsButtonPtr;
  optionsButton.bind_clicked_callback([]() { spdlog::info("Options clicked!"); });
  optionsButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  optionsButton.set_state(Button::State::Normal);

  auto exitGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 900.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, nullptr);
  auto& exitGameButton = *exitGameButtonPtr;
  exitGameButton.bind_clicked_callback([this]() { isRunning_ = false; });
  exitGameButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  exitGameButton.set_state(Button::State::Normal);

  userInterface_.add_child_widget(std::move(backgroundPtr));
  userInterface_.add_child_widget(std::move(joinGameButtonPtr));
  userInterface_.add_child_widget(std::move(hostGameButtonPtr));
  userInterface_.add_child_widget(std::move(optionsButtonPtr));
  userInterface_.add_child_widget(std::move(exitGameButtonPtr));
  // !TEST CODE END

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
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::update(float deltaTime) {
  if (isRunning_) {
    // TODO Update the current scene.
  } else {
    // TODO if isRunning is false, that means we have to save the game (if there is anything to save).
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::abort() {
  Game::abort();
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool GameClient::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");

  network_.set_ip_address("127.0.0.1");
  network_.set_port(DEFAULT_PORT);

  network_.connect();

  return true;
}
/* ------------------------------------------------------------------------------------------------------------------ */
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
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::draw() {
  window_.clear();
  window_.draw(userInterface_);
  // window.draw(gameObjects_); ...
  window_.display();
}
/* ------------------------------------------------------------------------------------------------------------------ */