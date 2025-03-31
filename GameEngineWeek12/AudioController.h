#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include "StandardIncludes.h"

//NOTE: The difference between a constant and constant EXPRESSION is that it MUST be initialized either here or in the constructor.
constexpr int MaxEffectChannels = 16;

class SoundEffect;
class Song;

//essentially a media player
class AudioController : public Singleton<AudioController> //NOTE: All singletons are stored on the stack.
{
public:
	//Constructors/Destructors
	AudioController();
	virtual ~AudioController();

	//Accessors
	string* GetCurrentEffects() { return m_currentEffects; } //new accessor to return the array's first pointer
	string GetMusicTitle() { return m_musicTitle; }
	string GetMusicLength() { return m_musicLength; }

	//Methods
	SoundEffect* LoadEffect(string _guid);
	Song* LoadSong(string _guid);
	void Play(SoundEffect* _effect);
	void Play(Song* _song);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	double MusicPosition();
	void Shutdown();

	static void CatchChannelDone(int _channel);
private:
	//Methods

	//Mix_chunk stores SDL sound effects, whereas music stores music itself. Easy way to differentiate.
	Mix_Chunk* GetSDLSFX(SoundEffect* _effect); //just renamed the methods to make more sense
	Mix_Music* GetSDLMusic(Song* _song);

	//Members
	map<string, Mix_Chunk*> m_effects;
	map<string, Mix_Music*> m_songs;
	//NOTE: All the objects in this string are char pointers, pointing to a location on heap for each string.
	string m_currentEffects[MaxEffectChannels]; //defining an array to know which effect is being played on which channel. All the memory will be held on the stack.
	string m_musicLength;
	string m_musicTitle;
	Mix_Music* m_currentSong;
};

#endif //AUDIOCONTROLLER_H