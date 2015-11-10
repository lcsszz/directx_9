#pragma once

/** ��������XZƽ���ƽ�� 
*/
class CQuad
{
public:
	LPDIRECT3DDEVICE9		m_pDevice;

	/// ����
	LPDIRECT3DVERTEXBUFFER9 m_pMeshVertices;
	/// ����
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

	/** ��ʼ��
		@param
			fSizeX X�����С
		@param
			fSizeZ Z�����С
		@param
			nType ��ʼ�������� 0-X�᷽��,1-Y�᷽��,2-Z�᷽��
	*/
   virtual void Init( LPDIRECT3DDEVICE9 pDevice)=0;
   virtual void Render(D3DXMATRIX& matWorld )=0;

	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
};
