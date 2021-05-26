#pragma once

#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			RPress,
			LDown,
			RDown,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
	private:
		Type type;
		int xPos;
		int yPos;
	public:
		Event(Type type, Mouse& parent) : type(type), xPos(parent.xPos), yPos(parent.yPos) { }
		bool IsValid() const { return type != Type::Invalid; }
		Type GetType() const { return type; }
		int GetPosX() const { return xPos; }
		int GetPosY() const { return yPos; }
		std::pair<int, int> GetPos() const { return { xPos, yPos }; }
	};
public:
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	int GetPosX() const;
	int GetPosY() const;
	bool IsEmpty() const;
	void Clear();
	Event Read();
	std::pair<int, int> GetPos() const;
private:
	void ChangeLeftState(bool pressed);
	void ChangeRightState(bool pressed);
	void OnWheelMove(bool isUp);
	void Move(int x, int y);
	void LimitBuffer();
private:
	static constexpr unsigned int bufferSize = 16u;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	int xPos;
	int yPos;
	std::queue<Event> events;
};