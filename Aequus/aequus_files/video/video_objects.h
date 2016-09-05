#ifndef _AEQUSS_FILES_VIDEO_VIDEO_OBJECTS_H_
#define _AEQUSS_FILES_VIDEO_VIDEO_OBJECTS_H_
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		//WINDOW
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
			bool bordered = true;
			bool grabbed = false;
			std::string title;
		};

		//MESSAGE BOX
		//Used to set different message box types
		enum MessageBoxFlags
		{
			ERROR = SDL_MESSAGEBOX_ERROR,
			WARNING = SDL_MESSAGEBOX_WARNING,
			INFORMATION = SDL_MESSAGEBOX_INFORMATION
		};
		//Used to set the default key controls for a button
		enum MessageBoxButtonFlags
		{
			RETURNKEY = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
			ESCAPEKEY = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
			NOKEY = 0
		};
		//Used to set specific color in a color scheme
		enum MessageBoxColorType {
			BACKGROUND,
			TEXT,
			BUTTON_BORDER,
			BUTTON_BACKGROUND,
			BUTTON_SELECTED,
			COLOR_MAX
		};

		//SURFACE
		struct SubSurface {
			SDL_Surface surface;
			SDL_Rect sourcerect, destinationrect;
		};
		enum SurfaceType {
			SIMPLE,
			CLIP,
			SPRITESHEET,
			COMBINATION
		};

		//RENDERER
		enum RendererFlags
		{
			SOFTWARE = SDL_RENDERER_SOFTWARE,
			ACCELERATED = SDL_RENDERER_ACCELERATED,
			VSYNC = SDL_RENDERER_PRESENTVSYNC,
			TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
		};
		enum BlendMode
		{
			NONE = SDL_BLENDMODE_NONE,
			BLEND = SDL_BLENDMODE_BLEND,
			ADD = SDL_BLENDMODE_ADD,
			MOD = SDL_BLENDMODE_MOD
		};
		struct Rectangle
		{
			int x, y, width, height;
		};
		struct Point
		{
			int x, y;
		};
	}
}
#endif // !_AEQUSS_FILES_VIDEO_VIDEO_OBJECTS_H_
