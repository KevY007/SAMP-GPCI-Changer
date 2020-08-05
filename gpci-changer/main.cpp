#include "main.h"

DWORD				g_SAMP = NULL;
HANDLE				g_DllHandle;

bool				samp037 = false;

LONG GetStringRegKey(HKEY hKey, std::string strValueName, std::string& strValue, std::string strDefaultValue)
{
	strValue = strDefaultValue;
	CHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	ULONG nError;
	nError = RegQueryValueExA(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if (ERROR_SUCCESS == nError)
	{
		strValue = szBuffer;
	}
	return nError;
}

void ChangeGPCI()
{
	HKEY key;

	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\SAMP\\", &key) != ERROR_SUCCESS)
		return addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Unable to open registry at \"Software\\SAMP\\\"");
	
	string value;
	GetStringRegKey(key, "GPCI_SPECIAL", value, "");

	if (value.length() <= 1 || value.compare("") == 0)
	{
		value = "";
		for (int i = 0; i < 32; i++)
		{
			value += to_string(rand() % 9);
		}

		if (RegSetValueEx(key, "GPCI_SPECIAL", 0, REG_SZ, (LPBYTE)value.c_str(), strlen(value.c_str()) * sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Unable to set registry value at \"Software\\SAMP\\GPCI_SPECIAL\"");
		}
	}

	int i = 13181804;
	for (char& c : value)
	{
		if(i < 13181842)
		{
			*(int*)(i) = (int)c;
			i++;
		}
	}

	RegCloseKey(key);
	return;
}

void cmd_changegpci(char* param)
{
	HKEY key;
	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\SAMP\\", &key) != ERROR_SUCCESS)
		return addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Unable to open registry at \"Software\\SAMP\\\"");

	if (strlen(param) >= 1)
	{
		if (RegSetValueEx(key, "GPCI_SPECIAL", 0, REG_SZ, (LPBYTE)param, strlen(param) * sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Unable to set registry value at \"Software\\SAMP\\GPCI_SPECIAL\"");
		}

		addMessageToChatWindow(D3DCOLOR_XRGB(0x0A, 0xDC, 0x22), "GPCI Changed to special preference: %s", param);
		addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Effective after restart and remains forever as long as mod remains in your directory.");
		ChangeGPCI();
	}
	else
	{
		string randomval = "";
		for (int i = 0; i < 32; i++)
		{
			randomval += to_string(rand() % 9);
		}

		if (RegSetValueEx(key, "GPCI_SPECIAL", 0, REG_SZ, (LPBYTE)randomval.c_str(), strlen(randomval.c_str()) * sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Unable to set registry value at \"Software\\SAMP\\GPCI_SPECIAL\"");
		}

		addMessageToChatWindow(D3DCOLOR_XRGB(0, 255, 0x33), "GPCI Changed. You can also add text parameter so you can switch between old and new.");
		addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 255), "Effective after restart and remains forever as long as mod remains in your directory.");
		ChangeGPCI();
	}

	RegCloseKey(key);
	return;
}

void ThrMainFS() 
{
	while (g_SAMP == NULL)
	{
		g_SAMP = (DWORD)GetModuleHandleA("samp.dll");
	
		Sleep(2000);
	}

	bool initSampRak = false;
	while (true)
	{
		if (!initSampRak)
		{
			if (memcmp_safe((uint8_t*)g_SAMP + 0xBABE, hex_to_bin(SAMP037_CMP), 10))
			{
				samp037 = true;
			}
			else samp037 = false;

			if (samp037)
			{
				g_Chat037 = stGetSampChatInfo037();
				if (isBadPtr_writeAny(g_Chat037, sizeof(stChatInfo_037)))
				{
					continue;
				}

				g_Input037 = stGetInputInfo037();
				if (isBadPtr_writeAny(g_Input037, sizeof(stInputInfo_037)))
				{
					continue;
				}
			}
			else
			{
				g_Chat = stGetSampChatInfo();
				if (isBadPtr_writeAny(g_Chat, sizeof(stChatInfo)))
				{
					continue;
				}

			
				g_Input = stGetInputInfo();
				if (isBadPtr_writeAny(g_Input, sizeof(stInputInfo)))
				{
					continue;
				}
			}

			initSampRak = true;

			ChangeGPCI();

			addClientCommand("changegpci", cmd_changegpci);
		}
		if (initSampRak)
		{
			// Code if you wanna execute any. Put it in here so it doesn't execute before samp has loaded.
		}
		Sleep(100); // Adjust according to your needs
	}
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, 
	DWORD fdwReason,    
	LPVOID lpReserved) 
{

	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;

	if (GetModuleHandle("samp.dll"))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThrMainFS, NULL, 0, NULL);
	}

	return TRUE;
}