
#ifndef	__gtTestObject2_h__
#define	__gtTestObject2_h__

#include	"ddComputer.h"
#include	"dsAction.h"
#include	"dvCoaster.h"
#include	"dvPlot.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTDVCTestObject2 : public DVCoaster
{
	public:
						 GTDVCTestObject2( DDvoid );
		virtual	~GTDVCTestObject2( DDvoid );
	
	protected:
		virtual	DDvoid	dvcIntro( DDvoid );
		virtual	DDvoid	dvcOutro( DDvoid );
	
	protected:
		D3DMATERIAL9	mMaterial;
};

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTTestObject2 : public DSAction, public DVPlot
{
	public:
						 GTTestObject2( DCvec& p );
		virtual	~GTTestObject2( DDvoid );
	
	// action
	public:
		virtual	DDbool	daAction( DDvoid );
	
	// plot
	public:
		virtual	DDbool	dvpSight( DDvoid   );
		virtual	DDvoid	dvpPos  ( DCvec& p );
		virtual	DDvoid	dvpPlot ( DDvoid   );
	
	protected:
		DCmtx			mM;
		
		DCvec			mP;
		DCmtx			mR;
		
		LPD3DXMESH		mMesh;
		LPD3DXBUFFER	mAdjacency;
};

#endif
