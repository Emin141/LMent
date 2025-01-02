#include "client/sound_manager.h"
/* ------------------------------------------------------------------------------------------------------------------ */
SoundManager::SoundManager(SoundManager::Passkey) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void SoundManager::playSound(const sf::SoundBuffer* soundBuffer) {
  if (soundBuffer == nullptr) {
    return;
  }

  soundsQueue_.emplace();
  soundsQueue_.back().setBuffer(*soundBuffer);
  soundsQueue_.back().play();

  while (!soundsQueue_.empty() && soundsQueue_.front().getStatus() == sf::Sound::Stopped) {
    soundsQueue_.pop();
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */