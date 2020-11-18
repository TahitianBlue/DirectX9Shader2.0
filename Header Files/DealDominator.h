
//----------------------------------------------------------
//----------------------------------------------------------
//	Deal Dominator
//		2002-04-19		tahei katagai
//----------------------------------------------------------
//----------------------------------------------------------

#ifndef	__DealDominator_h__
#define	__DealDominator_h__

#include	"ddJacket.h"
#include	"ddComputer.h"
#include	"ddStroke.h"

//----------------------------------------------------------
//----------------------------------------------------------

#define	CAPTION			"Deal Dominator Test"

#define	FULLSCREEN	( 0 )			// 0 = window mode : 1 = full screen mode

//----------------------------------------------------------
//----------------------------------------------------------

extern	LRESULT CALLBACK	procMain( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

//----------------------------------------------------------
//----------------------------------------------------------

class	DealDominator
{
	public:
		// constructor destructor
						 DealDominator( HINSTANCE hInst );
		virtual	~DealDominator( DDvoid );
	
	// copy protect
	private:
		DealDominator( DealDominator& ){ ddASSERT( true ); }
	
	// access
	public:
		static	DealDominator*	ddThis( DDvoid ){ return ddmThis; }
		
		HINSTANCE								ddGetHInst( DDvoid ){ return ddmHInst; }
		HWND										ddGetH_wnd( DDvoid ){ return ddmH_wnd; }
		
		// Error
		DDbool	ddGetError( DDvoid ){ return ddmError; }
		DDvoid	ddSetError( DDvoid ){ ddmError = true; }
		
		DDbool	ddGetEnd( DDvoid ){ return ddmEnd; }
		DDvoid	ddSetEnd( DDvoid ){ ddmEnd = true; }
	
	//--------------------------------
	
	// directX
	private:
		DDbool	ddInitialGraphic( DDvoid );
		DDbool	ddDisposeGraphic( DDvoid );
		
		DDbool	ddInitialSound( DDvoid );
		DDbool	ddDisposeSound( DDvoid );
		
		DDbool	ddInitialInput( DDvoid );
		DDbool	ddDisposeInput( DDvoid );
	
	//--------------------------------
	
	// game stroke
	public:
		DDvoid				ddMain  ( DDvoid );
	
	private:
		DDbool				ddStroke( DDvoid );
	
	//--------------------------------
	
	// system member
	private:
		DDbool									ddmError;
		DDbool									ddmEnd;
	
	private:
		DSstage									ddmStage;
		DSstage									ddmNextStage;
	
	//--------------------------------
	
	// create window method
	public:
		static	DDvoid	ddCreateWindow( HINSTANCE hInst );
	
	// windows and directX member
	private:
		static	HINSTANCE				ddmHInst;
		static	HWND						ddmH_wnd;
	
	private:
		static	DealDominator*	ddmThis;
};

//----------------------------------------------------------

inline DealDominator*	ddgThis( DDvoid )
{
	return	DealDominator::ddThis();
}

#endif
