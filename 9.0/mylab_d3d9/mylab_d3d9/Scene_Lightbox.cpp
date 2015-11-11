#include "StdAfx.h"
#include "Scene_Lightbox.h"
#include "Light.h"
#include "QuadInlight.h"

CScene_Lightbox::CScene_Lightbox(void):
m_pLight(NULL),
m_pQuadInlight(NULL)
{
}

CScene_Lightbox::~CScene_Lightbox(void)
{	
	SAFE_RELEASE( m_pSphereMesh );
	SAFE_RELEASE( m_pConeMesh );
}

void CScene_Lightbox::Init( LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	m_pLight = new CLight;
	m_pLight->Init(m_pDevice);

	m_pQuadInlight = new CQuadInlight;
	m_pQuadInlight->Init(m_pDevice);

	D3DXCreateSphere( m_pDevice, 0.25f, 20, 20, &m_pSphereMesh, NULL );
	D3DXCreateCylinder( m_pDevice, 0.0f, 0.25f, 0.5f, 20, 20, &m_pConeMesh, NULL );

	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

}

void CScene_Lightbox::Update(float fElapsedTime)
{	
	//�����޸�
	D3DXMATRIX matRroj;  //ͶӰ����
	D3DXMatrixPerspectiveFovLH( &matRroj, D3DX_PI/4, 4.f/3.f, 1.f, 500.0f ); //�Ž� ��߱� ������� ��Զ����
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matRroj);

	// �����Ӿ���
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3(13.0f, 13.0f, 13.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	 //�����������ϵ             ���                                 �յ�                             y��
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	m_pLight->Update(fElapsedTime);
}

void CScene_Lightbox::Render()
{
	m_pLight->Render();

	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRotate;

	// ���Ƶ���
	D3DXMatrixTranslation( &matTrans, -5.0f, -5.0f, -5.0f );
	D3DXMatrixRotationZ( &matRotate, 0.0f );
	matWorld = matRotate * matTrans;
	m_pQuadInlight->Render( matWorld );
	//m_pQuadSimple->Render(matWorld);

	// ����ǽ��
	D3DXMatrixTranslation( &matTrans, -5.0f,5.0f, -5.0f );
	D3DXMatrixRotationZ( &matRotate, -D3DXToRadian(90.0) );
	matWorld = matRotate * matTrans;
	m_pQuadInlight->Render( matWorld );

	// ����ǽ��
	D3DXMatrixTranslation( &matTrans, -5.0f, 5.0f, -5.0f );
	D3DXMatrixRotationX( &matRotate,  D3DXToRadian(90.0) );
	matWorld = matRotate * matTrans;
	m_pQuadInlight->Render( matWorld );

	//���ù�Դ��λ�úͷ���
  if( m_pLight->m_lightType == LIGHT_TYPE_POINT )
	{
		// ����λ��
		D3DXMatrixTranslation( &matWorld, m_pLight->m_light.Position.x, m_pLight->m_light.Position.y,m_pLight->m_light.Position.z );
		m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
		m_pDevice->SetTexture(0, NULL);
		m_pSphereMesh->DrawSubset(0);
	}
	else
	{
		// ����λ�ü�����
		D3DXVECTOR3 vecFrom( m_pLight->m_light.Position.x, m_pLight->m_light.Position.y, m_pLight->m_light.Position.z );
		D3DXVECTOR3 vecAt( m_pLight->m_light.Position.x + m_pLight->m_light.Direction.x, 
						   m_pLight->m_light.Position.y + m_pLight->m_light.Direction.y,
						   m_pLight->m_light.Position.z + m_pLight->m_light.Direction.z );
		D3DXVECTOR3 vecUp( 0.0f, 1.0f, 0.0f );
		D3DXMATRIX matWorldInv;
		D3DXMatrixLookAtLH( &matWorldInv, &vecFrom, &vecAt, &vecUp);
		D3DXMatrixInverse( &matWorld, NULL, &matWorldInv);
		m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
		m_pDevice->SetTexture(0, NULL);
		m_pConeMesh->DrawSubset(0);
	}
}
