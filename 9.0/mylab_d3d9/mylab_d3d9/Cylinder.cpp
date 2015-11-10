#include "StdAfx.h"
#include "Cylinder.h"


CCylinder::CCylinder(void):
m_pDevice(NULL),
m_pVB(NULL)
{
}


CCylinder::~CCylinder(void)
{
	SAFE_RELEASE( m_pVB );
}

void CCylinder::Init( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevice = pDevice;
	
	//创顶点缓冲区
    m_pDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, CUSTOMVERTEX::FVF_Flags,
                                                  D3DPOOL_DEFAULT, &m_pVB, NULL ) ;
   
	//填充顶点缓冲区
    CUSTOMVERTEX* pVertices;
    m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(50-1);
        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
		pVertices[2*i+0].color   =0xffffff00;
        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
		pVertices[2*i+1].color   =0xffffff00;
    }
    m_pVB->Unlock();

	m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		//关闭光照处理, 默认情况下启用光照处理 环境光 没有材质的物体 显示黑色
    m_pDevice->SetRenderState( D3DRS_LIGHTING, true );
}

void CCylinder::Update()
{
	
	//建立一个绕X轴动态旋转的世界矩阵
    D3DXMATRIX matWorld;
    UINT  iTime  = timeGetTime() % 1000;
    FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixIdentity( &matWorld );
    D3DXMatrixRotationZ( &matWorld, fAngle);

	//设置世界矩阵
    m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );

	  //建立并设置观察矩阵
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt,
		&vLookatPt, &vUpVec );
    m_pDevice->SetTransform( D3DTS_VIEW, &matView );

    //建立并设置投影矩阵
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 
		1.0f, 1.0f, 100.0f );
    m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

}

void CCylinder::Render()
{
        m_pDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
        m_pDevice->SetFVF( CUSTOMVERTEX::FVF_Flags );
        m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );
}
