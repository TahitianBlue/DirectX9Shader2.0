
#ifndef	__dsPlot_h__
#define	__dsPlot_h__

#include	"ddJacket.h"
#include	"ddComputer.h"
#include	"dvCoaster.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DVPlot
{
	public:
						 DVPlot( DVCcard card );
		virtual	~DVPlot( DDvoid );
	
	// copy protect
	protected:
		DVPlot( DVPlot& ){ ddASSERT( true ); }
	
	// over load
	public:
		virtual	DDbool	dvpSight( DDvoid   ) = 0;
		virtual	DDvoid	dvpPos  ( DCvec& p ) = 0;
		virtual	DDvoid	dvpPlot ( DDvoid   ) = 0;
	
	public:
		f32				dvpGetDepth( DDvoid    ){ return	dvpmDepth;	}
		DDvoid		dvpSetDepth( f32 depth ){ dvpmDepth = depth;	}
		
		//------------------
		
		public:
			DVPlot*			dvpGetNext( DDvoid ){ return dvpmNext; }
			DVPlot*			dvpGetPrev( DDvoid ){ return dvpmPrev; }
			
			DVPlot*			dvpGetBase( DDvoid );
			DDvoid			dvpSetBase( DVPlot* plot );
		
		//------------------
		
		protected:
			f32					dvpmDepth;
		
		private:
			DVCcard			dvpmCard;
			DVCoaster*	dvpmCoaster;
			
			DVPlot*			dvpmNext;
			DVPlot*			dvpmPrev;
		
		private:
			static	DVPlot*		dvpmSave;
};

#endif
