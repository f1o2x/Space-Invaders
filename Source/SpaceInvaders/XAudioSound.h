#pragma once
#include "stdafx.h"
class XAudioSound
{
private:
	IXAudio2* g_engine;
	IXAudio2SourceVoice* g_source;
	IXAudio2MasteringVoice* g_master;
	Wave buffer;
public:
	XAudioSound();
	void Init();
	void Stop();
	void LoadSound(char* path);

	void Start();
	void Update(bool loop);
	~XAudioSound();
};
