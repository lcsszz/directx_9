#include "StdAfx.h"
#include "QuadSimple.h"


CQuadSimple::CQuadSimple(void)
{
}


CQuadSimple::~CQuadSimple(void)
{
}

void CQuadSimple::Init( LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	// 创建纹理
	D3DXCreateTextureFromFile(m_pDevice, L"Image//dx_logo.dds", &m_pTexture);
	
	//顶点数据
    QuadVertex g_Vertices[] =
    {
		{ -10,   -10,  0.0f, 0.0f, 1.0f, 0.0, 0xffffff, 0.0f, 1.0f},   
	    { -10,    10,  0.0f, 0.0f, 1.0f, 0.0, 0xffffff, 0.0f, 0.0f},	
	    {  10,   -10,  0.0f, 0.0f, 1.0f, 0.0, 0xffffff, 1.0f, 1.0f},	
	    {  10,    10,  0.0f, 0.0f, 1.0f, 0.0, 0xffffff, 1.0f, 0.0f}
    };

	
	m_pDevice->CreateVertexBuffer( 4*sizeof(QuadVertex),
								   D3DUSAGE_WRITEONLY, QuadVertex::FVF_Flags,
								   D3DPOOL_MANAGED, &m_pMeshVertices, NULL );


	QuadVertex *v;
	m_pMeshVertices->Lock( 0, sizeof(g_Vertices), (void**)&v, 0 );
	memcpy( v, g_Vertices, sizeof(g_Vertices));
	m_pMeshVertices->Unlock();
}

void CQuadSimple::Render(D3DXMATRIX& matWorld )
{
	m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
	m_pDevice->SetStreamSource( 0, m_pMeshVertices, 0, sizeof(QuadVertex) );
	m_pDevice->SetFVF( QuadVertex::FVF_Flags );
	m_pDevice->SetTexture(0, m_pTexture);
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}