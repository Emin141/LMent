#include "client/ui/button.h"
#include "client/ui/widget.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
/* ------------------------------------------------------------------------------------------------------------------ */
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture* texture, Widget* parentWidget)
    : Widget(parentWidget) {
  set_click_disposition(Widget::ClickDisposition::Clickable);
  set_position(position);
  set_size(size);
  rectangleShape_.setTexture(texture);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::enable() {
  Widget::enable();
  set_state(State::Normal);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::disable() {
  Widget::disable();
  set_state(State::Disabled);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::set_state(State value) {
  state_ = value;

  if (state_ == State::Disabled) {
    set_click_disposition(Widget::ClickDisposition::Unclickable);
  } else {
    set_click_disposition(Widget::ClickDisposition::Clickable);
  }

  rectangleShape_.setTextureRect(styles_[state_].textureRect);

  if (sf::SoundBuffer* soundBuffer = styles_[state_].soundBuffer) {
    stateChangeSound_.setBuffer(*soundBuffer);
    stateChangeSound_.play();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
Button::State Button::get_state() const {
  return state_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
Button& Button::set_style(State state, const Style& style) {
  styles_[state] = style;
  return *this;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::set_position(const sf::Vector2f& value) {
  rectangleShape_.setPosition(value);
}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& Button::get_position() const {
  return rectangleShape_.getPosition();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::set_size(const sf::Vector2f& value) {
  rectangleShape_.setSize(value);
}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& Button::get_size() const {
  return rectangleShape_.getSize();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::bind_clicked_callback(const std::function<void(void)>& callback) {
  if (clicked_.slot_count() == 0) {
    clicked_.connect(callback);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::bind_clicked_when_disabled_callback(const std::function<void(void)>& callback) {
  if (clickedWhenDisabled_.slot_count() == 0) {
    clickedWhenDisabled_.connect(callback);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_button_pressed(sf::Mouse::Button mouseButton) {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  if (mouseButton == sf::Mouse::Left) {
    on_mouse_button_pressed(mouseButton);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_button_released(sf::Mouse::Button mouseButton) {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;  // ! BUG what if the button becomes unclickable after it was clicked?
  }

  if (mouseButton == sf::Mouse::Left) {
    on_mouse_button_released(mouseButton);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_hover_start() {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  on_mouse_hover_start();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_hover_end() {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  on_mouse_hover_end();
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Button::contains_point(const sf::Vector2i& mousePosition) const {
  const auto& [anchorX, anchorY] = get_position();
  const auto& [sizeX, sizeY] = get_size();

  return (mousePosition.x > anchorX && mousePosition.x < (anchorX + sizeX)) &&
         (mousePosition.y > anchorY && mousePosition.y < (anchorY + sizeY));
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::update(float deltaTime) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Widget::draw(target, states);

  target.draw(rectangleShape_, states);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_button_pressed(sf::Mouse::Button mouseButton) {
  if (enabled()) {
    set_state(State::Clicked);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_button_released(sf::Mouse::Button mouseButton) {
  if (enabled()) {
    set_state(State::Hovered);
    clicked_();
  } else {
    clickedWhenDisabled_();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_hover_start() {
  if (enabled()) {
    set_state(State::Hovered);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_hover_end() {
  if (enabled()) {
    set_state(State::Normal);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */