
#include	"dsAction.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DSAction*		DSAction::damBase[ DA_ACTOR_TOTAL ];
DSAction*		DSAction::damLast[ DA_ACTOR_TOTAL ];
DSAction*		DSAction::damSave;

//-------------------------------------------------------------------
// constract destract
//-------------------------------------------------------------------

DSAction::DSAction( DA_ACTOR actor )
{
	damActor = actor;
	
	// append this to link list last
	damPrev = damLast[ damActor ];
	damNext = NULL;
	
	if( damPrev ){  damPrev -> damNext  = this;  }
	else         {  damBase[ damActor ] = this;	 }
	
	damLast[ damActor ] = this;
}

//-------------------------------------------------------------------

DSAction::~DSAction( void )
{
	// remove this from link list
	if( damSave == this ){  damSave = damNext;  }
	
	if( damPrev ){  damPrev -> damNext  = damNext;  }
	else         {  damBase[ damActor ] = damNext;  }
	
	if( damNext ){  damNext -> damPrev  = damPrev;  }
	else         {	damLast[ damActor ] = damPrev;  }
}

//-------------------------------------------------------------------
// stroke
//-------------------------------------------------------------------

DDvoid		DSAction::daActionInitial( DDvoid )
{
	damSave = NULL;
	
	// NULL clear da link base[] and last[]
	for( s32 i = 0 ; i < DA_ACTOR_TOTAL ; i++ )
	{
		damBase[ i ] = NULL;
		damLast[ i ] = NULL;
	}
}

//-------------------------------------------------------------------

DDvoid		DSAction::daActionDispose( DDvoid )
{
	damSave = NULL;
	
	for( s32 i = 0 ; i < DA_ACTOR_TOTAL ; i++ )
	{
		while( damBase[ i ] )
		{
			delete	damBase[ i ];
		}
	}
}

//-------------------------------------------------------------------

DDvoid		DSAction::daActionProcess( DA_ACTOR actor )
{
	DSAction*		action;
	
	action = damBase[ actor ];
	
	while( action )
	{
		damSave = action -> daGetNext();
		
		if( action -> daAction() == false ){ delete action; }
		
		action = damSave;
	}
}


// END OF FILE