
#include	"dvPlot.h"
#include	"dvCoaster.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DVPlot*		DVPlot::dvpmSave = NULL;

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DVPlot::DVPlot( DVCcard card )
{
	dvpmCard    = card;
	dvpmCoaster = DVCoaster::dvcList( card );
	
	// coaster check
	ddASSERT( dvpmCoaster == NULL );
	
	// append link list
	dvpmNext = dvpGetBase();
	dvpmPrev = NULL;
	dvpSetBase( this );
	if( dvpmNext ){ dvpmNext -> dvpmPrev = this; }
}

//-------------------------------------------------------------------

DVPlot::~DVPlot( DDvoid )
{
	// remove link list
	if( dvpmNext ){ dvpmNext -> dvpmPrev = dvpmPrev; }
	if( dvpmPrev ){ dvpmPrev -> dvpmNext = dvpmNext; } else { dvpSetBase( dvpmNext ); }
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DVPlot*	DVPlot::dvpGetBase( DDvoid )
{
	return	dvpmCoaster -> dvcGetPlotBase();
}

DDvoid	DVPlot::dvpSetBase( DVPlot* plot )
{
	dvpmCoaster -> dvcSetPlotBase( plot );
}

