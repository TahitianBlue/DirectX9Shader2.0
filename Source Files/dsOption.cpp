
#include	"dsOption.h"

#include	"doCollision.h"
#include	"doRestriction.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	DSOption::doOptionInitial( DDvoid )
{
//DODamage::dodDamageInitial();
	
		DOCollision::docCollisionInitial();
		
			DORestriction::dorRestrictionInitial();
}

//-------------------------------------------------------------------

DDvoid	DSOption::doOptionDispose( DDvoid )
{
			DORestriction::dorRestrictionDispose();
			
		DOCollision::docCollisionDispose();
		
//DODamage::dodDamageDispose();
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

DDvoid	DSOption::doOptionProcess( DDvoid )
{
/*
	DODamage::dodDamageIntro();
	DODamage::dodDamageProcess();
	DODamage::dodDamageOutro();
*/
	
	DOCollision::docCollisionIntro();
	DOCollision::docCollisionProcess();
	DOCollision::docCollisionOutro();
	
	DORestriction::dorRestrictionIntro();
	DORestriction::dorRestrictionProcess();
	DORestriction::dorRestrictionOutro();
}

