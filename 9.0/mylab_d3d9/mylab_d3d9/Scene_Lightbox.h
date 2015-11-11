#pragma once
#include "Scene.h"

class CLight;
class CQuadInlight;

class CScene_Lightbox:
public CScene
{
	LPD3DXMESH	m_pSphereMesh; // ������ʾ���Դλ��
	LPD3DXMESH	m_pConeMesh;	// ������ʾƽ�й⼰�۹��
	CQuadInlight * m_pQuadInlight;

public:
	CLight * m_pLight;

	CScene_Lightbox(void);
	~CScene_Lightbox(void);

   virtual void Init( LPDIRECT3DDEVICE9 pDevice);
   virtual void Update(float fElapsedTime);
   virtual void Render();
};

