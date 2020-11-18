
#include	"ddJacket.h"
#include	"DealDominator.h"

//--------------------------------------------------------------
//--------------------------------------------------------------

// debugging break point
DDvoid	ddgAssert( DDbool exp )
{
	if( exp )
	{
		if( ddgThis() ){ ddgThis() -> ddSetError(); }		// break point
	}
}

