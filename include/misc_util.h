#pragma once
#include <ctime>
#include <string>
/* -------------------------------------------------------------------------- */
namespace util {
/* ---------------------------------------------------------------------- */
std::string current_datetime_as_string() {
  std::time_t time = std::time({});
  char logCreationTime[std::size("yyyy-mm-dd_hh:mm:ss")];
  std::strftime(std::data(logCreationTime), std::size(logCreationTime), "%F_%T",
                std::gmtime(&time));
  return logCreationTime;
}
/* -------------------------------------------------------------------------- */
} // namespace util
/* -------------------------------------------------------------------------- */