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

	//�����������
	if( FAILED( D3DXCreateTextureFromFile( m_pDevice,L"texture.jpg",&m_pTexture ) ) )
    {
       MessageBox(NULL, L"��������ʧ��", L"Texture.exe", MB_OK);
       return E_FAIL;
    }

	//��������1
    if( FAILED( D3DXCreateTextureFromFile(m_pDevice, L"texture1.bmp", &m_pTexture1)) )
    {
		MessageBox(NULL, L"��������ʧ��", L"Texture.exe", MB_OK);
		return E_FAIL;
    }

	//��������2
    if( FAILED( D3DXCreateTextureFromFile(m_pDevice, L"texture2.bmp", &m_pTexture2)) )
    {
		return E_FAIL;
    }
	

	CUSTOMVERTEX m_Vertices[] =
    {
	    { -3,    3,  0.0f,  0.0f, 0.0f},	
	    {  3,    3,  0.0f,  2.0f, 0.0f },
        { -3,   -3,  0.0f,  0.0f, 2.0f},     //ע����������
        {  3,   -3,  0.0f,  2.0f, 2.0f}

    };

	//�������㻺����
    if( FAILED( m_pDevice->CreateVertexBuffer( 4*sizeof(CUSTOMVERTEX),//���㻺�����Ĵ�С
                                                 0,//ָ�����㻺���������ԣ�����������Ϊ0��Ϊ���㻺�����������Ե����
												 D3DFVF_CUSTOMVERTEX,//����������ʽ
                                                 D3DPOOL_MANAGED,//����ָ�����㻺�����ڴ������
												 &m_pVB,//���ڷ��ض��㻺�����ĵ�ַ��
												 NULL ) ) )//����������һ������ΪNULL
    {
        return E_FAIL;
    }

    //��䶥�㻺����
    VOID* pVertices;
    if( FAILED( m_pVB->Lock( 0,//�����ڴ���ʼ��ַ
		sizeof(m_Vertices), //�����ڴ�Ĵ�С
		(void**)&pVertices,//���ڷ����ڴ�ָ���ַ
		0 ) ) )//���㻺�����ļ������ԣ�0Ϊ�������Ե�����ֵ
        return E_FAIL;
    memcpy( pVertices, m_Vertices, sizeof(m_Vertices) );
    m_pVB->Unlock();

    return S_OK;
}

void  CTexture::Update()
{
	//�����������������
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity( &matWorld );
    m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );

	//���������ù۲����
    D3DXVECTOR3 vEyePt( 0.0f, 0.0f, -10 );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );//�ײ����㷨��Ҫ�
    m_pDevice->SetTransform( D3DTS_VIEW, &matView );

	//����������ͶӰ����
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    m_pDevice->SetTransform( D3DTS_PROJECTION, &matProj );

}

void CTexture::Render()
{
	//m_pDevice->SetTexture( 0, m_pTexture ); //��������
	m_pDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
	m_pDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
}

void CTexture::SetTexture(int g_iTexAddressMode)
{
	switch(g_iTexAddressMode)
	{
	case 1:
		m_pDevice->SetTexture( 0, m_pTexture1 );  //��������
	//	//��������Ѱַģʽ
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;

	case 2:
		m_pDevice->SetTexture( 0, m_pTexture1 );  //��������
		//��������Ѱַģʽ
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
		break;

	case 3:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //��������
		//��������Ѱַģʽ
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
		
	case 4:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //��������
		//���ñ߿���ɫ
		m_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0xffff0000);
		//��������Ѱַģʽ
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		break;

	case 5:
		m_pDevice->SetTexture( 0, m_pTexture2 );  //��������
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