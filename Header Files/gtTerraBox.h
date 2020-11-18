
#ifndef	__gtTerraBox_h__
#define	__gtTerraBox_h__

#include	"ddComputer.h"
#include	"dsAction.h"
#include	"dvCoaster.h"
#include	"dvPlot.h"
#include	"doRorDynamic.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTDVCTerraBox : public DVCoaster
{
	public:
						 GTDVCTerraBox( DDvoid );
		virtual	~GTDVCTerraBox( DDvoid );
	
	protected:
		virtual	DDvoid	dvcIntro( DDvoid );
		virtual	DDvoid	dvcOutro( DDvoid );
	
	protected:
		D3DMATERIAL9	mMaterial;
};

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTTerraBox : public DSAction, public DVPlot
{
	public:
						 GTTerraBox( DCvec& p, DCvec& r );
		virtual	~GTTerraBox( DDvoid );
	
	// action
	public:
		virtual	DDbool	daAction( DDvoid );
	
	// plot
	public:
		virtual	DDbool	dvpSight( DDvoid   );
		virtual	DDvoid	dvpPos  ( DCvec& p );
		virtual	DDvoid	dvpPlot ( DDvoid   );
	
	protected:
		DCmtx						mM;
		DCvec						mP;
		DCmtx						mR;
		DCvec						mRV;
		
		DORorDynamic*		mRor;
		
		LPD3DXMESH			mMesh;
		LPD3DXBUFFER		mAdjacency;
};

#endif
