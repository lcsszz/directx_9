#include "StdAfx.h"
#include "QuadInlight.h"


CQuadInlight::CQuadInlight(void):
m_nNumVertsAlongX(32),
m_nNumVertsAlongZ(32),
m_fMeshLengthAlongX(10.0f),
m_fMeshLengthAlongZ(10.0f)
{
	m_nMeshVertCount = (m_nNumVertsAlongX - 1) * (m_nNumVertsAlongZ - 1) * 6;
}


CQuadInlight::~CQuadInlight(void)
{
}

void CQuadInlight::Init( LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	// 创建纹理
	D3DXCreateTextureFromFile(m_pDevice, L"Image//dx_logo.dds", &m_pTexture);

	float dX = 1.0f/(m_nNumVertsAlongX-1);
	float dZ = 1.0f/(m_nNumVertsAlongZ-1);

	int i = 0;
	int x = 0;
	int z = 0;
	
	m_pDevice->CreateVertexBuffer( m_nMeshVertCount*sizeof(QuadVertex),
								   D3DUSAGE_WRITEONLY, QuadVertex::FVF_Flags,
								   D3DPOOL_MANAGED, &m_pMeshVertices, NULL );


	QuadVertex *v;
	m_pMeshVertices->Lock( 0, 0, (void**)&v, 0 );
	for( i = 0; i < m_nMeshVertCount; ++i )
	{
		v[i].ny = 1.0f;

		v[i].nx = 0.0f;
		v[i].ny = 1.0f;
		v[i].nz = 0.0f;

		v[i].color = D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f);
	}

	// 初始化每一行
	for( z = 0, i = 0; z < (m_nNumVertsAlongZ-1); ++z )
	{
		for( x = 0; x < (m_nNumVertsAlongX-1); ++x )
		{
			// 1 ___ 2
			//  |  /|
			//  |/__|
			// 0

			// 0
			v[i].x = m_fMeshLengthAlongX * x * dX;
			v[i].z = m_fMeshLengthAlongZ * z * dZ;
			v[i].tu = x * dX;
			v[i].tv = z * dZ;
			++i;

			// 1
			v[i].x = m_fMeshLengthAlongX * x * dX;
			v[i].z = m_fMeshLengthAlongZ * (z+1) * dZ;
			v[i].tu = x * dX;
			v[i].tv = (z+1) * dZ;
			++i;

			// 2
			v[i].x = m_fMeshLengthAlongX * (x+1) * dX;
			v[i].z = m_fMeshLengthAlongZ * (z+1) * dZ;
			v[i].tu = (x+1) * dX;
			v[i].tv = (z+1) * dZ;
			++i;

			//   ___ 1
			//  |  /|
			//  |/__|
			// 0     2

			// 0
			v[i].x = m_fMeshLengthAlongX * x * dX; 
			v[i].z = m_fMeshLengthAlongZ * z * dZ;
			v[i].tu = x * dX;
			v[i].tv = z * dZ;
			++i;

			// 1
			v[i].x = m_fMeshLengthAlongX * (x+1) * dX;
			v[i].z = m_fMeshLengthAlongZ * (z+1) * dZ;
			v[i].tu = (x+1) * dX;
			v[i].tv = (z+1) * dZ;
			++i;

			// 2
			v[i].x = m_fMeshLengthAlongX * (x+1) * dX;  
			v[i].z = m_fMeshLengthAlongZ * z * dZ;
			v[i].tu = (x+1) * dX;
			v[i].tv = z * dZ;
			++i;
		}
	}

	m_pMeshVertices->Unlock();
}

void CQuadInlight::Render(D3DXMATRIX& matWorld )
{
	m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
	m_pDevice->SetStreamSource( 0, m_pMeshVertices, 0, sizeof(QuadVertex) );
	m_pDevice->SetFVF( QuadVertex::FVF_Flags );
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 5766 );
}