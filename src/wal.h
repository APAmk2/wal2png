// wal.cpp : ID Software's WAL Reader Header
// 2024 APAMk2 (c)

#pragma once

#include <vector>
#include <string>
#include "ByteReader.hpp"

class wal_t
{
public:
	std::string name;
	uint32_t width, height;
	std::vector<uint32_t> offsets;		// four mip maps stored
	std::string animname;			// next frame in animation chain
	int32_t flags;
	int32_t contents;
	int32_t value;

	std::vector<uint8_t> pixels;

	wal_t(ByteReader* reader);
};