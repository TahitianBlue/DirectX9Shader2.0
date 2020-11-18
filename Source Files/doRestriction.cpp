
#include	"doRestriction.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DORestriction::dorRestrictionInitial( DDvoid )
{
	DORestrictor::dororRestrictorInitial();
	DORestricted::doredRestrictedInitial();
}

//---------------------------------------------------------------------

DDvoid		DORestriction::dorRestrictionDispose( DDvoid )
{
	DORestricted::doredRestrictedDispose();
	DORestrictor::dororRestrictorDispose();
}

//---------------------------------------------------------------------

DDvoid		DORestriction::dorRestrictionIntro( DDvoid )
{
	DORestrictor::dororRestrictorIntro();
	DORestricted::doredRestrictedIntro();
}

//---------------------------------------------------------------------

DDvoid		DORestriction::dorRestrictionProcess( DDvoid )
{
	DORestricted*		rED;
	
	for( rED = DORestricted::doredGetBase( DO_ENTRY_ENABLE ) ; rED != NULL ; rED = rED -> doredGetNext() )
		rED->doredProcess();
}

//---------------------------------------------------------------------

DDvoid		DORestriction::dorRestrictionOutro( DDvoid )
{
	DORestrictor::dororRestrictorOutro();
	DORestricted::doredRestrictedOutro();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORestricted*	DORestricted::doredmSAVE;
DORestricted*	DORestricted::doredmBASE[ DO_ENTRY_TOTAL ];

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DORestricted::doredRestrictedInitial( DDvoid )
{
	doredmSAVE = NULL;
	
	doredmBASE[ DO_ENTRY_ENABLE  ] = NULL;
	doredmBASE[ DO_ENTRY_DISABLE ] = NULL;
}

DDvoid		DORestricted::doredRestrictedDispose( DDvoid )
{
	doredmSAVE = NULL;
	
	while( doredmBASE[ DO_ENTRY_ENABLE  ] ){ delete doredmBASE[ DO_ENTRY_ENABLE  ]; }
	while( doredmBASE[ DO_ENTRY_DISABLE ] ){ delete doredmBASE[ DO_ENTRY_DISABLE ]; }
}

DDvoid		DORestricted::doredRestrictedIntro( DDvoid )
{
	DORestricted*			option;
	
	option = doredmBASE[ DO_ENTRY_ENABLE ];
	
	while( option )
	{
		doredmSAVE = option -> doredGetNext();
		option -> doredIntro();
		option = doredmSAVE;
	}
}

DDvoid		DORestricted::doredRestrictedOutro( DDvoid )
{
	DORestricted*			option;
	
	option = doredmBASE[ DO_ENTRY_ENABLE ];
	
	while( option )
	{
		doredmSAVE = option -> doredGetNext();
		option -> doredOutro();
		option = doredmSAVE;
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORestricted::DORestricted( DDvoid )
{
	// append this to disable link list
	doredmBase = DO_ENTRY_DISABLE;
	
	doredAppend( doredmBase );
	
	// set default
	doredmOwner = (DDenum)this;
	doredmRBit  = (DDbits)DOR_BIT_ALL;
}

DORestricted::~DORestricted( DDvoid ) 
{
	// remove this from link list
	doredRemove();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DORestricted::doredEnable( DDvoid )
{
	doredRemove();
	
	doredmBase = DO_ENTRY_ENABLE;
	
	doredAppend( doredmBase );
}

DDvoid		DORestricted::doredDisable( DDvoid )
{
	doredRemove();
	
	doredmBase = DO_ENTRY_DISABLE;
	
	doredAppend( doredmBase );
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORestricted::doredEvaluateArrow( DCvec& P, DCvec& A, f32 Length, DORDresult& Result )
{
	return	DORestrictor::dororEvaluateArrow( doredGetRBit(), doredGetOwner(), P, A, Length, Result );
}

DDbool	DORestricted::doredEvaluateArrow( DCvec& P, DCvec& A, f32 Length, DORDresult& Result, DCvec& DP, DCvec& DR )
{
	return	DORestrictor::dororEvaluateArrow( doredGetRBit(), doredGetOwner(), P, A, Length, Result, DP, DR );
}

//---------------------------------------------------------------------

DDbool	DORestricted::doredEvaluateSphere( DCvec& P, f32 Radius, DORDresult& Result )
{
	return	DORestrictor::dororEvaluateSphere( doredGetRBit(), doredGetOwner(), P, Radius, Result );
}

DDbool	DORestricted::doredEvaluateSphere( DCvec& P, f32 Radius, DORDresult& Result, DCvec& DP, DCvec& DR )
{
	return	DORestrictor::dororEvaluateSphere( doredGetRBit(), doredGetOwner(), P, Radius, Result, DP, DR );
}


//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORestrictor*	DORestrictor::dorormSAVE;
DORestrictor*	DORestrictor::dorormBASE[ DOR_TYPE_TOTAL ];
DDenum				DORestrictor::dorormBaseID;

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DORestrictor::dororRestrictorInitial( DDvoid )
{
	dorormSAVE = NULL;
	
	for( s32 i=0 ; i!=DOR_TYPE_TOTAL ; i++ )
		dorormBASE[ i ] = NULL;
	
	// reset unique ID seed
	dorormBaseID = 1;
}

DDvoid		DORestrictor::dororRestrictorDispose( DDvoid )
{
	dorormSAVE = NULL;
	
	for( s32 i=0 ; i!=DOR_TYPE_TOTAL ; i++ )
		while( dorormBASE[ i ] )
			delete dorormBASE[ i ];
}

DDvoid		DORestrictor::dororRestrictorIntro( DDvoid )
{
	DORestrictor*			option;
	
	for( s32 i=0 ; i!=DOR_TYPE_DISABLE ; i++ )
	{
		option = dorormBASE[ i ];
		
		while( option )
		{
			dorormSAVE = option -> dororGetNext();
			option -> dororIntro();
			option = dorormSAVE;
		}
	}
}

DDvoid		DORestrictor::dororRestrictorOutro( DDvoid )
{
	DORestrictor*			option;
	
	for( s32 i=0 ; i!=DOR_TYPE_DISABLE ; i++ )
	{
		option = dorormBASE[ i ];
		
		while( option )
		{
			dorormSAVE = option -> dororGetNext();
			option -> dororOutro();
			option = dorormSAVE;
		}
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORestrictor::DORestrictor( DDvoid )
{
	dorormDomain = NULL;
	
	// set default owner
	dorormOwner = (DDenum)this;
	
	// pick up unique ID
	dorormID = dorormBaseID;
	
	dorormBaseID++;
	
	// append this to disable link list
	dorormType = DOR_TYPE_DISABLE;
	
	dororAppend( dorormType );
}

DORestrictor::~DORestrictor( DDvoid ) 
{
	if( dorormDomain )
		delete	dorormDomain;
	
	// remove this from linke list
	dororRemove();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid		DORestrictor::dororEnable( DORtype Rtype )
{
	dororRemove();
	
	dorormType = Rtype;
	
	dororAppend( dorormType );
}

DDvoid		DORestrictor::dororDisable( DDvoid )
{
	dororRemove();
	
	dorormType = DOR_TYPE_DISABLE;
	
	dororAppend( dorormType );
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool		DORestrictor::dororEvaluateArrow( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result )
{
	return	( dororEvaluateA( Bit, Owner, P, A, Length, Result ) != NULL );
}

//---------------------------------------------------------------------

DDbool		DORestrictor::dororEvaluateArrow( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result, DCvec& DP, DCvec& DR )
{
	DORestrictor*		ror;
	DCvec						hitP;
	
	DP = DR = dcZero();
	
	ror = dororEvaluateA( Bit, Owner, P, A, Length, Result );
	
	if( ror )
	{
		dcVAdd( P, Result.Length, A, hitP );
		
		ror -> dororCalculateVelocity( hitP, DP, DR );
		
		return	true;
	}
	return	false;
}

//---------------------------------------------------------------------

DORestrictor*	DORestrictor::dororEvaluateA( DDbits Bit, DDenum Owner, DCvec& P, DCvec& A, f32 Length, DORDresult& Result )
{
	DORestrictor*		ror;
	DORestrictor*		hitror;
	
	Result.Length = Length;
	Result.RorID  = 0;
	hitror        = NULL;
	
	// Aは単位ベクトルのこと
	ddASSERT( dcNorm( A ) > 1.0f + _128  ||  dcNorm( A ) < 1.0f - _128 );
	
	for( s32 rtype = 0 ; rtype != DOR_TYPE_DISABLE ; rtype++ )
	{
		if( Bit & BIT( rtype ) )
		{
			for( ror = DORestrictor::dororGetBase( (DORtype)rtype ) ; ror != NULL ; ror = ror -> dororGetNext() )
			{
				if( Owner != ror -> dororGetOwner() )
				{
					if( ror -> dororEvaA( P, A, Result ) )
					{
						hitror = ror;
					}
				}
			}
		}
	}
	return	( hitror );
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORestrictor::dororEvaluateSphere( DDbits Bit, DDenum Owner, DCvec& P, f32 Radius, DORDresult& Result )
{
	return	( dororEvaluateS( Bit, Owner, P, Radius, Result ) != NULL );
}

//---------------------------------------------------------------------

DDbool	DORestrictor::dororEvaluateSphere( DDbits Bit, DDenum Owner, DCvec& P, f32 Radius, DORDresult& Result, DCvec& DP, DCvec& DR )
{
	DORestrictor*		ror;
	DCvec							hitP;
	
	DP = DR = dcZero();
	
	ror = dororEvaluateS( Bit, Owner, P, Radius, Result );
	
	if( ror )
	{
		dcVSub( P, Result.Length, Result.Normal, hitP );
		
		ror -> dororCalculateVelocity( hitP, DP, DR );
		
		return	true;
	}
	return	false;
}



DORestrictor*	DORestrictor::dororEvaluateS( DDbits Bit, DDenum Owner, DCvec& P, f32 Radius, DORDresult& Result )
{
	DORestrictor*		ror;
	DORestrictor*		hitror;
	
	Result.Length = Radius;
	Result.RorID  = 0;
	hitror        = NULL;
	
	for( s32 rtype = 0 ; rtype != DOR_TYPE_DISABLE ; rtype++ )
	{
		if( Bit & BIT( rtype ) )
		{
			for( ror = DORestrictor::dororGetBase( (DORtype)rtype ) ; ror != NULL ; ror = ror -> dororGetNext() )
			{
				if( Owner != ror -> dororGetOwner() )
				{
					if( ror -> dororEvaS( P, Result ) )
					{
						hitror = ror;
					}
				}
			}
		}
	}
	return	( hitror );
}

