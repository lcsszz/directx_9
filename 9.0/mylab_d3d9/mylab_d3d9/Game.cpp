#include "StdAfx.h"
#include "Game.h"
#include "Cylinder.h"
#include "Box.h"
#include "Quad.h"

CGame::CGame(void) :
m_pD3D(NULL),
m_pDevice(NULL),
m_bDeviceLost(false),
m_pCylinder(NULL)
{
}

CGame::~CGame(void)
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pDevice);

	SAFE_DELETE(m_pCylinder);
}

bool CGame::Init( HINSTANCE hInstance, HWND hWnd )
{
	// COM��ʼ��
	CoInitialize(NULL);

	if(FAILED(_InitD3D(hWnd)))
		return false;

	m_pCylinder = new CCylinder;
	m_pCylinder->Init(m_pDevice);

	m_pBox = new CBox;
	m_pBox->Init(m_pDevice);

	m_pQuad = new CQuad;
	m_pQuad->Init(m_pDevice,27.0,27.0);

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
	//�����޸�
	D3DXMATRIX matRroj;  //ͶӰ����
	D3DXMatrixPerspectiveFovLH( &matRroj, D3DX_PI/4, 4.f/3.f, 1.f, 1000.0f ); //�Ž� ��߱� ������� ��Զ����
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matRroj);
	// �����Ӿ���
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3(13.0f, 13.0f, 13.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	 //�����������ϵ                                 ���                                                  �յ�                                            y��
	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
//	m_pCylinder->Update();    //ԲͲ����ת
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
//	m_pQuad->Render();
	
	DrawScene();
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

void CGame::DrawScene(void)
{
//===================================================================//

	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matRotate;

	// ���Ƶ���
	D3DXMatrixTranslation( &matTrans, -5.0f, -5.0f, -5.0f );
	D3DXMatrixRotationZ( &matRotate, 0.0f );
	matWorld = matRotate * matTrans;
	m_pQuad->Render( matWorld );

	// ����ǽ��
	D3DXMatrixTranslation( &matTrans, -5.0f,5.0f, -5.0f );
	D3DXMatrixRotationZ( &matRotate, -D3DXToRadian(90.0) );
	matWorld = matRotate * matTrans;
	m_pQuad->Render( matWorld );

	// ����ǽ��
	D3DXMatrixTranslation( &matTrans, -5.0f, 5.0f, -5.0f );
	D3DXMatrixRotationX( &matRotate,  D3DXToRadian(90.0) );
	matWorld = matRotate * matTrans;
	m_pQuad->Render( matWorld );
}
