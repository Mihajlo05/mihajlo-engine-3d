#include "Keyboard.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) const
{
	return keyStates[keycode];
}

Keyboard::Event Keyboard::ReadKey()
{
	if (!IsKeyEmpty())
	{
		Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else return Event();
}

bool Keyboard::IsKeyEmpty() const
{
	return keyBuffer.empty();
}

void Keyboard::ClearKeys()
{
	keyBuffer = std::queue<Event>();
}

char Keyboard::ReadChar()
{
	if (!IsCharEmpty())
	{
		char c = charBuffer.front();
		charBuffer.pop();
		return c;
	}
	else return 0;
}

bool Keyboard::IsCharEmpty() const
{
	return charBuffer.empty();
}

void Keyboard::ClearChars()
{
	charBuffer = std::queue<char>();
}

void Keyboard::Clear()
{
	ClearKeys();
	ClearChars();
}

void Keyboard::ClearStates()
{
	keyStates = std::bitset<nStates>();
}

void Keyboard::SetAutorepeateTo(bool value)
{
	isAutorepeatEnabled = value;
}

bool Keyboard::IsAutorepeatEnabled() const
{
	return isAutorepeatEnabled;
}

void Keyboard::OnKeyPress(unsigned char keycode)
{
	keyStates[keycode] = true;
	keyBuffer.push(Event(keycode, Event::Type::Pressed));
	LimitBuffer(keyBuffer);
}

void Keyboard::OnKeyRelease(unsigned char keycode)
{
	keyStates[keycode] = false;
	keyBuffer.push(Event(keycode, Event::Type::Release));
	LimitBuffer(keyBuffer);
}

void Keyboard::OnChar(char c)
{
	charBuffer.push(c);
	LimitBuffer(charBuffer);
}
