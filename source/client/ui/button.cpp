#include "client/ui/button.h"
#include "client/ui/widget.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
/* ------------------------------------------------------------------------------------------------------------------ */
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, Widget* parentWidget) : Widget(parentWidget) {
    set_click_disposition(Widget::ClickDisposition::Clickable);
    set_position(position);
    rectangleShape_.setPosition(position);
    set_size(size);
    rectangleShape_.setSize(size);
}
/* ------------------------------------------------------------------------------------------------------------------ */
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
void Button::handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& mouseClickEvent) {
    if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
        return;
    }

    if (mouseClickEvent.button == sf::Mouse::Left) {
        on_mouse_button_pressed(mouseClickEvent);
    }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::handle_mouse_button_released(const sf::Event::MouseButtonEvent& mouseClickEvent) {
    if (get_click_disposition() == Widget::ClickDisposition::Unclickable) {
        return;  // BUG what if the button becomes unclickable after it was clicked?
    }

    if (mouseClickEvent.button == sf::Mouse::Left) {
        on_mouse_button_released(mouseClickEvent);
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
void Button::update(float deltaTime) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rectangleShape_, states);

    Widget::draw(target, states);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_button_pressed(const sf::Event::MouseButtonEvent& mouseClickEvent) {
    if (enabled() && is_mouse_inside_boundaries({mouseClickEvent.x, mouseClickEvent.y})) {
        set_state(State::Clicked);
    }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_button_released(const sf::Event::MouseButtonEvent& mouseClickEvent) {
    const bool isMouseInside = is_mouse_inside_boundaries({mouseClickEvent.x, mouseClickEvent.y});
    if (isMouseInside) {
        if (enabled()) {
            set_state(State::Hovered);
            clicked_();
        } else {
            set_state(State::Disabled);
            clickedWhenDisabled_();
        }
    } else {
        set_state(State::Normal);
    }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_hover_start() {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Button::on_mouse_hover_end() {}
/* ------------------------------------------------------------------------------------------------------------------ */