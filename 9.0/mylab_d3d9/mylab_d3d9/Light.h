#pragma once
class CLight
{
	D3DLIGHT9	m_light;
	
	enum LightTypes
	{
		LIGHT_TYPE_DIRECTIONAL = 0,
		LIGHT_TYPE_SPOT,
		LIGHT_TYPE_POINT,
	};

	LightTypes m_lightType;

public:
	CLight(void);
	~CLight(void);

	LPDIRECT3DDEVICE9 m_pDevice;

	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Update(float fElapsedTime);
	void Render(float fElapsedTime);
	void Restore();
	void HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

