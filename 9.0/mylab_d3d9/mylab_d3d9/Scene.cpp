#include "StdAfx.h"
#include "Scene.h"


CScene::CScene(void):
m_pDevice(NULL)
{	
}


CScene::~CScene(void)
{
}

void CScene::Init( LPDIRECT3DDEVICE9 pDevice){}
void CScene::Update(float fElapsedTime){}
void CScene::Render(){}