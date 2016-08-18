#ifndef _AEQUUS_FRAMEWORK_H_
#define _AEQUUS_FRAMEWORK_H_
#include <string>
#include "sdl_headers.h"
namespace aequus {
	//namespace framework overall framework for SDL api that does not fit in any catagory
	namespace framework {
		//Used to declare the specific subsystems to be initialized
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
		//Sets log location for aequus framework logging
		extern int logloc;
		//Initalizes all SDL subsystems, and checks versions
		void SdlStartUp();
		//Initalizes specific SDL subsystems
		void InitializeSdl(Uint32 flags);
		//Terminates all initialized SDL subsystems
		void TerminateSdl();
		//Sets program main function over SDL main function
		void SetMain();
		//Returns SDL error for further logging
		std::string SdlError();
		//Checks and compairs compiled version of SDL and run version of SDL
		void CheckSdlVersions();
	}
}
#endif // !_AEQUUS_FRAMEWORK_H_
