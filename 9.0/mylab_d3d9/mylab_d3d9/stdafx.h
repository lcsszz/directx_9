// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>

#include <d3d9.h>
#include <d3dx9.h>

// TODO: 在此处引用程序需要的其他头文件
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)     { if(p) { (p)->Release(); (p)=NULL; }}
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

enum LightTypes
{
LIGHT_TYPE_DIRECTIONAL = 0,
LIGHT_TYPE_SPOT,
LIGHT_TYPE_POINT,
};