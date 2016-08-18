#include "framework.h"
#include <string>
#include "sdl_headers.h"
#include "../pessum_files/logging.h"

namespace aequus {
	namespace framework {
		int logloc = 0;
	}
}

void aequus::framework::SdlStartUp()
{
	InitializeSdl(EVERYTHING);
	CheckSdlVersions();
}

void aequus::framework::InitializeSdl(Uint32 flags)
{
	pessum::logging::AddLogLocation("aequus_files/framework/");
	if (SDL_Init(flags) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to initialize SDL", logloc, "InitializeSdl");
		SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Initialized SDL", logloc, "InitializeSdl");
	}
}

void aequus::framework::TerminateSdl()
{
	SDL_Quit();
	pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Terminated all SDL systems", logloc, "TermianteSdl");
}

void aequus::framework::SetMain()
{
	SDL_SetMainReady();
}

std::string aequus::framework::SdlError()
{
	std::string errorstring = "";
	const char* error = SDL_GetError();
	if (*error) {
		errorstring = error;
		SDL_ClearError();
	}
	pessum::logging::Log(pessum::logging::LOG_ERROR, "SDL Error: " + errorstring, "AEQUUS SDL ERROR");
	return(errorstring);
}

void aequus::framework::CheckSdlVersions()
{
	SDL_version compiled, linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	if (compiled.major == linked.major && compiled.minor == linked.minor && compiled.patch == linked.patch) {
		pessum::logging::LogLoc(pessum::logging::LOG_DATA,
			"SDL versions match: " + std::to_string(compiled.major) + "." + std::to_string(compiled.minor) + "." + std::to_string(compiled.patch),
			logloc, "CheckSdlVersions");
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "SDL versions do not match", logloc, "CheckSdlversons");
		pessum::logging::LogLoc(pessum::logging::LOG_DATA,
			"Compiled version: " + std::to_string(compiled.major) + "." + std::to_string(compiled.minor) + "." + std::to_string(compiled.patch),
			logloc, "CheckSdlVersions");
		pessum::logging::LogLoc(pessum::logging::LOG_DATA,
			"Linked version: " + std::to_string(linked.major) + "." + std::to_string(linked.minor) + "." + std::to_string(linked.patch),
			logloc, "CheckSdlVersions");
	}
}