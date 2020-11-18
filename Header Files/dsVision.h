
#ifndef	__dsVision_h__
#define	__dsVision_h__

#include	"ddJacket.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DSVision
{
	public:
						 DSVision( DDvoid ){}
	 virtual	~DSVision( DDvoid ){}
	
	// copy protect
	protected:
		DSVision( DSVision& ){ ddASSERT( true ); }
	
	//-----------------------------------------------
	
	public:
		virtual	DDvoid	dvVisionInitial( DDvoid );
		virtual	DDvoid	dvVisionDispose( DDvoid );
		virtual	DDvoid	dvVisionProcess( DDvoid );
};

#endif
