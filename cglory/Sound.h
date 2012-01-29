//#include "stdafx.h"
#include <vector>
#include "fmod.hpp"
#include "fmod_errors.h"

class SoundManager
{


	//----------------------Variables-------------------------
private:
	static FMOD::System *system;				//The sound system used by FMOD
	static bool initialized;					//Whether or not the system has been initialized
	static bool backgroundPlaying;				//Whether or not there is background music currently playing
	static FMOD::Channel *bgMusic;				//A pointer to the channel playing the background music. Used to stop the music
	static std::vector<FMOD::Sound*> sounds;	//A vector to hold pre-loaded sounds

	//----------------------Methods---------------------------
public: 
	SoundManager();
	~SoundManager();
	static void playSound(const char* filePath);	//Plays a sound once
	static void streamSound(const char* filePath);	//Streams a sound once. Should be used for anything more than a few seconds
	static void loopMusic(const char* filePath);	//Loops background music
	static void stopMusic();						//Stops looping background music
	void update();									//Should be called once a frame for FMOD
private:
	};