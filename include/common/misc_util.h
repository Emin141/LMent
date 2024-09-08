#pragma once
#include <ctime>
#include <string>
/* -------------------------------------------------------------------------- */
namespace util {
/* ---------------------------------------------------------------------- */
inline std::string current_datetime_as_string() {
  std::time_t time = std::time({});
  char logCreationTime[std::size("yyyy-mm-dd_hh:mm:ss")];
  std::strftime(std::data(logCreationTime), std::size(logCreationTime), "%F_%T",
                std::gmtime(&time));
  return logCreationTime;
}
/* -------------------------------------------------------------------------- */
// TODO I don't like this clamp honestly.
template <typename Type>
Type clamp(Type value, const Type &min, const Type &max) {
  value = value < min ? min : value;
  value = value > max ? max : value;
  return value;
}
/* -------------------------------------------------------------------------- */
template <class T> inline void hash_combine(std::size_t &s, const T &v) {
  std::hash<T> h;
  s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}
/* -------------------------------------------------------------------------- */
} // namespace util
/* -------------------------------------------------------------------------- */