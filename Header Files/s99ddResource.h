
#ifndef	__s99ddResource_h__
#define	__s99ddResource_h__

#include	"ddResource.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S99DDResource : public DDResource
{
	public:
						 S99DDResource( DDvoid ){}
	 virtual	~S99DDResource( DDvoid ){}
	
	public:
		virtual	DDvoid	ddResourceInitial( DDvoid );
		virtual	DDvoid	ddResourceDispose( DDvoid );
	
	//-----------------------------------------------
	private:
};

#endif
