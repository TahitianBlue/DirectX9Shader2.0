
// 部屋を想定したＢＯＸ　敷き詰める

#include	"gtTerraBox.h"
#include	"ddGraphic.h"

#define		TERRABOX_SIZE		( 1.f )

//------------------------------------------------------------------
//------------------------------------------------------------------

DORDsphere		gtTBoxRorSphere =
{
	{ 0.0f, 0.0f, 0.0f },
	0.866025404f						// sqrt( x*x + y*y + z*z )
};

DORDvertex		gtTBoxRorVertexList[ 8 ] =
{
	{	+0.5f,	+0.5f,	+0.5f	},
	{	+0.5f,	+0.5f,	-0.5f	},
	{	-0.5f,	+0.5f,	+0.5f	},
	{	-0.5f,	+0.5f,	-0.5f	},
	
	{	+0.5f,	-0.5f,	+0.5f	},
	{	+0.5f,	-0.5f,	-0.5f	},
	{	-0.5f,	-0.5f,	+0.5f	},
	{	-0.5f,	-0.5f,	-0.5f	},
};

DORDtriangle	gtTBoxRorTriangleList[ 12 ] =
{
	// 上
	{
		-0.5f,
		{	+0,		+16384,		+0	},
		{	0, 2, 1 },
	},
	{
		-0.5f,
		{	+0,		+16384,		+0	},
		{	1, 2, 3 },
	},
	// 前
	{
		-0.5f,
		{	+0,		+0,		-16384	},
		{	1, 3, 5 },
	},
	{
		-0.5f,
		{	+0,		+0,		-16384	},
		{	5, 3, 7 },
	},
	// 右
	{
		-0.5f,
		{	-16384,		+0,		+0	},
		{	3, 2, 7 },
	},
	{
		-0.5f,
		{	-16384,		+0,		+0	},
		{	7, 2, 6 },
	},
	// 奥
	{
		-0.5f,
		{	+0,		+0,		+16384	},
		{	2, 0, 6 },
	},
	{
		-0.5f,
		{	+0,		+0,		+16384	},
		{	6, 0, 4 },
	},
	// 左
	{
		-0.5f,
		{	+16384,		+0,		+0	},
		{	0, 1, 4 },
	},
	{
		-0.5f,
		{	+16384,		+0,		+0	},
		{	4, 1, 5 },
	},
	// 下
	{
		-0.5f,
		{	+0,		-16384,		+0	},
		{	5, 7, 4 },
	},
	{
		-0.5f,
		{	+0,		-16384,		+0	},
		{	4, 7, 6 },
	},
};

DORDtriangles	gtTBoxRorTrianglesData =
{
	12,															// number of triangles
	8,															// number of vertex
	gtTBoxRorTriangleList,					// triangle list
	gtTBoxRorVertexList,						// vertex list
	{
		(u8)DORD_SENS_MATERIAL_00,				// material
		(u8)DORD_SENS_BEHAVIOR_00_NONE,		// behavior
	}
};

//------------------------------------------------------------------
// plot coaster
//------------------------------------------------------------------

GTDVCTerraBox::GTDVCTerraBox( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_TERRAIN_MODEL_TERRA_BOX ] != NULL );
	
	dvcmList[ DVC_CARD_TERRAIN_MODEL_TERRA_BOX ] = this;
	
	D3DCOLORVALUE		cd = { 1.0f, 1.0f, 1.0f, 1.0f };
	D3DCOLORVALUE		ca = { 0.1f, 0.8f, 0.1f, 0.0f };
	D3DCOLORVALUE		cs = { 1.0f, 0.0f, 0.0f, 0.0f };
	D3DCOLORVALUE		ce = { 0.0f, 0.0f, 0.0f, 0.0f };
	
	mMaterial.Diffuse  = cd;
	mMaterial.Ambient  = ca;
	mMaterial.Specular = cs;
	mMaterial.Emissive = ce;
	mMaterial.Power    = 255.0f;
}

//------------------------------------------------------------------

GTDVCTerraBox::~GTDVCTerraBox( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_TERRAIN_MODEL_TERRA_BOX ] != this );
	
	dvcmList[ DVC_CARD_TERRAIN_MODEL_TERRA_BOX ] = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTDVCTerraBox::dvcIntro( DDvoid )
{
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

DDvoid	GTDVCTerraBox::dvcOutro( DDvoid )
{
}


//------------------------------------------------------------------
// action & plot
//------------------------------------------------------------------

GTTerraBox::GTTerraBox( DCvec& p, DCvec& r ) :
	DSAction( DA_ACTOR_ENEMY ),
	DVPlot	( DVC_CARD_TERRAIN_MODEL_TERRA_BOX )
{
	mP = p;
	mR.dcIdentity();
	
	mM.dcMakeM( mP, mR );
	mM.dcScale( TERRABOX_SIZE );
	
	mRV = r;
	
	D3DXCreateBox( dggD(), 1.0f, 1.0f, 1.0f, &mMesh, &mAdjacency );
	
	// restrictor set up
	{
		DORorDomain*	domain;
		
		// polygon triangle
		domain = new DORDTriangles( gtTBoxRorTrianglesData, NULL );
		
		// wraper sphere
		domain = new DORDSphere( gtTBoxRorSphere, domain, NULL );
		
		mRor = new DORorDynamic( *domain );
		
		mRor -> dororSetup( TERRABOX_SIZE, mM );
		
		mRor -> dororEnable( DOR_TYPE_EARTH );
	}
}


GTTerraBox::~GTTerraBox( DDvoid )
{
	delete	mRor;
	
	ddRELEASE( mMesh );
	ddRELEASE( mAdjacency );
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTerraBox::daAction( DDvoid )
{
/*
	mR.dcRotateZXY( mRV );
	
	mR.dcRotateY( -mRV.y );
	mR.dcRotateX( -mRV.x );
	mR.dcRotateZ( -mRV.z );
*/
	mR.dcRotateY( mRV.y );
	mR.dcRotateX( mRV.x );
	mR.dcRotateZ( mRV.z );
	
	mM.dcMakeM( mP, mR );
	mM.dcScale( TERRABOX_SIZE );
	
	mRor -> dororUpdate( mM );
	
	return	true;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTerraBox::dvpSight( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------

DDvoid	GTTerraBox::dvpPos( DCvec& p )
{
	p = mP;
}

//------------------------------------------------------------------

DDvoid	GTTerraBox::dvpPlot( DDvoid )
{
	DDGraphic::dgDraw( mM, mMesh, 1 );
}

