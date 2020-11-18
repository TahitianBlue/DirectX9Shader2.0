
#include	"DORorDynamic.h"

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DORorDynamic:: DORorDynamic( DORorDomain& Domain ) : DORestrictor()
{
	dorormDomain = &Domain;
	
	dorordmS  = 1.0f;
	dorordmRS = 1.0f;
	
	dorordmM .dcIdentity();
	dorordmIM.dcIdentity();
	dorordmPM.dcIdentity();
}

//---------------------------------------------------------------------

DORorDynamic::~DORorDynamic( DDvoid )
{
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid	DORorDynamic::dororIntro( DDvoid )
{
}

//---------------------------------------------------------------------

DDvoid	DORorDynamic::dororOutro( DDvoid )
{
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDvoid	DORorDynamic::dororSetup( f32 Scale, DCmtx& M )
{
	dorordmS  = Scale;
	dorordmRS = 1.0f / Scale;
	
	dorordmM .dcLoadM( M );
	dorordmM .dcInverse( dorordmIM );
	dorordmPM.dcLoadM( M );
}

//---------------------------------------------------------------------

DDvoid	DORorDynamic::dororUpdate( DCmtx& M )
{
	// mPM
	dorordmPM.dcLoadM( dorordmM );
	
	// mM
	dorordmM .dcLoadM( M );
	
	// mIM
	dorordmM .dcInverse( dorordmIM );
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORorDynamic::dororEvaA( DCvec P, DCvec A, DORDresult& Result )
{
	f32		resultLength;
	
	resultLength = Result.Length;
	
	dorordmIM.dcVxM  ( P );
	dorordmIM.dcVxM33( A );
	
	dcVScale( dorordmS, A );			// normalize
	Result.Length *= dorordmRS;
	
	if( dororDomain().dordEvaArrow( P, A, Result ) )
	{
		Result.RorID = dororGetID();
		
		dorordmM.dcVxM33( Result.Normal );
		
		dcVScale( dorordmRS, Result.Normal );
		
		Result.Length *= dorordmS;
		
		// normal check
		#ifdef	DD_DEBUG
		{
			f32		norm = dcNorm( Result.Normal );
			ddASSERT( norm > 1.0f + _128  ||  norm < 1.0f - _128 );
		}
		#endif
		
		return	true;
	}
	
	Result.Length = resultLength;
	
	return	false;
}

//---------------------------------------------------------------------

DDbool	DORorDynamic::dororEvaS( DCvec P, DORDresult& Result )
{
	f32		resultRadius;
	
	resultRadius = Result.Length;
	
	dorordmIM.dcVxM( P );
	
	Result.Length *= dorordmRS;
	
	if( dororDomain().dordEvaSphere( P, Result ) )
	{
		Result.RorID = dororGetID();
		
		dorordmM.dcVxM33( Result.Normal );
		
		dcVScale( dorordmRS, Result.Normal );
		
		Result.Length *= dorordmS;
		
		// normal check
		#ifdef	DD_DEBUG
		{
			f32		norm = dcNorm( Result.Normal );
			ddASSERT( norm > 1.0f + _128  ||  norm < 1.0f - _128 );
		}
		#endif
		
		return	true;
	}
	
	Result.Length = resultRadius;
	
	return	false;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------

DDbool	DORorDynamic::dororCalculateVelocity( DCvec& HitP, DCvec& DP, DCvec& DR )
{
	DCmtx				m;
	DCvec				p;
	DCvec				pp;
	
	DCmtx				drm;
	DCvec				sv;
	DCvec				dv;
	DCvec				rv;
	
	// DP
	
	m.dcLoadM( dorordmIM );
	
	m.dcVxM( HitP, p );
	
	dorordmPM.dcVxM( p, pp );
	
	dcVSub( HitP, pp, DP );
	
	// DR
	
	DR = dcZero();
	
	drm.dcLoadM( dorordmPM );
	
	for( s32 i=0 ; i!=3 ; i++ )
	{
		// X
		drm     .dcGX( sv );
		dorordmM.dcGX( dv );
		
		dcCrossShaft( sv, dv, rv );
		
		drm.dcShaft( rv );
		
		dcVAdd( DR, rv, DR );
		
		// Y
		drm     .dcGY( sv );
		dorordmM.dcGY( dv );
		
		dcCrossShaft( sv, dv, rv );
		
		drm.dcShaft( rv );
		
		dcVAdd( DR, rv, DR );
		
		// Z
		drm     .dcGZ( sv );
		dorordmM.dcGZ( dv );
		
		dcCrossShaft( sv, dv, rv );
		
		drm.dcShaft( rv );
		
		dcVAdd( DR, rv, DR );
	}
	
	dcVScale( 1.01f, DR );		// ŒoŒ±‘¥”’l
	
	return	true;
}

