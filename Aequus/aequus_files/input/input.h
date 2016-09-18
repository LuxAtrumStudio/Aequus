#ifndef _AEQUUS_FILES_INPUT_INPUT_H_
#define _AEQUUS_FILES_INPUT_INPUT_H_
#include <ctime>
#include <vector>
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
			RELEASED
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
			int windowid;
			//Window
			WindowEvent winevent;
			//Window
			int data1, data2;
			//Keyboard/MouseButton
			State buttonstate;
			//Keyboard
			bool repeate;
			//Keyboard
			SDL_Keysym keydata;
			//Keyboard
			int key;
			//TextEdit/TextInput
			std::string text;
			//TextEdit
			int start, length;
			//MouseMotion/MouseButton
			int posx, posy;
			//MouseButton
			int clicks;
			//MouseButton
			Button mousebutton;
			//MouseWheel
			int scrollx, scrolly;
			//Audio
			bool capture;
			//DragDrop
			std::string file;

		};
		extern EventType eventtype;
		extern SDL_Event sdlevent;
		extern Event newevent;
		extern std::vector<Event> events;
		void PollEvents();
		void InterpretEvent();
	}
}
#endif // !_AEQUUS_FILES_INPUT_INPUT_H_
