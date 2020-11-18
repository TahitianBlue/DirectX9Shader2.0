
#include	"DORorStatic.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORorStatic:: DORorStatic( DORorDomain& Domain ) : DORestrictor()
{
	dorormDomain = &Domain;
}

//---------------------------------------------------------------------

DORorStatic::~DORorStatic( DDvoid )
{
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORorStatic::dororEvaA( DCvec P, DCvec A, DORDresult& Result )
{
	if( dororDomain().dordEvaArrow( P, A, Result ) )
	{
		Result.RorID = dororGetID();
		
		return	true;
	}
	return	false;
}

//---------------------------------------------------------------------

DDbool	DORorStatic::dororEvaS( DCvec P, DORDresult& Result )
{
	if( dororDomain().dordEvaSphere( P, Result ) )
	{
		Result.RorID = dororGetID();
		
		return	true;
	}
	return	false;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORorStatic::dororCalculateVelocity( DCvec& HitP, DCvec& DP, DCvec& DR )
{
	(DDvoid)HitP;
	(DDvoid)DP;
	(DDvoid)DR;
	
	return	false;
}

