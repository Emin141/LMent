/*
Widget representing the main menu.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include <functional>

#include "client/ui/components/widget.h"
#include "sigslot/signal.hpp"
/* ------------------------------------------------------------------------------------------------------------------ */
class MainMenu : public Widget {
 public:
  MainMenu(const sf::Vector2u& windowSize);

  void bindJoinCallback(const std::function<void(void)>& callback);
  void bindHostCallback(const std::function<void(void)>& callback);
  void bindSettingsCallback(const std::function<void(void)>& callback);
  void bindExitCallback(const std::function<void(void)>& callback);

  void handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& event) override;
  void handle_mouse_button_released(const sf::Event::MouseButtonEvent& event) override;
  bool contains_point(const sf::Vector2i& mousePosition) const override;
  Widget* get_hovered_widget(const sf::Event::MouseMoveEvent& event) override;

 private:
  sigslot::signal<> joinCallback;
  sigslot::signal<> hostCallback;
  sigslot::signal<> settingsCallback;
  sigslot::signal<> exitCallback;
};
/* ------------------------------------------------------------------------------------------------------------------ */