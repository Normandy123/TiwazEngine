#include "window.h"

#include "engine_vars.h"
#include "log_system.h"
#include "event_system.h"

Tiwaz::Window::IRenderWindow* Tiwaz::Global::RENDERWINDOW;

#ifdef _WIN64
Tiwaz::Window::RenderWindow* Tiwaz::Window::p_callback_window;

void Tiwaz::Window::RenderWindow::TiwazCreateWindow(const uint16_t & width, const uint16_t & height, const std::string & title, const bool & fullscreen)
{
	Tiwaz::Window::p_callback_window = this;

	ZeroMemory(&h_wnd, sizeof(HWND));
	ZeroMemory(&h_device_context, sizeof(HDC));
	ZeroMemory(&opengl_rendering_context, sizeof(HGLRC));

	ZeroMemory(&wnd_msg, sizeof(MSG));

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = NULL;
	wcex.hCursor = LoadCursor(Platform::h_instance, IDC_ARROW);
	wcex.hIcon = LoadIcon(Platform::h_instance, IDI_APPLICATION);
	wcex.hInstance = Platform::h_instance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = "TIWAZ";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "ERROR: Could not register window class!", "ERROR", MB_OK);
		Log(LogSystem::TIWAZ_FATALERROR, "WINDOW", "Could not register window class!");
	}

	CREATESTRUCT cs;
	ZeroMemory(&cs, sizeof(cs));

	cs.x = 0;
	cs.y = 0;
	cs.cx = static_cast<int>(width);
	cs.cy = static_cast<int>(height);
	cs.dwExStyle = NULL;
	cs.hInstance = Platform::h_instance;
	cs.hMenu = NULL;
	cs.hwndParent = NULL;
	cs.lpCreateParams = NULL;
	cs.lpszClass = wcex.lpszClassName;
	cs.lpszName = static_cast<LPCTSTR>(title.c_str());
	cs.style = WS_OVERLAPPEDWINDOW;

	h_wnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);

	if (!h_wnd)
	{
		MessageBox(NULL, "ERROR: Could not create window!", "ERROR", MB_OK);
		Log(LogSystem::TIWAZ_FATALERROR, "WINDOW", "Could not create window!");
	}

	PIXELFORMATDESCRIPTOR temp_pfd;
	ZeroMemory(&temp_pfd, sizeof(PIXELFORMATDESCRIPTOR));

	temp_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	temp_pfd.nVersion = 1;
	temp_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	temp_pfd.iPixelType = PFD_TYPE_RGBA;
	temp_pfd.cColorBits = 32;
	temp_pfd.cRedBits = 0; temp_pfd.cRedShift = 0; temp_pfd.cGreenBits = 0; temp_pfd.cGreenShift = 0; temp_pfd.cBlueBits = 0; temp_pfd.cBlueShift = 0; temp_pfd.cAlphaBits = 0; temp_pfd.cAlphaShift = 0;
	temp_pfd.cAccumBits = 0;
	temp_pfd.cAccumRedBits = 0; temp_pfd.cAccumGreenBits = 0; temp_pfd.cAccumBlueBits = 0; temp_pfd.cAccumAlphaBits = 0;
	temp_pfd.cDepthBits = 24;
	temp_pfd.cStencilBits = 8;
	temp_pfd.cAuxBuffers = 0;
	temp_pfd.iLayerType = PFD_MAIN_PLANE;
	temp_pfd.bReserved = 0;
	temp_pfd.dwLayerMask = 0; temp_pfd.dwVisibleMask = 0; temp_pfd.dwDamageMask = 0;

	h_device_context = GetDC(h_wnd);

	int temp_pixel_format = ChoosePixelFormat(h_device_context, &temp_pfd);
	SetPixelFormat(h_device_context, temp_pixel_format, &temp_pfd);

	opengl_rendering_context = wglCreateContext(h_device_context);
	wglMakeCurrent(h_device_context, opengl_rendering_context);

	if (wglewInit() != GLEW_OK)
	{
		MessageBox(NULL, "ERROR: Could not intialize WGLEW!", "ERROR", MB_OK);
		Log(LogSystem::TIWAZ_FATALERROR, "WINDOW", "Could not intialize WGLEW!");
	}

	const int ARB_pixelformat_attributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_ALPHA_BITS_ARB, 0,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 8,
		0
	};

	const int ARB_context_attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		WGL_CONTEXT_FLAGS_ARB, GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT,
		0
	};

	const int EXT_pixelformat_attributes[] =
	{
		WGL_DRAW_TO_WINDOW_EXT, GL_TRUE,
		WGL_SUPPORT_OPENGL_EXT, GL_TRUE,
		WGL_DOUBLE_BUFFER_EXT, GL_TRUE,
		WGL_PIXEL_TYPE_EXT, WGL_TYPE_RGBA_EXT,
		WGL_ACCELERATION_EXT, WGL_FULL_ACCELERATION_EXT,
		WGL_ALPHA_BITS_EXT, 0,
		WGL_COLOR_BITS_EXT, 32,
		WGL_DEPTH_BITS_EXT, 24,
		WGL_STENCIL_BITS_EXT, 8,
		WGL_SAMPLE_BUFFERS_EXT, GL_TRUE,
		WGL_SAMPLES_EXT, 8,
		0
	};

	if (wglewIsSupported("WGL_ARB_pixel_format") && !wglewIsSupported("WGL_EXT_pixel_format"))
	{
		int ARB_pixel_format;
		UINT ARB_num_formats;

		wglChoosePixelFormatARB(h_device_context, ARB_pixelformat_attributes, NULL, 1, &ARB_pixel_format, &ARB_num_formats);

		PIXELFORMATDESCRIPTOR ARB_pfd;
		ZeroMemory(&ARB_pfd, sizeof(PIXELFORMATDESCRIPTOR));

		DescribePixelFormat(h_device_context, ARB_pixel_format, sizeof(ARB_pfd), &ARB_pfd);
		SetPixelFormat(h_device_context, ARB_pixel_format, &ARB_pfd);
	}

	if (wglewIsSupported("WGL_EXT_pixel_format"))
	{
		int EXT_pixel_format;
		UINT EXT_num_formats;

		wglChoosePixelFormatEXT(h_device_context, EXT_pixelformat_attributes, NULL, 1, &EXT_pixel_format, &EXT_num_formats);

		PIXELFORMATDESCRIPTOR EXT_pfd;
		ZeroMemory(&EXT_pfd, sizeof(PIXELFORMATDESCRIPTOR));

		DescribePixelFormat(h_device_context, EXT_pixel_format, sizeof(EXT_pfd), &EXT_pfd);
		SetPixelFormat(h_device_context, EXT_pixel_format, &EXT_pfd);
	}

	if (wglewIsSupported("WGL_ARB_create_context"))
	{
		HGLRC temp_context = wglCreateContextAttribsARB(h_device_context, 0, ARB_context_attributes);

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(opengl_rendering_context);
		ZeroMemory(&opengl_rendering_context, sizeof(HGLRC));

		opengl_rendering_context = temp_context;
		wglMakeCurrent(h_device_context, opengl_rendering_context);
	}

	m_should_quit = false;
}

void Tiwaz::Window::RenderWindow::TiwazDestroyWindow()
{
	if (!m_is_hidden)
	{
		CloseWindow(h_wnd);
	}

	p_callback_window = nullptr;

	wglDeleteContext(opengl_rendering_context);
	ReleaseDC(h_wnd, h_device_context);
	DestroyWindow(h_wnd);

	UnregisterClass("TIWAZ", Platform::h_instance);
}

void Tiwaz::Window::RenderWindow::TiwazShowWindow()
{
	ShowWindow(h_wnd, SW_SHOWDEFAULT);
	UpdateWindow(h_wnd);

	m_is_hidden = false;
}

void Tiwaz::Window::RenderWindow::TiwazCloseWindow()
{
	CloseWindow(h_wnd);

	m_is_hidden = true;
}

void Tiwaz::Window::RenderWindow::TiwazUpdate()
{
	if (PeekMessage(&wnd_msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&wnd_msg);
		DispatchMessage(&wnd_msg);
	}
}

void Tiwaz::Window::RenderWindow::TiwazSwapBuffers()
{
	SwapBuffers(h_device_context);
}

LRESULT CALLBACK Tiwaz::Window::RenderWindow::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_SHOWWINDOW:
		{
			EventSystem::ScreenShowEvent event;
			event.width = static_cast<uint16_t>(LOWORD(lParam));
			event.height = static_cast<uint16_t>(HIWORD(lParam));
			Global::ENGINEEVENTHANDLER->HandleEvent(&event);
		}
		break;
	case WM_SIZE:
		{
			EventSystem::ScreenResizeEvent event;
			event.width = static_cast<uint16_t>(LOWORD(lParam));
			event.height = static_cast<uint16_t>(HIWORD(lParam));
			Global::ENGINEEVENTHANDLER->HandleEvent(&event);
		}		
		break;
	case WM_PAINT:
		break;
	case WM_CLOSE:
		m_should_quit = true;
		Global::ENGINE_SHOULD_EXIT = true;
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
#endif