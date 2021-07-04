#include "DefaultMihException.h"
#include <sstream>

DefaultMihException::DefaultMihException(const std::string& file, int line, const std::string& msg)
	:
	MihajloException(file, line),
	msg(msg)
{ }

const char* DefaultMihException::what() const noexcept
{
	std::stringstream ss;
	ss << MihajloException::what() << std::endl;

	ss << msg;
	whatBuffer = ss.str();
	return whatBuffer.c_str();
}

std::string DefaultMihException::GetType() const noexcept
{
	return "Unidentified Mihajlo exception";
}
