#pragma once
/* ------------------------------------------------------------------------------------------------------------------ */
// Define logging levels using spdlog enums
#ifdef DEBUG_BUILD
#define LOG_LEVEL spdlog::level::debug
#else
#define LOG_LEVEL spdlog::level::info
#endif
/* ------------------------------------------------------------------------------------------------------------------ */
#define MIN_NUMBER_OF_PLAYERS (2)
#define MAX_NUMBER_OF_PLAYERS (4)
#define INVALID_PLAYER_ID (-1)
#define MAX_BYTES_IN_MESSAGE (32)
#define DEFAULT_PORT (50000)
#define MAX_RECONNECT_ATTEMPTS (5)
/* ------------------------------------------------------------------------------------------------------------------ */