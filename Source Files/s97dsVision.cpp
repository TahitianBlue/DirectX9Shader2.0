
#include	"s97dsVision.h"

#include	"ddGraphic.h"
#include	"ddInput.h"

#include	"gtTerraBox.h"
#include	"gtTestObject.h"
#include	"gtTestObject0.h"
#include	"gtTestObject1.h"
#include	"gtTestObject2.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

#define		S97DV_SHADOW_SIZE			( 1024.f )

#define		S97DV_HDR_WIDTH				( WIDTH  / 2.f )
#define		S97DV_HDR_HEIGHT			( HEIGHT / 2.f )

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S97DSVision::dvVisionInitial( DDvoid )
{
	HRESULT		res;
	s32				i;
	
	// null clear coaster list
	DSVision::dvVisionInitial();
	
	// set light 0
	DDGraphic::dgLightV() = dcYn();
	
	// render texture surface
	mpShadowTexture = NULL;
	mpShadowZBuffer = NULL;
	mpSceneTexture  = NULL;
	mpHDRTexture[0] = NULL;
	mpHDRTexture[1] = NULL;
	for( i = 0 ; i != 4 ; i++ ){ mpCrossTexture[ i ] = NULL; }
	
	res = dggD()->CreateTexture(
		(u32)S97DV_SHADOW_SIZE,
		(u32)S97DV_SHADOW_SIZE,
		1,
		D3DUSAGE_RENDERTARGET,
//	D3DFMT_G16R16,
		D3DFMT_G16R16F,
		D3DPOOL_DEFAULT,
		&mpShadowTexture,
		NULL );
	ddFAILED( res );
	
	res = dggD()->CreateDepthStencilSurface(
		(u32)S97DV_SHADOW_SIZE,
		(u32)S97DV_SHADOW_SIZE,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&mpShadowZBuffer,
		NULL );
	ddFAILED( res );
	
	res = dggD()->CreateTexture(
		(u32)WIDTH,
		(u32)HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&mpSceneTexture,
		NULL );
	ddFAILED( res );
	
	for( i = 0 ; i != 2 ; i++ )
	{
		res = dggD()->CreateTexture(
			(u32)S97DV_HDR_WIDTH,
			(u32)S97DV_HDR_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&mpHDRTexture[ i ],
			NULL );
		ddFAILED( res );
	}
	mHDRTexLatest = S97DV_BLOOM_TEX_0;
	
	for( i = 0 ; i != 4 ; i++ )
	{
		res = dggD()->CreateTexture(
			(u32)S97DV_HDR_WIDTH,
			(u32)S97DV_HDR_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&mpCrossTexture[ i ],
			NULL );
		ddFAILED( res );
	}
	
	// load texture
//res = D3DXCreateTextureFromFileEx( dggD(), "DDResource/Floor.bmp",
	res = D3DXCreateTextureFromFileEx( dggD(), "DDResource/Stripe.bmp",
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
	
//res = D3DXCreateCubeTextureFromFileEx( dggD(), "DDResource/LobbyCube.dds",
//res = D3DXCreateCubeTextureFromFileEx( dggD(), "DDResource/nvlobby_cube_mipmap.dds",
//res = D3DXCreateCubeTextureFromFileEx( dggD(), "DDResource/uffizi_cross_mmp.dds",			// 欧州裏路地
//res = D3DXCreateCubeTextureFromFileEx( dggD(), "DDResource/stpeters_cross_mmp.dds",		// 欧州建築屋内
	res = D3DXCreateCubeTextureFromFileEx( dggD(), "DDResource/rnl_cross_mmp.dds",				// 森の中
						D3DX_DEFAULT, D3DX_DEFAULT,
						0,
					//D3DFMT_A16B16G16R16,
						D3DFMT_A16B16G16R16F,			
						D3DPOOL_MANAGED,
						D3DX_DEFAULT, D3DX_DEFAULT, 0,
						NULL, NULL, &mpLobbyCubeTexture );
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
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_DepthShadow1CubeEnvMap.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_DepthShadowP1 );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// depth shadow pass 1 stealth
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_DepthShadow1Stealth.vs" ), NULL, NULL, 0, &pCode, NULL );

		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_DepthShadowP1Stealth );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// HDR filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_HDRFilter.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_HDRFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// alpha HDR filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_AlphaHDRFilter.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_AlphaHDRFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// 4 texture filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_4TextureFilter.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_4TextureFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// 8 texture filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_8TextureFilter.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_8TextureFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// ortho
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_Ortho.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_Ortho );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// ortho dif
		res = D3DXAssembleShaderFromFile( _T( "DDShader/VS_OrthoDif.vs" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreateVertexShader( (DWORD*)pCode->GetBufferPointer(), &mVS_OrthoDif );
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
		
		// depth shadow pass 1 cube env map
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_DepthShadow1CubeEnvMap.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_DepthShadowP1CubeEnvMap );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// HDR filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_HDRFilter.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_HDRFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// alpha HDR filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_AlphaHDRFilter.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_AlphaHDRFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// 4 texture filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_4TextureFilter.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_4TextureFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// 8 texture filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_8TextureFilter.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_8TextureFilter );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// 8 texture filter mul
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_8TextureFilterMul.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_8TextureFilterMul );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// ortho filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_Ortho.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_Ortho );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// ortho mul filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_OrthoMul.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_OrthoMul );
		ddFAILED( res );
		ddRELEASE( pCode );
		
		// ortho dif filter
		res = D3DXAssembleShaderFromFile( _T( "DDShader/PS_OrthoDif.ps" ), NULL, NULL, 0, &pCode, NULL );
		ddFAILED( res );
		res = dggD() -> CreatePixelShader( (DWORD*)pCode->GetBufferPointer(), &mPS_OrthoDif );
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
	
	mCount   = 0;
	mStealth = false;

	// entry da plot coasters
	(DDvoid)new GTDVCTestObject();
	
	(DDvoid)new GTDVCTestObject0();
	(DDvoid)new GTDVCTestObject1();
	
	(DDvoid)new GTDVCTestObject2();
	(DDvoid)new GTDVCTerraBox();
}

//-------------------------------------------------------------------

DDvoid	S97DSVision::dvVisionDispose( DDvoid )
{
	s32			i;
	
	// release pixel shader
	ddRELEASE( mPS_OrthoDif );
	ddRELEASE( mPS_OrthoMul );
	ddRELEASE( mPS_Ortho );
	ddRELEASE( mPS_8TextureFilterMul );
	ddRELEASE( mPS_8TextureFilter );
	ddRELEASE( mPS_4TextureFilter );
	ddRELEASE( mPS_AlphaHDRFilter );
	ddRELEASE( mPS_HDRFilter );
	ddRELEASE( mPS_DepthShadowP1CubeEnvMap );
	ddRELEASE( mPS_DepthShadowP1 );
	ddRELEASE( mPS_DepthShadowP0 );
	DDGraphic::dgSetPS( NULL );
	
	// release vertex shader
	ddRELEASE( mVS_OrthoDif );
	ddRELEASE( mVS_Ortho );
	ddRELEASE( mVS_8TextureFilter );
	ddRELEASE( mVS_4TextureFilter );
	ddRELEASE( mVS_AlphaHDRFilter );
	ddRELEASE( mVS_HDRFilter );
	ddRELEASE( mVS_DepthShadowP1Stealth );
	ddRELEASE( mVS_DepthShadowP1 );
	ddRELEASE( mVS_DepthShadowP0 );
	DDGraphic::dgSetVS( NULL );
	DDGraphic::dgSetDrawMode( DG_DRAW_MODE_DEFAULT );
	
	// release texture
	ddRELEASE( mpCubeTex );
	ddRELEASE( mpBallTex );
	
	// release render texture
	ddRELEASE( mpShadowTexture );
	ddRELEASE( mpShadowZBuffer );
	ddRELEASE( mpSceneTexture );
	for( i = 0 ; i != 2 ; i++ ){ ddRELEASE( mpHDRTexture[i] ); }
	for( i = 0 ; i != 2 ; i++ ){ ddRELEASE( mpCrossTexture[i] ); }
	
	// delete coasters
	DSVision::dvVisionDispose();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S97DSVision::dvVisionProcess( DDvoid )
{
	HRESULT		res;
	DCmtx			tvm;
	DCmtx			tpm;
	DCmtx			m;
	DCvec			e;
	DCvec			c;
	DCvec			u;
	
	LPDIRECT3DSURFACE9	pSurface;
	LPDIRECT3DSURFACE9	pZBuffer;
	
	//-----------------------------------
	// stealth toggle
	//-----------------------------------
	
	if( digPush() & DI_BIT_BR ){ mStealth = !mStealth; }
	
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
	// render shadow texture pass
	//-----------------------------------
	
	// memo back buffer and z buffer
	dggD()->GetRenderTarget( 0, &mpBackBufferSurface );
	dggD()->GetDepthStencilSurface( &pZBuffer );
	
	// set render target ( shadow texture )
	res = mpShadowTexture->GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// set depth surface
	res = dggD()->SetDepthStencilSurface( mpShadowZBuffer );
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
		
		// 逆 culling
		dggD() -> SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		
		// view and perspective matrix
		dcVNegate( mLM.dcGY(), DDGraphic::dgLightV() );
		
		dcVScale( -14.0f, DDGraphic::dgLightV(), e );
		
		c = dcZero();
		u = mLM.dcGZ();
		
		D3DXMatrixLookAtRH( &tvm, &e, &c, &u );
		D3DXMatrixOrthoRH ( &tpm, 13.f, 13.f, 1.0f, 48.0f );
		
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
	{
		if( mStealth == false )
		{
			DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP, DVC_CARD_OBJECT_END );
		}
		DVCoaster::dvcCoasterProcess( DVC_CARD_TERRAIN_TOP, DVC_CARD_TERRAIN_END );
	}
	dggD()->EndScene();
	
	//-----------------------------------
	// scene render - object and terrain -
	//-----------------------------------
	
	// set render target	( scene texture )
	res = mpSceneTexture -> GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
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
		m.dcIdentity();
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
		
		// shader entry
		DDGraphic::dgSetVS( mVS_DepthShadowP1 );
		DDGraphic::dgSetPS( mPS_DepthShadowP1 );
		DDGraphic::dgSetDrawMode( DG_DRAW_MODE_M44LS44 );
		dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_NORMAL );
		{
			// VS light reflect parameter [ c5.x ]
			D3DCOLORVALUE		c = { 0.20f * 0.5f, 0.0f, 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( 5, (f32*)&c, 1 );
			
			// 視点位置 [ c20.xyz ]
			D3DCOLORVALUE		c20 = { e.x, e.y, e.z, 0.0f };
			dggD() -> SetVertexShaderConstantF( 20, (f32*)&c20, 1 );
		}
		
		// 通常 culling
		dggD() -> SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
		
		// set texture 0 [ model ]
		res = dggD()->SetTexture( 0, mpCubeTex );
		ddFAILED( res );
		
		dggD()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
		
		// set texture 1 [ shadow ]
		res = dggD()->SetTexture( 1, mpShadowTexture );
		ddFAILED( res );
		
		// フィルタかけると少しノイズが発生する
		dggD()->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		dggD()->SetSamplerState( 1, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		
		dggD()->SetSamplerState( 1, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 1, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );
		
		// shadow tex border color ( bright 0.0f, depth 0.0f, -, - )
		dggD()->SetSamplerState( 1, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA( 0x00, 0x00, 0x00, 0x00 ) );
		
		// set texture 2 [ lobby cube map ]
		res = dggD()->SetTexture( 2, mpLobbyCubeTexture );
		ddFAILED( res );
		
		dggD()->SetSamplerState( 2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 2, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 2, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		dggD()->SetSamplerState( 2, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	{
		DVCoaster::dvcCoasterProcess( DVC_CARD_TERRAIN_TOP, DVC_CARD_TERRAIN_END );
		
		if( mStealth )
		{
			// shader entry
			DDGraphic::dgSetVS( mVS_DepthShadowP1Stealth );
			DDGraphic::dgSetDrawMode( DG_DRAW_MODE_M44LS44 );
			{
				// VS stealth tex offset 0.5f+- [ c15.xyz ]
				D3DCOLORVALUE		c15 = { +0.49f, -0.49f, 0.5f, 0.0f };
				dggD() -> SetVertexShaderConstantF( 15, (f32*)&c15, 1 );
			}
			// set texture 0 [ model ]
			res = dggD()->SetTexture( 0, mpSceneTexture );
			ddFAILED( res );
		}
		else
		{
			// shader entry
			DDGraphic::dgSetPS( mPS_DepthShadowP1CubeEnvMap );
			DDGraphic::dgSetDrawMode( DG_DRAW_MODE_M44LS44W44 );
			{
				// PS cube env map parameter [ c0.xyz ]
				//	.x		RGB co					( src alpha )
				//	.y		1.0f - RGB co		( inv src alpha )
				//	.z		仮 A multi / 3.0f ( A = (R+G+B) / 3 * A multi )
				//	.w		仮 HDR to LDR coef
				D3DCOLORVALUE		c0 = { 0.5f, 1.0f - 0.5f, 0.52f / 3.0f, 96.0f };
				dggD() -> SetPixelShaderConstantF( 0, (f32*)&c0, 1 );
			}
			
			// set texture 0 [ model ]
			res = dggD()->SetTexture( 0, mpBallTex );
			ddFAILED( res );
		}
		DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP, DVC_CARD_OBJECT_END );
	}
	dggD()->EndScene();
	
	//-----------------------------------
	// Color( RGB ) HDR bloom effect
	//-----------------------------------
	
	// dither enable
//dggD() -> SetRenderState( D3DRS_DITHERENABLE, TRUE );
	
	// z test and write disable
	dggD() -> SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	
	dvColorHDRAbstract( 0.750f, 4.0f );
	
	dvColorHDRBloom( 1.01f, 2 );
	
	//-----------------------------------
	// Alpha HDR cross effect
	//-----------------------------------
	
	dvAlphaHDRAbstract( 0.5f );
	
	dvAlphaHDRCross( +2.0f, 0.0f, 4 );
	dvAlphaHDRCross( -2.0f, 0.0f, 4 );
	
	dvAlphaHDRCross( COS60 * +2.0f, SIN60 * +2.0f, 2 );
	dvAlphaHDRCross( COS60 * -2.0f, SIN60 * -2.0f, 2 );
	
	dvAlphaHDRCross( COS60 * -2.0f, SIN60 * +2.0f, 2 );
	dvAlphaHDRCross( COS60 * +2.0f, SIN60 * -2.0f, 2 );
	
	//-----------------------------------
	// frame buffer = scene + bloom + cross
	//-----------------------------------
	
	dvFrameMargeSceneHDR( 0.25f, 1.0f, 1.0f );
	
	//-----------------------------------
	
	// z test and write enable
	dggD() -> SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	
	// dither disable
//dggD() -> SetRenderState( D3DRS_DITHERENABLE, FALSE );
}


//-------------------------------------------------------------------
//-------------------------------------------------------------------

// シーンRGBから高光度部分を抽出し mpHDRTexture[0] へ
//	Sub		切り捨て光度
//	Mul		切捨て後の倍率

DDvoid	S97DSVision::dvColorHDRAbstract( f32 Sub, f32 Mul )
{
	LPDIRECT3DSURFACE9	pSurface;
	HRESULT							res;
	
	mHDRTexLatest = S97DV_BLOOM_TEX_0;
	
	// set render target	( HDR texture )
	res = mpHDRTexture[ mHDRTexLatest ] -> GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_HDRFilter );
		DDGraphic::dgSetPS( mPS_HDRFilter );
		dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
		{
			// VS texture offset ( 1 / 4 size ) parameter [ c0 ]
			D3DCOLORVALUE		c = { +2.0f / WIDTH, +2.0f / HEIGHT, -0.0f / WIDTH, -0.0f / HEIGHT };
			dggD() -> SetVertexShaderConstantF( 0, (f32*)&c, 1 );
			
			// PS 抽出光度, 光度倍率 [ c0.xy ]
			D3DCOLORVALUE		d = { Sub, Mul, 0.0f, 0.0f };
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&d, 1 );
		}
		
		// set texture 0 [ scene texture ]
		res = dggD()->SetTexture( 0, mpSceneTexture );
		ddFAILED( res );
		
		dggD()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	DDGraphic::dgRenderOrthoFullScreen();
}

//-------------------------------------------------------------------

// ぼかし処理
// mpHDRTexture[ 0 ] << >> [ 1 ]

DDvoid	S97DSVision::dvColorHDRBloom( f32 Mul, s32 Count )
{
	LPDIRECT3DSURFACE9	pSurface;
	HRESULT							res;
	
	s32						texSrc;
	s32						texDst;
	
	
	// vertex shader entry
	DDGraphic::dgSetVS( mVS_8TextureFilter );
	DDGraphic::dgSetPS( mPS_8TextureFilter );
	{
		// PS  光度倍率 / 8.0f [ c0.x ]
		D3DCOLORVALUE		d = { Mul * _8,  0.0f, 0.0f, 0.0f };
		dggD() -> SetPixelShaderConstantF( 0, (f32*)&d, 1 );
	}
	{
		// VS texture offset parameter [ c0_c7 ]
		D3DCOLORVALUE		c0 = { -1.0f / S97DV_HDR_WIDTH, +1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c1 = { +1.0f / S97DV_HDR_WIDTH, +1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c2 = { -1.0f / S97DV_HDR_WIDTH, -1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c3 = { +1.0f / S97DV_HDR_WIDTH, -1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c4 = { -3.0f / S97DV_HDR_WIDTH, +1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c5 = { +1.0f / S97DV_HDR_WIDTH, +3.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c6 = { -1.0f / S97DV_HDR_WIDTH, -3.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		D3DCOLORVALUE		c7 = { +3.0f / S97DV_HDR_WIDTH, +1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
		dggD() -> SetVertexShaderConstantF( 0, (f32*)&c0, 1 );
		dggD() -> SetVertexShaderConstantF( 1, (f32*)&c1, 1 );
		dggD() -> SetVertexShaderConstantF( 2, (f32*)&c2, 1 );
		dggD() -> SetVertexShaderConstantF( 3, (f32*)&c3, 1 );
		dggD() -> SetVertexShaderConstantF( 4, (f32*)&c4, 1 );
		dggD() -> SetVertexShaderConstantF( 5, (f32*)&c5, 1 );
		dggD() -> SetVertexShaderConstantF( 6, (f32*)&c6, 1 );
		dggD() -> SetVertexShaderConstantF( 7, (f32*)&c7, 1 );
	}
	
	//-----------------------
	
	for( s32 i = 0 ; i != Count ; i++ )
	{
		texSrc = mHDRTexLatest;
		mHDRTexLatest = ( mHDRTexLatest + 1 ) & 1;
		texDst = mHDRTexLatest;
		
		// set render target	( HDR 0:1 texture )
		res = mpHDRTexture[ texDst ] -> GetSurfaceLevel( 0, &pSurface );
		ddFAILED( res );
		res = dggD()->SetRenderTarget( 0, pSurface );
		ddFAILED( res );
		pSurface->Release();
		
		// set texture 0 [ HDR 1:0 texture ]
		res = dggD()->SetTexture( 0, mpHDRTexture[ texSrc ] );
		ddFAILED( res );
		
		DDGraphic::dgRenderOrthoFullScreen();
	}
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

// シーンAlphaから高光度部分( A 0.5f 以上 )を抽出し mpCrossTexture[ 0 ] へ

DDvoid	S97DSVision::dvAlphaHDRAbstract( f32 AlphaSub )
{
	LPDIRECT3DSURFACE9	pSurface;
	HRESULT							res;
	
	mCrossResultVirgin = true;
	
	// set render target	( HDR texture )
	res = mpCrossTexture[ 0 ] -> GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_AlphaHDRFilter );
		DDGraphic::dgSetPS( mPS_AlphaHDRFilter );
		dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
		{
			// PS		c0.x = alpha 切り捨て値, c0.y = 光度倍率 / ( 1.0f - alpha切り捨て値 ) [ c0.xy ]
			D3DCOLORVALUE		d = { AlphaSub, 2.0f / ( 1.0f - AlphaSub ), 0.0f, 0.0f };
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&d, 1 );
		}
		
		// set texture 0 [ scene texture ]
		res = dggD()->SetTexture( 0, mpSceneTexture );
		ddFAILED( res );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	DDGraphic::dgRenderOrthoFullScreen();
	
	// 外枠１ピクセルを消去
	DDGraphic::dgSetVS( mVS_OrthoDif );
	DDGraphic::dgSetPS( mPS_OrthoDif );
	dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
	
	DDGraphic::dgRenderOrthoOuterFrame( 1.0f / S97DV_HDR_WIDTH, 1.0f / S97DV_HDR_HEIGHT, D3DCOLOR_RGBA( 0x00, 0x00, 0x00, 0x00 ) );
}

//-------------------------------------------------------------------

// クロスフィルタ
// mpCrossTexture[ 0 ] >> ( [ 1 ] >> << [ 2 ] ) >> +[ 3 ]

DDvoid	S97DSVision::dvAlphaHDRCross( f32 X, f32 Y, s32 Count )
{
	LPDIRECT3DSURFACE9	pSurface;
	HRESULT							res;
	
	f32					xv;
	f32					yv;
	f32					x;
	f32					y;
	s32					texSrc;
	s32					texDst;
	f32					pixelMul;
	f32					pixelMulV;
	DDbool			workVirgin;
	s32					i;
	
	
	xv = X * ( 1.0f / S97DV_HDR_WIDTH );
	yv = Y * ( 1.0f / S97DV_HDR_HEIGHT );
	x = 0.0f;
	y = 0.0f;
	
	texSrc = S97DV_CROSS_TEX_BASE;
	texDst = S97DV_CROSS_TEX_WORK;
	
	pixelMul  = 1.0f;
	pixelMulV = -pixelMul / ( dcSF( Count ) * 8.0f );
	
	workVirgin = true;
	
	// vertex shader entry
	DDGraphic::dgSetVS( mVS_8TextureFilter );
	DDGraphic::dgSetPS( mPS_8TextureFilterMul );
	dggD() -> SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
	
	//-----------------------------
	// ( base >> work ) x count
	//-----------------------------
	
	for( i = 0 ; i != Count ; i++ )
	{
		// VS texture offset parameter [ c0_c7 ]
		for( s32 j = 0 ; j != 8 ; j++ )
		{
			D3DCOLORVALUE		c = { x, y, 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( j, (f32*)&c, 1 );
			x += xv;
			y += yv;
		}
		
		// PS multiple parameter 光度倍率 [ c0.xyzw c1.xyzw ]
		{
			D3DCOLORVALUE		c;
			
			c.r = pixelMul;			pixelMul += pixelMulV;
			c.g = pixelMul;			pixelMul += pixelMulV;
			c.b = pixelMul;			pixelMul += pixelMulV;
			c.a = pixelMul;			pixelMul += pixelMulV;
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&c, 1 );
			
			c.r = pixelMul;			pixelMul += pixelMulV;
			c.g = pixelMul;			pixelMul += pixelMulV;
			c.b = pixelMul;			pixelMul += pixelMulV;
			c.a = pixelMul;			pixelMul += pixelMulV;
			dggD() -> SetPixelShaderConstantF( 1, (f32*)&c, 1 );
		}
		
		// texDst alpha blend
		if( workVirgin )
		{
			workVirgin = false;
			
			dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		}
		else
		{
			dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
			dggD()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
			dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		}
		
		// set render target	( cross 1 texture )
		res = mpCrossTexture[ texDst ] -> GetSurfaceLevel( 0, &pSurface );
		ddFAILED( res );
		res = dggD()->SetRenderTarget( 0, pSurface );
		ddFAILED( res );
		pSurface->Release();
		
		// set texture 0 [ cross 0:1:2 texture ]
		res = dggD()->SetTexture( 0, mpCrossTexture[ texSrc ] );
		ddFAILED( res );
		
		DDGraphic::dgRenderOrthoFullScreen();
	}
	
	//-----------------------------
	// result copy
	//-----------------------------
	
	texSrc = S97DV_CROSS_TEX_WORK;
	texDst = S97DV_CROSS_TEX_RESULT;
	
	if( mCrossResultVirgin )
	{
		mCrossResultVirgin = false;
		
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}
	else
	{
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		dggD()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	}
	
	// vertex shader entry
	DDGraphic::dgSetVS( mVS_Ortho );
	DDGraphic::dgSetPS( mPS_Ortho );
	{
		// VS texture offset( shapeness ) parameter [ c0.xy ]
		D3DCOLORVALUE		c = { 0.0f * ( 1.0f / S97DV_HDR_WIDTH ), 0.0f * ( 1.0f / S97DV_HDR_WIDTH ), 0.0f, 0.0f };
		dggD() -> SetVertexShaderConstantF( 0, (f32*)&c, 1 );
	}
	
	// set render target	( cross result texture )
	res = mpCrossTexture[ texDst ] -> GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// set texture 0 [ cross work texture ]
	res = dggD()->SetTexture( 0, mpCrossTexture[ texSrc ] );
	ddFAILED( res );
	
	DDGraphic::dgRenderOrthoFullScreen();
	
	// alpha function
	dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

// frame buffer = scene + bloom + cross
//	SceneSharpness	0.0f = soft : 0.5f = sharp

DDvoid	S97DSVision::dvFrameMargeSceneHDR( f32 SceneSharpness, f32 BloomMul, f32 CrossMul )
{
	HRESULT							res;
	
	// set render target  back buffer and z buffer
	res = dggD()->SetRenderTarget( 0, mpBackBufferSurface );
	ddFAILED( res );
	mpBackBufferSurface -> Release();
	
	//-------------------------------
	// scene texture コピー
	//-------------------------------
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_Ortho );
		DDGraphic::dgSetPS( mPS_Ortho );
		{
			// VS texture offset( shapeness ) parameter [ c0.xy ]
			D3DCOLORVALUE		c = { SceneSharpness * ( 1.0f / WIDTH ), SceneSharpness * ( 1.0f / HEIGHT ), 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( 0, (f32*)&c, 1 );
		}
		
		// set texture 0 [ scene texture ]
		res = dggD()->SetTexture( 0, mpSceneTexture );
		ddFAILED( res );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	DDGraphic::dgRenderOrthoFullScreen();
	
	//-------------------------------
	// HDR bloom texture 加算合成
	//-------------------------------
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_4TextureFilter );
		DDGraphic::dgSetPS( mPS_4TextureFilter );
		{
			// VS texture offset parameter [ c0 ]
			D3DCOLORVALUE		c = { +2.0f / S97DV_HDR_WIDTH, +2.0f / S97DV_HDR_HEIGHT, -0.0f / S97DV_HDR_WIDTH, -0.0f / S97DV_HDR_HEIGHT };
			dggD() -> SetVertexShaderConstantF( 0, (f32*)&c, 1 );
			
			// PS 光度倍率 / 4.0f [ c0.x ]
			D3DCOLORVALUE		d = { BloomMul * _4, 0.0f, 0.0f, 0.0f };
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&d, 1 );
		}
		
		// set texture 0 HDR result
		res = dggD()->SetTexture( 0, mpHDRTexture[ mHDRTexLatest ] );
		ddFAILED( res );
		
		// alpha function
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		dggD()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
		dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	DDGraphic::dgRenderOrthoFullScreen();
	
	//-------------------------------
	// HDR cross texture 半透明
	//-------------------------------
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( mVS_Ortho );
		DDGraphic::dgSetPS( mPS_OrthoMul );
		{
			// VS texture offset( shapeness ) parameter [ c0.xy ]
			D3DCOLORVALUE		c = { 1.0f / S97DV_HDR_WIDTH, 1.0f / S97DV_HDR_HEIGHT, 0.0f, 0.0f };
			dggD() -> SetVertexShaderConstantF( 0, (f32*)&c, 1 );
			
			// PS multiple parameter [ c0.rgba ]
			D3DCOLORVALUE		d = { CrossMul, CrossMul, CrossMul, CrossMul };
			dggD() -> SetPixelShaderConstantF( 0, (f32*)&d, 1 );
		}
		
		// set texture 0 [ scene texture ]
		res = dggD()->SetTexture( 0, mpCrossTexture[ S97DV_CROSS_TEX_RESULT ] );
		ddFAILED( res );
		
		// alpha function
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	DDGraphic::dgRenderOrthoFullScreen();
	
	//-------------------------------
	
	// alpha function
	dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
}

