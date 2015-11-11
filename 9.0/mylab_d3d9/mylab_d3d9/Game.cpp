#include "StdAfx.h"
#include "Game.h"
#include "Cylinder.h"
#include "Box.h"
#include "Light.h"
#include "Scene_Lightbox.h"


CGame::CGame(void) :
m_pD3D(NULL),
m_pDevice(NULL),
m_bDeviceLost(false),
m_bRenderInWireFrame(false),
m_pScene_Lightbox(NULL)
{
}

CGame::~CGame(void)
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pDevice);
	SAFE_DELETE(m_pScene_Lightbox);
//	SAFE_DELETE(m_pCylinder);
}

bool CGame::Init( HINSTANCE hInstance, HWND hWnd )
{
	// COM��ʼ��
	CoInitialize(NULL);

	if(FAILED(_InitD3D(hWnd)))
		return false;

	m_pScene_Lightbox = new CScene_Lightbox;
	m_pScene_Lightbox->Init(m_pDevice);

	return true;
}

HRESULT CGame::_InitD3D(HWND hWnd)
{
	// COM interface
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// current display mode
	D3DDISPLAYMODE d3ddm;
	if( FAILED(m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	RECT rect;
	GetClientRect(hWnd, &rect);  //��ȡ�û�����

	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.BackBufferWidth = rect.right - rect.left;
	m_d3dpp.BackBufferHeight = rect.bottom - rect.top;
	//m_d3dpp.BackBufferWidth = d3ddm.Width;
	//m_d3dpp.BackBufferHeight = d3ddm.Height;
	m_d3dpp.hDeviceWindow = hWnd;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.EnableAutoDepthStencil = TRUE;   

	// Create D3D Device  
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3dpp, &m_pDevice ) ) )
	{
		return E_FAIL;
	}
	
	//�����޸�
	D3DXMATRIX matRroj;  //ͶӰ����
	D3DXMatrixPerspectiveFovLH( &matRroj, D3DX_PI/4, 1.f, 1.f, 500.0f ); //�Ž� ��߱� ������� ��Զ����
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matRroj);

	// �����Ӿ���
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3(0.0f, 0.0f, -50.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	 //�����������ϵ             ���                                 �յ�                             y��
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);

	//����
	//RECT rect;
	//GetClientRect(hWnd,&rect);
	D3DVIEWPORT9 vp;
	vp.X      = 0;
	vp.Y      = 0;
	vp.Width  = rect.right;
	vp.Height = rect.bottom;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;
	m_pDevice->SetViewport(&vp);

	return S_OK;
}

void CGame::Update(float fElapsedTime)
{

//	m_pCylinder->Update();    //ԲͲ����תht
	m_pScene_Lightbox->Update(fElapsedTime);
}

void CGame::Render(float fElapsedTime)
{
	// ��ÿ����Ⱦǰ�ж��Ƿ����豸��ʧ
	HRESULT hr;

	// �󱸻��������봰�ڴ�Сһ�²�����ȷ���D3DERR_DEVICENOTRESET
	// ������ϵͳЭ���㼶ֻ�ܻ��D3DERR_DEVICELOST
	if( m_bDeviceLost == true )
	{
		Sleep( 100 ); // 100 milliseconds
		// ���ϵͳЭ���㼶��ϵͳ���Ը��ݺ�������ֵ�ж��豸��ʧʱ��ȡ�Ĵ�ʩ
		if( FAILED( hr = m_pDevice->TestCooperativeLevel() ) )
		{
			if( hr == D3DERR_DEVICELOST )
				return;

			// �豸��ʧ�ܹ����Զ����ã���ʱ�򷵻ؽ����ٴγ���
			if( hr == D3DERR_DEVICENOTRESET )
			{
				// ����ڴ���Դ
				InvalidateDeviceObjects();
				// ����Reset���������豸
				hr = m_pDevice->Reset( &m_d3dpp );
				if( FAILED(hr ) )
					return;
				// ���������ڴ���Դ�������
				RestoreDeviceObjects();

				return;
			}
		}
		m_bDeviceLost = false;
	}

	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
					  D3DCOLOR_XRGB(0,50,128), 1.0f, 0 );

	m_pDevice->BeginScene();
//	m_pCylinder->Render();
//	m_pBox->Render();
	m_pScene_Lightbox->Render();
	m_pDevice->EndScene();

	hr = m_pDevice->Present( NULL, NULL, NULL, NULL );
	if( hr == D3DERR_DEVICELOST )
		m_bDeviceLost = true;
}

void CGame::InvalidateDeviceObjects(void)
{
}

void CGame::RestoreDeviceObjects(void)
{
}

//void CGame::DrawScene(void)
//{
////===================================================================//
//
//	D3DXMATRIX matWorld;
//	D3DXMATRIX matTrans;
//	D3DXMATRIX matRotate;
//
//	// ���Ƶ���
//	D3DXMatrixTranslation( &matTrans, -5.0f, -5.0f, -5.0f );
//	D3DXMatrixRotationZ( &matRotate, 0.0f );
//	matWorld = matRotate * matTrans;
//	m_pQuadInlight->Render( matWorld );
//	//m_pQuadSimple->Render(matWorld);
//
//	// ����ǽ��
//	D3DXMatrixTranslation( &matTrans, -5.0f,5.0f, -5.0f );
//	D3DXMatrixRotationZ( &matRotate, -D3DXToRadian(90.0) );
//	matWorld = matRotate * matTrans;
//	m_pQuadInlight->Render( matWorld );
//
//	// ����ǽ��
//	D3DXMatrixTranslation( &matTrans, -5.0f, 5.0f, -5.0f );
//	D3DXMatrixRotationX( &matRotate,  D3DXToRadian(90.0) );
//	matWorld = matRotate * matTrans;
//	m_pQuadInlight->Render( matWorld );
//
//	//���ù�Դ��λ�úͷ���
//  if( m_pLight->m_lightType == LIGHT_TYPE_POINT )
//	{
//		// ����λ��
//		D3DXMatrixTranslation( &matWorld, m_pLight->m_light.Position.x, m_pLight->m_light.Position.y,m_pLight->m_light.Position.z );
//		m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
//		//m_pDevice->SetTexture(0, NULL);
//		//m_pSphereMesh->DrawSubset(0);
//	}
//	else
//	{
//		// ����λ�ü�����
//		D3DXVECTOR3 vecFrom( m_pLight->m_light.Position.x, m_pLight->m_light.Position.y, m_pLight->m_light.Position.z );
//		D3DXVECTOR3 vecAt( m_pLight->m_light.Position.x + m_pLight->m_light.Direction.x, 
//						   m_pLight->m_light.Position.y + m_pLight->m_light.Direction.y,
//						   m_pLight->m_light.Position.z + m_pLight->m_light.Direction.z );
//		D3DXVECTOR3 vecUp( 0.0f, 1.0f, 0.0f );
//		D3DXMATRIX matWorldInv;
//		D3DXMatrixLookAtLH( &matWorldInv, &vecFrom, &vecAt, &vecUp);
//		D3DXMatrixInverse( &matWorld, NULL, &matWorldInv);
//		m_pDevice->SetTransform( D3DTS_WORLD, &matWorld );
//		//m_pDevice->SetTexture(0, NULL);
//		//m_pConeMesh->DrawSubset(0);
//	}
//}
//
void CGame::HandleMessage(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
			m_pScene_Lightbox->m_pLight->m_lightType = LIGHT_TYPE_DIRECTIONAL;
			break;

		case '2':
			m_pScene_Lightbox->m_pLight->m_lightType = LIGHT_TYPE_SPOT;
			break;

		case '3':
			m_pScene_Lightbox->m_pLight->m_lightType = LIGHT_TYPE_POINT;
			break;

		case VK_F1:
			m_bRenderInWireFrame = !m_bRenderInWireFrame;
			if( m_bRenderInWireFrame == true )
				m_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
			else
				m_pDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
			break;
		}
		break;
	}
}