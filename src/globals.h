#pragma once

#define ISOLATION_AWARE_ENABLED		1

#define GDIPVER	0x0110

#include <windows.h>
#include <mlang.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <shlwapi.h>
#include <litehtml.h>
#include <winhttp.h>
#include <algorithm>

#include "dib.h"  // simpledib

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "gdiplus.lib")