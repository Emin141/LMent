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

 private:
  sigslot::signal<> joinCallback;
  sigslot::signal<> hostCallback;
  sigslot::signal<> settingsCallback;
  sigslot::signal<> exitCallback;
};
/* ------------------------------------------------------------------------------------------------------------------ */