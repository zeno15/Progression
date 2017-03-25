#include <Window/Window.hpp>

namespace Window {

	Window::Window(void) :
		m_VideoMode(),
		m_Title(std::string()),
		m_WindowStyle(WindowStyle::Default) {
	}

	Window::Window(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/) :
		m_VideoMode(_videoMode),
		m_Title(_title),
		m_WindowStyle(_style) {
		create(m_VideoMode, m_Title, m_WindowStyle);
	}

	Window::~Window(void) {
		close();
	}


	bool Window::create(const VideoMode& _videoMode, const std::string& _title, uint32_t _style /*= WindowStyle::Default*/) {
		m_VideoMode = _videoMode;
		m_Title = _title;
		m_WindowStyle = _style;

		if (!m_WindowImpl.create(_videoMode, _title, _style)) {
			return false;
		}
		if (!m_ContextImpl.create(m_WindowImpl.getHandle(), _videoMode)) {
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void Window::close(void) {
		m_WindowImpl.close();
	}

	bool Window::isOpen(void) const {
		return m_WindowImpl.isOpen();
	}

	System::Vector2i Window::getPosition(void) const {
		return m_WindowImpl.getPosition();
	}

	void Window::setPosition(const System::Vector2i& _position) {
		m_WindowImpl.setPosition(_position);
	}

	System::Vector2u Window::getSize(void) const {
		return m_WindowImpl.getSize();
	}

	void Window::setSize(const System::Vector2u& _size) {
		m_WindowImpl.setSize(_size);
	}

	void Window::display(void) {
		m_WindowImpl.display();
	}

	void Window::clear(void) {
		m_ContextImpl.clear();
	}

	bool Window::pollEvent(System::Event& _event) {
		return m_WindowImpl.pollEvent(_event, false);
	}
	void Window::waitEvent(System::Event& _event) {
		m_WindowImpl.pollEvent(_event, true);
	}

	void Window::setRepeatedKeys(bool _repeat) {
		m_WindowImpl.setRepeatedKeys(_repeat);
	}

	WindowHandle Window::getHandle(void) const {
		return m_WindowImpl.getHandle();
	}

	void Window::setTitle(const std::string& _title) {
		m_WindowImpl.setTitle(_title);
	}

	std::string Window::getTitle(void) const {
		return m_WindowImpl.getTitle();
	}

}