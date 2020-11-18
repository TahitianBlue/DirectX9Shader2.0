
#include	"s98ddStroke.h"
#include	"s98ddResource.h"
#include	"s98dsVision.h"

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

S98DDStroke::S98DDStroke( DDvoid ) :
	DDStroke()
{
	// DDResource and DSVision
	dsmResource = new S98DDResource();
	dsmVision   = new S98DSVision  ();
}

//---------------------------------------------------------------

S98DDStroke::~S98DDStroke( DDvoid )
{
	delete	dsmResource;
	delete	dsmVision;
	
	dsmResource = NULL;
	dsmVision   = NULL;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

DDvoid	S98DDStroke::dsCreateObject( DDvoid )
{
	s32				i;
	s32				j;
	DCvec			p;
	DCvec			r;
	
	// bound ball
	for( i=0 ; i!=16 ; i++ )
		(DDvoid)new GTTestObject1();
	
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
}

//---------------------------------------------------------------

DDvoid	S98DDStroke::dsDeleteObject( DDvoid )
{
}

