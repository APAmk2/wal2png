// wal.cpp : ID Software's WAL Reader Logic
// 2024 APAMk2 (c)

#include "wal.h"

#define MIPLEVELS 4

wal_t::wal_t(ByteReader* reader)
{
	name = reader->string(32);
	width = reader->u32();
	height = reader->u32();
	for (size_t i = 0; i < MIPLEVELS; i++)
	{
		offsets.push_back(reader->u32());
	}
	animname = reader->string(32);
	flags = reader->i32();
	contents = reader->i32();
	value = reader->i32();

	reader->Pos(offsets[0]);

	for (size_t i = 0, len = width * height; i < len; i++)
	{
		pixels.push_back(reader->u8());
	}
}