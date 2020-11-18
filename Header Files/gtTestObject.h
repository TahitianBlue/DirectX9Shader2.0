
#ifndef	__gtTestObject_h__
#define	__gtTestObject_h__

#include	"ddComputer.h"
#include	"dsAction.h"
#include	"dvPlot.h"
#include	"dvCoaster.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTDVCTestObject : public DVCoaster
{
	public:
						 GTDVCTestObject( DDvoid );
		virtual	~GTDVCTestObject( DDvoid );
	
	protected:
		virtual	DDvoid	dvcIntro( DDvoid );
		virtual	DDvoid	dvcOutro( DDvoid );
	
	protected:
};

//------------------------------------------------------------------
//------------------------------------------------------------------

class	GTTestObject : public DSAction, public DVPlot
{
	public:
						 GTTestObject( DDvoid );
		virtual	~GTTestObject( DDvoid );
	
	public:
		virtual	DDbool	daAction( DDvoid );
	
	public:
		virtual	DDbool	dvpSight( DDvoid   );
		virtual	DDvoid	dvpPos  ( DCvec& p );
		virtual	DDvoid	dvpPlot ( DDvoid   );
	
	protected:
};

#endif
