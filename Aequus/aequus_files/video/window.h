#ifndef _AEQUUS_FILES_VIDEO_WINDOW_H_
#define _AEQUUS_FILES_VIDEO_WINDOW_H_
#include <string>
#include <vector>
#include "video_objects.h"
#include "messagebox.h"
#include "renderer.h"
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		//Window class to contain SDL window objects, and manage all internal
		//data related to the window, and to contain all relevent functions for
		//window manipulation
		namespace window {
			//Class that is used to contain all information and functions for
			//managing textures
			class Texture;
			class Renderer;
			//Class storage for windows internal data
			extern WindowData data;
			extern Renderer render;
			//Storage for any messagecoxes that are daughter windows to current
			//window
			extern std::vector<MessageBox> messageboxes;
			//Creates new SDL window based off of given arguments
			void CreateWindow(std::string title = "NULL", int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED, int width = 600, int height = 600, Uint32 flags = WINDOWED);
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
			//Toggels window border mode
			void SetBordered(bool border);
			//Sets window brightness
			void SetBrightness(float brightness);
			//Toggles fullscreen mode
			void SetFullscreen(Uint32 flags);
			//Sets gamma color ramp of window
			void SetGammaRamp(float red, float green, float blue);
			//Toggles grabing of input to window
			void SetGrab(bool grab);
			//Sets window icon, given imagedirectory
			//TODO (Arden): create SetIcon function
			void SetIcon(std::string iconfiledirectory);
			//Sets the maximum size for the window to be resized to
			void SetMaximumSize(int width, int height);
			//Sets the minimum size for the window to be resized to
			void SetMinimumSize(int width, int height);
			//Sets the windows position in pixels
			void SetPosition(int x, int y);
			//Sets the window size in pixels
			void SetSize(int width, int height);
			//Changes the windows title
			void SetTitle(std::string title);
			//Displays the updated window surface
			void Update();
		};
	}
}
#endif // !_AEQUUS_VIDEO_WINDOW_H_
