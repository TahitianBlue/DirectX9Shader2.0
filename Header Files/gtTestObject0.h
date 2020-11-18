
#ifndef	__gtTestObject0_h__
#define	__gtTestObject0_h__

#include	"ddComputer.h"
#include	"dsAction.h"
#include	"dvCoaster.h"
#include	"dvPlot.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTDVCTestObject0 : public DVCoaster
{
	public:
						 GTDVCTestObject0( DDvoid );
		virtual	~GTDVCTestObject0( DDvoid );
	
	protected:
		virtual	DDvoid	dvcIntro( DDvoid );
		virtual	DDvoid	dvcOutro( DDvoid );
	
	protected:
		D3DMATERIAL9	mMaterial;
};

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTTestObject0 : public DSAction, public DVPlot
{
	public:
						 GTTestObject0( DDvoid );
		virtual	~GTTestObject0( DDvoid );
	
	public:
		virtual	DDbool	daAction( DDvoid );
	
	public:
		virtual	DDbool	dvpSight( DDvoid   );
		virtual	DDvoid	dvpPos  ( DCvec& p );
		virtual	DDvoid	dvpPlot ( DDvoid   );
	
	protected:
		DCmtx			mM;
		
		DCvec			mP;
		DCmtx			mR;
		DCvec			mPV;
		DCvec			mRV;
		
		LPD3DXMESH		mMesh;
		LPD3DXBUFFER	mAdjacency;
};

#endif
