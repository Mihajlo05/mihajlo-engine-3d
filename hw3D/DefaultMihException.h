#pragma once

#include "MihajloException.h"

class DefaultMihException : public MihajloException
{
public:
	DefaultMihException(const std::string& file, int line, const std::string& msg);
	const char* what() const noexcept override;
	virtual std::string GetType() const noexcept override;
private:
	std::string msg;
};