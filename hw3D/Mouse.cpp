#include "Mouse.h"

bool Mouse::LeftIsPressed() const
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const
{
	return rightIsPressed;
}

int Mouse::GetPosX() const
{
	return xPos;
}

int Mouse::GetPosY() const
{
	return yPos;
}

Mouse::Event Mouse::Read()
{
	Event e = events.front();
	events.pop();
	return e;
}

std::pair<int, int> Mouse::GetPos() const
{
	return { xPos, yPos };
}

void Mouse::ChangeLeftState(bool pressed)
{
	leftIsPressed = pressed;
	if (LeftIsPressed()) events.emplace(Event::Type::RPress, *this);
	else events.emplace(Event::Type::LPress, *this);
}

void Mouse::ChangeRightState(bool pressed)
{
	rightIsPressed = pressed;
	if (RightIsPressed()) events.emplace(Event::Type::RPress, *this);
	else events.emplace(Event::Type::LPress, *this);
}

void Mouse::Move(int x, int y)
{
	xPos = x;
	yPos = y;
	events.emplace(Event::Type::Move, *this);
}
