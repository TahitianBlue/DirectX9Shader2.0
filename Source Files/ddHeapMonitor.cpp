
// debug heap monitor

#include	"ddHeapMonitor.h"

#ifdef	DD_DEBUG

//--------------------------------------------------------------
//--------------------------------------------------------------

// local class
class	DDHeapMonitor
{
	private:
						 DDHeapMonitor( DDvoid );
		virtual	~DDHeapMonitor( DDvoid );
	
	private:
		DDHeapMonitor*		dhmNext;
		DDHeapMonitor*		dhmPrev;
		_CrtMemState			dhmState;
	
	//----------------------------
	
	public:
		static	DDvoid	dhHeapMonitorInitial( DDvoid );
		static	DDvoid	dhHeapMonitorDispose( DDvoid );
		
		static	DDvoid	dhHeapMonitorSaveStatus( DDvoid );
		static	DDvoid	dhHeapMonitorLeakDetect( DDvoid );
	
	private:
		static	DDHeapMonitor*		dhmBase;
		static	DDHeapMonitor*		dhmLast;
};

//--------------------------------------------------------------
//--------------------------------------------------------------

DDHeapMonitor*	DDHeapMonitor::dhmBase;
DDHeapMonitor*	DDHeapMonitor::dhmLast;

//--------------------------------------------------------------
//--------------------------------------------------------------

DDHeapMonitor::DDHeapMonitor( DDvoid )
{
	// append this to link list last
	dhmPrev = dhmLast;
	dhmNext = NULL;
	
	if( dhmPrev ){  dhmPrev -> dhmNext = this;  }
	else         {	dhmBase            = this;  }
	
	dhmLast = this;
}

//--------------------------------------------------------------

DDHeapMonitor::~DDHeapMonitor( DDvoid )
{
	// remove this from link list last
	ddASSERT( dhmNext != NULL );
	
	if( dhmPrev ){  dhmPrev -> dhmNext = NULL;  }
	else         {  dhmBase            = NULL;  }
	
	dhmLast = dhmPrev;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	DDHeapMonitor::dhHeapMonitorInitial( DDvoid )
{
	dhmBase = NULL;
	dhmLast = NULL;
}

//--------------------------------------------------------------

DDvoid	DDHeapMonitor::dhHeapMonitorDispose( DDvoid )
{
	ddASSERT( dhmBase != NULL );
	ddASSERT( dhmLast != NULL );
}

//--------------------------------------------------------------

DDvoid	DDHeapMonitor::dhHeapMonitorSaveStatus( DDvoid )
{
	// construct link list last
	(DDvoid)new DDHeapMonitor();
	
	// get heap state snap shot
	_CrtMemCheckpoint( &dhmLast -> dhmState );
}

//--------------------------------------------------------------

DDvoid	DDHeapMonitor::dhHeapMonitorLeakDetect( DDvoid )
{
	_CrtMemState		status;
	_CrtMemState		result;
	DDbool					leak;
	
	// get heap state snap shot
	_CrtMemCheckpoint( &status );
	
	// cross check
	leak = ( _CrtMemDifference( &result, &status, &dhmLast -> dhmState ) == TRUE );
	
	// memory leak detect
	ddASSERT( leak );
	
	// leak detect in each block type
	{
		s32			block;
		
		block = _FREE_BLOCK;
		ddASSERT( status.lSizes[ block ] != dhmLast -> dhmState.lSizes[ block ] );
		
		block = _NORMAL_BLOCK;
		ddASSERT( status.lSizes[ block ] != dhmLast -> dhmState.lSizes[ block ] );
		
		block = _CRT_BLOCK;
		ddASSERT( status.lSizes[ block ] != dhmLast -> dhmState.lSizes[ block ] );
		
		block = _IGNORE_BLOCK;
		ddASSERT( status.lSizes[ block ] != dhmLast -> dhmState.lSizes[ block ] );
		
		block = _CLIENT_BLOCK;
		ddASSERT( status.lSizes[ block ] != dhmLast -> dhmState.lSizes[ block ] );
	}
	
	// destruct link list last
	delete	dhmLast;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	dhgHeapMonitorInitial( DDvoid )
{
	DDHeapMonitor::dhHeapMonitorInitial();
}

DDvoid	dhgHeapMonitorDispose( DDvoid )
{
	DDHeapMonitor::dhHeapMonitorDispose();
}

DDvoid	dhgHeapMonitorSaveStatus( DDvoid )
{
	DDHeapMonitor::dhHeapMonitorSaveStatus();
}

DDvoid	dhgHeapMonitorLeakDetect( DDvoid )
{
	DDHeapMonitor::dhHeapMonitorLeakDetect();
}


#endif	DD_DEBUG
