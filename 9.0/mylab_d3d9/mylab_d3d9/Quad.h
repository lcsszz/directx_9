#pragma once

/** ��������XZƽ���ƽ�� 
*/
class CQuad
{
	LPDIRECT3DDEVICE9		m_pDevice;

	/// ����
	LPDIRECT3DVERTEXBUFFER9 m_pMeshVertices;
	/// ����
	LPDIRECT3DTEXTURE9 m_pTexture;

	int		m_nNumVertsAlongX;
	int		m_nNumVertsAlongZ;
	float	m_fMeshLengthAlongX;
	float	m_fMeshLengthAlongZ;
	int		m_nMeshVertCount;

public:
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
	void Init( LPDIRECT3DDEVICE9 pDevice, float fSizeX, float fSizeZ);
	void Render(D3DXMATRIX& matWorld );

	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
};
