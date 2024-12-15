#include "client/game_client.h"
#include "client/ui/button.h"
#include "common/defines.h"
#include "spdlog/spdlog.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
/* ------------------------------------------------------------------------------------------------------------------ */
GameClient::GameClient() : Game::Game(), window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
    window_.setVisible(false);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::run() {
    spdlog::info("Running client.");

    // !TEST CODE BEGIN
    auto buttonPtr = std::make_unique<Button>(sf::Vector2f{20.0f, 20.f}, sf::Vector2f{160.0f, 90.f}, nullptr);
    auto& button = *buttonPtr;
    button.bind_clicked_callback([]() { spdlog::info("Clicked!"); });
    // Memory leak, idgaf it's test code
    sf::Texture* textureNormal = new sf::Texture();
    textureNormal->loadFromFile("assets/test/ButtonTest_Normal.png");
    sf::Texture* textureHovered = new sf::Texture();
    textureHovered->loadFromFile("assets/test/ButtonTest_Hovered.png");
    sf::Texture* textureClicked = new sf::Texture();
    textureClicked->loadFromFile("assets/test/ButtonTest_Clicked.png");
    button.set_style(Button::State::Normal, Button::Style{textureNormal, nullptr})
        .set_style(Button::State::Hovered, Button::Style{textureHovered, nullptr})
        .set_style(Button::State::Clicked, Button::Style{textureClicked, nullptr});
    button.set_state(Button::State::Normal);
    widgets_.emplace_back(std::move(buttonPtr));
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
    // TODO Update the current scene.
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
    // TODO Create event handling
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                isRunning_ = false;
                break;
            }
            case sf::Event::MouseButtonPressed: {
                // TODO Move this code somewhere else. Test code only.
                for (const auto& widget : widgets_) {
                    widget->handle_mouse_button_pressed(event.mouseButton,
                                                        sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                // TODO Move this code somewhere else. Test code only.
                for (const auto& widget : widgets_) {
                    widget->handle_mouse_button_released(event.mouseButton,
                                                         sf::Vector2i{event.mouseButton.x, event.mouseButton.y});
                }
                break;
            }
            default:
                break;
        }
    }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void GameClient::draw() {
    window_.clear();

    for (const std::unique_ptr<Widget>& widget : widgets_) {
        window_.draw(*widget);
    }

    window_.display();
}
/* ------------------------------------------------------------------------------------------------------------------ */