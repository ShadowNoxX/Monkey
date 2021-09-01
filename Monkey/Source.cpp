#include "Monkey.h"

lua_State* L;

lua_State* giveState() {
	lua_getglobal(L, "ASYNCIO");
	return L;
}

void init() {
	L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "InfoBox", lua_infoBox);
	lua_register(L, "ErrorBox", lua_errorBox);
	lua_register(L, "HttpGet", lua_httpGet);
	lua_register(L, "HttpPost", lua_httpPost);
	lua_register(L, "printnoline", lua_printnoline);
	lua_register(L, "SetTitle", lua_setTitle);
	lua_register(L, "SetRemoteTitle", lua_setRemoteTitle);
	lua_register(L, "shutdown", lua_shutdown);
	lua_register(L, "pluginhelp", lua_pluginhelp);
	lua_pushstring(L, MONKEY_VERSION);
	lua_setglobal(L, "VERSION");
	lua_pop(L, -1);
	int r = luaL_dofile(L, "script.mkey");
	if (r != LUA_OK) {
		MessageBoxA(GetConsoleWindow(), lua_tostring(L, -1), "Monkey Engine", MB_ICONERROR);
	}
}

int main() {
	init();
	return 0;
}