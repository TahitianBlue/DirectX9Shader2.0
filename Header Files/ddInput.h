
#ifndef	__ddInput_h__
#define	__ddInput_h__

#define		DIRECTINPUT_VERSION		( 0x0800 )
#include	<dinput.h>

#include	"ddJacket.h"
#include	"ddComputer.h"

//--------------------------------------------------------------
//--------------------------------------------------------------

enum	DIbit
{
	// axis X( R L ) Y( U D )
	DI_BIT_XR			= BIT( 0 ),
	DI_BIT_XL			= BIT( 1 ),
	DI_BIT_YU			= BIT( 2 ),
	DI_BIT_YD			= BIT( 3 ),
	
	// button Start
	DI_BIT_BST		= BIT( 4 ),
	
	// button Select
	DI_BIT_BSL		= BIT( 5 ),
	
	// button R L
	DI_BIT_BR			= BIT( 6 ),
	DI_BIT_BL			= BIT( 7 ),
	
	// button A B C D
	DI_BIT_BA			= BIT( 8 ),			// R
	DI_BIT_BB			= BIT( 9 ),			// D
	DI_BIT_BC			= BIT( 10 ),		// U
	DI_BIT_BD			= BIT( 11 ),		// L
};

//--------------------------------------------------------------
//--------------------------------------------------------------

class	DDInput
{
	// constructor / destructor
	private:
						 DDInput( DDvoid ){}
		virtual	~DDInput( DDvoid ){}
	
	// copy protect
	private:
		DDInput( DDInput& ){ ddASSERT( true ); }
	
	//-----------------------------------

	// accessor
	public:
		static	DDbits	diGetBits( DDvoid ){ return dimBits; }
		static	DDbits	diGetPush( DDvoid ){ return dimPush; }
		
		static	DDvoid	diSetBits( DDbits Bits ){ dimBits = Bits; }
	
	//-----------------------------------
	
	// initial / dispose
	public:
		static	DDbool	diInputInitial( DDvoid );
		static	DDbool	diInputDispose( DDvoid );
	
	// stroke
	public:
		static	DDvoid	diInputProcess( DDvoid );
	
	//-----------------------------------
	
	// direct input call back
	public:
		static	BOOL	CALLBACK	diEnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
		static	BOOL	CALLBACK	diEnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );
	
	// data member
	private:
		static	LPDIRECTINPUT8				dimDXI;						// direct input
		static	LPDIRECTINPUTDEVICE8	dimDXID;					// direct input Device
		static	DIDEVCAPS							dimDXIDCaps;			// joystick spec
	
	private:
		static	DDbits		dimBits;		// current buttons
		static	DDbits		dimPrev;		// previous buttons
		static	DDbits		dimPush;		// off to on moment
};

//--------------------------------------------------------------
//--------------------------------------------------------------

inline	DDbits	digBits( DDvoid )
{
	return	DDInput::diGetBits();
}

inline	DDbits	digPush( DDvoid )
{
	return	DDInput::diGetPush();
}


#endif
