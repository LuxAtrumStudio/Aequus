#ifndef _AEQUUS_FILES_VIDEO_MESSAGEBOX_H_
#define _AEQUUS_FILES_VIDEO_MESSAGEBOX_H_
#include <string>
#include <vector>
#include "../sdl_headers.h"
#include "../aequus_core.h"
#include "../video.h"
namespace aequus {
	namespace video {
		class MessageBox {
		public:
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
				NONE = 0
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
			//Sets the color scheme for all rgb colors for five sections, with variables of 0.0-1.0
			void SetColorScheme(float r1, float g1, float b1,
				float r2, float g2, float b2,
				float r3, float g3, float b3,
				float r4, float g4, float b4,
				float r5, float g5, float b5);
			//Sets single color of the color scheme, with variables of 0.0-1.0
			void SetColor(MessageBoxColorType type, float red, float green, float blue);
			//Adds an additional button to the message box
			void AddButton(MessageBoxButtonFlags flags, std::string text);
			//Creates a message box, must be called before any other message box function
			void NewMessageBox(MessageBoxFlags flags, SDL_Window* parentwindow, std::string title, std::string message);
			//Displays the message box, and returns button press
			int RunMessageBox();
		private:
			struct MessageBoxData {
				Uint32 flags;
				SDL_Window* window;
				const char* title;
				const char* message;
				std::vector<SDL_MessageBoxButtonData> buttons;
				SDL_MessageBoxColorScheme* colorscheme;
			};
			MessageBoxData internalmessageboxdata;
			SDL_MessageBoxData messageboxdata;
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_WINDOW_MESSAGEBOX_H_
