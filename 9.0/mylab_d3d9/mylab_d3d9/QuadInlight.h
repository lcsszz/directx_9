#pragma once
#include "quad.h"
class CQuadInlight :
	public CQuad
{
private:
	int		m_nNumVertsAlongX;
	int		m_nNumVertsAlongZ;
	float	m_fMeshLengthAlongX;
	float	m_fMeshLengthAlongZ;
	int		m_nMeshVertCount;

public:

	CQuadInlight(void);
	~CQuadInlight(void);
	virtual void Init( LPDIRECT3DDEVICE9 pDevice);
	virtual void Render(D3DXMATRIX& matWorld );
};

