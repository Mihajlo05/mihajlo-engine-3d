#pragma once

#include <exception>
#include <string>

class MihajloException : public std::exception
{
public:
	MihajloException(const std::string& file, int line) noexcept;
	virtual const char* what() const noexcept override;
	virtual std::string GetType() const noexcept;
	std::string GetLocation() const noexcept;
protected:
	mutable std::string whatBuffer;
private:
	std::string file;
	int line;
};