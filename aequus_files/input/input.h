#ifndef _AEQUUS_FILES_INPUT_INPUT_H_
#define _AEQUUS_FILES_INPUT_INPUT_H_
#include <ctime>
#include <vector>
#include <string>
#include "../sdl_headers.h"
namespace aequus {
	namespace input {
		enum EventType {
			WINDOW,
			KEYBOARD,
			TEXTEDIT,
			TEXTINPUT,
			MOUSEMOTION,
			MOUSEBUTTON,
			MOUSEWHEEL,
			AUDIO,
			QUIT,
			DROP
		};
		enum WindowEvent {
			SHOWN,
			HIDDEN,
			EXPOSED,
			MOVED,
			RESIZED,
			SIZECHANGED,
			MINIMIZED,
			MAXIMIZED,
			RESTORED,
			ENTER,
			LEAVE,
			FOCUSGAINED,
			FOCUSLOST,
			CLOSE
		};
		enum State {
			PRESSED,
			RELEASED,
			NONE
		};
		enum Button {
			LEFT,
			MIDDLE,
			RIGHT
		};
		struct Event {
			//All event types
			EventType type;
			//All event types
			time_t timestamp;
			//Window/Keyboard/TextEdit/TextInput/MouseMotion/MouseButton/MouseWheel
			int windowid = 0;
			//Window
			WindowEvent winevent;
			//Window
			int data1 = 0, data2 = 0;
			//Keyboard/MouseButton
			State buttonstate = NONE;
			//Keyboard
			bool repeate = false;
			//Keyboard
			SDL_Keysym keydata;
			//Keyboard
			int key = 0;
			//TextEdit/TextInput
			std::string text = "NULL";
			//TextEdit
			int start = 0, length = 0;
			//MouseMotion/MouseButton
			int posx = 0, posy = 0;
			//MouseButton
			int clicks = 0;
			//MouseButton
			Button mousebutton = LEFT;
			bool mousepress = false;
			//MouseWheel
			int scrollx = 0, scrolly = 0;
			//Audio
			bool capture = false;
			//DragDrop
			std::string file = "NULL";
		};
		extern EventType eventtype;
		extern SDL_Event sdlevent;
		extern Event newevent;
		extern bool press;
		extern bool quitevent;
		extern std::vector<Event> events;
		void PollEvents();
		void InterpretEvent();
	}
}
#endif // !_AEQUUS_FILES_INPUT_INPUT_H_
