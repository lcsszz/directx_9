#pragma once

class CBox
{
public:
struct BoxVertex
	{
		float x, y, z,rhw;
		DWORD color;

		enum FVF
		{
			FVF_Flags = D3DFVF_XYZRHW | D3DFVF_DIFFUSE
		};
	};

public:
	CBox(void);
	~CBox(void);

	/// 方盒VertexBuffer
	LPDIRECT3DVERTEXBUFFER9 m_pBoxVB;
	/// 方盒IndexBuffer，此处组织为Triangle Stirp
	LPDIRECT3DINDEXBUFFER9 m_pBoxIB;

	LPDIRECT3DDEVICE9 m_pDevice;

	
	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Render( );
};
