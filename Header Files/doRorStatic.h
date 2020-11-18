
#ifndef	__doRorStatic_h__
#define	__doRorStatic_h__

#include	"doRestriction.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

class	DORorStatic : public DORestrictor
{
	public:
						 DORorStatic( DORorDomain& Domain );
		virtual	~DORorStatic( DDvoid );
	
	public:
		virtual	DDvoid	dororIntro( DDvoid ){}
		virtual	DDvoid	dororOutro( DDvoid ){}
	
	private:
		virtual	DDbool	dororEvaA( DCvec P, DCvec A, DORDresult& Result );
		virtual	DDbool	dororEvaS( DCvec P,          DORDresult& Result );
		virtual	DDbool	dororCalculateVelocity( DCvec& HitP, DCvec& DP, DCvec& DR );
};


#endif
