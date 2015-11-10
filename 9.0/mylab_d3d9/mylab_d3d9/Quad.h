#pragma once

/** 建立处于XZ平面的平面 
*/
class CQuad
{
public:
	LPDIRECT3DDEVICE9		m_pDevice;

	/// 顶点
	LPDIRECT3DVERTEXBUFFER9 m_pMeshVertices;
	/// 纹理
	LPDIRECT3DTEXTURE9 m_pTexture;

	struct QuadVertex
	{
		float x, y, z;
		float nx,ny,nz;
		DWORD color;
		float tu, tv;


		enum FVF
		{
			FVF_Flags = D3DFVF_XYZ|D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1
		};
	};


	CQuad(void);
	~CQuad(void);

	/** 初始化
		@param
			fSizeX X方向大小
		@param
			fSizeZ Z方向大小
		@param
			nType 初始朝向类型 0-X轴方向,1-Y轴方向,2-Z轴方向
	*/
   virtual void Init( LPDIRECT3DDEVICE9 pDevice)=0;
   virtual void Render(D3DXMATRIX& matWorld )=0;

	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
};
