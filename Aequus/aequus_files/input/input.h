#ifndef _AEQUUS_FILES_INPUT_H_
#define _AEQUUS_FILES_INPUT_H_
#include <ctime>
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
			SIZECHANGE,
			MINIMIZED,
			MAXIMIZED,
			RESTORED,
			ENTER,
			LEAVE,
			FOCUSGAINED,
			FOCUSLOST,
			CLOSE
		};
		struct Event {
			EventType type;
			time_t timestamp;
			int windowid;
			WindowEvent winevent;
			int data1, data2;
		};
		extern EventType eventtype;
		extern SDL_Event* sdlevent;
		void PollEvents();
	}
}
#endif // !_AEQUUS_FILES_INPUT_H_
