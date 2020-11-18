
#ifndef	__ddStroke_h__
#define	__ddStroke_h__

#include	"ddJacket.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

enum	DSstatus
{
	DS_STATUS_GOING,
	DS_STATUS_PAUSE,
	
	DS_STATUS_TOTAL
};

enum	DSstage
{
	DS_STAGE_NULL,
	
//DS_STAGE_00,			// selector
	DS_STAGE_97,
	DS_STAGE_98,
	DS_STAGE_99,
	
	DS_STAGE_TOTAL
};

//---------------------------------------------------------------
//---------------------------------------------------------------

// forward declare
class	DDResource;
class	DSVision;


class	DDStroke
{
	protected:
						 DDStroke( DDvoid );
		virtual	~DDStroke( DDvoid );
	
	// copy protect
	protected:
		DDStroke( DDStroke& ){ ddASSERT( true ); }
	
	protected:
		virtual	DDvoid	dsCreateObject( DDvoid ) = 0;
		virtual	DDvoid	dsDeleteObject( DDvoid ) = 0;
	
	//------------------------------
	
	// local process
	private:
		DDvoid	dsProcessAction( DDvoid );
		DDvoid	dsProcessOption( DDvoid );
		DDvoid	dsProcessVision( DDvoid );
	
	// local memba
	protected:
		DDResource*		dsmResource;
		DSVision*			dsmVision;
	
	private:
		DSstatus			dsmStatus;
	
	//------------------------------
	
	// stroke ( constructor / destructor )
	public:
		static	DDvoid	dsStrokeInitial( DSstage stage );
		static	DDvoid	dsStrokeDispose( DDvoid );
	
	public:
		static	DDvoid	dsStrokeProcess( DDvoid );
	
	// current stage stroke instance
	private:
		static	DDStroke*		dsmThis;
};


#endif
 