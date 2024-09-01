#pragma once
#include <cstdint>
/* -------------------------------------------------------------------------- */
struct Message {
  enum class Type : uint8_t { GameStarted };

  Type type_;
};
/* -------------------------------------------------------------------------- */