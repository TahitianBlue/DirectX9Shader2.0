
#include	"dvCoaster.h"
#include	"dvPlot.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DVCoaster*	DVCoaster::dvcmList[ DVC_CARD_TOTAL ];

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DVCoaster::DVCoaster( DDvoid )
{
	dvcmPlotBase = NULL;
}

//-------------------------------------------------------------------

DVCoaster::~DVCoaster( DDvoid )
{
	ddASSERT( dvcmPlotBase != NULL );
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcPlot( DDvoid )
{
	DVPlot*		plot;
	
	plot = dvcmPlotBase;
	
	do
	{
		if( plot -> dvpSight() )
		{
			plot -> dvpPlot();
		}
		plot = plot -> dvpGetNext();
	}
	while( plot );
}

//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcProcess( DDvoid )
{
	if( dvcmPlotBase )
	{
		dvcIntro();
		dvcPlot ();
		dvcOutro();
	}
}

//-------------------------------------------------------------------
// statics
//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcCoasterInitial( DDvoid )
{
	for( s32 i=0 ; i!=DVC_CARD_TOTAL ; i++ )
	{
		dvcmList[ i ] = NULL;
	}
}

//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcCoasterDispose( DDvoid )
{
	for( s32 i=0 ; i!=DVC_CARD_TOTAL ; i++ )
	{
		if( dvcmList[ i ] )
		{
			delete	dvcmList[ i ];
			
			dvcmList[ i ] = NULL;
		}
	}
}

//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcCoasterProcess( DDvoid )
{
	for( s32 i=0 ; i!=DVC_CARD_TOTAL ; i++ )
		if( dvcmList[ i ] )
			dvcmList[ i ] -> dvcProcess();
}

//-------------------------------------------------------------------

DDvoid	DVCoaster::dvcCoasterProcess( DVCcard top, DVCcard end )
{
	for( s32 i=( top + 1 ) ; i!=end ; i++ )
		if( dvcmList[ i ] )
			dvcmList[ i ] -> dvcProcess();
}

// END OF FILE