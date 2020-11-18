
#ifndef	__doRorDynamic_h__
#define	__doRorDynamic_h__


#include	"doRestriction.h"


//---------------------------------------------------------------------
//---------------------------------------------------------------------

class	DORorDynamic : public DORestrictor
{
	public:
						 DORorDynamic( DORorDomain& Domain );
		virtual	~DORorDynamic( DDvoid );
	
	public:
		virtual	DDvoid	dororIntro( DDvoid );
		virtual	DDvoid	dororOutro( DDvoid );
	
	public:
		DDvoid					dororSetup ( f32 Scale, DCmtx& M );
		DDvoid					dororUpdate( DCmtx& M );
	
	private:
		virtual	DDbool	dororEvaA( DCvec P, DCvec A, DORDresult& Result );
		virtual	DDbool	dororEvaS( DCvec P,          DORDresult& Result );
		virtual	DDbool	dororCalculateVelocity( DCvec& HitP, DCvec& DP, DCvec& DR );
	
	private:
		f32					dorordmS;				// scale
		f32					dorordmRS;			// reciprocal scale
		DCmtx				dorordmM;				// matrix
		DCmtx				dorordmIM;			// inverse matrix
		DCmtx				dorordmPM;			// previous matrix
};


#endif
