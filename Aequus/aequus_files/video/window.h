#ifndef _AEQUUS_VIDEO_WINDOW_H_
#define _AEQUUS_VIDEO_WINDOW_H_
#include <string>
#include <vector>
#include "messagebox.h"
#include "../sdl_headers.h"
#include "../aequus_core.h"
#include "../video.h"
namespace aequus {
	namespace video {
		//Used for setting different window initialization settings
		enum WindowFlags
		{
			FULLSCREEN = SDL_WINDOW_FULLSCREEN,
			FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
			OPENGL = SDL_WINDOW_OPENGL,
			SHOWN = SDL_WINDOW_SHOWN,
			HIDDEN = SDL_WINDOW_HIDDEN,
			BORDERLESS = SDL_WINDOW_BORDERLESS,
			RESIZABLE = SDL_WINDOW_RESIZABLE,
			MINIMIZED = SDL_WINDOW_MINIMIZED,
			MAXIMIZED = SDL_WINDOW_MAXIMIZED,
			INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
			INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
			MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
			FOREIGN = SDL_WINDOW_FOREIGN,
			ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI,
			MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
			WINDOWED = 0
		};
		//Used for setting different window position settings
		enum WindowPositionFlags
		{
			CENTERED = SDL_WINDOWPOS_CENTERED,
			CENTERED_MASK = SDL_WINDOWPOS_CENTERED_MASK,
			UNDEFINED = SDL_WINDOWPOS_UNDEFINED,
			UNDEFINED_MASK = SDL_WINDOWPOS_UNDEFINED_MASK
		};
		//Structure for storing window data
		struct WindowData {
			SDL_Window* sdlwindow = NULL;
			int logloc = 0;
			bool hidden = false;
			bool minimized = false;
			bool maximized = false;
		};
		//Window class to contain SDL window objects, and manage all internal data
		//related to the window, and to contain all relevent functions for window manipulation
		class Window {
		public:
			//Creates new SDL window based off of given arguments
			void CreateWindow(std::string title = "NULL", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int width = 600, int height = 600, Uint32 flags = SDL_INIT_EVERYTHING);
			//Terminates an SDL window, and erases all data
			void TerminateWindow();
			//Toggles weather the window is hidden
			void SetHidden(bool hide);
			//Maximizes window
			void Maximize();
			//Minimizes window
			void Minimize();
			//Brings window to top above other windows
			void Raise();
			//Restores window to original size and position
			void Restore();
			void SetBordered(bool border);
			void SetBrightness(float brightness);
			void SetFullscreen(Uint32 flags);
			void SetGammaRamp(float red, float green, float blue);
			void SetGrab(bool grab);
			void SetIcon(std::string iconfiledirectory);
			void SetMaximumSize(int width, int height);
			void SetMinimumSize(int width, int height);
			void SetPosition(int x, int y);
			void SetSize(int width, int height);
			void SetTitle(std::string title);
		private:
			//Class storage for windows internal data
			WindowData data;
			std::vector<MessageBox> messageboxes;
		};
	}
}
#endif // !_AEQUUS_VIDEO_WINDOW_H_
