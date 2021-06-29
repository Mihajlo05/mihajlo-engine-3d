#pragma once

class Color //taken from https://github.com/planetchili/hw3d/blob/T22-End/hw3d/Surface.h
{
public:
	unsigned int dword;
public:
	Color() : dword()
	{}
	Color(const Color& col)
		:
		dword(col.dword)
	{}
	Color(unsigned int dw)
		:
		dword(dw)
	{}
	Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b)
		:
		dword((x << 24u) | (r << 16u) | (g << 8u) | b)
	{}
	Color(unsigned char r, unsigned char g, unsigned char b)
		:
		dword((r << 16u) | (g << 8u) | b)
	{}
	Color(Color col, unsigned char x)
		:
		Color((x << 24u) | col.dword)
	{}
	Color& operator =(Color color)
	{
		dword = color.dword;
		return *this;
	}
	unsigned char GetX() const
	{
		return dword >> 24u;
	}
	unsigned char GetA() const
	{
		return GetX();
	}
	unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX(unsigned char x)
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA(unsigned char a)
	{
		SetX(a);
	}
	void SetR(unsigned char r)
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG(unsigned char g)
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB(unsigned char b)
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};