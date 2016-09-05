#ifndef _AEQUUS_FILES_VIDEO_H_
#define _AEQUUS_FILES_VIDEO_H_
#include "sdl_headers.h"
#include "video\window.h"
#include "video\messagebox.h"
namespace aequus {
	//namespace video controlls all video componenents of SDL, with windows
	//textures, and everything elses that the end user will see.
	namespace video {
		namespace window {}
		class MessageBox;
		//Sets log location for aequus framework logging
		extern int logloc;
		//Either enables or disables the screensaver
		void SetScreenSaver(bool screensaver);
	}
}
#endif // !_AEQUUS_VIDEO_H_
