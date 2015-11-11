#pragma once
#include "d3dx9.h"

class CTexture
{

public:
	struct CUSTOMVERTEX
{
	FLOAT x, y, z;    //����λ��  
	FLOAT u,v ;		  //������������
	};
#define D3DFVF_CUSTOMVERTEX   (D3DFVF_XYZ|D3DFVF_TEX1)
	
	CTexture(void);
	~CTexture(void);

	LPDIRECT3DVERTEXBUFFER9   m_pVB;
	LPDIRECT3DDEVICE9				  m_pDevice;
	LPDIRECT3DTEXTURE9			  m_pTexture; 
	LPDIRECT3DTEXTURE9			  m_pTexture1;  //�������
	LPDIRECT3DTEXTURE9			  m_pTexture2;
	int        g_iTexAddressMode;

	HRESULT   InitGriphics(LPDIRECT3DDEVICE9 pDevice);
	void Update();
	void Render();
	void SetTexture(int g_iTexAddressMode);
};

