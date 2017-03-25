#include <Window/ContextWin32.hpp>

#include <Window/OpenGL.hpp>


namespace Window {

	ContextWin32::ContextWin32(void) {
	}

	ContextWin32::~ContextWin32(void) {
		wglMakeCurrent(hdc, 0);
		wglDeleteContext(hrc);

		ReleaseDC(hwnd, hdc);
	}


	bool ContextWin32::create(HWND _handle, const VideoMode& _videoMode) {
		hwnd = _handle;
		ShowWindow(hwnd, SW_HIDE);
		hdc = GetDC(hwnd);

		PIXELFORMATDESCRIPTOR pfd;

		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int nPixelFormat = ChoosePixelFormat(hdc, &pfd);

		if (nPixelFormat == 0) {
			return false;
		}

		bool bResult = SetPixelFormat(hdc, nPixelFormat, &pfd) != 0;

		if (!bResult) {
			return false;
		}

		HGLRC tempOpenGLContext = wglCreateContext(hdc);
		wglMakeCurrent(hdc, tempOpenGLContext);

		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB,		static_cast<int>(_videoMode.major),
			WGL_CONTEXT_MINOR_VERSION_ARB,		static_cast<int>(_videoMode.minor),
			WGL_CONTEXT_FLAGS_ARB,				WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		auto renderer = glGetString(GL_RENDERER);
		auto version = glGetString(GL_VERSION);
		auto vendor = glGetString(GL_VENDOR);

		initialiseExtensions();


		hrc = wglCreateContextAttribsARB(hdc, NULL, attributes);
		if (hrc != NULL) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(tempOpenGLContext);
			wglMakeCurrent(hdc, hrc);
		}
		else {
			hrc = tempOpenGLContext;
		}

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		return true;
	}

	void ContextWin32::clear(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}