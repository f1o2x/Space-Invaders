#include "stdafx.h"

XAudioSound::XAudioSound()
{
	Init();
}
void XAudioSound::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//create the engine
	if (FAILED(XAudio2Create(&g_engine)))
	{
		CoUninitialize();
		MessageBox(0, L"XAudio2Create(&g_engine)", L"Error", MB_OK);
	}
	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		MessageBox(0, L"CreateMasteringVoice(&g_master)", L"Error", MB_OK);
	}
}
void XAudioSound::Stop()
{
	if (g_source)
		g_source->Stop();
}
void XAudioSound::LoadSound(char* path)
{
	//load a wave file
	if (!buffer.load(path))
	{
		g_engine->Release();
		CoUninitialize();
		MessageBox(0, L"!buffer.load(Path)", L"Error", MB_OK);
	}
	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		MessageBox(0, L"CreateSourceVoice(&g_source, buffer.wf()", L"Error", MB_OK);
	}
}

void XAudioSound::Start()
{
	//start consuming audio in the source voice
	g_source->Start();
}
void XAudioSound::Update(bool loop)
{
	g_source->FlushSourceBuffers();
	g_source->SubmitSourceBuffer(buffer.xaBuffer());
	if (!loop)
		g_source->ExitLoop();
}
XAudioSound::~XAudioSound()
{
	g_engine->Release();
	CoUninitialize();
}