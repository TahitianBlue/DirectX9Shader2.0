
#ifndef	__s98ddResource_h__
#define	__s98ddResource_h__

#include	"ddResource.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S98DDResource : public DDResource
{
	public:
						 S98DDResource( DDvoid ){}
	 virtual	~S98DDResource( DDvoid ){}
	
	public:
		virtual	DDvoid	ddResourceInitial( DDvoid );
		virtual	DDvoid	ddResourceDispose( DDvoid );
	
	//-----------------------------------------------
	private:
};

#endif
