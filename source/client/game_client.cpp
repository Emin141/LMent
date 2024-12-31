#include "client/game_client.h"
#include "client/ui/components/button.h"
#include "client/ui/widgets/user_interface.h"
#include "client/ui/components/image_widget.h"
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
#include <lz4.h>
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
                                    sf::IntRect(0, 0, window_.getSize().x, window_.getSize().y));

  sf::Texture* gameTexture = new sf::Texture();
  gameTexture->loadFromFile("assets/game_texture.png");

  {
    const char* src =
        "Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of "
        "classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a "
        "Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin "
        "words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in "
        "classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections "
        "1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by "
        "Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during "
        "the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a "
        "line in section 1.10.32. The standard chunk of Lorem Ipsum used since the 1500s is reproduced "
        "below for those interested. Sections 1.10.32 and 1.10.33 from \"de Finibus Bonorum et Malorum\" "
        "by Cicero are also reproduced in their exact original form, accompanied by English versions "
        "from the 1914 translation by H. Rackham.";

    const int srcSize = strlen(src);

    // Dynamically allocate buffers to handle large data
    std::vector<char> compressed;
    compressed.reserve(LZ4_compressBound(srcSize));

    std::vector<char> decompressed;
    decompressed.reserve(srcSize);

    // Compress
    int compressedSize = LZ4_compress_fast(src, compressed.data(), srcSize, LZ4_compressBound(srcSize), 1);
    if (compressedSize <= 0) {
      spdlog::error("Compression failed!");
    }
    spdlog::info("Compression successful, decompressed size: {}, compressed size: {}", srcSize, compressedSize);

    // Decompress
    int decompressedSize = LZ4_decompress_safe(compressed.data(), decompressed.data(), compressedSize, srcSize);
    if (decompressedSize < 0) {
      spdlog::error("Decompression failed!");
    }
    spdlog::info("Decompression successful: {}", decompressed.data());
  }

  sf::Font* titleFont = new sf::Font();
  titleFont->loadFromFile("assets/fonts/NewRocker.ttf");

  auto joinGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 450.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, "JOIN GAME", titleFont);
  auto& joinGameButton = *joinGameButtonPtr;
  joinGameButton.bind_clicked_callback([]() { spdlog::info("Join game clicked!"); });
  joinGameButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  joinGameButton.set_state(Button::State::Normal);

  auto hostGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 600.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, "HOST GAME", titleFont);
  auto& hostGameButton = *hostGameButtonPtr;
  hostGameButton.bind_clicked_callback([]() { spdlog::info("Host game clicked!"); });
  hostGameButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  hostGameButton.set_state(Button::State::Normal);

  auto optionsButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 750.0f},
                                                   sf::Vector2f{320.0f, 100.f}, gameTexture, "OPTIONS", titleFont);
  auto& optionsButton = *optionsButtonPtr;
  optionsButton.bind_clicked_callback([]() { spdlog::info("Options clicked!"); });
  optionsButton.set_style(Button::State::Normal, Button::Style{sf::IntRect{0, 0, 320, 100}, nullptr})
      .set_style(Button::State::Hovered, Button::Style{sf::IntRect{0, 100, 320, 100}, nullptr})
      .set_style(Button::State::Clicked, Button::Style{sf::IntRect{0, 200, 320, 100}, nullptr});
  optionsButton.set_state(Button::State::Normal);

  auto exitGameButtonPtr = std::make_unique<Button>(sf::Vector2f{window_.getSize().x / 2.0f - 160.0f, 900.0f},
                                                    sf::Vector2f{320.0f, 100.f}, gameTexture, "EXIT GAME", titleFont);
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