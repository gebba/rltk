#pragma once

#include <fstream>
#include <string>
#include "color_t.hpp"

namespace rltk {

template<class T>
inline void serialize(std::ostream &lbfile, const T &target) {
	lbfile.write(reinterpret_cast<const char *>(&target), sizeof(target));
}
template<>
inline void serialize(std::ostream &lbfile, const std::string &target) {
	std::size_t size = target.size();
	serialize<std::size_t>(lbfile, size);
	for (std::size_t i = 0; i < size; ++i)
	{
		serialize<char>(lbfile, target[i]);
	}
}
template<>
inline void serialize(std::ostream &lbfile, const rltk::color_t &col) {
	serialize<uint8_t>(lbfile, col.r);
	serialize<uint8_t>(lbfile, col.g);
	serialize<uint8_t>(lbfile, col.b);
}

template<typename T>
inline void deserialize(std::istream &lbfile, T &target)
{
	lbfile.read(reinterpret_cast<char *>(&target), sizeof(target));
}
template<>
inline void deserialize(std::istream &lbfile, std::string &target)
{
	std::string result;
	std::size_t size = 0;
	deserialize<std::size_t>(lbfile, size);
	for (std::size_t i = 0; i < size; ++i)
	{
		char c;
		deserialize<char>(lbfile, c);
		result += c;
	}
	target = result;
}
template<>
inline void deserialize(std::istream &lbfile, rltk::color_t &target) {
	deserialize(lbfile, target.r);
	deserialize(lbfile, target.g);
	deserialize(lbfile, target.b);
}

}