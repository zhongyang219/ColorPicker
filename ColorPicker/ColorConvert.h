#pragma once
class CColorConvert
{
public:
	CColorConvert();
	~CColorConvert();

	static unsigned int RGB2Hex(unsigned char R, unsigned char G, unsigned char B);	//RGB值转换成颜色十六进制值
	static unsigned char Hex2R(unsigned int hex);	//从颜色十六进制获取RGB中的红色值
	static unsigned char Hex2G(unsigned int hex);	//从颜色十六进制获取RGB中的绿色值
	static unsigned char Hex2B(unsigned int hex);	//从颜色十六进制获取RGB中的蓝色值

};

