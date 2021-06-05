#include "Monkey.h"

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
	s->append(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

int lua_httpGet(lua_State* L) {
	CSTRING url = lua_tostring(L, 1);
	CURL* curl = curl_easy_init();
	if (curl) {
		STRING response;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		CURLcode res = curl_easy_perform(curl);
		lua_pushstring(L, response.c_str());
		curl_easy_cleanup(curl);
	}
	return 1;
}

int lua_httpPost(lua_State* L) {
	CSTRING url = lua_tostring(L, 1);
	CSTRING data = lua_tostring(L, 2);
	CSTRING contentType = lua_tostring(L, 3);
	if (!contentType) {
		contentType = "*/*";
	}
	CURL* curl = curl_easy_init();
	if (curl) {
		STRING response;
		struct curl_slist* headers = NULL;
		STRING s = contentType;
		STRING contentTypeA = "Content-Type: " + s;
		headers = curl_slist_append(headers, contentTypeA.c_str());
		headers = curl_slist_append(headers, "charset: utf-8");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		CURLcode res = curl_easy_perform(curl);
		lua_pushstring(L, response.c_str());
		curl_easy_cleanup(curl);
	}
	return 1;
}
int lua_infoBox(lua_State* L) {
	CSTRING caption = lua_tostring(L, 1);
	CSTRING title = lua_tostring(L, 2);
	MessageBoxA(NULL, title, caption, MB_ICONINFORMATION);
	return 0;
}

int lua_errorBox(lua_State* L) {
	CSTRING caption = lua_tostring(L, 1);
	CSTRING title = lua_tostring(L, 2);
	MessageBoxA(NULL, title, caption, MB_ICONERROR);
	return 0;
}

int lua_printnoline(lua_State* L) {
	CSTRING string = lua_tostring(L, 1);
	std::cout << string;
	return 0;
}

int lua_setTitle(lua_State* L) {
	CSTRING title = lua_tostring(L, 1);
	HWND hWindow = GetConsoleWindow();
	SetWindowTextA(hWindow, title);
	return 0;
}

int lua_setRemoteTitle(lua_State* L) {
	CSTRING windowName = lua_tostring(L, 1);
	CSTRING newWindowName = lua_tostring(L, 2);
	HWND hWindow = FindWindowA(NULL, windowName);
	SetWindowTextA(hWindow, newWindowName);
	return 0;
}

int lua_loadstring(lua_State* L) {
	int r = luaL_loadstring(L, lua_tostring(L, 1));
	lua_pushnumber(L, r);
	return 1;
}