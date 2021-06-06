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
int lua_bsod(lua_State* L);
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOption, PULONG Response);
size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s);