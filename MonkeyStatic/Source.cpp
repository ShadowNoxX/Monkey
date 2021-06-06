#include "Monkey.h"

void init() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "InfoBox", lua_infoBox);
	lua_register(L, "ErrorBox", lua_errorBox);
	lua_register(L, "HttpGet", lua_httpGet);
	lua_register(L, "HttpPost", lua_httpPost);
	lua_register(L, "printnoline", lua_printnoline);
	lua_register(L, "SetTitle", lua_setTitle);
	lua_register(L, "SetRemoteTitle", lua_setRemoteTitle);
	lua_register(L, "shutdown", lua_shutdown);
	lua_register(L, "bsod", lua_bsod);
	lua_pushstring(L, MONKEY_VERSION);
	lua_setglobal(L, "VERSION");
	std::string script;
	HRSRC hRes;
	hRes = FindResource(0, MAKEINTRESOURCE(IDR_TEXT1), L"Text");
	if (NULL != hRes)
	{
		HGLOBAL hData = LoadResource(0, hRes);
		if (NULL != hData)
		{
			DWORD dataSize = SizeofResource(0, hRes);
			char* data = (char*)LockResource(hData);
			script.assign(data, dataSize);
		}
	}
	int r = luaL_dostring(L, script.c_str());
	if (r != LUA_OK) {
		MessageBoxA(GetConsoleWindow(), lua_tostring(L, -1), "Monkey Engine", MB_ICONERROR);
	}
}

int main() {
	init();
	return 0;
}