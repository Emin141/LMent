#include "client/game_client.h"
#include "common/game_started_message.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
  window_.setVisible(false);
  if (!initialize_network()) {
    abort();
  }

  window_.setVisible(true);
  window_.setFramerateLimit(60);
}
/* -------------------------------------------------------------------------- */
void GameClient::run() {
  spdlog::info("Running client.");

  float deltaTime{1.0f / 60};
  while (isRunning_) {
    sf::Clock dtClock;

    poll_events();
    update(deltaTime);
    draw();

    deltaTime = dtClock.restart().asSeconds();
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::update(float deltaTime) {
  // TODO add logic code.
}
/* -------------------------------------------------------------------------- */
void GameClient::abort() { Game::abort(); }
/* -------------------------------------------------------------------------- */
bool GameClient::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");

  if (socket_.connect(serverAddress_, serverPort_, sf::Time(sf::seconds(10))) !=
      sf::Socket::Done) {
    spdlog::error("Failed to connect to server at {}:{}.",
                  serverAddress_.toString(), serverPort_);
    return false;
  }

  spdlog::info("Client has connected to server at {}:{}.",
               serverAddress_.toString(), serverPort_);

  spdlog::info("Waiting for host to start the match.");
  sf::Packet receivedPacket{};
  if (socket_.receive(receivedPacket) != sf::Socket::Done) {
    spdlog::error("Failed to receive GameStarted message from server.");
    return false;
  }

  GameStartedMessage message;
  receivedPacket >> message;

  spdlog::info("Received GameStarted message as playerId:{}, playerCount:{}.",
               message.thisPlayerId, message.initialPlayerInfoList.size());

  for (const auto &playerInfo : message.initialPlayerInfoList) {
    spdlog::debug("Player {} is at {}.", playerInfo.id, playerInfo.position);
  }

  return true;
}
/* -------------------------------------------------------------------------- */
void GameClient::poll_events() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      // TODO Create event handling
      isRunning_ = false;
  }
}
/* -------------------------------------------------------------------------- */
void GameClient::draw() {
  window_.clear();
  // TODO Call draw on all drawable objects.
  window_.display();
}
/* -------------------------------------------------------------------------- */