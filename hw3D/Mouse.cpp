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
	return buffer.empty();
}

void Mouse::Clear()
{
	buffer = std::queue<Event>();
}

Mouse::Event Mouse::Read()
{
	Event e = buffer.front();
	buffer.pop();
	return e;
}

std::pair<int, int> Mouse::GetPos() const
{
	return { xPos, yPos };
}

void Mouse::ChangeLeftState(bool pressed)
{
	leftIsPressed = pressed;
	if (LeftIsPressed()) buffer.emplace(Event::Type::RPress, *this);
	else buffer.emplace(Event::Type::LPress, *this);
	LimitBuffer();
}

void Mouse::ChangeRightState(bool pressed)
{
	rightIsPressed = pressed;
	if (RightIsPressed()) buffer.emplace(Event::Type::RPress, *this);
	else buffer.emplace(Event::Type::LPress, *this);
	LimitBuffer();
}

void Mouse::OnWheelMove(bool isUp)
{
	if (isUp) buffer.emplace(Event::Type::WheelUp, *this);
	else      buffer.emplace(Event::Type::WheelDown, *this);
	LimitBuffer();
}

void Mouse::Move(int x, int y)
{
	xPos = x;
	yPos = y;
	buffer.emplace(Event::Type::Move, *this);
	LimitBuffer();
}

void Mouse::LimitBuffer()
{
	while (buffer.size() > bufferSize) buffer.pop();
}
