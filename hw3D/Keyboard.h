#pragma once

#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Release,
			Invalid
		};
	public:
		Event() : Event(0u, Type::Invalid) { }
		Event(unsigned char code, Type type) : code(code), type(type) { }
		unsigned char GetCode() { return code; }
		Type GetType() { return type; }
		bool IsPressed() { return type == Type::Pressed; }
		bool IsValid() { return type != Type::Invalid; }
	private:
		unsigned char code;
		Type type;
	};
public:
	//Key Events
	bool IsKeyPressed(unsigned char keycode) const;
	Event ReadKey();
	bool IsKeyEmpty() const;
	void ClearKeys();
	//Char events
	char ReadChar();
	bool IsCharEmpty() const;
	void ClearChars();
	void Clear(); //clears both keyBuffer and charBuffer
	void ClearStates(); //clear keyStates
	void SetAutorepeateTo(bool value);
	bool IsAutorepeatEnabled() const;
private:
	void OnKeyPress(unsigned char keycode);
	void OnKeyRelease(unsigned char keycode);
	void OnChar(char c);
	template<typename T>
	void LimitBuffer(std::queue<T>& buf)
	{
		while (buf.size() > maxBufferSize)
		{
			buf.pop();
		}
	}
private:
	static constexpr unsigned int nStates = 256u;
	static constexpr unsigned int maxBufferSize = 16u;
	bool isAutorepeatEnabled = false;
	std::bitset<nStates> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};