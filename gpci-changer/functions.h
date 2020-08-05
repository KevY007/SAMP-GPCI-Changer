#pragma once

#include "main.h"

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

// maps unsigned 8 bits/channel to D3DCOLOR // Copied from d3d9types with love.
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_XYUV(y,u,v)   D3DCOLOR_ARGB(0xff,y,u,v)
#define D3DCOLOR_AYUV(a,y,u,v) D3DCOLOR_ARGB(a,y,u,v)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))

#pragma pack(push, 1)


enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 2100,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_MAPICONS = 100,
};

struct stChatInfo_037
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	void* chatEntry[100];
	void* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
	int					m_iTimeStampTextOffset;
};

typedef void(__cdecl* CMDPROC037) (PCHAR);
struct stInputInfo_037
{
	void* pD3DDevice;
	void* pDXUTDialog;
	void* pDXUTEditBox;
	CMDPROC037			pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC037				pszDefaultCMD;
};

struct stChatInfo
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	void*	chatEntry[100];
	void* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo
{
	void* pD3DDevice;
	void* pDXUTDialog;
	void* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

enum ChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

// FUNCTIONS

extern struct stSAMP* g_stSAMP;
extern struct stChatInfo* g_Chat;
extern struct stInputInfo* g_Input;

extern struct stSAMP_037* g_stSAMP037;
extern struct stChatInfo_037* g_Chat037;
extern struct stInputInfo_037* g_Input037;


static signed char hex_to_dec(signed char ch);
uint8_t* hex_to_bin(const char* str);
int memcpy_safe(void* _dest, const void* _src, uint32_t len, int check = NULL, const void* checkdata = NULL);
int memcmp_safe(const void* _s1, const void* _s2, uint32_t len);
bool isBadPtr_writeAny(void* pointer, ULONG size);
bool isBadPtr_readAny(void* pointer, ULONG size);
bool isBadPtr_handlerAny(void* pointer, ULONG size, DWORD dwFlags);
struct stChatInfo* stGetSampChatInfo(void);
struct stInputInfo* stGetInputInfo(void);
struct stChatInfo_037* stGetSampChatInfo037(void);
struct stInputInfo_037* stGetInputInfo037(void);
void addToChatWindow(char* text, D3DCOLOR textColor);
void addMessageToChatWindow(D3DCOLOR col, const char* text, ...);
void addClientCommand(char* name, CMDPROC function);