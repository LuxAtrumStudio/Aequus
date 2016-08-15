#ifndef _AEQUUS_FRAMEWORK_H_
#define _AEQUUS_FRAMEWORK_H_
#include <string>
#include "sdl_headers.h"
namespace aequus {
	namespace framework {
		enum SubSystem
		{
			TIMER = SDL_INIT_TIMER,
			AUDIO = SDL_INIT_AUDIO,
			VIDEO = SDL_INIT_VIDEO,
			JOYSTICK = SDL_INIT_JOYSTICK,
			HAPTIC = SDL_INIT_HAPTIC,
			GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
			EVENTS = SDL_INIT_EVENTS,
			EVERYTHING = SDL_INIT_EVERYTHING,
			NOPARACHUTE = SDL_INIT_NOPARACHUTE
		};
		extern int logloc;
		void SdlStartUp();
		void InitializeSdl(Uint32 flags);
		void TerminateSdl();
		void SetMain();
		std::string SdlError();
		void CheckSdlVersions();
	}
}
#endif // !_AEQUUS_FRAMEWORK_H_
