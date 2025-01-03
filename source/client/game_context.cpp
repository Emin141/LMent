#include "client/game_context.h"
/* ------------------------------------------------------------------------------------------------------------------ */
GameContext::GameContext() : soundManager_(SoundManager::Passkey{}) {}
/* ------------------------------------------------------------------------------------------------------------------ */
GameContext& GameContext::get() {
  static GameContext INSTANCE;
  return INSTANCE;
}
/* ------------------------------------------------------------------------------------------------------------------ */
SoundManager& GameContext::getSoundManager() {
  return soundManager_;
}
/* ------------------------------------------------------------------------------------------------------------------ */