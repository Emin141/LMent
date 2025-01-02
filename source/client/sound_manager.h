/*
This class will be instanced inside the GameContext and used anywhere in the code base through that single instance.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include <SFML/Audio/Sound.hpp>
#include <queue>
/* ------------------------------------------------------------------------------------------------------------------ */
class SoundManager {
 public:
  class Passkey {
   private:
    Passkey() = default;
    friend class GameContext;
  };

  SoundManager(Passkey);

  void playSound(const sf::SoundBuffer* soundBuffer);

 private:
  std::queue<sf::Sound> soundsQueue_;
};
/* ------------------------------------------------------------------------------------------------------------------ */