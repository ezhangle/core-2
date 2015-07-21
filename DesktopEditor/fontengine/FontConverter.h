﻿#ifndef _BUILD_FONT_CONVERTER_H
#define _BUILD_FONT_CONVERTER_H

#include <string>

class CFontConverter
{
public:
    bool ToOTF(std::wstring sFontIn, std::wstring sFontOut, unsigned int* pSymbols, int nCount, std::wstring sName, long nFlag);
    bool ToOTF2(std::wstring sFontIn, unsigned int* pSymbols, int nCount, std::wstring sName, long nFlag, long lFaceIndex, unsigned char*& pDstData, int& nDstLen);
};

#endif /* _BUILD_FONT_CONVERTER_H */
