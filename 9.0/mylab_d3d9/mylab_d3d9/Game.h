#pragma once
#include "d3dx9.h"

class CCylinder;
class CBox;
class CQuad;
class CQuadInlight;
class CQuadSimple;
class CLight;

class CGame
{
	LPDIRECT3D9					m_pD3D;
	LPDIRECT3DDEVICE9			m_pDevice;
	D3DPRESENT_PARAMETERS		m_d3dpp;

	bool						m_bDeviceLost;  //�豸��ʧ
	bool						m_bRenderInWireFrame;
	/** ��ʼ��D3D�豸
	*/
	HRESULT _InitD3D(HWND hWnd);

	//////////////////////////////////////////////////////////////////////////
	CCylinder		*m_pCylinder;
	CBox			*m_pBox;
	//CQuad			*m_pQuad;
	CQuad			*m_pQuadInlight;
	CQuadSimple     *m_pQuadSimple;
	CLight			*m_pLight;
	//////////////////////////////////////////////////////////////////////////

public:
	CGame(void);
	~CGame(void);

	bool Init( HINSTANCE hInstance, HWND hWnd );
	
	void Update(float fElapsedTime);
	void Render(float fElapsedTime);

	void InvalidateDeviceObjects(void);  //�����豸��ʧ
	void RestoreDeviceObjects(void);
	void DrawScene(void);
	void HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
