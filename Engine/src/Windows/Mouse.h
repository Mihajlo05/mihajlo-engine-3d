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
			LRelease,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			RawDelta, //x and y represent delta in this case, not the position
			Invalid
		};
	private:
		Type type;
		int x;
		int y;
	public:
		Event(Type type, Mouse& parent) : type(type), x(parent.xPos), y(parent.yPos) { }
		static Event RawDeltaEvent(int dx, int dy)
		{
			Event e;
			e.type = Type::RawDelta; e.x = dx; e.y = dy;
			return e;
		}
		bool IsValid() const { return type != Type::Invalid; }
		bool IsRawDelta() const { return type == Type::RawDelta; }
		Type GetType() const { return type; }
		int GetX() const { return x; }
		int GetY() const { return y; }
		std::pair<int, int> GetPos() const { return { x, y }; }
	private:
		Event() = default;
	};
public:
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	int GetPosX() const;
	int GetPosY() const;
	bool IsEmpty() const;
	bool IsInWindow() const;
	void Clear();
	Event Read();
	std::pair<int, int> GetPos() const;
	void EnableCursor();
	void DisableCursor();
	bool IsCursorEnabled() const;
	void EnableRawInput();
	void DisableRawInput();
	bool IsRawEnabled() const;
private:
	void ChangeLeftState(bool pressed);
	void ChangeRightState(bool pressed);
	void OnWheelMove(bool isUp);
	void Move(int x, int y);
	void MoveWithoutEvent(int x, int y);
	void OnMouseLeave();
	void OnMouseEnter();
	void OnRawDelta(int dx, int dy);
	void LimitBuffer();
	void ShowCursor();
	void HideCursor();
	void EnableImGuiMouse();
	void DisableImGuiMouse();
	void LockCursor();
	void FreeCursor();
private:
	static constexpr unsigned int bufferSize = 16u;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = true;
	int xPos = 0;
	int yPos = 0;
	std::queue<Event> buffer;
	bool isCursorEnabled = true;
	bool isRawEnabled = false;
};