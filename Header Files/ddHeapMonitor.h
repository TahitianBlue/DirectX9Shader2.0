
// debug heap monitor

#ifndef	__ddHeapMonitor_h__
#define	__ddHeapMonitor_h__

#include	<crtdbg.h>
#include	"ddJacket.h"

//--------------------------------------------------------------
//--------------------------------------------------------------

#ifdef	DD_DEBUG

	DDvoid	dhgHeapMonitorInitial( DDvoid );
	DDvoid	dhgHeapMonitorDispose( DDvoid );
	DDvoid	dhgHeapMonitorSaveStatus( DDvoid );
	DDvoid	dhgHeapMonitorLeakDetect( DDvoid );

#else		DD_DEBUG

	#define	dhgHeapMonitorInitial()						( (DDvoid)0 )
	#define	dhgHeapMonitorDispose()						( (DDvoid)0 )
	#define	dhgHeapMonitorSaveStatus()				( (DDvoid)0 )
	#define	dhgHeapMonitorLeakDetect()				( (DDvoid)0 )

#endif	DD_DEBUG


#endif
