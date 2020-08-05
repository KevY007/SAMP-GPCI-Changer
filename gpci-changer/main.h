#pragma once

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdio>
#include <stdio.h>
#include <memory>
#include <string>
#include <queue>

#include "functions.h"

using namespace std;

extern DWORD g_SAMP;
extern HANDLE g_DllHandle;
extern bool samp037;


#define SAMP037_CMP									"F8036A004050518D4C24"

#define SAMP037_CHAT_INFO_OFFSET					0x21A0E4
#define SAMP037_CHAT_INPUT_INFO_OFFSET				0x21A0E8

#define SAMP037_FUNC_ADDTOCHATWND					0x64010
#define SAMP037_FUNC_ADDCLIENTCMD					0x65AD0



#define SAMP_CHAT_INFO_OFFSET						0x2ACA10
#define SAMP_CHAT_INPUT_INFO_OFFSET					0x2ACA14

#define SAMP_FUNC_ADDTOCHATWND						0x67650
#define SAMP_FUNC_ADDCLIENTCMD						0x691B0