
//	deal dominator jacket

#ifndef	__ddJacket_h__
#define	__ddJacket_h__

#include	<windows.h>
#include	<d3dx9.h>
#include	<dxerr9.h>
#include	<tchar.h>					// _T()ƒ}ƒNƒ

//--------------------------------------------------------------
//--------------------------------------------------------------

#ifdef	_DEBUG
#define	DD_DEBUG
#endif	_DEBUG


#ifdef	DD_DEBUG

	#define	ddASSERT( exp )		ddgAssert( exp )
	#define	ddFAILED( res )		if( FAILED( res ) ){ DXTRACE_ERR( NULL, res ); ddgAssert( true ); }
	#define	ddNAN( exp )			ddgAssert( _isnan( exp ) != 0 )

#else		DD_DEBUG

	#define	ddASSERT( exp )		( (DDvoid)0 )
	#define	ddFAILED( res )		( (DDvoid)0 )
	#define	ddNAN( exp )			( (DDvoid)0 )

#endif	DD_DEBUG


#define	ddRELEASE(o)			if( o ){ o->Release(); o = NULL; }

//--------------------------------------------------------------
//--------------------------------------------------------------

typedef	signed		__int8 			s8;
typedef	unsigned	__int8			u8;

typedef	signed		__int16			s16;
typedef	unsigned	__int16			u16;

typedef	signed		__int32			s32;
typedef	unsigned	__int32			u32;

typedef	signed 		__int64			s64;
typedef	unsigned	__int64			u64;

typedef	float									f32;

typedef	char									DDchar;

typedef	bool									DDbool;
typedef	s32										DDenum;
typedef	u32										DDbits;

typedef	void									DDvoid;


//--------------------------------------------------------------
//--------------------------------------------------------------

DDvoid	ddgAssert( DDbool );


#endif
