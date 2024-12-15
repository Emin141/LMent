#pragma once
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
/* ------------------------------------------------------------------------------------------------------------------ */
namespace util {
/* ------------------------------------------------------------------------------------------------------------------ */
inline std::string current_datetime_as_string() {
    std::time_t time = std::time({});
    char logCreationTime[std::size("yyyy-mm-dd_hh:mm:ss")];
    std::strftime(std::data(logCreationTime), std::size(logCreationTime), "%F_%T", std::gmtime(&time));
    return logCreationTime;
}
/* ------------------------------------------------------------------------------------------------------------------ */
// TODO I don't like this clamp honestly.
template <typename Type>
Type clamp(Type value, const Type& min, const Type& max) {
    value = value < min ? min : value;
    value = value > max ? max : value;
    return value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type>
inline void hash_combine(std::size_t& size, const Type& value) {
    std::hash<Type> hash;
    size ^= hash(value) + 0x9e3779b9 + (size << 6) + (size >> 2);
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type>
Type* find(std::vector<Type>& vec, const Type& elementToFind) {
    auto elementIterator = std::find_if(
        vec.begin(), vec.end(), [&](const Type& elementInContainer) { return elementInContainer == elementToFind; });

    return (elementIterator != vec.end()) ? &(*elementIterator) : nullptr;
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type>
const Type* find(const std::vector<Type>& vec, const Type& elementToFind) {
    auto elementIterator =
        std::find_if(vec.begin(), vec.end(), [&](const Type& elementInVec) { return elementInVec == elementToFind; });

    return (elementIterator != vec.end()) ? &(*elementIterator) : nullptr;
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type>
void erase(std::vector<Type>& vec, const Type& elementToErase) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [&](const Type& elementInVec) { return elementInVec == elementToErase; }),
              vec.end());
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type, typename Predicate>
void erase(std::vector<Type>& vec, Predicate predicate) {
    vec.erase(std::remove_if(vec.begin(), vec.end(), predicate), vec.end());
}
/* ------------------------------------------------------------------------------------------------------------------ */
template <typename Type>
void erase_at(std::vector<Type>& vec, size_t index) {
    if (index < vec.size()) {
        vec.erase(vec.begin() + index);
    }
}
/* ------------------------------------------------------------------------------------------------------------------ */
}  // namespace util
