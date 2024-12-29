/*
This class represents an abstract UI element. A widget needs to be drawn, and
sometimes, a widget needs to be clicked. Therefore, I suppose that any widget
will need a position and size, and some will need some click, hover, and focus
functionality.
Regarding clickability of a widget, in order to avoid tracking two lists and
lifetimes of the widgets in both lists, every widget has click functionality.
The widget should also provide a way to add other widgets as childs into it, it
should hold a reference to the widget that contains *this* widget, and should
also provide an update method with delta time to animate if needed.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <memory>
#include <vector>
/* ------------------------------------------------------------------------------------------------------------------ */
class Widget;
/* ------------------------------------------------------------------------------------------------------------------ */
class Widget : public sf::Drawable {
 public:
  /* ---------------------------------------------------- Types --------------------------------------------------- */
  enum class ClickDisposition : uint8_t { Unclickable, ChildrenClickable, Clickable };

  enum class HorizontalAlignment : uint8_t { Free, Left, Right, Center, Stretch };

  enum class VerticalAlignment : uint8_t { Free, Top, Right, Center, Stretch };

  struct Padding {
    float top{0.0f};
    float left{0.0f};
    float bottom{0.0f};
    float right{0.0f};

    Padding& set_top(float value) {
      top = value;
      return *this;
    }
    Padding& set_left(float value) {
      left = value;
      return *this;
    }
    Padding& set_bottom(float value) {
      bottom = value;
      return *this;
    }
    Padding& set_right(float value) {
      right = value;
      return *this;
    }
  };

  /* -------------------------------------------------- Functions ------------------------------------------------- */
  Widget() = default;
  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;
  Widget(Widget&&) = delete;
  Widget& operator=(Widget&&) = delete;

  // Focus and ability
  virtual void enable();
  virtual void disable();
  bool enabled() const;
  bool disabled() const;
  void set_parent_widget(Widget* parentWidget);

  // TODO Do I even need these?
  virtual void set_position(const sf::Vector2f& value);
  virtual const sf::Vector2f& get_position() const;
  virtual void set_size(const sf::Vector2f& value);
  virtual const sf::Vector2f& get_size() const;

  void set_alignment(HorizontalAlignment value);
  void set_alignment(VerticalAlignment value);
  void set_alignment(HorizontalAlignment haValue, VerticalAlignment vaValue);
  std::pair<HorizontalAlignment, VerticalAlignment> get_alignment() const;

  void set_padding(Padding value);
  Padding get_padding() const;

  // Mouse interaction
  void set_click_disposition(ClickDisposition value);
  ClickDisposition get_click_disposition() const;
  virtual void handle_mouse_button_pressed(sf::Mouse::Button mouseButton);
  virtual void handle_mouse_button_released(sf::Mouse::Button mouseButton);
  virtual void handle_mouse_hover_start();
  virtual void handle_mouse_hover_end();
  virtual bool contains_point(const sf::Vector2i& mousePosition) const;

  // Children
  Widget* add_child_widget(std::unique_ptr<Widget> childWidget);
  const std::vector<std::unique_ptr<Widget>>& get_child_widgets() const;
  const Widget* get_widget_at_index(uint8_t index) const;
  Widget* get_widget_at_index(uint8_t index);
  void remove_widget(Widget* childWidget);
  void remove_widget_at(uint8_t index);

  // Update and draw
  virtual void update(float deltaTime);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 protected:
  /* -------------------------------------------------- Variables ------------------------------------------------- */
  Widget* parentWidget_{nullptr};

  bool enabled_{true};

  HorizontalAlignment horizontalAlignment_;
  VerticalAlignment verticalAlignment_;
  Padding padding_;

  ClickDisposition clickDisposition_{ClickDisposition::Unclickable};

  std::vector<std::unique_ptr<Widget>> childWidgets_;
};
/* ------------------------------------------------------------------------------------------------------------------ */