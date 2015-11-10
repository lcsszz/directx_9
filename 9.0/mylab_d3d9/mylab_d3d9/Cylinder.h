#pragma once

class CCylinder
{
public:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3 position;
		DWORD color;

		enum FVF
		{
			FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE
		};
	};
public:
	CCylinder(void);
	~CCylinder(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DDEVICE9 m_pDevice;

	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Update();
	void Render( );
};

