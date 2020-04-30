#include <string.h>
#include "id_utility.h"
#include <sstream>  
#include <iostream> 
#include <random>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <time.h>

/*
* | Timestamp | Seq ID | onlne ID	|
*| 32bit	  | 16bit  | 16 bit		|
*| ----------------------64bit------|
*/

static const uint32_t TIMESTAMP_BITS_MULTI = 32;				///< 时间戳占位数, MULTI方式
static const uint32_t SEQUENCE_MASK_MULTI = 0xFFFF;				///< 序列号16位掩码, MULTI方式
static const uint32_t SEQUENCE_BITS_MULTI = 16;                 ///< 序列号位数, MULTI方式
static const uint32_t SERVER_MASK = 0xFFFF;               		///< server 16位掩码

uint32_t CIDUtility::m_dwIndex = 0;

uint64_t CIDUtility::GetNewSerialID()
{
	if (m_dwIndex == 0)
	{
		m_dwIndex = 1;
	}

	return MakeUINT64((uint32_t)time(0), m_dwIndex++);
}

uint64_t CIDUtility::MakeUINT64(uint32_t HiDWord, uint32_t LoDWord)
{
	return ((uint64_t)HiDWord << 32 | LoDWord);
}

uint32_t CIDUtility::GetHiDword(uint64_t qwVal)
{
	return (uint32_t)(qwVal >> 32 & 0xFFFFFFFF);
}

uint32_t CIDUtility::GetLoDword(uint64_t qwVal)
{
	return (uint32_t)(qwVal & 0xFFFFFFFF);
}

uint32_t CIDUtility::MakeUINT32(uint16_t HiWord, uint16_t LoWord)
{
	return ((uint32_t)HiWord << 16 | LoWord);
}

uint16_t CIDUtility::GetHiWord(uint32_t dwVal)
{
	return (uint16_t)(dwVal >> 16 & 0xFFFF);
}

uint16_t CIDUtility::GetLoWord(uint32_t dwVal)
{
	return (uint16_t)(dwVal & 0xFFFF);
}

uint64_t CIDUtility::GUIDCreate(uint32_t serverId)
{
	static uint32_t sequence = 0;
	static uint64_t lastTimestamp = time(nullptr);
	uint64_t        guid = 0;
	uint64_t        currentTimestamp = time(nullptr);

	if (currentTimestamp == lastTimestamp) {
		sequence += 1;
		if (sequence > SEQUENCE_MASK_MULTI) {
			return 0; 
		}
	}
	else {
		lastTimestamp = currentTimestamp;
		sequence = 1;
	}
	
	guid |= (lastTimestamp << TIMESTAMP_BITS_MULTI);
	guid |= ((sequence & SEQUENCE_MASK_MULTI) << SEQUENCE_BITS_MULTI);
	guid |= serverId & SERVER_MASK;
	return guid;
}
