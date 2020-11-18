
#ifndef	__ddResource_h__
#define	__ddResource_h__

#include	"ddJacket.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DDResource
{
	public:
						 DDResource( DDvoid ){}
	 virtual	~DDResource( DDvoid ){}
	
	// copy protect
	protected:
		DDResource( DDResource& ){ ddASSERT( true ); }
	
	//-----------------------------------------------
	public:
		virtual	DDvoid	ddResourceInitial( DDvoid );
		virtual	DDvoid	ddResourceDispose( DDvoid );
};

#endif
