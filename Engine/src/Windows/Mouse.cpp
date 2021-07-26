#include "MihajloWin.h"
#include "Mouse.h"
#include "Gui/imgui/imgui.h"

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

bool Mouse::IsInWindow() const
{
	return isInWindow;
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

void Mouse::EnableCursor()
{
	isCursorEnabled = true;
	ShowCursor();
	EnableImGuiMouse();
	FreeCursor();
}

void Mouse::DisableCursor()
{
	isCursorEnabled = false;
	HideCursor();
	DisableImGuiMouse();
	LockCursor();
}

bool Mouse::IsCursorEnabled() const
{
	return isCursorEnabled;
}

void Mouse::EnableRawInput()
{
	isRawEnabled = true;
}

void Mouse::DisableRawInput()
{
	isRawEnabled = false;
}

bool Mouse::IsRawEnabled() const
{
	return isRawEnabled;
}

void Mouse::ChangeLeftState(bool pressed)
{
	leftIsPressed = pressed;
	if (LeftIsPressed()) buffer.emplace(Event::Type::LPress, *this);
	else buffer.emplace(Event::Type::LRelease, *this);
	LimitBuffer();
}

void Mouse::ChangeRightState(bool pressed)
{
	rightIsPressed = pressed;
	if (RightIsPressed()) buffer.emplace(Event::Type::RPress, *this);
	else buffer.emplace(Event::Type::RRelease, *this);
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
	MoveWithoutEvent(x, y);
	buffer.emplace(Event::Type::Move, *this);
	LimitBuffer();
}

void Mouse::MoveWithoutEvent(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Mouse::OnMouseLeave()
{
	isInWindow = false;
	buffer.emplace(Event::Type::Leave, *this);
	LimitBuffer();
}

void Mouse::OnMouseEnter()
{
	isInWindow = true;
	buffer.emplace(Event::Type::Enter, *this);
	LimitBuffer();
}

void Mouse::OnRawDelta(int dx, int dy)
{
	assert(isRawEnabled);
	buffer.push(Event::RawDeltaEvent(dx, dy));
}

void Mouse::LimitBuffer()
{
	while (buffer.size() > bufferSize) buffer.pop();
}

void Mouse::ShowCursor()
{
	while (::ShowCursor(TRUE) < 0);
}

void Mouse::HideCursor()
{
	while (::ShowCursor(FALSE) >= 0);
}

void Mouse::EnableImGuiMouse()
{
	ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
}

void Mouse::DisableImGuiMouse()
{
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
}

void Mouse::LockCursor()
{
	RECT r;
	POINT p;
	GetCursorPos(&p);
	r.left = p.x - 1; r.right = p.x;
	r.top = p.y - 1; r.bottom = p.y;
	ClipCursor(&r);
}

void Mouse::FreeCursor()
{
	ClipCursor(nullptr);
}
