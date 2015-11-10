// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <mmsystem.h>

#include <d3d9.h>
#include <d3dx9.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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