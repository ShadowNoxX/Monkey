#include "Monkey.h"

bool isUpdated() {
	CSTRING url = "https://thefakewater.github.io/latest.txt";
	CURL* curl = curl_easy_init();
	STRING response;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	response.erase(std::remove(response.begin(), response.end(), '\n'), response.end());
	if (response != MONKEY_VERSION) {
		return false;
	}
	return true;
}
int Update() {
	if (!isUpdated()) {
		rename("Monkey.exe", "Monkey.old");
		LPCTSTR Url = L"https://thefakewater.github.io/Monkey.exe";
		LPCTSTR File = L"Monkey.exe";
		URLDownloadToFile(0, Url, File, 0, 0);
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(L"Monkey.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		exit(0);
		return 0;
	}
	std::remove("Monkey.old");
	return 0;
}
void init() {
	Update();
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "InfoBox", lua_infoBox);
	lua_register(L, "ErrorBox", lua_errorBox);
	lua_register(L, "HttpGet", lua_httpGet);
	lua_register(L, "HttpPost", lua_httpPost);
	lua_register(L, "printnoline", lua_printnoline);
	lua_register(L, "SetTitle", lua_setTitle);
	lua_register(L, "SetRemoteTitle", lua_setRemoteTitle);
	STRING version = MONKEY_VERSION;
	STRING instruction = "VERSION=";
	version = instruction + version;
	luaL_dostring(L, version.c_str());
	int r = luaL_dofile(L, "script.mkey");
	if (r != LUA_OK) {
		MessageBoxA(GetConsoleWindow(), lua_tostring(L, -1), "Monkey Engine", MB_ICONERROR);
	}
}

int main() {
	init();
	return 0;
}