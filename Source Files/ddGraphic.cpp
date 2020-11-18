
#include	"ddGraphic.h"
#include	"DealDominator.h"			// CAPTION

//--------------------------------------------------------------
//--------------------------------------------------------------

// direct 3D
D3DDISPLAYMODE						DDGraphic::mDispMode;
D3DPRESENT_PARAMETERS			DDGraphic::mParam;

// direct 3D device
LPDIRECT3D9								DDGraphic::mD3D;
LPDIRECT3DDEVICE9					DDGraphic::mD3DD;

// shader
LPDIRECT3DVERTEXSHADER9		DDGraphic::mVS;
LPDIRECT3DPIXELSHADER9		DDGraphic::mPS;

DGdrawMode								DDGraphic::mDrawMode;

// matrix
DCmtx				DDGraphic::mVM;
DCmtx				DDGraphic::mPM;
DCmtx				DDGraphic::mVPM;
DCmtx				DDGraphic::mSM;

// light
DCvec				DDGraphic::mLightV;

// primitive vertex list

// full screen copy
DDG_VTXFMT_PT	DDGraphic::mOrthoScreenTriangleStripList[ 4 ] =
{
	//	x					y					z					u					v
	{	-1.0f,		+1.0f,		0.0f,			0.0f,			0.0f	},		// ����
	{	-1.0f,		-1.0f,		0.0f,			0.0f,			1.0f	},		// ����
	{	+1.0f,		+1.0f,		0.0f,			1.0f,			0.0f	},		// �E��
	{	+1.0f,		-1.0f,		0.0f,			1.0f,			1.0f	},		// �E��
};

// offset screen copy ( overwrite x, y )
DDG_VTXFMT_PT	DDGraphic::mOrthoOffsetTriangleStripList[ 4 ] =
{
	//	x					y					z					u					v
	{	-1.0f,		+1.0f,		0.0f,			0.0f,			0.0f	},		// ����
	{	-1.0f,		-1.0f,		0.0f,			0.0f,			1.0f	},		// ����
	{	+1.0f,		+1.0f,		0.0f,			1.0f,			0.0f	},		// �E��
	{	+1.0f,		-1.0f,		0.0f,			1.0f,			1.0f	},		// �E��
};

// outer frame line ( overwrite dif )
DDG_VTXFMT_PD	DDGraphic::mOrthoOuterFrameLineStripList[ 5 ] =
{
	//	x					y					z					dif
	{	-1.0f,		+1.0f,		0.0f,			D3DCOLOR_RGBA( 0, 0, 0, 0 )	},		// ����
	{	-1.0f,		-1.0f,		0.0f,			D3DCOLOR_RGBA( 0, 0, 0, 0 )	},		// ����
	{	+1.0f,		-1.0f,		0.0f,			D3DCOLOR_RGBA( 0, 0, 0, 0 )	},		// �E��
	{	+1.0f,		+1.0f,		0.0f,			D3DCOLOR_RGBA( 0, 0, 0, 0 )	},		// �E��
	{	-1.1f,		+1.0f,		0.0f,			D3DCOLOR_RGBA( 0, 0, 0, 0 )	},		// ���� �Ȃ���1pixel�`����Ȃ�
};

//--------------------------------------------------------------
//--------------------------------------------------------------

DDbool	DDGraphic::dgGraphicInitial( DDvoid )
{
	int					adapter;
	
	//---------------------------
	
	mD3D  = NULL;
	mD3DD = NULL;
	
	mVS = NULL;
	mPS = NULL;
	
	mDrawMode = DG_DRAW_MODE_DEFAULT;
	
	mVM .dcIdentity();
	mPM .dcIdentity();
	mVPM.dcIdentity();
	
	mLightV = dcYn();
	
	//---------------------------
	
	// Direct3D �I�u�W�F�N�g���쐬
	DXTRACE_MSG( "Direct3D �I�u�W�F�N�g�쐬" );
	
	mD3D = Direct3DCreate9( D3D_SDK_VERSION );
	
	if( !mD3D )
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox( NULL, "Direct3D �̍쐬�Ɏ��s", "Base", MB_OK | MB_ICONSTOP );
		
		// �I������
		return	true;
	}
	
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;
	
	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	DXTRACE_MSG( "�E�C���h�E�̍쐬�����������̂ŁADirect3D ������������" );
	
	D3DPRESENT_PARAMETERS		d3dpp;
	
	ZeroMemory( &d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );
	
	// ���݂̉�ʃ��[�h���擾
	mD3D->GetAdapterDisplayMode( adapter, &mDispMode );
	
	// Direct3D �������p�����[�^�̐ݒ�
	#if	( FULLSCREEN )
	{
		// �t���X�N���[��
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
//	d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		
		// �\���̈�T�C�Y�̐ݒ�
		d3dpp.BackBufferWidth  = (u32)WIDTH;
		d3dpp.BackBufferHeight = (u32)HEIGHT;
		d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	}
	#else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		d3dpp.BackBufferFormat = mDispMode.Format;
		
		// �\���̈�T�C�Y�̐ݒ�
		d3dpp.BackBufferWidth  = (u32)WIDTH;
		d3dpp.BackBufferHeight = (u32)HEIGHT;
		d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;		// D3DSWAPEFFECT_FLIP;
		
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}
	#endif

	
	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	mParam = d3dpp;
	
	// �f�o�C�X�̍쐬 - T&L HAL
	DXTRACE_MSG( "�f�o�C�X�̍쐬 - T&L HAL" );
	
	if( FAILED( mD3D->CreateDevice( adapter, D3DDEVTYPE_HAL, ddgThis()->ddGetH_wnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DD ) ) )
	{
		// ���s�����̂� HAL �Ŏ��s
		DXTRACE_MSG( "���s�����̂� HAL �Ŏ��s" );
		
		if( FAILED( mD3D->CreateDevice( adapter, D3DDEVTYPE_HAL, ddgThis()->ddGetH_wnd(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DD ) ) )
		{
			// ���s�����̂� REF �Ŏ��s
			DXTRACE_MSG( "���s�����̂� REF �Ŏ��s" );
			
			if( FAILED( mD3D->CreateDevice( adapter, D3DDEVTYPE_REF, ddgThis()->ddGetH_wnd(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DD ) ) )
			{
				// ���ǎ��s����
				MessageBox( NULL, "Direct3D �̏������Ɏ��s", CAPTION, MB_OK | MB_ICONSTOP );
				
				ddRELEASE( mD3D );
				
				// �I������
				return	true;
			}
		}
	}
	
	
	// setup default view and perspective matrix
	{
		RECT			rect;
		DCvec			view;
		DCvec			v0;
		DCvec			v1;
		
		GetClientRect( ddgThis()->ddGetH_wnd(), &rect );
		
		dcVLoad( view, 0.0f, 0.0f, +20.0f );
		
		dcVLoad( v0, 0.f, 0.f, 0.f );
		dcVLoad( v1, 0.f, 1.f, 0.f );
		
		D3DXMatrixLookAtRH( &mVM, &view, &v0, &v1 );
		D3DXMatrixPerspectiveFovRH( &mPM, D3DXToRadian( 45.f ), (f32)rect.right / (f32)rect.bottom, 1.0f, 500.0f );
		mD3DD->SetTransform( D3DTS_VIEW, &mVM );
		mD3DD->SetTransform( D3DTS_PROJECTION, &mPM );
	}
	
	// setup default render state
	mD3DD->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	
	mD3DD->SetRenderState( D3DRS_LIGHTING, TRUE );
	mD3DD->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
	mD3DD->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
	mD3DD->SetRenderState( D3DRS_AMBIENT, 0x40404040 );
	
	mD3DD->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	mD3DD->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	
	return	false;
}

//--------------------------------------------------------------

DDbool	DDGraphic::dgGraphicDispose( DDvoid )
{
	ddRELEASE( mPS );
	ddRELEASE( mVS );
	
	// release direct3D object
	ddRELEASE( mD3DD );
	ddRELEASE( mD3D );
	
	return	false;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	DDGraphic::dgSetVS( LPDIRECT3DVERTEXSHADER9 vs )
{
	mVS = vs;
	
	mD3DD -> SetVertexShader( vs );
}

//--------------------------------------------------------------

DDvoid	DDGraphic::dgSetPS( LPDIRECT3DPIXELSHADER9 ps )
{
	mPS = ps;
	
	mD3DD -> SetPixelShader( ps );
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	DDGraphic::dgDraw( DCmtx& M, LPD3DXMESH Mesh, s32 SubSet )
{
	s32			i;
	
	
	// �V�F�[�_�ɍ��킹���萔�f�[�^�ݒ�
	switch( mDrawMode )
	{
		default:		ddASSERT( true );		break;
		
		
		// disable vertex/pixel shader
		case	DG_DRAW_MODE_DEFAULT:
			dggD() -> SetTransform( D3DTS_WORLD, &M );
			break;
		
		
		// Matrix44
		case	DG_DRAW_MODE_M44:
			{
				DCmtx				m;

				// transform matrix [ c0_c3 ]
				m.dcLoadM( mVPM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 0, &m.dcM( 0, 0 ), 4 );
			}
			break;
		
		
		// Matrix44, Light
		case	DG_DRAW_MODE_M44L:
			{
				DCmtx				m;
				DCvec				v;
				
				// transform matrix [ c0_c3 ]
				m.dcLoadM( mVPM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 0, &m.dcM( 0, 0 ), 4 );
				
				// local light vector [ c4 ]
				M.dcM33xV( mLightV, v );
				ddASSERT( dcNormSqr( v ) <= SQR( 0.99f )  ||  dcNormSqr( v ) >= SQR( 1.01f ) );
				dggD() -> SetVertexShaderConstantF( 4, (f32*)&v, 1 );
			}
			break;
		
		
		// Matrix44, Light, Shadow44
		case	DG_DRAW_MODE_M44LS44:
			{
				DCmtx				m;
				DCvec				v;
				
				// transform matrix [ c0_c3 ]
				m.dcLoadM( mVPM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 0, &m.dcM( 0, 0 ), 4 );
				
				// local light vector [ c4 ]
				M.dcM33xV( mLightV, v );
				ddASSERT( dcNormSqr( v ) <= SQR( 0.99f )  ||  dcNormSqr( v ) >= SQR( 1.01f ) );
				dggD() -> SetVertexShaderConstantF( 4, (f32*)&v, 1 );
				
				// shadow matrix [ c8_c11 ]
				m.dcLoadM( mSM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 8, &m.dcM( 0, 0 ), 4 );
			}
			break;
		
		
		// Matrix44, Light, Shadow44, World44
		case	DG_DRAW_MODE_M44LS44W44:
			{
				DCmtx				m;
				DCvec				v;
				
				// transform matrix [ c0_c3 ]
				m.dcLoadM( mVPM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 0, &m.dcM( 0, 0 ), 4 );
				
				// local light vector [ c4 ]
				M.dcM33xV( mLightV, v );
				ddASSERT( dcNormSqr( v ) <= SQR( 0.99f )  ||  dcNormSqr( v ) >= SQR( 1.01f ) );
				dggD() -> SetVertexShaderConstantF( 4, (f32*)&v, 1 );
				
				// shadow matrix [ c8_c11 ]
				m.dcLoadM( mSM );
				m.dcINxM( M );
				m.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 8, &m.dcM( 0, 0 ), 4 );
				
				// world ( cube map ) matrix [ c16_c19 ]
				M.dcTranspose( m );
				dggD() -> SetVertexShaderConstantF( 16, &m.dcM( 0, 0 ), 4 );
			}
			break;
	}
	
	// draw model
	for( i=0 ; i < SubSet ; i++ )
	{
		Mesh -> DrawSubset( i );
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	DDGraphic::dgRenderOrthoFullScreen( DDvoid )
{
	dggD()->BeginScene();
	{
		dggD()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2,
			mOrthoScreenTriangleStripList, sizeof( DDG_VTXFMT_PT ) );
	}
	dggD()->EndScene();
}

//--------------------------------------------------------------
// Xofs Yofs = offset pixel / screen size

DDvoid	DDGraphic::dgRenderOrthoFullScreen( f32 Xofs, f32 Yofs )
{
	s32					i;
	
	// �S��ʃ��X�g�{�I�t�Z�b�g
	for( i = 0 ; i != 4 ; i++ )
	{
		mOrthoOffsetTriangleStripList[ i ].x = mOrthoScreenTriangleStripList[ i ].x + Xofs;
		mOrthoOffsetTriangleStripList[ i ].y = mOrthoScreenTriangleStripList[ i ].y + Yofs;
	}
	
	dggD()->BeginScene();
	{
		dggD()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2,
			mOrthoOffsetTriangleStripList, sizeof( DDG_VTXFMT_PT ) );
	}
	dggD()->EndScene();
}

//--------------------------------------------------------------

DDvoid	DDGraphic::dgRenderOrthoOuterFrame( f32 RWidth, f32 RHeight, DWORD Diffuse )
{
	s32					i;
	
	// �F�ݒ�
	for( i = 0 ; i != 5 ; i++ )
	{
		mOrthoOuterFrameLineStripList[ i ].dif = Diffuse;
	}
	
	// ���W���P�s�N�Z������ʓ��ɕ␳�@�E�Ɖ�
	mOrthoOuterFrameLineStripList[ 1 ].y = -1.0f + RHeight;
	
	mOrthoOuterFrameLineStripList[ 2 ].x = +1.0f - RWidth;
	mOrthoOuterFrameLineStripList[ 2 ].y = -1.0f + RHeight;
	
	mOrthoOuterFrameLineStripList[ 3 ].x = +1.0f - RWidth;
	
	// �`��
	dggD()->BeginScene();
	{
		dggD()->DrawPrimitiveUP( D3DPT_LINESTRIP, 4,
			mOrthoOuterFrameLineStripList, sizeof( DDG_VTXFMT_PD ) );
	}
	dggD()->EndScene();
}

