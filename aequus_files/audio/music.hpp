#ifndef _AEQUUS_FILES_AUDIO_MUSIC_H_
#define _AEQUUS_FILES_AUDIO_MUSIC_H_
#include "../aequus_headers.hpp"
namespace aequus {
namespace audio {
namespace music {
// Stucture to store song data
struct Song {
  // SDL music pointer
  Mix_Music *mixsong;
  // Song name
  std::string songname;
};
// Stores loaded songs and data
extern std::vector<Song> songs;
// int pointer to current song in song playlist
extern int currentsong;
// Pointer to log location index
extern int logloc;
// Playback settings for autoplay, shuffle, and check if song is playing
extern bool autoplay, shuffle, playing;
// Saves the number of loops to play for a song, and the ms for fade in
extern int loops, fadeint;
// Saves the position in s to begin song at
extern double position;
// Initalizes music playback
void InitalizeMusic();
// Loads a song into the song vector from given file(mp3)
void LoadSong(std::string file);
// Plays the current song from the song vector with given fade in time ms, for
// number of loops, and given start positon s
void PlaySong(int startfadein = -1, int startloops = -1,
              double startposition = -1.0);
// Sets the song playing volume for song playback
void SetVolume(double percent);
// Stops song playback immediately
void StopSong();
// Toggles auto playing funciton for song vector. Requiers update to be called
// regularly
void SetAutoPlay(bool setting);
// Toggles shuffle playng for song vector, selecting a random song as the
// current song
void SetShuffle(bool setting);
// Fades out current song given ms for fade time
void FadeOut(int endfadeout = -1);
// Loades songs from a given playlist folder
void LoadPlaylist(std::string folder);
// Clears song vector of all current songs
void ClearQueue();
// Updates any per frame checks eg. autoplay
void Update();
// Terminates all music functions
void TerminateMusic();
}
}
}
#endif // !_AEQUUS_FILES_AUDIO_MUSIC_H_
