#ifndef _AEQUUS_FILES_VIDEO_WINDOW_H_
#define _AEQUUS_FILES_VIDEO_WINDOW_H_
#include <string>
#include <vector>
#include "renderer.h"
#include "texture.h"
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		class MessageBox;
		//Window namespace to contain SDL window objects, and manage all internal
		//data related to the window, and to contain all relevent functions for
		//window manipulation
		namespace window {
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
				Renderer windowrenderer;
				std::vector<Texture>textures;
				int logloc = 0;
				bool hidden = false;
				bool minimized = false;
				bool maximized = false;
				bool bordered = true;
				bool grabbed = false;
				std::string title;
			};
			//Storage for all windows that are created
			extern std::vector<WindowData>windows;
			//Int pointer to the currently active window from windows
			extern int boundwindow;
			//Storage for any messagecoxes that are daughter windows to current
			//window
			extern std::vector<MessageBox> messageboxes;
			//Creates new SDL window based off of given arguments
			void CreateWindow(std::string title = "NULL", int width = 600, int height = 600, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = WINDOWED);
			//Terminates an SDL window, and erases all data
			void TerminateWindow(int pointer = boundwindow);
			//Toggles weather the window is hidden
			void SetHidden(bool hide, int pointer = boundwindow);
			//Maximizes window
			void Maximize(int pointer = boundwindow);
			//Minimizes window
			void Minimize(int pointer = boundwindow);
			//Brings window to top above other windows
			void Raise(int pointer = boundwindow);
			//Restores window to original size and position
			void Restore(int pointer = boundwindow);
			//Toggels window border mode
			void SetBordered(bool border, int pointer = boundwindow);
			//Sets window brightness
			void SetBrightness(float brightness, int pointer = boundwindow);
			//Toggles fullscreen mode
			void SetFullscreen(Uint32 flags, int pointer = boundwindow);
			//Sets gamma color ramp of window
			void SetGammaRamp(float red, float green, float blue, int pointer = boundwindow);
			//Toggles grabing of input to window
			void SetGrab(bool grab, int pointer = boundwindow);
			//Sets window icon, given imagedirectory
			//TODO (Arden): create SetIcon function
			void SetIcon(std::string iconfiledirectory, int pointer = boundwindow);
			//Sets the maximum size for the window to be resized to
			void SetMaximumSize(int width, int height, int pointer = boundwindow);
			//Sets the minimum size for the window to be resized to
			void SetMinimumSize(int width, int height, int pointer = boundwindow);
			//Sets the windows position in pixels
			void SetPosition(int x, int y, int pointer = boundwindow);
			//Sets the window size in pixels
			void SetSize(int width, int height, int pointer = boundwindow);
			//Changes the windows title
			void SetTitle(std::string title, int pointer = boundwindow);
			//Displays the updated window surface
			void Update(int pointer = boundwindow);
			//Sets the currently active window
			void BindWindow(int pointer = 0);

			void NewTexture(std::string filepath, int pointer = boundwindow);
		};
	}
}
#endif // !_AEQUUS_VIDEO_WINDOW_H_
