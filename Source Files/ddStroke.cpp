
#include	"ddStroke.h"

#include	"ddComputer.h"
#include	"ddResource.h"
#include	"ddInput.h"
#include	"ddHeapMonitor.h"
#include	"dsAction.h"
#include	"dsOption.h"
#include	"dsVision.h"

#include	"s97ddStroke.h"
#include	"s98ddStroke.h"
#include	"s99ddStroke.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

DDStroke*		DDStroke::dsmThis = NULL;

//---------------------------------------------------------------
//---------------------------------------------------------------

DDvoid	DDStroke::dsStrokeInitial( DSstage stage )
{
	// stroke constructor ( + resource & vision )
	dhgHeapMonitorSaveStatus();
	
	switch( stage )
	{
		default:							ddASSERT( true );						break;
		
//	case	DS_STAGE_00:		(DDvoid)new S00DDStroke;		break;
		
		case	DS_STAGE_97:		(DDvoid)new S97DDStroke;		break;
		case	DS_STAGE_98:		(DDvoid)new S98DDStroke;		break;
		case	DS_STAGE_99:		(DDvoid)new S99DDStroke;		break;
	}
	
	//---------------------
	
	dhgHeapMonitorSaveStatus();
	dsmThis -> dsmResource -> ddResourceInitial();
	
		dhgHeapMonitorSaveStatus();
		dsmThis -> dsmVision -> dvVisionInitial();
		
			dhgHeapMonitorSaveStatus();
			DSOption::doOptionInitial();
			
				dhgHeapMonitorSaveStatus();
				DSAction::daActionInitial();
				
					dsmThis -> dsCreateObject();
}

//---------------------------------------------------------------

DDvoid	DDStroke::dsStrokeDispose( DDvoid )
{
					dsmThis -> dsDeleteObject();
					
				DSAction::daActionDispose();
				dhgHeapMonitorLeakDetect();
				
			DSOption::doOptionDispose();
			dhgHeapMonitorLeakDetect();
			
		dsmThis -> dsmVision -> dvVisionDispose();
		dhgHeapMonitorLeakDetect();
		
	dsmThis -> dsmResource -> ddResourceDispose();
	dhgHeapMonitorLeakDetect();
	
	//---------------------
	
	// DDStroke destructor ( + DDResource & DSVision )
	delete	dsmThis;
	
	dhgHeapMonitorLeakDetect();
}

//---------------------------------------------------------------

DDvoid	DDStroke::dsStrokeProcess( DDvoid )
{
	DDInput::diInputProcess();
	
	
	switch( dsmThis -> dsmStatus )
	{
		case	DS_STATUS_GOING:
			
			dsmThis -> dsProcessAction();
			dsmThis -> dsProcessOption();
			dsmThis -> dsProcessVision();
			
			if( digPush() & DI_BIT_BST )
				dsmThis -> dsmStatus = DS_STATUS_PAUSE;
			
			break;
		
		case	DS_STATUS_PAUSE:
			
			dsmThis -> dsProcessVision();
			
			if( digPush() & DI_BIT_BST )
				dsmThis -> dsmStatus = DS_STATUS_GOING;
			
			break;
	}
}

//---------------------------------------------------------------
//---------------------------------------------------------------

DDStroke::DDStroke( DDvoid )
{
	// set one and only this
	ddASSERT( dsmThis != NULL );
	
	dsmThis = this;
	
	// set default status
	dsmStatus = DS_STATUS_GOING;
	
	// clear instance socket
	dsmResource = NULL;
	dsmVision   = NULL;
}

//---------------------------------------------------------------

DDStroke::~DDStroke( DDvoid )
{
	// check instance socket already deleted
	ddASSERT( dsmResource != NULL );
	ddASSERT( dsmVision   != NULL );
	
	// clear one and only this
	ddASSERT( dsmThis != this );
	
	dsmThis = NULL;
}

//---------------------------------------------------------------
// process method
//---------------------------------------------------------------

DDvoid	DDStroke::dsProcessAction( DDvoid )
{
	s32			i;
	
	for( i=0 ; i!=DA_ACTOR_TOTAL ; i++ )
	{
		DSAction::daActionProcess( ( DA_ACTOR )i );
	}
}

DDvoid	DDStroke::dsProcessOption( DDvoid )
{
	DSOption::doOptionProcess();
}

DDvoid	DDStroke::dsProcessVision( DDvoid )
{
	dsmVision -> dvVisionProcess();
}

