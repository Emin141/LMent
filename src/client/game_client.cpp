#include "client/game_client.h"
#include "common/misc_util.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */
GameClient::GameClient()
    : Game::Game(),
      window_(sf::VideoMode(800, 600), "LMent", sf::Style::Default) {
  window_.setVisible(false);
  if (!initialize_network()) {
    exit();
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

  exit();
}
/* -------------------------------------------------------------------------- */
void GameClient::update(float deltaTime) {
  // TODO add logic code.
}
/* -------------------------------------------------------------------------- */
void GameClient::exit() { Game::exit(); }
/* -------------------------------------------------------------------------- */
bool GameClient::initialize_network() {
  // TODO temporary, the port and player number should be specified in the GUI
  spdlog::info("Initializing network.");

  /* std::string inputLine;
  std::printf("Server IP address: ");
  if (std::getline(std::cin, inputLine)) {
    std::stringstream lineStream{inputLine};
    lineStream >> serverAddress_;
  } else {
    spdlog::error("Failed to read IP address.");
    return false;
  }

  std::printf("Server port (40000 - 60000): ");
  if (std::getline(std::cin, inputLine)) {
    std::stringstream lineStream{inputLine};
    lineStream >> serverPort_;
    util::clamp<int>(serverPort_, 40000, 60000);
  } else {
    spdlog::error("Failed to read port number.");
    return false;
  } */

  if (socket_.connect(serverAddress_, serverPort_, sf::Time(sf::seconds(10))) !=
      sf::Socket::Done) {
    spdlog::error("Failed to connect to server at {}:{}.",
                  serverAddress_.toString(), serverPort_);
    return false;
  }

  spdlog::info("Client has connected to server at {}:{}.",
               serverAddress_.toString(), serverPort_);
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