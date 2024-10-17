#include "client/ui/button.h"
#include "client/ui/widget.h"
#include "spdlog/spdlog.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
/* -------------------------------------------------------------------------- */
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
               Widget* parentWidget)
    : Widget(parentWidget) {
  set_click_disposition(Widget::ClickDisposition::Clickable);
  rectangleShape_.setPosition(position);
  rectangleShape_.setSize(size);
}
/* -------------------------------------------------------------------------- */
void Button::set_state(State value) {
  state_ = value;

  if (state_ == State::Disabled) {
    set_click_disposition(Widget::ClickDisposition::Unclickable);
  } else {
    set_click_disposition(Widget::ClickDisposition::Clickable);
  }

  if (sf::Texture* texture = styles_[state_].texture) {
    rectangleShape_.setTexture(texture);
  }

  if (sf::SoundBuffer* soundBuffer = styles_[state_].soundBuffer) {
    stateChangeSound_.setBuffer(*soundBuffer);
    stateChangeSound_.play();
  }
}
/* -------------------------------------------------------------------------- */
Button::State Button::get_state() const { return state_; }
/* -------------------------------------------------------------------------- */
Button& Button::set_style(State state, const Style& style) {
  styles_[state] = style;
  return *this;
}
/* -------------------------------------------------------------------------- */
void Button::bind_callback(const std::function<void(void)>& callback) {
  if (clicked_.slot_count() == 0) {
    clicked_.connect(callback);
  }
}
/* -------------------------------------------------------------------------- */
void Button::handle_hover() {
  spdlog::info("Hovering logic not implemented for buttons.");
}
/* -------------------------------------------------------------------------- */
void Button::handle_mouse_button_pressed(const sf::Event& mouseClickEvent,
                                         const sf::Vector2i& mousePosition) {
  if (is_mouse_inside_boundaries(mousePosition) == false ||
      get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  if (mouseClickEvent.mouseButton.button == sf::Mouse::Left) {
    on_mouse_button_pressed();
  }
}
/* -------------------------------------------------------------------------- */
void Button::handle_mouse_button_released(const sf::Event& mouseClickEvent,
                                          const sf::Vector2i& mousePosition) {
  if (is_mouse_inside_boundaries(mousePosition) == false ||
      get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  if (mouseClickEvent.mouseButton.button == sf::Mouse::Left) {
    on_mouse_button_released();
  }
}
/* -------------------------------------------------------------------------- */
void Button::update(float deltaTime) {}
/* -------------------------------------------------------------------------- */
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(rectangleShape_, states);

  Widget::draw(target, states);
}
/* -------------------------------------------------------------------------- */
bool Button::is_mouse_inside_boundaries(
    const sf::Vector2i& mousePosition) const {
  const auto& [rectX, rectY] = rectangleShape_.getPosition();
  const auto& [rectSizeX, rectSizeY] = rectangleShape_.getSize();

  return (mousePosition.x > rectX && mousePosition.x < (rectX + rectSizeX)) &&
         (mousePosition.y > rectY && mousePosition.y < (rectY + rectSizeY));
}
/* -------------------------------------------------------------------------- */
void Button::on_mouse_button_pressed() { set_state(State::Clicked); }
/* -------------------------------------------------------------------------- */
void Button::on_mouse_button_released() {
  set_state(State::Normal); // TODO Should be hovered

  clicked_();
}
/* -------------------------------------------------------------------------- */