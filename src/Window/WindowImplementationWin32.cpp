#include <Window/WindowImplementationWin32.hpp>

#include <System/InputImplementation.hpp>

#define KEY_REPEAT_BIT 0x40000000 

namespace Window {

	bool WindowImplementationWin32::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style) {
		LPCSTR title = _title.c_str();

		WNDCLASS windowClass;
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

		HINSTANCE hInstance = GetModuleHandle(NULL);

		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = (WNDPROC)WndProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = title;

		if (!RegisterClass(&windowClass)) {
			return false;
		}

		m_Handle = CreateWindowExA(
			dwExStyle, 
			title, 
			title, 
			WS_OVERLAPPEDWINDOW, 
			0, 
			0, 
			_videoMode.width, 
			_videoMode.height,
			NULL, 
			NULL, 
			hInstance, 
			NULL);

		SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		return true;
	}

	void WindowImplementationWin32::close(void) {
		m_Running = false;
	}

	bool WindowImplementationWin32::isOpen(void) const {
		return m_Running;
	}

	System::Vector2i WindowImplementationWin32::getPosition(void) const {
		throw std::runtime_error("Not implemented: WindowImplementationWin32::getPosition");
	}

	void WindowImplementationWin32::setPosition(const System::Vector2i& _position) {
		throw std::runtime_error("Not implemented: WindowImplementationWin32::setPosition");
	}

	System::Vector2u WindowImplementationWin32::getSize(void) const {
		throw std::runtime_error("Not implemented: WindowImplementationWin32::getSize");
	}

	void WindowImplementationWin32::setSize(const System::Vector2u& _size) {
		throw std::runtime_error("Not implemented: WindowImplementationWin32::setSize");
	}

	void WindowImplementationWin32::display(void) {
		SwapBuffers(GetDC(m_Handle));
	}

	HWND WindowImplementationWin32::getHandle(void) const {
		return m_Handle;
	}
	
	bool WindowImplementationWin32::pollEvent(System::Event& _event, bool _blocking /*= false*/) {
		if (m_EventQueue.empty()) {
			processWaitingEvents();

			if (_blocking) {
				while (m_EventQueue.empty()) {
					Sleep(10);
					processWaitingEvents();
				}
			}
		}

		if (!m_EventQueue.empty()) {
			_event = m_EventQueue.front();

			m_EventQueue.erase(m_EventQueue.begin());

			return true;
		}

		return false;
	}

	void WindowImplementationWin32::pushEvent(const System::Event& _event) {
		m_EventQueue.push_back(_event);
	}

	LRESULT CALLBACK WindowImplementationWin32::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		WindowImplementationWin32 *thisWindow = reinterpret_cast<WindowImplementationWin32 *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (thisWindow) {
			thisWindow->processEvent(message, wParam, lParam);

			if (message == WM_CLOSE) {
				// Handle closing the window how the app chooses
				return 0;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}


	void WindowImplementationWin32::processEvent(UINT message, WPARAM wParam, LPARAM lParam) {
		if (m_Handle == NULL) {
			return;
		}

		System::Event e;

		switch (message) {
		case (WM_CLOSE):
			e.type = System::Event::EventType::WindowClosed;
			pushEvent(e);
			break;

		case (WM_EXITSIZEMOVE):
			m_ExitSizeChange = true;
			break;

		case (WM_SIZE):
			// Only want the last size change event
			if (!m_ExitSizeChange) {
				return;
			}
			m_ExitSizeChange = false;

			e.type = System::Event::EventType::WindowSizeChanged;

			m_Size = System::Vector2u(HIWORD(lParam), LOWORD(lParam));

			e.size.height = HIWORD(lParam);
			e.size.width = LOWORD(lParam);

			if (wParam == SIZE_MAXIMIZED) {
				e.size.type = System::Event::ResizedType::Maximized;
			}
			else if (wParam == SIZE_MINIMIZED) {
				e.size.type = System::Event::ResizedType::Minimized;
			}
			else {
				e.size.type = System::Event::ResizedType::Restored;
			}
			pushEvent(e);
			break;

		case (WM_SETFOCUS):
			e.type = System::Event::EventType::GainedFocus;
			pushEvent(e);
			break;

		case (WM_KILLFOCUS):
			e.type = System::Event::EventType::LostFocus;
			pushEvent(e);
			break;

		case (WM_KEYDOWN):
			if ((lParam & KEY_REPEAT_BIT) && !m_RepeatedKeys) {
				break;
			}
			e.type = System::Event::EventType::KeyDown;
			e.key.key = System::InputImplementation::systemToZeno(wParam);
			pushEvent(e);
			break;

		case (WM_KEYUP):
			e.type = System::Event::EventType::KeyUp;
			e.key.key = System::InputImplementation::systemToZeno(wParam);
			pushEvent(e);
			break;

		case (WM_MOUSEWHEEL):
			e.type = System::Event::EventType::MouseWheelChanged;
			e.wheel.delta = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
			e.wheel.x = LOWORD(lParam);
			e.wheel.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_LBUTTONDOWN):
			e.type = System::Event::EventType::MouseButtonPressed;
			e.mouseButton.button = System::Mouse::Button::Left;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_LBUTTONUP):
			e.type = System::Event::EventType::MouseButtonReleased;
			e.mouseButton.button = System::Mouse::Button::Left;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_RBUTTONDOWN):
			e.type = System::Event::EventType::MouseButtonPressed;
			e.mouseButton.button = System::Mouse::Button::Right;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_RBUTTONUP):
			e.type = System::Event::EventType::MouseButtonReleased;
			e.mouseButton.button = System::Mouse::Button::Right;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_MBUTTONDOWN):
			e.type = System::Event::EventType::MouseButtonPressed;
			e.mouseButton.button = System::Mouse::Button::Middle;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_MBUTTONUP):
			e.type = System::Event::EventType::MouseButtonReleased;
			e.mouseButton.button = System::Mouse::Button::Middle;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_XBUTTONDOWN):
			e.type = System::Event::EventType::MouseButtonPressed;
			e.mouseButton.button = (HIWORD(wParam) == XBUTTON1) ? System::Mouse::Button::Extra1 : System::Mouse::Button::Extra2;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_XBUTTONUP):
			e.type = System::Event::EventType::MouseButtonReleased;
			e.mouseButton.button = (HIWORD(wParam) == XBUTTON1) ? System::Mouse::Button::Extra1 : System::Mouse::Button::Extra2;
			e.mouseButton.x = LOWORD(lParam);
			e.mouseButton.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case (WM_MOUSEMOVE):
			e.type = System::Event::EventType::MouseMoved;
			e.position.x = LOWORD(lParam);
			e.position.y = HIWORD(lParam);
			pushEvent(e);
			break;

		case WM_CHAR:
		{
			if (m_RepeatedKeys || ((lParam & (1 << 30)) == 0))
			{
				// Get the code of the typed character
				uint32_t character = static_cast<uint32_t>(wParam);
				// Send a TextEntered event
				e.type = System::Event::TextEntered;
				e.text.unicode = character;
				pushEvent(e);
			}
			break;
		}

		}
	}

	void WindowImplementationWin32::processWaitingEvents(void) {
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowImplementationWin32::setRepeatedKeys(bool _repeat) {
		m_RepeatedKeys = _repeat;
	}

	void WindowImplementationWin32::setTitle(const std::string& _title) {
		if (SetWindowText(m_Handle, _title.c_str())) {
			m_Title = _title;
		}
	}

	std::string WindowImplementationWin32::getTitle(void) const {
		return m_Title;
	}

}