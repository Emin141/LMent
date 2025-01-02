#include "client/ui/components/button.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "client/game_context.h"
#include "client/ui/components/widget.h"
/* ------------------------------------------------------------------------------------------------------------------ */
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture* texture,
               const std::string& text, const sf::Font* font) {
  const unsigned int fontSize{48};

  // General
  set_click_disposition(Widget::ClickDisposition::Clickable);
  set_position(position);
  set_size(size);

  // Background sprite
  rectangleShape_.setTexture(texture);

  // Text
  text_.setString(text);
  text_.setFont(*font);
  text_.setFillColor(sf::Color(0xFFAA00FF));
  text_.setCharacterSize(fontSize);

  sf::Vector2f textOrigin;
  {
    textOrigin.x = text_.getGlobalBounds().width / 2.0f + text_.getLocalBounds().left;
    sf::Text hackText("I", *font, fontSize);  // HACK This will force vertical center. I'm not fixing this.
    textOrigin.y = hackText.getGlobalBounds().height / 2.0f + text_.getLocalBounds().top;
  }
  text_.setOrigin(textOrigin);
  text_.setPosition(rectangleShape_.getPosition() + (rectangleShape_.getSize() / 2.f));
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::enable() {
  Widget::enable();

  rectangleShape_.setTextureRect(styles_[State::Normal].textureRect);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::disable() {
  Widget::disable();

  rectangleShape_.setTextureRect(styles_[State::Disabled].textureRect);
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
void Button::handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& event) {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  if (event.button == sf::Mouse::Left) {
    on_lmb_pressed();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_button_released(const sf::Event::MouseButtonEvent& event) {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;  // ! BUG what if the button becomes unclickable after it was clicked?
  }

  if (event.button == sf::Mouse::Left) {
    on_lmb_released();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_hover_start() {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  on_hover_start();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_hover_end() {
  if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
    return;
  }

  on_hover_end();
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Button::contains_point(const sf::Vector2i& mousePosition) const {
  const auto& [anchorX, anchorY] = get_position();
  const auto& [sizeX, sizeY] = get_size();

  return (mousePosition.x > anchorX && mousePosition.x < (anchorX + sizeX)) &&
         (mousePosition.y > anchorY && mousePosition.y < (anchorY + sizeY));
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget* Button::get_hovered_widget(const sf::Event::MouseMoveEvent&) {
  return this;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::update(float deltaTime) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Widget::draw(target, states);

  target.draw(rectangleShape_, states);
  target.draw(text_, states);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_lmb_pressed() {
  if (enabled()) {
    rectangleShape_.setTextureRect(styles_[State::Clicked].textureRect);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_lmb_released() {
  if (enabled()) {
    rectangleShape_.setTextureRect(styles_[State::Hovered].textureRect);
    GameContext::get().getSoundManager().playSound(styles_[State::Clicked].soundBuffer);
    clicked_();
  } else {
    clickedWhenDisabled_();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_hover_start() {
  if (enabled()) {
    rectangleShape_.setTextureRect(styles_[State::Hovered].textureRect);
    GameContext::get().getSoundManager().playSound(styles_[State::Hovered].soundBuffer);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_hover_end() {
  if (enabled()) {
    rectangleShape_.setTextureRect(styles_[State::Normal].textureRect);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */