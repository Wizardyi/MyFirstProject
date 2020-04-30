#ifndef _ID_UTILITY_H_
#define _ID_UTILITY_H_
#include <stdio.h>
#include <stdint.h>
#include <google/protobuf/message.h>
#include <string>
#include <vector>
#include <cmath>


class CIDUtility
{
public:
	static uint64_t GetNewSerialID();

	static uint64_t MakeUINT64(uint32_t HiDWord, uint32_t LoDWord);

	static uint32_t GetHiDword(uint64_t qwVal);

	static uint32_t GetLoDword(uint64_t qwVal);

	static uint32_t MakeUINT32(uint16_t HiWord, uint16_t LoWord);

	static uint16_t GetHiWord(uint32_t dwVal);

	static uint16_t GetLoWord(uint32_t dwVal);

	static uint64_t GUIDCreate(uint32_t serverId);
private:
	static uint32_t m_dwIndex;
};

#endif
