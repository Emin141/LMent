#include "client/ui/widgets/main_menu.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <fstream>

#include "client/ui/components/button.h"
#include "client/ui/components/image_widget.h"
#include "client/ui/components/widget.h"
#include "json/json.hpp"
/* ------------------------------------------------------------------------------------------------------------------ */
using nlohmann::json;
/* ---------------------------------------------------------------------------------------------------------------- */
MainMenu::MainMenu(const sf::Vector2u& windowSize) {
  clickDisposition_ = Widget::ClickDisposition::ChildrenClickable;
  childWidgets_.reserve(5);

  using nlohmann::json;

  // TODO Asset manager will do this.
  std::ifstream inputFile{"assets/widgets/main_menu.json"};
  if (!inputFile.is_open()) {
    throw std::runtime_error("Failed to open main_menu.json file");
  }

  json widgetDesc = json::parse(inputFile);

  const auto& childrenDesc = widgetDesc["children"];

  sf::Texture* backgroundTexture = new sf::Texture();
  backgroundTexture->loadFromFile(childrenDesc[0]["resource"]);
  auto background = std::make_unique<ImageWidget>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(windowSize), backgroundTexture,
                                                  sf::IntRect(0, 0, windowSize.x, windowSize.y));
  childWidgets_.emplace_back(std::move(background));

  // TODO Temporary, will have a living reference in the asset manager
  const auto& button_style = widgetDesc["button_style"];
  const auto& button_style_states = button_style["states"];
  sf::Texture* gameTexture = new sf::Texture();
  gameTexture->loadFromFile(button_style["texture"]);
  sf::Font* decoratedFont = new sf::Font();
  decoratedFont->loadFromFile("assets/fonts/NewRocker.ttf");

  Button::Style normalStyle{sf::IntRect{button_style_states[0]["sprite_x"], button_style_states[0]["sprite_y"],
                                        button_style_states[0]["sprite_w"], button_style_states[0]["sprite_h"]},
                            nullptr};
  Button::Style hoveredStyle{sf::IntRect{button_style_states[1]["sprite_x"], button_style_states[1]["sprite_y"],
                                         button_style_states[1]["sprite_w"], button_style_states[1]["sprite_h"]},
                             nullptr};
  Button::Style clickedStyle{sf::IntRect{button_style_states[2]["sprite_x"], button_style_states[2]["sprite_y"],
                                         button_style_states[2]["sprite_w"], button_style_states[2]["sprite_h"]},
                             nullptr};

  sf::Vector2f buttonSize{button_style["size_x"], button_style["size_y"]};

  {
    const auto& buttonDesc = childrenDesc[1];
    auto joinButton = std::make_unique<Button>(sf::Vector2f{buttonDesc["position_x"], buttonDesc["position_y"]},
                                               buttonSize, gameTexture, buttonDesc["text"], decoratedFont);
    joinButton->bind_clicked_callback([this]() { joinCallback(); });
    joinButton->set_style(Button::State::Normal, normalStyle)
        .set_style(Button::State::Hovered, hoveredStyle)
        .set_style(Button::State::Clicked, clickedStyle);
    joinButton->set_state(Button::State::Normal);

    childWidgets_.emplace_back(std::move(joinButton));
  }
  {
    const auto& buttonDesc = childrenDesc[2];
    auto hostButton = std::make_unique<Button>(sf::Vector2f{buttonDesc["position_x"], buttonDesc["position_y"]},
                                               buttonSize, gameTexture, buttonDesc["text"], decoratedFont);
    hostButton->bind_clicked_callback([this]() { hostCallback(); });
    hostButton->set_style(Button::State::Normal, normalStyle)
        .set_style(Button::State::Hovered, hoveredStyle)
        .set_style(Button::State::Clicked, clickedStyle);
    hostButton->set_state(Button::State::Normal);

    childWidgets_.emplace_back(std::move(hostButton));
  }
  {
    const auto& buttonDesc = childrenDesc[3];
    auto settingsButton = std::make_unique<Button>(sf::Vector2f{buttonDesc["position_x"], buttonDesc["position_y"]},
                                                   buttonSize, gameTexture, buttonDesc["text"], decoratedFont);
    settingsButton->bind_clicked_callback([this]() { settingsCallback(); });
    settingsButton->set_style(Button::State::Normal, normalStyle)
        .set_style(Button::State::Hovered, hoveredStyle)
        .set_style(Button::State::Clicked, clickedStyle);
    settingsButton->set_state(Button::State::Normal);

    childWidgets_.emplace_back(std::move(settingsButton));
  }
  {
    const auto& buttonDesc = childrenDesc[4];
    auto exitButton = std::make_unique<Button>(sf::Vector2f{buttonDesc["position_x"], buttonDesc["position_y"]},
                                               buttonSize, gameTexture, buttonDesc["text"], decoratedFont);
    exitButton->bind_clicked_callback([this]() { exitCallback(); });
    exitButton->set_style(Button::State::Normal, normalStyle)
        .set_style(Button::State::Hovered, hoveredStyle)
        .set_style(Button::State::Clicked, clickedStyle);
    exitButton->set_state(Button::State::Normal);

    childWidgets_.emplace_back(std::move(exitButton));
  }
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void MainMenu::bindJoinCallback(const std::function<void(void)>& callback) {
  joinCallback.connect(callback);
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void MainMenu::bindHostCallback(const std::function<void(void)>& callback) {
  hostCallback.connect(callback);
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void MainMenu::bindSettingsCallback(const std::function<void(void)>& callback) {
  settingsCallback.connect(callback);
}
/* ------------------------------------------------------------------------------------------------------------------
 */
void MainMenu::bindExitCallback(const std::function<void(void)>& callback) {
  exitCallback.connect(callback);
}
/* ------------------------------------------------------------------------------------------------------------------
 */