
#ifndef	__dsOption_h__
#define	__dsOption_h__

#include	"ddJacket.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

enum	DOentry
{
	DO_ENTRY_ENABLE,
	DO_ENTRY_DISABLE,
	DO_ENTRY_TOTAL
};

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	DSOption
{
	private:
						 DSOption( DDvoid ){}
	 virtual	~DSOption( DDvoid ){}
	
	// copy protect
	private:
		DSOption( DSOption& ){ ddASSERT( true ); }
	
	//-----------------------------------------------
	
	public:
		static	DDvoid	doOptionInitial( DDvoid );
		static	DDvoid	doOptionDispose( DDvoid );
		static	DDvoid	doOptionProcess( DDvoid );
};

#endif
