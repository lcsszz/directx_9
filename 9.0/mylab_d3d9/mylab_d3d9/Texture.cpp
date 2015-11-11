#include "StdAfx.h"
#include "Texture.h"


CTexture::CTexture(void):
m_pDevice(NULL),
m_pVB(NULL),
m_pTexture(NULL),
m_pTexture1(NULL),
m_pTexture2(NULL)
{

}

CTexture::~CTexture(void)
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pTexture1);
	SAFE_RELEASE(m_pTexture2);
}


HRESULT CTexture::InitGriphics(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice ;

	//创建纹理对象
	if( FAILED( D3DXCreateTextureFromFile( m_pDevice,L"texture.jpg",&m_pTexture ) ) )
    {
       MessageBox(NULL, L"创建纹理失败", L"Texture.exe", MB_OK);
       return E_FAIL;
    }

	//创建纹理1
    if( FAILED( D3DXCreateTextureFromFile(m_pDevice, L"texture1.bmp", &m_pTexture1)) )
    {
		MessageBox(NULL, L"创建纹理失败", L"Texture.exe", MB_OK);
		return E_FAIL;
    }

	//创建纹理2
    if( FAILED( D3DXCreateTextureFromFile(m_pDevice, L"texture2.bmp", &m_pTexture2)) )
    {
		return E_FAIL;
    }
	

	CUSTOMVERTEX m_Vertices[] =
    {
	    { -3,    3,  0.0f,  0.0f, 0.0f},	
	    {  3,    3,  0.0f,  2.0f, 0.0f },
        { -3,   -3,  0.0f,  0.0f, 2.0f},     //注意纹理坐标
        {  3,   -3,  0.0f,  2.0f, 2.0f}

    };

	//创建顶点缓冲区
    if( FAILED( m_pDevice->CreateVertexBuffer( 4*sizeof(CUSTOMVERTEX),//顶点缓冲区的大小
                                                 0,//指定顶点缓冲区的属性，它可以设置为0，为顶点缓冲区任意属性的组合
												 D3DFVF_CUSTOMVERTEX,//顶点的灵活顶点格式
                                                 D3DPOOL_MANAGED,//用于指定顶点缓冲区内存的类型
												 &m_pVB,//用于返回顶点缓冲区的地址。
												 NULL ) ) )//保留参数，一般设置为NULL
    {
        return E_FAIL;
    }

    //填充顶点缓冲区
    VOID* pVertices;
    if( FAILED( m_pVB->Lock( 0,//加锁内存起始地址
		sizeof(m_Vertices), //加锁内存的大小
		(void**)&pVertices,//用于返回内存指针地址
		0 ) ) )//顶点缓冲区的加锁属性，0为所有属性的任意值
        return E_FAIL;
    memcpy( pVertices, m_Vertices, sizeof(m_Vertices) );
    m_pVB->Unlock();

    return S_OK;
}

void  CTexture::Update()
{
	//创建并设置世界矩阵
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity( &matWorld );
    m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );

	//创建并设置观察矩阵
    D3DXVECTOR3 vEyePt( 0.0f, 0.0f, -10 );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );//底层生算法需要深究
    m_pDevice->SetTransform( D3DTS_VIEW, &matView );

	//创建并设置投影矩阵
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

}

void CTexture::Render()
{
	//m_pDevice->SetTexture( 0, m_pTexture ); //设置纹理
	m_pDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	m_pDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
}

void CTexture::SetTexture(int g_iTexAddressMode)
{
	switch(g_iTexAddressMode)
	{
	case 1:
		m_pDevice->SetTexture( 0, m_pTexture1 );  //设置纹理
	//	//设置纹理寻址模式
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;

	case 2:
		m_pDevice->SetTexture( 0, m_pTexture1 );  //设置纹理
		//设置纹理寻址模式
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
		break;

	case 3:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //设置纹理
		//设置纹理寻址模式
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
		
	case 4:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //设置纹理
		//设置边框颜色
		m_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff0000);
		//设置纹理寻址模式
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		break;

	case 5:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //设置纹理
		m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRRORONCE);
		m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_MIRRORONCE);
		break;

	case 6:
		    m_pDevice->SetTexture( 0, m_pTexture );  
			m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			break;

	case 7:
	  	     m_pDevice->SetTexture( 0, m_pTexture ); 
			m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			break;

	}
}