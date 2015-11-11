#pragma once
class CLight
{
		

public:
	CLight(void);
	~CLight(void);
	
	D3DLIGHT9	m_light;
	LightTypes m_lightType;
	LPDIRECT3DDEVICE9 m_pDevice;

	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Update(float fElapsedTime);
	void Render();
	void Restore();
	//void HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

