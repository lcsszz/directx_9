#pragma once
class CLight
{
	D3DLIGHT9	m_light;	

public:
	CLight(void);
	~CLight(void);
	
	
	LightTypes m_lightType;
	LPDIRECT3DDEVICE9 m_pDevice;

	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Update(float fElapsedTime);
	void Render(float fElapsedTime);
	void Restore();
	//void HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

