
#include	"s99dsVision.h"

#include	"ddGraphic.h"

#include	"gtTerraBox.h"
#include	"gtTestObject.h"
#include	"gtTestObject0.h"
#include	"gtTestObject1.h"
#include	"gtTestObject2.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

#define		S99DV_SHADOW_SIZE			( 512.f )

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S99DSVision::dvVisionInitial( DDvoid )
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
		dcVLoad( v, -15.0f,  -30.0f,   -10.0f );
		dcNormalize( v );
		light.Direction = v;
		
		DDGraphic::dgLightV() = v;
		
		// set light enable
		dggD() -> SetLight( 0, &light );
		dggD() -> LightEnable( 0, TRUE );
	}
	
	// render tex surface
	mpRenderTexture = NULL;
	mpRenderZBuffer = NULL;
	
	res = dggD()->CreateTexture(
		(u32)S99DV_SHADOW_SIZE,
		(u32)S99DV_SHADOW_SIZE,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&mpRenderTexture,
		NULL );
	
	ddFAILED( res );
	
	// rotate y axis
	mRY = 0.0f;
	
	
	// entry da plot coasters
	(DDvoid)new GTDVCTestObject();
	
	(DDvoid)new GTDVCTestObject0();
	(DDvoid)new GTDVCTestObject1();
	
	(DDvoid)new GTDVCTestObject2();
	(DDvoid)new GTDVCTerraBox();
}

//-------------------------------------------------------------------

DDvoid	S99DSVision::dvVisionDispose( DDvoid )
{
	// release render texture
	ddRELEASE( mpRenderTexture );
	
	// delete coasters
	DSVision::dvVisionDispose();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	S99DSVision::dvVisionProcess( DDvoid )
{
	HRESULT		res;
	DCmtx			tvm;
	DCmtx			tpm;
	DCmtx			m;
	DCmtx			ivm;
	DCvec			e;
	DCvec			c;
	DCvec			u;
	
	LPDIRECT3DSURFACE9	pBackBuf;
//LPDIRECT3DSURFACE9	pZBuffer;
	LPDIRECT3DSURFACE9	pSurface;
	
	//-----------------------------------
	// render shadow tex pass
	//-----------------------------------
	
	// memo backbuffer
	dggD()->GetRenderTarget( 0, &pBackBuf );
	
	// memo z buffer
//dggD()->GetDepthStencilSurface( &pZBuffer );
	
	// set render target
	res = mpRenderTexture->GetSurfaceLevel( 0, &pSurface );
	ddFAILED( res );
	
	res = dggD()->SetRenderTarget( 0, pSurface );
	ddFAILED( res );
	pSurface->Release();
	
	// shadow tex white clear
	res = dggD()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA( 0xff, 0xff, 0xff, 0x00 ), 1.0f, 0 );
	ddFAILED( res );
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// vertex shader entry
		DDGraphic::dgSetVS( NULL );
		DDGraphic::dgSetDrawMode( DG_DRAW_MODE_DEFAULT );
		
		// pixel  shader entry
		DDGraphic::dgSetPS( NULL );
		
		// setup shadow view and perspective matrix
		dcVLoad( e, +15.0f,  +30.0f,   +10.0f );
		dcVLoad( c, +0.0f,    +0.0f,    +0.0f );
		dcVLoad( u, +0.0f,    +1.0f,    +0.0f );
		
		D3DXMatrixLookAtRH( &tvm, &e, &c, &u );
		D3DXMatrixPerspectiveFovRH( &tpm, D3DXToRadian( 20.f ), S99DV_SHADOW_SIZE / S99DV_SHADOW_SIZE, 1.0f, 500.0f );
		
		dggD()->SetTransform( D3DTS_VIEW      , &tvm );
		dggD()->SetTransform( D3DTS_PROJECTION, &tpm );
		
		// z disable
		dggD()->SetRenderState( D3DRS_ZENABLE, FALSE );
		
		// light off
		dggD() -> LightEnable( 0, FALSE );
		
		// tex stage 0 matrix mode
		res = dggD()->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU );
		ddFAILED( res );
		
		res = dggD()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
		ddFAILED( res );
		
		// tex stage 0 operation
		dggD()->SetRenderState( D3DRS_BLENDFACTOR, D3DCOLOR_RGBA( 0x80, 0x80, 0x80, 0x80 ) );
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		dggD()->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_BLENDFACTOR );
		dggD()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP, DVC_CARD_OBJECT_END );
	
	dggD()->EndScene();
	
	//-----------------------------------
	// normal render - object -
	//-----------------------------------
	
	// render target  back buffer
	res = dggD()->SetRenderTarget( 0, pBackBuf );
	ddFAILED( res );
	
	pBackBuf->Release();
	
	// z enable
	dggD()->SetRenderState( D3DRS_ZENABLE, TRUE );
	
	// clear back and z buffer
	res = dggD()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 0x00, 0x00, 0x00, 0x00 ), 1.0f, 0 );
	ddFAILED( res );
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// light on
		dggD() -> LightEnable( 0, TRUE );
		
		// view matrix
		mRY += _768PI;
		
		dcVLoad( e, dcSin( mRY ) * 12.f,   +3.0f, dcCos( mRY ) * 12.f );
		dcVLoad( c, 0.0f,   +0.0f,   +0.0f );
		dcVLoad( u, 0.0f,   +1.0f,   +0.0f );
		
		D3DXMatrixLookAtRH( &DDGraphic::dgVM(), &e, &c, &u );
		D3DXMatrixPerspectiveFovRH( &DDGraphic::dgPM(), D3DXToRadian( 45.f ), 640.f / 480.f, 1.0f, 500.0f );
		
		DDGraphic::dgVPM().dcLoadM( DDGraphic::dgPM() );
		DDGraphic::dgVPM().dcINxM ( DDGraphic::dgVM() );
		
		dggD()->SetTransform( D3DTS_VIEW,       &DDGraphic::dgVM() );
		dggD()->SetTransform( D3DTS_PROJECTION, &DDGraphic::dgPM() );
		
		dggD()->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_OBJECT_TOP,  DVC_CARD_OBJECT_END );
	
	dggD()->EndScene();
	
	//-----------------------------------
	// normal render - terrain shadow tex -
	//-----------------------------------
	
	// state block
	{
		IDirect3DStateBlock9*		pStateBlock;
		
		// begin state block
		res = dggD() -> BeginStateBlock();
		ddFAILED( res );
		
		// set texture
		res = dggD()->SetTexture( 0, mpRenderTexture );
		ddFAILED( res );
		
		// tex stage 0 matrix mode
		res = dggD()->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );
		ddFAILED( res );
		
		res = dggD()->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_PROJECTED | D3DTTFF_COUNT3 );
		ddFAILED( res );
		
		// tex filter
		dggD()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_PYRAMIDALQUAD );
		
		// tex stage 0 addressing mode
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		dggD()->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );
		
		dggD()->SetSamplerState( 0, D3DSAMP_BORDERCOLOR, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
		
		// tex stage 0 operation
		dggD()->SetTextureStageState( 0, D3DTSS_COLOROP  , D3DTOP_MODULATE );
		dggD()->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		dggD()->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		
		dggD()->SetTextureStageState( 0, D3DTSS_ALPHAOP  , D3DTOP_SELECTARG2 );
		dggD()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		dggD()->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		
		// tex stage 0 matrix
		DDGraphic::dgVM().dcInverse( ivm );			// camera 2 world space
		
		ZeroMemory( &m.m[0][0], sizeof( D3DMATRIX ) );
		m.dcM( 0, 0 ) = +0.5f;
		m.dcM( 1, 1 ) = -0.5f;
		m.dcM( 2, 2 ) = +1.0f;
		m.dcM( 3, 0 ) = +0.5f;
		m.dcM( 3, 1 ) = +0.5f;
		m.dcM( 3, 2 ) = +0.0f;
		m.dcM( 3, 3 ) = +1.0f;
		
		// m = ivm * tvm * tpm * m;
		m.dcINxM( tpm );
		m.dcINxM( tvm );
		m.dcINxM( ivm );
		
		res = dggD()->SetTransform( D3DTS_TEXTURE0, &m );
		ddFAILED( res );
		
		// end state block
		res = dggD() -> EndStateBlock( &pStateBlock );
		ddFAILED( res );
		
		res = pStateBlock -> Apply();
		ddFAILED( res );
		
		pStateBlock -> Release();
	}
	
	dggD()->BeginScene();
	
	DVCoaster::dvcCoasterProcess( DVC_CARD_TERRAIN_TOP, DVC_CARD_TERRAIN_END );
	
	dggD()->EndScene();
	
	
	// set texture
	res = dggD()->SetTexture( 0, NULL );
	ddFAILED( res );
}

