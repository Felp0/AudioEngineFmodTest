
#pragma once
#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

//Fmod includes for the engine
#include <fmod_studio.hpp>
#include <fmod.hpp>

//Standard library needed for the engine
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>

//Creating struct to place sound in 3D space
struct Vec3D
{
	float x;
	float y;
	float z;
};

//Creating struct for Implematation
//This is used to separete the calls from the game engine to prevent bugs
struct Implementation
{
	Implementation();
	~Implementation();

	void UpdateImplementation();

	FMOD::Studio::System* pStudioSystem;
	FMOD::System* pSystem;

	int m_NextChannelId;

	//Creating Maps
	typedef std::map <std::string, FMOD::Sound*> SoundMap;
	typedef std::map <int, FMOD::Channel*> ChannelMap;
	typedef std::map <std::string, FMOD::Studio::EventInstance*> EventMap;
	typedef std::map <std::string, FMOD::Studio::Bank*> BankMap;

	BankMap m_Banks;
	EventMap m_Events;
	SoundMap m_Sounds;
	ChannelMap m_Channels;
};

class AudioEngine
{
public:
	static void Init();
	static void Update();
	static void Shutdown();
	
	static int ErrorCheck(FMOD_RESULT result);

	void LoadBank(const std::string& stringBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void LoadEvent(const std::string& stringEventName);
	void LoadSound(const std::string& stringSoundName, bool bed = true, bool loop = false, bool stream = false);
	void UnloadSound(const std::string& stringSoundName);
	void Set3DListenerAndOrientation(const Vec3D& vPos = Vec3D{ 0,0,0 }, float volumeDB = 0.0f);
	void PlaySound(const std::string& stringSoundName, const Vec3D& vPos = Vec3D{ 0,0,0 }, float volumeDB = 0.0f);
	void PlayEvent(const std::string& stringEventName);
	void StopChannel(int channelID);
	void StopEvent(const std::string& stringEventName, bool immediate = false);
	void GetEventParameter(const std::string& stringEventName, const std::string& stringEventParameter, float* parameter);
	void SetEventParameter(const std::string& stringEventName, const std::string& stringParameterName, float value);
	void StopAllChannels();
	void SetChannel3DPosition(int channelID, const Vec3D& position);
	void SetChannelVolume(int channelID, float volumeDB);
	
	bool IsPlaying(int channelID) const;
	bool IsEventPlaying(const std::string& stringEventName) const;

	float DBToVolume(float DB);
	float VolumeToDB(float volume);

	FMOD_VECTOR VectorToFmod(const Vec3D& position);
};
#endif // !AUDIOENGINE_H

