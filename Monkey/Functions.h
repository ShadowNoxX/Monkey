#pragma once
#include "Monkey.h"

int lua_infoBox(lua_State* L);
int lua_errorBox(lua_State* L);
int lua_httpGet(lua_State* L);
int lua_httpPost(lua_State* L);
int lua_printnoline(lua_State* L);
int lua_setTitle(lua_State* L);
int lua_setRemoteTitle(lua_State* L);
int lua_shutdown(lua_State* L);
int lua_pluginhelp(lua_State* L);
lua_State* giveState();