#pragma once
class CScene
{
public:
	LPDIRECT3DDEVICE9		m_pDevice;
	CScene(void);
	~CScene(void);

   virtual void Init( LPDIRECT3DDEVICE9 pDevice)=0;
   virtual void Update(float fElapsedTime)=0;
   virtual void Render()=0;
};

