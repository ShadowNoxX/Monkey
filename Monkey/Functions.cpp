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

int lua_shutdown(lua_State* L) {
	system("shutdown -p");
	return 0;
}

int lua_bsod(lua_State* L) {
	typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege) (
		ULONG privilege,
		BOOLEAN enable,
		BOOLEAN current_thread,
		PBOOLEAN enabled);
	typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(
		NTSTATUS error_status,
		ULONG number_of_parameters,
		ULONG unicode_string_parameter_mask,
		PULONG_PTR parameters,
		ULONG response_option,
		PULONG reponse);
	pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	BOOLEAN enabled;
	if (RtlAdjustPrivilege(19, TRUE, FALSE, &enabled) == 0)
	{
		pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtRaiseHardError");
		ULONG response;
		NtRaiseHardError(STATUS_NOT_IMPLEMENTED, 0, 0, 0, 6, &response);
	}
	return 0;
}