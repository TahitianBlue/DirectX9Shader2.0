
// ïîâÆÇëzíËÇµÇΩÇaÇnÇw ì‡ë§ï`âÊ

#include	"gtTestObject2.h"
#include	"ddGraphic.h"

#define	INBOX_SIZE		( 12.f )

//------------------------------------------------------------------
// plot coaster
// constract destract
//------------------------------------------------------------------

GTDVCTestObject2::GTDVCTestObject2( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_TERRAIN_MODEL_INNER_BOX ] != NULL );
	
	dvcmList[ DVC_CARD_TERRAIN_MODEL_INNER_BOX ] = this;
	
	
	D3DCOLORVALUE		cd = { 1.0f, 1.0f, 1.0f, 1.0f };
	D3DCOLORVALUE		ca = { 0.6f, 1.0f, 0.6f, 0.6f };
	D3DCOLORVALUE		ce = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	mMaterial.Diffuse  = cd;
	mMaterial.Ambient  = ca;
	mMaterial.Specular = cd;
	mMaterial.Emissive = ce;
	mMaterial.Power    = 255.0f;
}

//------------------------------------------------------------------

GTDVCTestObject2::~GTDVCTestObject2( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_TERRAIN_MODEL_INNER_BOX ] != this );
	
	dvcmList[ DVC_CARD_TERRAIN_MODEL_INNER_BOX ] = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTDVCTestObject2::dvcIntro( DDvoid )
{
	dggD() -> SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );
	
	dggD() -> SetMaterial( &mMaterial );
}

//------------------------------------------------------------------

DDvoid	GTDVCTestObject2::dvcOutro( DDvoid )
{
}


//------------------------------------------------------------------
// action & plot
//------------------------------------------------------------------

GTTestObject2::GTTestObject2( DCvec& p ) :
	DSAction( DA_ACTOR_ENEMY ),
	DVPlot( DVC_CARD_TERRAIN_MODEL_INNER_BOX )
{
	mP = p;
	mR.dcIdentity();
	
	mM.dcMakeM( mP, mR );
	mM.dcScaleY( 0.75f );
	
	D3DXCreateBox( dggD(), INBOX_SIZE, INBOX_SIZE, INBOX_SIZE, &mMesh, &mAdjacency );
}

//------------------------------------------------------------------

GTTestObject2::~GTTestObject2( DDvoid )
{
	ddRELEASE( mMesh );
	ddRELEASE( mAdjacency );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject2::daAction( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject2::dvpSight( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------

DDvoid	GTTestObject2::dvpPos( DCvec& p )
{
	p = mP;
}

//------------------------------------------------------------------

DDvoid	GTTestObject2::dvpPlot( DDvoid )
{
	DCmtx			m;
	
	m.dcLoadM( mM );
	m.dcScale( -1.0f );			// ñ@ê¸ÇÕïœä∑Ç≥ÇÍÇ»Ç≠Çƒñ≥à”ñ°Ç≈ÇµÇΩ
	
	DDGraphic::dgDraw( m, mMesh, 1 );
}

