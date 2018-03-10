#pragma once

#include <cstdint>

#include <string>

namespace Tiwaz::Window
{
	class IWindow
	{
	public:
		virtual void TiwazCreateWindow(const uint16_t & width, const uint16_t & height, const std::string & title) = 0;
		virtual void TiwazDestroyWindow() = 0;

		virtual void TiwazShowWindow() = 0;
		virtual void TiwazCloseWindow() = 0;

		virtual void TiwazUpdate() = 0;
		virtual void TiwazSwapBuffers() = 0;

		virtual const bool ShouldQuit() = 0;
		virtual const bool IsOpen() = 0;
	};
}

namespace Tiwaz::Global
{
	extern Window::IWindow* RENDERWINDOW;
}

#ifdef _WIN64
#include "platform.h"

#include <GLEW/glew.h>
#include <GLEW/wglew.h>

namespace Tiwaz::Window
{
	class Window : public IWindow
	{
	public:
		void TiwazCreateWindow(const uint16_t & width, const uint16_t & height, const std::string & title);
		void TiwazDestroyWindow();
	
		void TiwazShowWindow();
		void TiwazCloseWindow();
	
		void TiwazUpdate();
		void TiwazSwapBuffers();
	
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	
		const bool ShouldQuit() { return m_should_quit; };
		const bool IsOpen() { return m_is_hidden; }
	private:
		bool m_should_quit = true;
		bool m_is_hidden = true;
	
		HWND h_wnd;
		HDC h_device_context;
		HGLRC opengl_rendering_context;
	
		MSG wnd_msg;
	};
		
	extern Window* p_callback_window;
	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return p_callback_window->MessageHandler(hWnd, msg, wParam, lParam);
	}
}
#endif