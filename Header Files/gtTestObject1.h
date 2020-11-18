
#ifndef	__gtTestObject1_h__
#define	__gtTestObject1_h__

#include	"ddComputer.h"
#include	"dsAction.h"
#include	"dvCoaster.h"
#include	"dvPlot.h"
#include	"doCollision.h"
#include	"doRestriction.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTDVCTestObject1 : public DVCoaster
{
	public:
						 GTDVCTestObject1( DDvoid );
		virtual	~GTDVCTestObject1( DDvoid );
	
	protected:
		virtual	DDvoid	dvcIntro( DDvoid );
		virtual	DDvoid	dvcOutro( DDvoid );
	
	protected:
		D3DMATERIAL9	mMaterial;
};

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTTestObject1 :
	public DSAction,
	public DVPlot,
	public DOCollision,
	public DORestricted
{
	public:
						 GTTestObject1( DDvoid );
		virtual	~GTTestObject1( DDvoid );
	
	// action
	public:
		virtual	DDbool	daAction( DDvoid );
	
	// plot
	public:
		virtual	DDbool	dvpSight( DDvoid   );
		virtual	DDvoid	dvpPos  ( DCvec& p );
		virtual	DDvoid	dvpPlot ( DDvoid   );
	
	// collision
	public:
		virtual	DDvoid	docIntro( DDvoid );
		virtual	DDvoid	docOutro( DDvoid );
	
	// restricted
	public:
		virtual	DDvoid	doredIntro  ( DDvoid );
		virtual	DDvoid	doredProcess( DDvoid );
		virtual	DDvoid	doredOutro  ( DDvoid );
	
	
	protected:
		DCmtx			mM;
		
		DCvec			mP;
		DCmtx			mR;
		DCvec			mPV;
		DCvec			mRV;
		
		f32				mRadius;
		f32				mRadMC;
		
		DCvec			mPP;
		
		LPD3DXMESH		mMesh;
		LPD3DXBUFFER	mAdjacency;
	
	
	public:
		static	DDvoid	gttoSetGravity( DDbool Flag ){ gttomGravity = Flag; }
	
	private:
		static	DDbool	gttomGravity;
};

#endif
