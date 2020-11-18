
#include	"s98dsVision.h"

#include	"ddGraphic.h"
#include	"ddInput.h"

#include	"gtTerraBox.h"
#include	"gtTestObject.h"
#include	"gtTestObject0.h"
#include	"gtTestObject1.h"
#include	"gtTestObject2.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

#define		S98DV_SHADOW_SIZE			( 512.f )

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S98DSVision::dvVisionInitial( DDvoid )
{
	HRESULT		res;
	
	// null clear coaster list
	DSVision::dvVisionInitial();
	
	// set light 0
	{
		D3DLIGHT9		light;
		DCvec				v;
		
		ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
		
		light.Type       = D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r  = 0.8f;
		light.Diffuse.g  = 0.8f;
		light.Diffuse.b  = 0.8f;
		light.Diffuse.a  = 0.0f;
		light.Specular.r = 1.0f;
		light.Specular.g = 1.0f;
		light.Specular.b = 1.0f;
		light.Specular.a = 0.0f;
		light.Ambient.r  = 0.2f;
		light.Ambient.g  = 0.2f;
		light.Ambient.b  = 0.2f;
		light.Ambient.a  = 0.0f;
		
		// light direction
		dcVLoad( v, -5.0f,  -30.0f,   -10.0f );
		dcNormalize( v );
		light.Direction = v;
		
		DDGraphic::dgLightV() = v;
		
		// set light enable
		dggD() -> SetLight( 0, &light );
		dggD() -> LightEnable( 0, TRUE );
	}
	
	// render texture surface
	mpRenderTexture = NULL;
	mpRenderZBuffer = NULL;
	
	res = dggD()->CreateTexture(
		(u32)S98DV_SHADOW_SIZE,
		(u32)S98DV_SHADOW_SIZE,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_G16R16F,					// D3DFMT_G16R16
		D3DPOOL_DEFAULT,
		&mpRenderTexture,
		NULL );
	ddFAILED( res );
	
	res = dggD()->CreateDepthStencilSurface(
		(u32)S98DV_SHADOW_SIZE,
		(u32)S98DV_SHADOW_SIZE,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&mpRenderZBuffer,
		NULL );
	ddFAILED( res );
	
	// load texture
	res = D3DXCreateTextureFromFileEx( dggD(), "DDResource/Floor.bmp",
						D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
						0, D3DFMT_R5G6B5, D3DPOOL_MANAGED,
						D3DX_DEFAULT, D3DX_DEFAULT, 0,
						NULL, NULL, &mpBallTex );
	ddFAILED( res );
	
	res = D3DXCreateTextureFromFileEx( dggD(), "DDResource/BtnPause.bmp",
						D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
						0, D3DFMT_R5G6B5, D3DPOOL_MANAGED,
						D3DX_DEFAULT, D3DX_DEFAULT, 0,
						NULL, NULL, &mpCubeTex );
	ddFAILED( res );
	
	// create vertex shader
	{
		LPD3DXBUFFER			pCode;
		
		// depth shadow pass 0
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_DepthShadow0.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_DepthShadowP0 );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// depth shadow pass 1
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_DepthShadow1.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_DepthShadowP1 );
		ddFAILED( res );
		ddRELEASE( pCode );
	}
	
	// create pixel shader
	{
		LPD3DXBUFFER			pCode;
		
		// depth shadow pass 0
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_DepthShadow0.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_DepthShadowP0 );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// depth shadow pass 1
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_DepthShadow1.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_DepthShadowP1 );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// depth shadow pass 1 soft
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_DepthShadow1Soft.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_DepthShadowP1Soft );
		ddFAILED( res );
		ddRELEASE( pCode );
	}
	
	
	// light and view angle
	mLM.dcIdentity();
	mVM.dcIdentity();
	
	mLV = dcZero();
	mVV = dcZero();
	
	mVV.x = _128PI;
	mVV.y = _96PI;
	
	mCount = 0;
	mSoftShadow = false;
	
	// entry da plot coasters
	(DDvoid)new GTDVCTestObject();
	
	(DDvoid)new GTDVCTestObject0();
	(DDvoid)new GTDVCTestObject1();
	
	(DDvoid)new GTDVCTestObject2();
	(DDvoid)new GTDVCTerraBox();
}

//-------------------------------------------------------------------

DDvoid	S98DSVision::dvVisionDispose( DDvoid )
{
	// release pixel shader
	ddRELEASE( mPS_DepthShadowP1Soft );
	ddRELEASE( mPS_DepthShadowP1 );
	ddRELEASE( mPS_DepthShadowP0 );
	DDGraphic::dgSetPS( NULL );
	
	// release vertex shader
	ddRELEASE( mVS_DepthShadowP1 );
	ddRELEASE( mVS_DepthShadowP0 );
	DDGraphic::dgSetVS( NULL );
	DDGraphic::dgSetDrawMode( DG_DRAW_MODE_DEFAULT );
	
	// release texture
	ddRELEASE( mpCubeTex );
	ddRELEASE( mpBallTex );
	
	// release render texture
	ddRELEASE( mpRenderTexture );
	ddRELEASE( mpRenderZBuffer );
	
	// delete coasters
	DSVision::dvVisionDispose();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S98DSVision::dvVisionProcess( DDvoid )
{
	HRESULT		res;
	DCmtx			tvm;
	DCmtx			tpm;
	DCmtx			m;
	DCvec			e;
	DCvec			c;
	DCvec			u;
	
	LPDIRECT3DSURFACE9	pBackBuf;
	LPDIRECT3DSURFACE9	pZBuffer;
	LPDIRECT3DSURFACE9	pSurface;
	
	//-----------------------------------
	// auto control
	//-----------------------------------
	
	mCount = digBits() != 0 ? 0 : mCount + 1;
	
	GTTestObject1::gttoSetGravity( false );
	
	if( mCount >= 60 * 10 )
	{
		// ボール重力
		if( mCount & 0x400 ){ GTTestObject1::gttoSetGravity( true ); }
		
		mLV.y += PI * 0.00003f;
		mLV.x += PI * 0.00001f;
		
		mVV.y += PI * 0.00010f;
		mVV.x += PI * 0.00007f;
	}
	
	//-----------------------------------
	// control light
	//-----------------------------------
	
	// R L
	if( digBits() & DI_BIT_BA )		mLV.y += PI * 0.0006f;
	if( digBits() & DI_BIT_BD )		mLV.y -= PI * 0.0006f;
	
	// U D
	if( digBits() & DI_BIT_BC )		mLV.x += PI * 0.0005f;
	if( digBits() & DI_BIT_BB )		mLV.x -= PI * 0.0005f;
	
	mLM.dcRotateZXY( mLV.x, 0.0f, mLV.y );
	dcVScale( 0.875f, mLV );
	
	//-----------------------------------
	// control view
	//-----------------------------------
	
	// R L
	if( digBits() & DI_BIT_XR )		mVV.y += PI * 0.0006f;
	if( digBits() & DI_BIT_XL )		mVV.y -= PI * 0.0006f;
	
	// U D
	if( digBits() & DI_BIT_YU )		mVV.x += PI * 0.0005f;
	if( digBits() & DI_BIT_YD )		mVV.x -= PI * 0.0005f;
	
	mVM.dcRotateX( mVV.x );
	m.dcLoadRotateY( mVV.y * dcClamp( +1.0f, -1.0f, mVM.dcGY().y * 4.0f ) );
	mVM.dcMxIN( m );
	dcVScale( 0.875f, mVV );
	
	//-----------------------------------
	// render shadow tex pass
	//-----------------------------------
	
	// memo backbuffer
	dggD()->GetRenderTarget( 0, &pBackBuf );
	
	// memo z buffer
	dggD()->GetDepthStencilSurface( &pZBuffer );
	
	// set render target
	res = mpRenderTexture->GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// set depth surface
	res = dggD()->SetDepthStencilSurface( mpRenderZBuffer );
	ddFAILED( res );
	
	// shadow tex white clear
	res = dggD()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 0, 0, 0, 0 ), 1.0f, 0 );
	ddFAILED( res );
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_DepthShadowP0 );
		DDGraphic::dgSetPS( mPS_DepthShadowP0 );
		DDGraphic::dgSetDrawMode( DG_DRAW_MODE_M44 );
		dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_NORMAL );
		{
			// shadow tex color [ c4.x ]
			D3DCOLORVALUE		c = { 0.7f, 0.0f, 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( 4, (f32*)&c, 1 );
		}
		
		// 逆 カリング
		dggD() -> SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		
		// shadow view and perspective matrix
		dcVNegate( mLM.dcGY(), DDGraphic::dgLightV() );
		
		dcVScale( -14.0f, DDGraphic::dgLightV(), e );
		
		c = dcZero();
		u = mLM.dcGZ();
		
		D3DXMatrixLookAtRH( &tvm, &e, &c, &u );
		D3DXMatrixOrthoRH ( &tpm, 12.f, 12.f, 1.0f, 48.0f );
		
		dggD()->SetTransform( D3DTS_VIEW      , &tvm );
		dggD()->SetTransform( D3DTS_PROJECTION, &tpm );
		
		DDGraphic::dgVM().dcLoadM( tvm );
		DDGraphic::dgPM().dcLoadM( tpm );
		
		DDGraphic::dgVPM().dcLoadM( tpm );
		DDGraphic::dgVPM().dcINxM ( tvm );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP, DVC_CARD_OBJECT_END );
	DVCoaster::dvcCoasterProcess( DVC_CARD_TERRAIN_TOP, DVC_CARD_TERRAIN_END );
	
	dggD()->EndScene();
	
	//-----------------------------------
	// normal render - object and terrain -
	//-----------------------------------
	
	// render target  back buffer
	res = dggD()->SetRenderTarget( 0, pBackBuf );
	ddFAILED( res );
	pBackBuf->Release();
	
	res = dggD()->SetDepthStencilSurface( pZBuffer );
	ddFAILED( res );
	pZBuffer->Release();
	
	// clear back and z buffer
	res = dggD()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 0, 0, 0, 0 ), 1.0f, 0 );
	ddFAILED( res );
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_DepthShadowP1 );
		DDGraphic::dgSetDrawMode( DG_DRAW_MODE_M44LS44 );
		dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_NORMAL );
		{
			// VS light reflect parameter [ c5.x ]
			D3DCOLORVALUE		c = { 0.20f * 0.5f, 0.0f, 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( 5, (f32*)&c, 1 );
		}
		
		// pixel shader entry
		if( digPush() & DI_BIT_BR ){ mSoftShadow = !mSoftShadow; }
		
		if( mSoftShadow )
		{
			DDGraphic::dgSetPS( mPS_DepthShadowP1Soft );
			
			// PS shadow offset parameter [ c0_c7 ]
			D3DCOLORVALUE		c0 = { -2.0f / S98DV_SHADOW_SIZE, -2.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c1 = { -2.0f / S98DV_SHADOW_SIZE, +2.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c2 = { +2.0f / S98DV_SHADOW_SIZE, -2.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c3 = { +2.0f / S98DV_SHADOW_SIZE, +2.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c4 = { -3.0f / S98DV_SHADOW_SIZE, -0.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c5 = { -0.0f / S98DV_SHADOW_SIZE, +3.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c6 = { +3.0f / S98DV_SHADOW_SIZE, -0.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			D3DCOLORVALUE		c7 = { +0.0f / S98DV_SHADOW_SIZE, -3.0f / S98DV_SHADOW_SIZE, 0.0f, 0.0f };
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&c0, 1 );
			dggD() -> SetPixelShaderConstantF( 1, (f32*)&c1, 1 );
			dggD() -> SetPixelShaderConstantF( 2, (f32*)&c2, 1 );
			dggD() -> SetPixelShaderConstantF( 3, (f32*)&c3, 1 );
			dggD() -> SetPixelShaderConstantF( 4, (f32*)&c4, 1 );
			dggD() -> SetPixelShaderConstantF( 5, (f32*)&c5, 1 );
			dggD() -> SetPixelShaderConstantF( 6, (f32*)&c6, 1 );
			dggD() -> SetPixelShaderConstantF( 7, (f32*)&c7, 1 );
		}
		else
		{
			DDGraphic::dgSetPS( mPS_DepthShadowP1 );
		}
		
		// 通常 カリング
		dggD() -> SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		
		// set texture 0 [ model ]
		res = dggD()->SetTexture( 0, mpBallTex );
		ddFAILED( res );
		
		dggD()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
		
		// set texture 1 [ shadow ]
		res = dggD()->SetTexture( 1, mpRenderTexture );
		ddFAILED( res );
		
		// フィルタかけると少しノイズが発生する
		dggD()->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 1, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		
		dggD()->SetSamplerState( 1, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 1, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 1, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA( 0x00, 0xff, 0xff, 0xff ) );
		
		// set texture 2 [ shadow ]
		res = dggD()->SetTexture( 2, mpRenderTexture );
		ddFAILED( res );
		
		dggD()->SetSamplerState( 2, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 2, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 2, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		
		dggD()->SetSamplerState( 2, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 2, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 2, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA( 0x00, 0xff, 0xff, 0xff ) );
		
		// view matrix
		dcVScale( -12.0f, mVM.dcGZ(), e );
		
		c = dcZero();
		u = mVM.dcGY();
		
		D3DXMatrixLookAtRH( &DDGraphic::dgVM(), &e, &c, &u );
		D3DXMatrixPerspectiveFovRH( &DDGraphic::dgPM(), D3DXToRadian( 45.f ), 640.f / 480.f, 1.0f, 500.0f );
		
		DDGraphic::dgVPM().dcLoadM( DDGraphic::dgPM() );
		DDGraphic::dgVPM().dcINxM ( DDGraphic::dgVM() );
		
		dggD()->SetTransform( D3DTS_VIEW,       &DDGraphic::dgVM() );
		dggD()->SetTransform( D3DTS_PROJECTION, &DDGraphic::dgPM() );
		
		// shadow matrix
		ZeroMemory( &m.m[0][0], sizeof( D3DMATRIX ) );
		m.dcM( 0, 0 ) = +0.5f;
		m.dcM( 1, 1 ) = -0.5f;
		m.dcM( 2, 2 ) = +1.0f;
		m.dcM( 3, 0 ) = +0.5f;
		m.dcM( 3, 1 ) = +0.5f;
		m.dcM( 3, 2 ) = +0.0f;
		m.dcM( 3, 3 ) = +1.0f;
		
		m.dcINxM( tpm );
		m.dcINxM( tvm );
		
		DDGraphic::dgSM().dcLoadM( m );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP, DVC_CARD_OBJECT_END );
	
	// set texture 0 [ model ]
	res = dggD()->SetTexture( 0, mpCubeTex );
	ddFAILED( res );
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_TERRAIN_TOP, DVC_CARD_TERRAIN_END );
	
	dggD()->EndScene();
}

