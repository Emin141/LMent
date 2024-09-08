#include "server/game_server.h"
/* -------------------------------------------------------------------------- */
int main(int argc, char **argv) {
  GameServer gameServer;
  // TODO Make the init so that users can specify port and player count.
  gameServer.init();
  gameServer.run();
}
/* -------------------------------------------------------------------------- */