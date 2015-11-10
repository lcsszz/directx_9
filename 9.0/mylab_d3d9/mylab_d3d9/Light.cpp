#include "StdAfx.h"
#include "Light.h"


CLight::CLight(void)
{
}


CLight::~CLight(void)
{
}

void CLight::Init( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevice = pDevice;

	// 设置材质
	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = 1.0f;
	mtrl.Diffuse.g = 1.0f;
	mtrl.Diffuse.b = 1.0f;
	mtrl.Diffuse.a = 1.0f;
	mtrl.Ambient.r = 1.0f;
	mtrl.Ambient.g = 1.0f;
	mtrl.Ambient.b = 1.0f;
	mtrl.Ambient.a = 1.0f;
	m_pDevice->SetMaterial( &mtrl );

	// 照亮表示灯光的物体
	D3DLIGHT9 light_0;
	ZeroMemory( &light_0, sizeof(D3DLIGHT9) );
	light_0.Type = D3DLIGHT_DIRECTIONAL;
	light_0.Direction = D3DXVECTOR3( 0.0f, -0.5f, 0.0f );
	light_0.Diffuse.r = 1.0f;
	light_0.Diffuse.g = 1.0f;
	light_0.Diffuse.b = 1.0f;
	m_pDevice->SetLight( 0, &light_0 );

	// 照亮墙面
	D3DLIGHT9 light_1;
	ZeroMemory( &light_1, sizeof(D3DLIGHT9) );
	light_1.Type = D3DLIGHT_DIRECTIONAL;
	light_1.Direction = D3DXVECTOR3( 0.3f, -0.5f, 0.2f );
	light_1.Diffuse.r = 0.25f;
	light_1.Diffuse.g = 0.25f;
	light_1.Diffuse.b = 0.25f;
	m_pDevice->SetLight( 1, &light_1 );

	// Light #2 will be the demo light used to light the floor and walls. 
	// It will be set up in render() since its type can be changed at 
	// run-time.

	// 设置环境光
	m_pDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_COLORVALUE( 0.25, 0.25, 0.25, 1.0 ) );
}

void CLight::Update(float fElapsedTime)
{
	float x = sinf( fElapsedTime * 2.000f );
	float y = sinf( fElapsedTime * 2.246f );
	float z = sinf( fElapsedTime * 2.640f );

	ZeroMemory( &m_light, sizeof(D3DLIGHT9) );

	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Range     = 100.0f;

	switch( m_lightType )
	{
	case LIGHT_TYPE_DIRECTIONAL:
		{
			m_light.Type      = D3DLIGHT_DIRECTIONAL;
			m_light.Direction = D3DXVECTOR3( x, y, z );
		}
		break;

	case LIGHT_TYPE_SPOT:
		{
			m_light.Type         = D3DLIGHT_SPOT;
			m_light.Position     = 2.0f * D3DXVECTOR3( x, y, z );
			m_light.Direction    = D3DXVECTOR3( x, y, z );
			m_light.Theta        = 0.5f;
			m_light.Phi          = 1.0f;
			m_light.Falloff      = 1.0f;
			m_light.Attenuation0 = 1.0f;
		}
		break;

	case LIGHT_TYPE_POINT:
		{
			m_light.Type         = D3DLIGHT_POINT;
			m_light.Position     = 4.5f * D3DXVECTOR3( x, y, z );
			m_light.Attenuation1 = 0.4f;
		}
		break;
	}

	m_pDevice->SetLight( 2, &m_light );
}

void CLight::Render(float fElapsedTime)
{
	// 关闭灯光0，打开灯光1、2以便照亮墙体和地面
	m_pDevice->LightEnable( 0, FALSE );
	m_pDevice->LightEnable( 1, TRUE );
	m_pDevice->LightEnable( 2, TRUE );
}

void CLight::Restore()
{	
	// 打开灯光0，关闭灯光1、2
	m_pDevice->LightEnable( 0, TRUE );
	m_pDevice->LightEnable( 1, FALSE );
	m_pDevice->LightEnable( 2, FALSE );
}

void CLight::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
			m_lightType = LIGHT_TYPE_DIRECTIONAL;
			break;

		case '2':
			m_lightType = LIGHT_TYPE_SPOT;
			break;

		case '3':
			m_lightType = LIGHT_TYPE_POINT;
			break;

		}
		break;
	}
}