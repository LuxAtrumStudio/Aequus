#ifndef _AEQUUS_VIDEO_H_
#define _AEQUUS_VIDEO_H_
#include "sdl_headers.h"
namespace aequus {
	//namespace video controlls all video componenents of SDL, with windows
	//textures, and everything elses that the end user will see
	namespace video {
		//Components declaired and commented in window sub file
		enum WindowFlags;
		enum WindowPositionFlags;
		struct WindowData;
		class Window;
		class MessageBox;
		//Core video components
		//Sets log location for aequus framework logging
		extern int logloc;
		//Either enables or disables the screensaver
		void SetScreenSaver(bool screensaver);
	}
}
#endif // !_AEQUUS_VIDEO_H_
