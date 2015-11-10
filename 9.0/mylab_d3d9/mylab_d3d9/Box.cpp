#include "StdAfx.h"
#include "Box.h"
#include "d3dx9.h"

#define new VNEW

CBox::CBox(void) :
m_pDevice(NULL),
m_pBoxVB(NULL),
m_pBoxIB(NULL)
{
}

CBox::~CBox(void)
{
	/*SAFE_RELEASE( m_pBoxVB );
	SAFE_RELEASE( m_pBoxIB );*/
}

void CBox::Init( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevice = pDevice;

	/*float fSize = 15.0f;*/
	BoxVertex cvVertices[] =
	{	
		//顶面
		{200.0f, 100.0f, 0.5f,1.0f, D3DCOLOR_XRGB(0, 0, 255),},		//Vertex 0 - Blue 
		{250.0f, 50.0f, 200.5f,1.0f,D3DCOLOR_XRGB(255, 0, 0),},		//Vertex 1 - Red 
		{400.0f, 100.0f, 0.5f,1.0f,D3DCOLOR_XRGB(255, 0, 0),},		//Vertex 2 - Red 
		{450.0f, 50.0f, 200.5f,1.0f, D3DCOLOR_XRGB(0, 255, 0),},		//Vertex 3 - Green 

		//底面
		{400.0f, 300.0f, 0.5f,1.0f, D3DCOLOR_XRGB(0, 255, 0),},		//Vertex 4 - Green 
		{450.0f, 250.0f, 200.5f,  1.0f,D3DCOLOR_XRGB(0, 0, 255),},		//Vertex 5 - Blue 
		{200.0f, 300.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0),},	//Vertex 6 - Red 
		{250.0f, 250.0f, 200.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0),},		//Vertex 7 - Green
	};

	m_pDevice->CreateVertexBuffer( sizeof( cvVertices), D3DUSAGE_WRITEONLY,
		BoxVertex::FVF_Flags, D3DPOOL_MANAGED, &m_pBoxVB, NULL);

	// 创建索引缓冲
	m_pDevice->CreateIndexBuffer( 36 * sizeof(WORD), D3DUSAGE_WRITEONLY, 
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pBoxIB, NULL );

	void* pBuffer = NULL;
	m_pBoxVB->Lock( 0, sizeof( cvVertices),&pBuffer,0 );
	memcpy( pBuffer, cvVertices, sizeof( cvVertices) );
	m_pBoxVB->Unlock();

	WORD wIndices[] ={ 0,1,2,1,3,2,
					   0,4,6,0,2,4,
					   2,5,4,2,3,5,
					   3,7,5,3,1,7,
					   1,6,7,1,0,6,
					   4,5,7,7,6,4 };
	WORD *pIndices = NULL;
	m_pBoxIB->Lock( 0, sizeof(wIndices), (void**)&pIndices, 0 );
	memcpy( pIndices, wIndices, sizeof(wIndices) ) ;
	m_pBoxIB->Unlock();
}

void CBox::Render()
{

	/*D3DXMATRIX matWorld;   //矩阵
	D3DXMatrixIdentity(&matWorld);*/  //单位化矩阵
	/*m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );*/
	//m_pDevice->SetRenderState( D3DRS_LIGHTING, false );
	m_pDevice->SetStreamSource( 0, m_pBoxVB, 0, sizeof(BoxVertex) );
	m_pDevice->SetIndices( m_pBoxIB );
	m_pDevice->SetFVF( BoxVertex::FVF_Flags );

	m_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12 );
	


}
