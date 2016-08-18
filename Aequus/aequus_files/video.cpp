#include "video.h"
#include "sdl_headers.h"
#include "../pessum_files/logging.h"

namespace aequus {
	namespace video {
		int logloc = 0;
	}
}

void aequus::video::SetScreenSaver(bool screensaver)
{
	if (screensaver == true) {
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Enabled screen saver", logloc, "SetScreenSaver");
		SDL_EnableScreenSaver();
	}
	else if (screensaver == false) {
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Disabled screen saver", logloc, "SetScreenSaver");
		SDL_DisableScreenSaver();
	}
}