#define NO_SWITCHES

#include "Windows/MihajloWin.h"
#include "Surface.h"
#include <sstream>

#define SURFACE_EXCEPTION(msg) Surface::Exception(__FILE__, __LINE__, msg)

namespace Gdiplus
{
	using std::max;
	using std::min;
}

#include <gdiplus.h>

namespace gp = Gdiplus;

std::string Surface::Exception::GetType() const noexcept
{
	return "Surface Exception";
}

Surface::Surface(uint64_t width, uint64_t height, Color fillColor)
	:
	width(width),
	height(height),
	pBuffer(std::make_unique<Color[]>(size_t(width * height)))
{
	for (int i = 0; i < width * height; i++)
	{
		pBuffer[i] = fillColor;
	}
}

Surface::Surface(uint64_t width, uint64_t height)
	:
	Surface(width, height, {255, 255, 255})
{ }

Surface::Surface(const std::string& filename)
{
	wchar_t wideName[512];
	mbstowcs_s(nullptr, wideName, filename.c_str(), _TRUNCATE);

	gp::Bitmap bitmap(wideName);
	if (bitmap.GetLastStatus() != Gdiplus::Status::Ok)
	{
		std::stringstream ss;
		ss << "Loading image [" << filename << "]: failed to load.";
		throw SURFACE_EXCEPTION(ss.str());
	}

	width = bitmap.GetWidth();
	height = bitmap.GetHeight();

	pBuffer = std::make_unique<Color[]>(size_t(width * height));
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gp::Color c;
			bitmap.GetPixel(x, y, &c);
			At(x, y) = c.GetValue();
		}
	}
}

Surface::Surface(const Surface& other)
{
	*this = other;
}

Surface& Surface::operator=(const Surface& other)
{
	width = other.width;
	height = other.height;
	
	pBuffer = std::make_unique<Color[]>(size_t(width * height));

	for (int i = 0; i < width * height; i++)
	{
		pBuffer[i] = other.pBuffer[i];
	}

	return *this;
}

Color Surface::GetPixel(int x, int y) const
{
	return At(x, y);
}

void Surface::SetPixel(int x, int y, Color c)
{
	At(x, y) = c;
}

uint64_t Surface::GetWidth() const
{
	return width;
}

uint64_t Surface::GetHeight() const
{
	return height;
}

Color* Surface::GetBufferPointer()
{
	return pBuffer.get();
}

const Color* Surface::GetBufferPointer() const
{
	return pBuffer.get();
}

Color& Surface::At(int x, int y)
{
	return pBuffer[size_t(y * width + x)];
}

const Color& Surface::At(int x, int y) const
{
	return const_cast<Surface&>(*this).At(x, y);
}
