#include "stdafx.h"
#include "Sound.h"

bool SoundManager::initialized = false;
bool SoundManager::backgroundPlaying = false;
FMOD::System* SoundManager::system;
FMOD::Channel* SoundManager::bgMusic;
std::vector<FMOD::Sound*> SoundManager::sounds;

//Creates the FMOD system
SoundManager::SoundManager()
{
	FMOD::System_Create(&system);		// Create the main system object.	
	system->init(100, FMOD_INIT_NORMAL, 0);
	initialized = true;
}


//Releases the system
SoundManager::~SoundManager()
{
	system->release();
}

//Loads and plays a sound effect at the filepath once
void SoundManager::playSound(const char* filePath)
{
	if(!initialized)
	{
		FMOD::System_Create(&system);
		system->init(100, FMOD_INIT_NORMAL, 0);
		initialized = true;
	}
	FMOD::Sound *sound;
	FMOD_RESULT result=system->createSound(filePath, FMOD_DEFAULT, 0, &sound);
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, 0);
}

//Loads and streams a sound effect at the filepath once
void SoundManager::streamSound(const char* filePath)
{
	if(!initialized)
	{
		FMOD::System_Create(&system);
		system->init(100, FMOD_INIT_NORMAL, 0);
		initialized = true;
	}
	FMOD::Sound *sound;
	FMOD_RESULT result=system->createStream(filePath, FMOD_DEFAULT, 0, &sound);
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, 0);
}

//An update method that should be called once a frame
void SoundManager::update()
{
	system->update();
}

//A method to play background music. The music will loop continually, and only one song can be played
//at a time
void SoundManager::loopMusic(const char* filePath)
{
	if(!initialized)
	{
		FMOD::System_Create(&system);
		system->init(100, FMOD_INIT_NORMAL, 0);
		initialized = true;
	}

	if(backgroundPlaying)
	{
		//Stop the background before starting the new song
		stopMusic();
	}
	FMOD::Sound *sound;
	FMOD_RESULT result = system->createStream(filePath, FMOD_DEFAULT, 0, &sound);
	sound->setMode(FMOD_LOOP_NORMAL);
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &bgMusic);
	backgroundPlaying = true;
}

//Stops the background music
void SoundManager::stopMusic()
{
	bgMusic->stop();
}