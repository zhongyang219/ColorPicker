#include "stdafx.h"
#include "ColorConvert.h"


CColorConvert::CColorConvert()
{
}


CColorConvert::~CColorConvert()
{
}

unsigned int CColorConvert::RGB2Hex(unsigned char R, unsigned char G, unsigned char B)
{
	return static_cast<unsigned int>(R) << 16 | static_cast<unsigned short>(G) << 8 | B;
}

unsigned char CColorConvert::Hex2R(unsigned int hex)
{
	return hex / 256 / 256;
}

unsigned char CColorConvert::Hex2G(unsigned int hex)
{
	return hex / 256 % 256;
}

unsigned char CColorConvert::Hex2B(unsigned int hex)
{
	return hex % 256;
}
