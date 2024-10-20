/*
This class represents an abstract UI element. A widget needs to be drawn, and
sometimes, a widget needs to be clicked. Therefore, I suppose that any widget
will need a position and size, and some will need some click, hover, and focus
functionality.
That being said, size may not be the same for text and rectangular widgets,
and position is stored in sf::Transformable, which are both sf::Text and
sf::RectangleShape and it seems wasteful to hold another copy of the variable
when they can contain it. It may have some more boilerplate, but it is better to
define set/get functions for size and position in the child widgets only.
Regarding clickability of a widget, in order to avoid tracking two lists and
lifetimes of the widgets in both lists, every widget has click functionality.
The widget should also provide a way to add other widgets as childs into it, it
should hold a reference to the widget that contains *this* widget, and should
also provide an update method with delta time to animate if needed.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <memory>
#include <vector>
/* -------------------------------------------------------------------------- */
class Widget;
/* -------------------------------------------------------------------------- */
class Widget : public sf::Drawable {
public:
  /* --------------------------------- Types -------------------------------- */
  enum class ClickDisposition : uint8_t {
    Unclickable,
    ChildrenClickable,
    Clickable
  };

  /* ------------------------------- Functions ------------------------------ */
  Widget() = delete;
  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;
  Widget(Widget&&) = delete;
  Widget& operator=(Widget&&) = delete;
  Widget(Widget* parentWidget);

  void set_focused(bool value);
  bool is_focused() const;

  void set_click_disposition(ClickDisposition value);
  ClickDisposition get_click_disposition() const;
  virtual void handle_mouse_button_pressed(const sf::Event& mouseClickEvent,
                                           const sf::Vector2i& mousePosition);
  virtual void handle_mouse_button_released(const sf::Event& mouseClickEvent,
                                            const sf::Vector2i& mousePosition);

  Widget* add_child_widget(std::unique_ptr<Widget> childWidget);
  const std::vector<std::unique_ptr<Widget>>& get_child_widgets() const;
  const Widget* get_widget_at_index(uint8_t index) const;
  Widget* get_widget_at_index(uint8_t index);
  void remove_widget(Widget* childWidget);
  void remove_widget_at(uint8_t index);

  virtual void update(float deltaTime);
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

protected:
  /* ------------------------------- Functions ------------------------------ */
  virtual void on_mouse_button_pressed();
  virtual void on_mouse_button_released();

private:
  /* ------------------------------- Variables ------------------------------ */
  Widget* parentWidget_{nullptr};
  ClickDisposition clickDisposition_{ClickDisposition::Unclickable};
  bool focused_{false};

  std::vector<std::unique_ptr<Widget>> childWidgets_;
};
/* -------------------------------------------------------------------------- */