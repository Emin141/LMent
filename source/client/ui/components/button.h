/*
This class represents a basic button. Buttons are clickable by default and have
four states: Normal, Hovered, Clicked, and Disabled.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <unordered_map>

#include "client/ui/components/widget.h"
#include "sigslot/signal.hpp"
/* ------------------------------------------------------------------------------------------------------------------ */
class Button : public Widget {
 public:
  /* ---------------------------------------------------- Types --------------------------------------------------- */
  enum class State : uint8_t { Normal, Hovered, Clicked, Disabled };

  struct Style {
    sf::IntRect textureRect{};
    const sf::SoundBuffer* soundBuffer{nullptr};
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

  Button& set_style(State state, const Style& style);

  void set_position(const sf::Vector2f& value) override;
  const sf::Vector2f& get_position() const override;
  void set_size(const sf::Vector2f& value) override;
  const sf::Vector2f& get_size() const override;

  void bind_clicked_callback(const std::function<void(void)>& callback);
  void bind_clicked_when_disabled_callback(const std::function<void(void)>& callback);

  void handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& event) override;
  void handle_mouse_button_released(const sf::Event::MouseButtonEvent& event) override;
  void handle_hover_start() override;
  void handle_hover_end() override;
  bool contains_point(const sf::Vector2i& mousePosition) const override;
  Widget* get_hovered_widget(const sf::Event::MouseMoveEvent& event) override;
  void update(float deltaTime) override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  /* -------------------------------------------------- Functions ------------------------------------------------- */
  void on_lmb_pressed();
  void on_lmb_released();
  void on_hover_start();
  void on_hover_end();

  /* -------------------------------------------------- Variables ------------------------------------------------- */
  const sf::Texture* texture;
  sf::Text text_;
  std::unordered_map<State, Style> styles_{
      {State::Normal, Style{}}, {State::Hovered, Style{}}, {State::Clicked, Style{}}, {State::Disabled, Style{}}};
  sigslot::signal<> clicked_;
  sigslot::signal<> hovered_;
  sigslot::signal<> clickedWhenDisabled_;
  sf::RectangleShape rectangleShape_;
};
/* ------------------------------------------------------------------------------------------------------------------ */