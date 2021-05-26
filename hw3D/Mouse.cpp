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

bool Mouse::IsEmpty() const
{
	return events.empty();
}

void Mouse::Clear()
{
	events = std::queue<Event>();
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
	LimitBuffer();
}

void Mouse::ChangeRightState(bool pressed)
{
	rightIsPressed = pressed;
	if (RightIsPressed()) events.emplace(Event::Type::RPress, *this);
	else events.emplace(Event::Type::LPress, *this);
	LimitBuffer();
}

void Mouse::OnWheelMove(bool isUp)
{
	if (isUp) events.emplace(Event::Type::WheelUp, *this);
	else      events.emplace(Event::Type::WheelDown, *this);
	LimitBuffer();
}

void Mouse::Move(int x, int y)
{
	xPos = x;
	yPos = y;
	events.emplace(Event::Type::Move, *this);
	LimitBuffer();
}

void Mouse::LimitBuffer()
{
	while (events.size() > bufferSize) events.pop();
}
