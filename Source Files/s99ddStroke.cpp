
#include	"s99ddStroke.h"
#include	"s99ddResource.h"
#include	"s99dsVision.h"

#include	"ddComputer.h"

#include	"gtTerraBox.h"
#include	"gtTestObject.h"
#include	"gtTestObject0.h"
#include	"gtTestObject1.h"
#include	"gtTestObject2.h"

#define		ROOM_X		( 4.25f )
#define		ROOM_Y		( 4.25f * 0.75f )
#define		ROOM_Z		( 4.25f )
#define		BOXSIZE		( 1.2f )
#define		ROOMRAND	( 0.5f )

//---------------------------------------------------------------
//---------------------------------------------------------------

S99DDStroke::S99DDStroke( DDvoid ) :
	DDStroke()
{
	// DDResource and DSVision
	dsmResource = new S99DDResource();
	dsmVision   = new S99DSVision  ();
}

//---------------------------------------------------------------

S99DDStroke::~S99DDStroke( DDvoid )
{
	delete	dsmResource;
	delete	dsmVision;
	
	dsmResource = NULL;
	dsmVision   = NULL;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

DDvoid	S99DDStroke::dsCreateObject( DDvoid )
{
	s32				i;
	s32				j;
	DCvec			p;
	DCvec			r;
	
	// bound cube
//for( i=0 ; i!=8 ; i++ )
//	(DDvoid)new GTTestObject0();
	
	// bound ball
	for( i=0 ; i!=24 ; i++ )
		(DDvoid)new GTTestObject1();
	
	// 部屋　InnerBox
//dcVLoad( p, 0.0f, 0.0f, 0.0f );
//(DDvoid)new GTTestObject2( p );
	
	// 床
	for( i=0 ; i<=ROOM_X*2/BOXSIZE ; i++ )
	{
		for( j=0 ; j<=ROOM_Z*2/BOXSIZE ; j++ )
		{
			dcVLoad( p, -i * BOXSIZE + ROOM_X,  -ROOM_Y + dcRandFS( ROOMRAND ),  -j * BOXSIZE + ROOM_Z );
			
			if( ( j & 1 ) == ( i & 1 ) )
				dcVLoad( r, +0.0f, dcRandFS( _128PI ), 0.0f );
			else
				r = dcZero();
			
			(DDvoid)new GTTerraBox( p, r );
		}
	}
	
	// 空中ボックス 回転処理確認
	{
		DCmtx			m;
		DCvec			p;
		DCvec			r;
		DCvec			a;
		
		m.dcUnit();
		
		// X
		dcVLoad( p, +0.0f, +2.0f, +0.0f );
		m.dcGX( a );
		dcVAdd( p, +4.0f, a, p );
		dcVLoad( r, +_128PI, +0.0f, +0.0f );
		(DDvoid)new GTTerraBox( p, r );
		
		dcVLoad( p, -0.0f, +2.0f, +0.0f );
		m.dcGX( a );
		dcVAdd( p, -4.0f, a, p );
		dcVLoad( r, -_128PI, +0.0f, +0.0f );
		(DDvoid)new GTTerraBox( p, r );
		
		// Y
		dcVLoad( p, +0.0f, +2.0f, +0.0f );
		m.dcGY( a );
		dcVAdd( p, +1.0f, a, p );
		dcVLoad( r, +0.0f, +_128PI, +0.0f );
		(DDvoid)new GTTerraBox( p, r );
		
		dcVLoad( p, -0.0f, +2.0f, +0.0f );
		m.dcGY( a );
		dcVAdd( p, -1.0f, a, p );
		dcVLoad( r, +0.0f, -_128PI, +0.0f );
		(DDvoid)new GTTerraBox( p, r );
		
		// Z
		dcVLoad( p, +0.0f, +2.0f, +0.0f );
		m.dcGZ( a );
		dcVAdd( p, +4.0f, a, p );
		dcVLoad( r, +0.0f, +0.0f, +_128PI );
		(DDvoid)new GTTerraBox( p, r );
		
		dcVLoad( p, +0.0f, +2.0f, +0.0f );
		m.dcGZ( a );
		dcVAdd( p, -2.0f, a, p );
		dcVLoad( r, +0.0f, +0.0f, -_128PI );
		(DDvoid)new GTTerraBox( p, r );
	}
	
	// test DCmtx anti R ( vector multi post and anti )
	{
		DCmtx				m;
		DCvec				vx;
		DCvec				vy;
		DCvec				vz;
		
		vx = dcXp();
		vy = dcYp();
		vz = dcZp();
		
		m.dcUnit();
		m.dcRotateX( _4PI );
		m.dcRotateY( _2PI );
		m.dcRotateZ( _6PI );
		
		// post multi
		m.dcVxM33( vx );
		m.dcVxM33( vy );
		m.dcVxM33( vz );
		
		// anti multi
		m.dcM33xV( vx );
		m.dcM33xV( vy );
		m.dcM33xV( vz );
		
		// valid!
		ddASSERT( dcNormSqr( dcXp(), vx ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcYp(), vy ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcZp(), vz ) >= SQR( 0.00001f ) );
	}
	
/*
	// test DCmtx anti S ( vector multi post and anti )
	{
		DCmtx				m;
		DCvec				vx;
		DCvec				vy;
		DCvec				vz;
		
		vx = dcXp();
		vy = dcYp();
		vz = dcZp();
		
		m.dcUnit();
		m.dcScaleX( 0.5f );
		m.dcScaleY( 2.0f );
		m.dcScaleZ( 3.0f );
		
		// post multi
		m.dcVxM33( vx );
		m.dcVxM33( vy );
		m.dcVxM33( vz );
		
		// anti multi
		m.dcM33xV( vx );
		m.dcM33xV( vy );
		m.dcM33xV( vz );
		
		// invalid!
		ddASSERT( dcNormSqr( dcXp(), vx ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcYp(), vy ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcZp(), vz ) >= SQR( 0.00001f ) );
	}
*/
	
/*
	// test DCmtx anti T ( vector multi post and anti )
	{
		DCmtx				m;
		DCvec				vx;
		DCvec				vy;
		DCvec				vz;
		
		vx = dcXp();
		vy = dcYp();
		vz = dcZp();
		
		m.dcUnit();
		m.dcTranslate( 1.0f, 2.0f, 0.5f );
		
		// post multi
		m.dcVxM( vx );
		m.dcVxM( vy );
		m.dcVxM( vz );
		
		// anti multi
		m.dcM33xV( vx );
		m.dcM33xV( vy );
		m.dcM33xV( vz );
		
		// invalid! M33 not used matrix translate
		ddASSERT( dcNormSqr( dcXp(), vx ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcYp(), vy ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcZp(), vz ) >= SQR( 0.00001f ) );
	}
*/
	
	// test DCmtx dcCTInverse TR
	{
		DCmtx				m;
		DCvec				vx;
		DCvec				vy;
		DCvec				vz;
		
		vx = dcXp();
		vy = dcYp();
		vz = dcZp();
		
		m.dcUnit();
		m.dcTranslate( 1.0f, 2.0f, 3.0f );
		m.dcRotateZXY( _4PI, _6PI, _3PI );
		m.dcTranslate( 2.5f, 0.2f, 0.4f );
		m.dcRotateZXY( _6PI, _2PI, _7PI );
	//m.dcScale( 1.5f, 0.5f, 3.0f );				invalid S
		
		// post multi
		m.dcVxM( vx );
		m.dcVxM( vy );
		m.dcVxM( vz );
		
		// anti multi ( CTInverse )
		m.dcCTInverse( m );
		m.dcVxM( vx );
		m.dcVxM( vy );
		m.dcVxM( vz );
		
		// valid! CTInverse TR
		ddASSERT( dcNormSqr( dcXp(), vx ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcYp(), vy ) >= SQR( 0.00001f ) );
		ddASSERT( dcNormSqr( dcZp(), vz ) >= SQR( 0.00001f ) );
	}
}

//---------------------------------------------------------------

DDvoid	S99DDStroke::dsDeleteObject( DDvoid )
{
}

