
#ifndef	__s97ddResource_h__
#define	__s97ddResource_h__

#include	"ddResource.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S97DDResource : public DDResource
{
	public:
						 S97DDResource( DDvoid ){}
	 virtual	~S97DDResource( DDvoid ){}
	
	public:
		virtual	DDvoid	ddResourceInitial( DDvoid );
		virtual	DDvoid	ddResourceDispose( DDvoid );
	
	//-----------------------------------------------
	private:
		
};

#endif
