#define _CRT_SECURE_NO_WARNINGS
#define MONKEY_VERSION "1.1"
#include <Windows.h>
#include <iostream>
#include <lua.hpp>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wldap32.Lib")
#pragma comment(lib, "ntdll.lib")
#define CURL_STATICLIB
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "Functions.h"
#include <tlhelp32.h>
#include <iomanip>
#include <thread>
#define CurlCallback writefunc
#pragma comment(lib, "urlmon.lib")
typedef std::string STRING;
typedef const char* CSTRING;