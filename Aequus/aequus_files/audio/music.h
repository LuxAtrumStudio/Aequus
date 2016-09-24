#ifndef _AEQUUS_FILES_AUDIO_MUSIC_H_
#define _AEQUUS_FILES_AUDIO_MUSIC_H_
#include "../aequus_headers.h"
namespace aequus {
	namespace audio {
		namespace music {
			extern std::vector<Mix_Music*> songs;
			extern int currentsong;
			extern int logloc;
			extern bool autoplay, shuffle, playing;
			extern int loops, fadeint;
			extern double position;
			void InitalizeMusic();
			void LoadSong(std::string file);
			void PlaySong(int startfadein = -1, int startloops = -1, double startposition = -1.0);
			void SetVolume(double percent);
			void StopSong();
			void SetAutoPlay(bool setting);
			void SetShuffle(bool setting);
			void FadeOut(int endfadeout = -1);
			void LoadPlaylist(std::string folder);
			void ClearQueue();
			void Update();
			void TerminateMusic();
		}
	}
}
#endif // !_AEQUUS_FILES_AUDIO_MUSIC_H_
