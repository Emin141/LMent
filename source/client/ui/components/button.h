/*
This class represents a basic button. Buttons are clickable by default and have
four states: Normal, Hovered, Clicked, and Disabled.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#pragma once
#include "client/ui/components/widget.h"
#include "sigslot/signal.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <unordered_map>
/* ------------------------------------------------------------------------------------------------------------------ */
class Button : public Widget {
 public:
  /* ---------------------------------------------------- Types --------------------------------------------------- */
  enum class State : uint8_t { Normal, Hovered, Clicked, Disabled };

  struct Style {
    sf::IntRect textureRect{};
    sf::SoundBuffer* soundBuffer{nullptr};  // TODO Maybe not even here?
  };

  /* -------------------------------------------------- Functions ------------------------------------------------- */
  Button() = delete;
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;
  Button(Button&&) = delete;
  Button& operator=(Button&&) = delete;
  Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture* texture, const std::string& text,
         const sf::Font* font);

  void enable() override;
  void disable() override;

  void set_state(State value);
  State get_state() const;

  Button& set_style(State state, const Style& style);

  void set_position(const sf::Vector2f& value) override;
  const sf::Vector2f& get_position() const override;
  void set_size(const sf::Vector2f& value) override;
  const sf::Vector2f& get_size() const override;

  void bind_clicked_callback(const std::function<void(void)>& callback);
  void bind_clicked_when_disabled_callback(const std::function<void(void)>& callback);

  void handle_mouse_button_pressed(sf::Mouse::Button mouseButton) override;
  void handle_mouse_button_released(sf::Mouse::Button mouseButton) override;
  void handle_mouse_hover_start() override;
  void handle_mouse_hover_end() override;
  bool contains_point(const sf::Vector2i& mousePosition) const override;
  void update(float deltaTime) override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /* -------------------------------------------------- Functions ------------------------------------------------- */
  void on_mouse_button_pressed(sf::Mouse::Button mouseButton);
  void on_mouse_button_released(sf::Mouse::Button mouseButton);
  void on_mouse_hover_start();
  void on_mouse_hover_end();

  /* -------------------------------------------------- Variables ------------------------------------------------- */
  const sf::Texture* texture;
  sf::Text text_;
  State state_{State::Normal};
  std::unordered_map<State, Style> styles_{
      {State::Normal, Style{}}, {State::Hovered, Style{}}, {State::Clicked, Style{}}, {State::Disabled, Style{}}};
  sf::Sound stateChangeSound_;
  sigslot::signal<> clicked_;
  sigslot::signal<> hovered_;
  sigslot::signal<> clickedWhenDisabled_;
  sf::RectangleShape rectangleShape_;
};
/* ------------------------------------------------------------------------------------------------------------------ */