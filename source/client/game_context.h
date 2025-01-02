/*
Holds the singular reference of manager classes.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include "client/sound_manager.h"
/* ------------------------------------------------------------------------------------------------------------------ */
class GameContext {
 public:
  static GameContext& get();

  SoundManager& getSoundManager();

 private:
  GameContext();

  SoundManager soundManager_;
  // Asset and Network manager here as well?
};
/* ------------------------------------------------------------------------------------------------------------------ */