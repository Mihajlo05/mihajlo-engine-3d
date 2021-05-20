#include "MihajloException.h"
#include <sstream>

MihajloException::MihajloException(const std::string& file, int line) noexcept
	:
	file(file),
	line(line)
{ }

const char* MihajloException::what() const noexcept
{
	std::ostringstream msg;
	msg << "[Type] " << GetType() << std::endl;
	msg << GetLocation();

	whatBuffer = msg.str();
	return whatBuffer.c_str();
}

std::string MihajloException::GetType() const noexcept
{
	return "Type unidentified";
}

std::string MihajloException::GetLocation() const noexcept
{
	std::ostringstream msg;

	msg << "[File] " << file << std::endl;
	msg << "[Line] " << line << std::endl;

	return msg.str();
}
