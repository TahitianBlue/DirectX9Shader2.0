
// 跳ね回る球体　相互コリジョン判定

#include	"gtTestObject1.h"

#include	"ddGraphic.h"
#include	"ddInput.h"

#define		TO1_X		( 5.0f )
#define		TO1_Yp	( 24.f )
#define		TO1_Yn	( -5.f )
#define		TO1_Z		( 5.0f )

#define		TO1_R		( 0.35f )
#define		TO1mc		( _3 )					// 摩擦係数に相当
#define		TO1_e		( 1.75f )				// 反発係数

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject1::gttomGravity = false;

//------------------------------------------------------------------
// plot coaster
//------------------------------------------------------------------

GTDVCTestObject1::GTDVCTestObject1( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_OBJECT_MODEL_SPHERE ] != NULL );
	
	dvcmList[ DVC_CARD_OBJECT_MODEL_SPHERE ] = this;
	
	
	D3DCOLORVALUE		cd = { 1.0f, 1.0f, 1.0f, 1.0f };
	D3DCOLORVALUE		ca = { 0.1f, 0.1f, 0.8f, 0.1f };
	D3DCOLORVALUE		ce = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	mMaterial.Diffuse  = cd;
	mMaterial.Ambient  = ca;
	mMaterial.Specular = cd;
	mMaterial.Emissive = ce;
	mMaterial.Power    = 255.0f;
}

//------------------------------------------------------------------

GTDVCTestObject1::~GTDVCTestObject1( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_OBJECT_MODEL_SPHERE ] != this );
	
	dvcmList[ DVC_CARD_OBJECT_MODEL_SPHERE ] = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTDVCTestObject1::dvcIntro( DDvoid )
{
	dggD()->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
	
	dggD() -> SetMaterial( &mMaterial );
	
	// シェーダ用カラーマテリアル
	{
		D3DCOLORVALUE		cd = { 0.8f, 0.8f, 0.8f, 1.0f };
		D3DCOLORVALUE		ca = { 0.3f, 0.3f, 0.3f, 0.0f };
		
		// diffuse color [ c32 ]
		dggD() -> SetVertexShaderConstantF( 32, (f32*)&cd, 1 );
		
		// ambient color [ c33 ]
		dggD() -> SetVertexShaderConstantF( 33, (f32*)&ca, 1 );
	}
}

//------------------------------------------------------------------

DDvoid	GTDVCTestObject1::dvcOutro( DDvoid )
{
}

//------------------------------------------------------------------
// action & plot
//------------------------------------------------------------------

GTTestObject1::GTTestObject1( DDvoid ) :
	DSAction( DA_ACTOR_ENEMY ),
	DVPlot( DVC_CARD_OBJECT_MODEL_SPHERE ),
	DOCollision()
{
	mM.dcUnit();
	
	dcVLoad( mP, 0.0f, 0.0f, 0.0f );
	mR.dcUnit();
	
	dcRandV( 0.07f, mPV );
	dcRandV(  _8PI, mRV );
	
	mRadius = ( dcRandFU( 0.75f ) + 1.0f ) * TO1_R;
	mRadMC  = 1.0f / mRadius;
	
	D3DXCreateSphere( dggD(), mRadius, 24, 24, &mMesh, &mAdjacency );
	
	// collision
	docmP = mP;
	docmV = mPV;
	
	docmMass   = ( 4.0f / 3.0f * PI ) * mRadius * mRadius * mRadius;			// 球体積
	docmRadius = mRadius;
	
	docSetOwner( (DDenum)this );
	docEnable();
	
	// restricted
	mPP    = mP;
	doredEnable();
}

//------------------------------------------------------------------

GTTestObject1::~GTTestObject1( DDvoid )
{
	ddRELEASE( mMesh );
	ddRELEASE( mAdjacency );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject1::daAction( DDvoid )
{
	DCvec			M;		// moment
	DCvec			v;
	
	// x
	if( mP.x + mRadius > +TO1_X )
	{
		mP.x = +TO1_X -  mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcXn() ), dcXn(), mPV );
		
		dcCross( dcXn(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	if( mP.x - mRadius < -TO1_X )
	{
		mP.x = -TO1_X + mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcXp() ), dcXp(), mPV );
		
		dcCross( dcXp(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	
	// y
	if( mP.y + mRadius > TO1_Yp )
	{
		mP.y = TO1_Yp - mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcYn() ), dcYn(), mPV );
		
		dcCross( dcYn(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	if( mP.y - mRadius < TO1_Yn )
	{
		mP.y = TO1_Yn + mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcYp() ), dcYp(), mPV );
		
		dcCross( dcYp(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	
	// z
	if( mP.z + mRadius > +TO1_Z )
	{
		mP.z = +TO1_Z - mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcZn() ), dcZn(), mPV );
		
		dcCross( dcZn(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	if( mP.z - mRadius < -TO1_Z )
	{
		mP.z = -TO1_Z + mRadius;
		dcVSub( mPV, TO1_e * dcDot( mPV, dcZp() ), dcZp(), mPV );
		
		dcCross( dcZp(), mPV, M );
		dcVSub( mRadMC, M, mRV, M );
		dcVAdd( mRV,  TO1mc, M, mRV );
	}
	
	// center gravity
	if( digBits() & ( DI_BIT_BR | DI_BIT_BL )  ||  gttomGravity )
	{
		dcVSub( dcYp(), mP, v );
		
		if( dcNormSqr( v ) > SQR( 2.0f ) )
			dcVScale( 2.0f / dcNorm( v ), v );
		
		dcVAdd( mPV, 0.005f, v, mPV );
	}
	
	// gravity
	dcVAdd( mPV, -0.002f, dcYp(), mPV );
	
	// update
	dcVAdd( mP, mPV, mP );
	
	mR.dcAngular( mRV );
	
	mM.dcMakeM( mP, mR );
	
	dcVScale( 0.99f, mRV );
	
	return	true;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject1::dvpSight( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------

DDvoid	GTTestObject1::dvpPos( DCvec& p )
{
	p = mP;
}

//------------------------------------------------------------------

DDvoid	GTTestObject1::dvpPlot( DDvoid )
{
	DDGraphic::dgDraw( mM, mMesh, 1 );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTTestObject1::docIntro( DDvoid )
{
	docmP = mP;
	docmV = mPV;
}

DDvoid	GTTestObject1::docOutro( DDvoid )
{
	DCvec		v;
	
	if( docCollided() )
	{
	//mP = docmP;
		dcVSub( docmP, mP, v );
		dcVAdd( mP, _2, v, mP );
		
		dcVScale( 1.0f - ( ( 1.0f - ( TO1_e - 1.0f ) ) * 0.25f ), docmV, mPV );
	}
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTTestObject1::doredIntro( DDvoid )
{
}

DDvoid	GTTestObject1::doredProcess( DDvoid )
{
	DCvec					A;
	DCvec					V;
	DCvec					P;
	DORDresult		result;
	f32						length;
	DCvec					dp;
	DCvec					dr;
	DCvec					dp2;
	DCvec					dr2;
	s32						i;
	
	//------------------------------
	// sphere
	
	i   = 2;
	dp2 = dcZero();
	dr2 = dcZero();
	
	while( doredEvaluateSphere( mP, mRadius, result, dp, dr )  &&  i != 0 )
	{
		// position correct
		dcVAdd( mP, ( mRadius - result.Length ) * _3, result.Normal, mP );
		
		// reflect
		dcVSub( mPV, dcMaxClampZero( TO1_e * dcDot( mPV, result.Normal ) ), result.Normal, mPV );
		
		// torque
		dcCross( result.Normal, mPV, V );
		
		dcVSub( V, mRV, V );
		
		dcVAdd( mRV, TO1mc, V, mRV );
		
		// max delta
		if( dcDot( dcYp(), result.Normal ) > COS30 )
		{
			if( dcNormSqr( dp ) > dcNormSqr( dp2 ) )		dp2 = dp;
			if( dcNormSqr( dr ) > dcNormSqr( dr2 ) )		dr2 = dr;
		}
		
		// loop count dec
		i--;
	}

	// delta
	dcVAdd( mP, dp2, mP );
	
	mR.dcAngular( dr2 );
	
	//------------------------------
	// safty arrow
	
	dcVSub( mP, mPP, V );
	
	if( dcNormSqr( V ) > 0.0f )
	{
		dcNormalize( V, A );
		
		length = mRadius * 2.0f * 0.5f + dcDot( V, A );
		
		dcVAdd( mPP, mRadius * -0.5f, A, P );
		
		if( doredEvaluateArrow( P, A, length, result ) )
		{
			dcVSub( mP, length - result.Length, A, mP  );
			
			dcVSub( mPV, dcMaxClampZero( TO1_e * dcDot( mPV, result.Normal ) ), result.Normal, mPV );
		}
	}
	
	// outro
	mPP = mP;
}

DDvoid	GTTestObject1::doredOutro( DDvoid )
{
}

