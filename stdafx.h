// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>

#include <atlctrlw.h>
#include <atlctrlxp.h>

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <fex/fex.h>

#include <nes_emu/Nes_Recorder.h>
#include <nes_emu/Nes_Effects_Buffer.h>
#include <nes_emu/Nes_Mapper.h>
#include <nes_emu/nes_util.h>
#include "std_file_u.h"

#include "../nes_ntsc/Nes_Blitter.h"

#include "ZapFC/database.h"

#include <cmath>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace std
{
#ifdef UNICODE
	typedef wstring        tstring;
	typedef wistringstream tistringstream;
	typedef wostringstream tostringstream;
#else
	typedef string         tstring;
	typedef istringstream  tistringstream;
	typedef ostringstream  tostringstream;
#endif
}
