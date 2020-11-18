
// ’µ‚Ë‰ñ‚é‚a‚n‚w

#include	"gtTestObject0.h"
#include	"ddGraphic.h"

#define		TO0_R		( 10.0f )
#define		TO0_X		( 80.f - TO0_R )
#define		TO0_Y		( 80.f * 0.75f - TO0_R )
#define		TO0_Z		( 80.f - TO0_R )

//------------------------------------------------------------------
// plot coaster
//------------------------------------------------------------------

GTDVCTestObject0::GTDVCTestObject0( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_OBJECT_MODEL_BOX ] != NULL );
	
	dvcmList[ DVC_CARD_OBJECT_MODEL_BOX ] = this;
	
	
	D3DCOLORVALUE		cd = { 1.0f, 1.0f, 1.0f, 1.0f };
	D3DCOLORVALUE		ca = { 0.1f, 0.1f, 0.1f, 0.1f };
	D3DCOLORVALUE		cs = { 1.0f, 0.0f, 0.0f, 0.0f };
	D3DCOLORVALUE		ce = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	mMaterial.Diffuse  = cd;
	mMaterial.Ambient  = ca;
	mMaterial.Specular = cs;
	mMaterial.Emissive = ce;
	mMaterial.Power    = 255.0f;
}

//------------------------------------------------------------------

GTDVCTestObject0::~GTDVCTestObject0( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_OBJECT_MODEL_BOX ] != this );
	
	dvcmList[ DVC_CARD_OBJECT_MODEL_BOX ] = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTDVCTestObject0::dvcIntro( DDvoid )
{
	dggD()->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );
	
	dggD() -> SetMaterial( &mMaterial );
}

//------------------------------------------------------------------

DDvoid	GTDVCTestObject0::dvcOutro( DDvoid )
{
}

//------------------------------------------------------------------
// action & plot
// constract destract
//------------------------------------------------------------------

GTTestObject0::GTTestObject0( DDvoid ) :
	DSAction( DA_ACTOR_ENEMY ),
	DVPlot	( DVC_CARD_OBJECT_MODEL_BOX )
{
	mM.dcUnit();
	
	dcVLoad( mP, 0.0f, 0.0f, 0.0f );
	mR.dcUnit();
	
	dcRandV( 4.0f, mPV );
	dcRandV( _4PI, mRV );
	
	D3DXCreateBox( dggD(), 10.0f, 10.0f, 10.0f, &mMesh, &mAdjacency );
}

//------------------------------------------------------------------

GTTestObject0::~GTTestObject0( DDvoid )
{
	ddRELEASE( mMesh );
	ddRELEASE( mAdjacency );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject0::daAction( DDvoid )
{
	DCvec			M;
	
	// x
	if( mP.x > +TO0_X )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcXn() ), dcXn(), mPV );
		
		dcCross( dcXn(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	if( mP.x < -TO0_X )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcXp() ), dcXp(), mPV );
		
		dcCross( dcXp(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	
	// y
	if( mP.y > +TO0_Y )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcYn() ), dcYn(), mPV );
		
		dcCross( dcYn(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	if( mP.y < -TO0_Y )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcYp() ), dcYp(), mPV );
		
		dcCross( dcYp(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	
	// z
	if( mP.z > +TO0_Z )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcZn() ), dcZn(), mPV );
		
		dcCross( dcZn(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	if( mP.z < -TO0_Z )
	{
		dcVSub( mPV, 2.0f * dcDot( mPV, dcZp() ), dcZp(), mPV );
		
		dcCross( dcZp(), mPV, M );
		dcVAdd ( mRV, _8, M, mRV );
	}
	
	
	dcVAdd( mP, mPV, mP );
	
	mR.dcShaft( mRV );
	
	mM.dcMakeM( mP, mR );
	
	dcVScale( 0.99f, mRV );
	
	return	true;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject0::dvpSight( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------

DDvoid	GTTestObject0::dvpPos( DCvec& p )
{
	p = mP;
}

//------------------------------------------------------------------

DDvoid	GTTestObject0::dvpPlot( DDvoid )
{
	DDGraphic::dgDraw( mM, mMesh, 1 );
}

