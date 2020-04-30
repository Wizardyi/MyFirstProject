#pragma once
#include <stdint.h>

int DecodeEncode(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);
int DecodeEncode(uint32_t uSize, const unsigned char *pbySrcBuf, unsigned char *pbyDstBuf, unsigned *puKey);
int DecodeEncode_ASM(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);

int DecodeBuf(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);
int EncodeBuf(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);
int EncodeBuf(uint32_t uSize, const unsigned char *pbySrcBuf, unsigned char *pbyDstBuf, unsigned *puKey);

int DecodeBufSimple(uint32_t uSize, unsigned char *pbyBuf);
int EncodeBufSimple(uint32_t uSize, unsigned char *pbyBuf);

int DecodeDynamic(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);
int EncodeDynamic(uint32_t uSize, unsigned char *pbyBuf, unsigned *puKey);
