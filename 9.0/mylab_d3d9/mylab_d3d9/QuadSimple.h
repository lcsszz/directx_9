#pragma once
#include "quad.h"
class CQuadSimple :
	public CQuad
{
public:
	CQuadSimple(void);
	~CQuadSimple(void);

   virtual void Init( LPDIRECT3DDEVICE9 pDevice);
   virtual void Render(D3DXMATRIX& matWorld );
};

