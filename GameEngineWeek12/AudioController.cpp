#include "AudioController.h"
#include "SoundEffect.h"
#include "Song.h"

AudioController::AudioController() {
	M_ASSERT((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0), "Failed to initialize Mix Audio");
	Mix_AllocateChannels(MaxEffectChannels); //letting SDL fill up to as many channels as in the parameters (in this case, 16)
	SoundEffect::Pool = new ObjectPool<SoundEffect>();
	m_currentSong = nullptr;
}

AudioController::~AudioController() {
	Shutdown();
}

SoundEffect* AudioController::LoadEffect(string _guid) {
	SoundEffect* effect = SoundEffect::Pool->GetResource();
	effect->Load(_guid);
	return effect;
}

Song* AudioController::LoadSong(string _guid) {
	SoundEffect* song = SoundEffect::Pool->GetResource();
	song->Load(_guid);
	return static_cast<Song*>(song); //here, we can tell if it is a song or not, which is why we dynamic cast.
}

void AudioController::Play(SoundEffect* _effect) {
	int channel; //defining a channel
	channel = Mix_PlayChannel(-1, GetSDLSFX(_effect), 0); //passing -1 as a parameter makes SDL choose which channel to use, either creating a new mix chunk, or getting the current one.
	if (channel == -1) return; // means all channels are playing a sound, and cannot play the sound itself.
	m_currentEffects[channel] = _effect->GetData()->GetGUID(); //if not, return the GUIDs
	Mix_ChannelFinished(AudioController::CatchChannelDone);
}

void AudioController::CatchChannelDone(int _channel) {
	AudioController::Instance().m_currentEffects[_channel] = ""; //
}

Mix_Chunk* AudioController::GetSDLSFX(SoundEffect* _effect) { //regardless of asset, create a mixed chunk
	Asset* asset = _effect->GetData();
	string guid = asset->GetGUID();
	if (m_effects.count(guid) == 0) {
		//If not found, create the SDL mix buffer
		SDL_RWops* rw = SDL_RWFromMem((void*)asset->GetData(), asset->GetDataSize());
		Mix_Chunk* audio = Mix_LoadWAV_RW(rw, 0);
		m_effects[guid] = audio;
	}
	return m_effects[guid];
}

void AudioController::Play(Song* _song) {
	m_currentSong = GetSDLMusic(_song);
	M_ASSERT(Mix_PlayMusic(m_currentSong, -1) != -1, "Failed to play Song");
	m_musicTitle = string(Mix_GetMusicTitle(m_currentSong));
	m_musicLength = to_string((int)Mix_MusicDuration(m_currentSong));
}

Mix_Music* AudioController::GetSDLMusic(Song* _song) {
	Asset* asset = _song->GetData();
	string guid = asset->GetGUID();
	if (m_songs.count(guid) == 0) {
		//If not found, create the SDL mix buffer
		SDL_RWops* rw = SDL_RWFromMem((void*)asset->GetData(), asset->GetDataSize());
		Mix_Music* audio = Mix_LoadMUS_RW(rw, 0);
		m_songs[guid] = audio;
	}

	return m_songs[guid];
}

void AudioController::StopMusic() {
	m_currentSong = nullptr;
	m_musicTitle = "";
	m_musicLength = "";
	Mix_HaltMusic();
}

void AudioController::PauseMusic() {
	Mix_PauseMusic();
}

void AudioController::ResumeMusic() {
	Mix_ResumeMusic();
}

double AudioController::MusicPosition() {
	if (m_currentSong == nullptr) return 0;
	return Mix_GetMusicPosition(m_currentSong);
}

void AudioController::Shutdown() {
	for (auto ie = m_effects.begin(); ie != m_effects.end(); ie++) {
		Mix_FreeChunk(ie->second);
	}
	m_effects.clear();

	for (auto is = m_songs.begin(); is != m_songs.end(); is++) {
		Mix_FreeMusic(is->second);
	}
	m_songs.clear();

	delete SoundEffect::Pool;
	SoundEffect::Pool = nullptr;

	Mix_Quit();
}