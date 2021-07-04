#pragma once

#include "ErrorHandling/DefaultMihException.h"
#include "Color.h"
#include <string>
#include <memory>

class Surface
{
private:
	class Exception : public DefaultMihException
	{
	public:
		using DefaultMihException::DefaultMihException;
		std::string GetType() const noexcept override;
	};
public:
	Surface(uint64_t width, uint64_t height, Color fillColor);
	Surface(uint64_t width, uint64_t height);
	Surface(const std::string& filename);
	Surface(const Surface& other);
	Surface& operator=(const Surface& other);
	Surface(Surface&&) = default;
	Surface& operator=(Surface&&) = default;
	~Surface() = default;
	Color GetPixel(int x, int y) const;
	void SetPixel(int x, int y, Color c);
	uint64_t GetWidth() const;
	uint64_t GetHeight() const;
	Color* GetBufferPointer();
	const Color* GetBufferPointer() const;
private:
	Color& At(int x, int y);
	const Color& At(int x, int y) const;
private:
	std::unique_ptr<Color[]> pBuffer;
	uint64_t width;
	uint64_t height;
};