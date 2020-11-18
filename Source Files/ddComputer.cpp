
// deal dominater computer

#include	"ddJacket.h"
#include	"ddComputer.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//	static memba
DCmtx		DCmtx::work;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// valid TR
DDvoid	DCmtx::dcCTInverse( DCmtx& M )
{
	f32			m10;
	f32			m20;
	f32			m21;
	f32			m30;
	f32			m31;
	
	M.m[ 0 ][ 3 ] = 0.0f;
	M.m[ 1 ][ 3 ] = 0.0f;
	M.m[ 2 ][ 3 ] = 0.0f;
	M.m[ 3 ][ 3 ] = 1.0f;
	
	M.m[ 0 ][ 0 ] = m[ 0 ][ 0 ];
	M.m[ 1 ][ 1 ] = m[ 1 ][ 1 ];
	M.m[ 2 ][ 2 ] = m[ 2 ][ 2 ];
	
	m10 = m[ 1 ][ 0 ];
	m20 = m[ 2 ][ 0 ];
	m21 = m[ 2 ][ 1 ];
	
	M.m[ 1 ][ 0 ] = m[ 0 ][ 1 ];
	M.m[ 2 ][ 0 ] = m[ 0 ][ 2 ];
	M.m[ 2 ][ 1 ] = m[ 1 ][ 2 ];
	
	M.m[ 0 ][ 1 ] = m10;
	M.m[ 0 ][ 2 ] = m20;
	M.m[ 1 ][ 2 ] = m21;
	
	m30 = m[ 3 ][ 0 ];
	m31 = m[ 3 ][ 1 ];
	
	M.m[ 3 ][ 0 ] = -( m30         * M.m[ 0 ][ 0 ] + 
										 m31         * M.m[ 1 ][ 0 ] +
										 m[ 3 ][ 2 ] * M.m[ 2 ][ 0 ] );
	
	M.m[ 3 ][ 1 ] = -( m30         * M.m[ 0 ][ 1 ] + 
										 m31         * M.m[ 1 ][ 1 ] +
										 m[ 3 ][ 2 ] * M.m[ 2 ][ 1 ] );
	
	M.m[ 3 ][ 2 ] = -( m30         * M.m[ 0 ][ 2 ] + 
										 m31         * M.m[ 1 ][ 2 ] +
										 m[ 3 ][ 2 ] * M.m[ 2 ][ 2 ] );
}

//-----------------------------------------------------------------

DDvoid	DCmtx::dcLoadRotateAxis( f32 a, f32 x, f32 y, f32 z )
{
	f32			c;
	f32			s;
	f32			t;
	f32			xx;
	f32			yy;
	f32			zz;
	f32			rs;
	
	xx = x * x;
	yy = y * y;
	zz = z * z;
	
	rs = dcRSqrt( xx + yy + zz );
	
	x *= rs;
	y *= rs;
	z *= rs;
	
	xx = x * x;
	yy = y * y;
	zz = z * z;
	
	c = dcCos( a );
	s = dcSin( a );
	t = 1.0f - c;
	
	m[ 0 ][ 0 ] = ( t * xx    ) + (   c   );
	m[ 0 ][ 1 ] = ( t * x * y ) + ( s * z );
	m[ 0 ][ 2 ] = ( t * x * z ) - ( s * y );
	m[ 0 ][ 3 ] = 0.0f;
	
	m[ 1 ][ 0 ] = ( t * x * y ) - ( s * z );
	m[ 1 ][ 1 ] = ( t * yy    ) + (   c   );
	m[ 1 ][ 2 ] = ( t * y * z ) + ( s * x );
	m[ 1 ][ 3 ] = 0.0f;
	
	m[ 2 ][ 0 ] = ( t * x * z ) + ( s * y );
	m[ 2 ][ 1 ] = ( t * y * z ) - ( s * x );
	m[ 2 ][ 2 ] = ( t * zz    ) + (   c   );
	m[ 2 ][ 3 ] = 0.0f;
	
	m[ 3 ][ 0 ] = 0.0f;
	m[ 3 ][ 1 ] = 0.0f;
	m[ 3 ][ 2 ] = 0.0f;
	m[ 3 ][ 3 ] = 1.0f;
}

//-----------------------------------------------------------------

DDvoid	DCmtx::dcLoadRotateZXY( f32 x, f32 y, f32 z )
{
	f32			cx, cy, cz;
	f32			sx, sy, sz;
	
	cx = dcCos( x ); cy = dcCos( y ); cz = dcCos( z );
	sx = dcSin( x ); sy = dcSin( y ); sz = dcSin( z );
	
	m[ 0 ][ 0 ] =  cy * cz + sx * sy * sz;
	m[ 0 ][ 1 ] =                 cx * sz;
	m[ 0 ][ 2 ] = -cz * sy + sx * sz * cy;
	m[ 0 ][ 3 ] = 0.0f;

	m[ 1 ][ 0 ] = -cy * sz + cz * sx * sy;
	m[ 1 ][ 1 ] =                 cx * cz;
	m[ 1 ][ 2 ] =  sy * sz + cy * cz * sx;
	m[ 1 ][ 3 ] = 0.0f;
	
	m[ 2 ][ 0 ] = cx * sy;
	m[ 2 ][ 1 ] =     -sx;
	m[ 2 ][ 2 ] = cx * cy;
	m[ 2 ][ 3 ] = 0.0f;
	
	m[ 3 ][ 0 ] = 0.0f;
	m[ 3 ][ 1 ] = 0.0f;
	m[ 3 ][ 2 ] = 0.0f;
	m[ 3 ][ 3 ] = 1.0f;
}

//-----------------------------------------------------------------

DDvoid	DCmtx::dcShaft( DCvec& v )
{
	f32			ag;
	
	ag = dcNormSqr( v );
	
	if( ag > SQR( 0.0f ) )
	{
		work.dcLoadRotateAxis( dcSqrt( ag ), v );
		
		dcMxIN( work );
	}
}

//-----------------------------------------------------------------

// valid under _2PI angular
DDvoid	DCmtx::dcAngular( DCvec& v )
{
	DCvec			mX;
	DCvec			mY;
	DCvec			gX;
	DCvec			gY;
	DCvec			gZ;
	
	dcGX( gX );
	dcGY( gY );
	
		dcCross( v, gX, mX );
		dcCross( v, gY, mY );
		
		dcVAdd( gX, mX, gX );
		dcVAdd( gY, mY, gY );
		
		dcNormalize( gX );
		
		dcVSub( gY, dcDot( gY, gX ), gX, gY );
		dcNormalize( gY );
		
		dcCross( gX, gY, gZ );
		
	dcSetGX( gX );
	dcSetGY( gY );
	dcSetGZ( gZ );
}

//-----------------------------------------------------------------

// valid R
DDvoid	DCmtx::dcM33xV( DCvec& u )
{
	f32			x;
	f32			y;
	f32			z;
	
	x = u.x;
	y = u.y;
	z = u.z;
	
	u.x = x * m[ 0 ][ 0 ] + y * m[ 0 ][ 1 ] + z * m[ 0 ][ 2 ];
	u.y = x * m[ 1 ][ 0 ] + y * m[ 1 ][ 1 ] + z * m[ 1 ][ 2 ];
	u.z = x * m[ 2 ][ 0 ] + y * m[ 2 ][ 1 ] + z * m[ 2 ][ 2 ];
}

DDvoid	DCmtx::dcM33xV( DCvec& u, DCvec& v )
{
	v.x = u.x * m[ 0 ][ 0 ] + u.y * m[ 0 ][ 1 ] + u.z * m[ 0 ][ 2 ];
	v.y = u.x * m[ 1 ][ 0 ] + u.y * m[ 1 ][ 1 ] + u.z * m[ 1 ][ 2 ];
	v.z = u.x * m[ 2 ][ 0 ] + u.y * m[ 2 ][ 1 ] + u.z * m[ 2 ][ 2 ];
}

//---------------------------------------------------------------
//---------------------------------------------------------------

// cast( F32 to S22 ) 四捨五入( ただし0.5捨 )
s32		dcFS( f32 f )
{
	IntFlt32		n;
	IntFlt32		b;
	
	ddASSERT( dcAbs( f ) > (f32)( 1 << 22 ) );
	
	n.f  = f;
	b.i  = ( ( 23 + 127 ) << 23 ) + ( 1 << 22 );
	n.f += b.f;
	n.i -= b.i;
	
	return	n.i;
}

//---------------------------------------------------------------

f32		dcSF( s32 i )
{
	return (f32)i;
}

//---------------------------------------------------------------

// cast( F32 to S1D14 ) decimal 14 bit [ -2.0f( -32768 ) _ +1.99993896f( 32767 ) ]
s16		dcFS1D14( f32 f )
{
	IntFlt32		n;
	IntFlt32		b;
	
	ddASSERT( dcAbs( f ) >= 2.0f );
	
	n.f  = f;
	b.i  = ( ( 23 - 14 + 127 ) << 23 ) + ( 1 << 22 );
	n.f += b.f;
	n.i -= b.i;
	
	return	(s16)n.i;
}

//---------------------------------------------------------------

f32		dcS1D14F( s16 d )
{
	return (f32)d * _16384;
}

//---------------------------------------------------------------

// cast( DCvec to S1D14 x3 )
DDvoid	dcVS1D14( DCvec& v, s16* d )
{
	d[ 0 ] = dcFS1D14( v.x );
	d[ 1 ] = dcFS1D14( v.y );
	d[ 2 ] = dcFS1D14( v.z );
}

//---------------------------------------------------------------

DDvoid	dcS1D14V( s16* d, DCvec& v )
{
	v.x = dcS1D14F( d[ 0 ] );
	v.y = dcS1D14F( d[ 1 ] );
	v.z = dcS1D14F( d[ 2 ] );
}

//---------------------------------------------------------------

// 非数の取得
f32		dcNan( DDvoid )
{
	IntFlt32	n;
	
	n.i = 0x7fffffff;
	
	return	n.f;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

// 0以上をクランプ
f32		dcMaxClampZero( f32 x )
{
	IntFlt32	n;
	s32				s;
	
	n.f  = x;
	s    = n.i >> 31;
	n.i &= s;
	
	return	n.f;
}

// 0未満をクランプ
f32		dcMinClampZero( f32 x )
{
	IntFlt32	n;
	s32				s;
	
	n.f  = x;
	s    = n.i >> 31;
	s    = ~s;
	n.i &= s;
	
	return	n.f;
}

// 符号( 正 = +1 : 負 = -1 )
f32		dcStep( f32 x )
{
	IntFlt32	n;
	IntFlt32	m;
	
	n.f = 1.0f;
	m.f = x;
	n.i = n.i | ( m.i & BIT( 31 ) );
	
	return	n.f;
}

//---------------------------------------------------------------
//---------------------------------------------------------------

static	s32		dcmRand = 0xdea1;

DDvoid	dcRandSetSeed( s32 seed )
{
	dcmRand = seed;
}

//---------------------------------------------------------------

s32		dcRand( DDvoid )
{
	dcmRand = dcmRand * ( BIT(11) | BIT(2) | BIT(0) ) + ( BIT(10) | BIT(0) );
	
	return	dcmRand;
}

s32		dcRand( u32 mask )
{
	return	( dcRand() & mask );
}

//---------------------------------------------------------------

s32		dcDomino( s32& seed )
{
	seed = seed * 5 + 1;
	
	return	seed;
}

s32		dcDomino( s32& seed, u32 mask )
{
	return	( dcDomino( seed ) & mask );
}

//---------------------------------------------------------------

// +1.0f : -1.0f ( non zero )
f32		dcRandFS( DDvoid )
{
	return	( (f32)dcRand( 0xffff ) * ( 1.0f / 32767.5f ) - 1.0f );
}

f32		dcRandFS( f32 ratio )
{
	return	( dcRandFS() * ratio );
}

// +1.0f : 0.0f
f32		dcRandFU( DDvoid )
{
	return	( (f32)dcRand( 0xffff ) * ( 1.0f / 65535.f ) );
}

f32		dcRandFU( f32 ratio )
{
	return	( dcRandFU() * ratio );
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// ground axis.									0     1     2      3     4     5      6     7     8
const	f32		dcGrounds[ 9 ] = {  0.0f, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f };

//-----------------------------------------------------------------
//-----------------------------------------------------------------

f32		dcNorm( DCvec& v )
{
	return	dcSqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

f32		dcNorm( DCvec& u, DCvec& v )
{
	DCvec		w;
	
	dcVSub( u, v, w );
	
	return	dcNorm( w );
}

f32		dcNormSqr( DCvec& u )
{
	return	u.x * u.x + u.y * u.y + u.z * u.z;
}

f32		dcNormSqr( DCvec& u, DCvec& v )
{
	f32			dx = u.x - v.x;
	f32			dy = u.y - v.y;
	f32			dz = u.z - v.z;
	
	return	dx * dx + dy * dy + dz * dz;
}

f32		dcNormalizer( DCvec& v )
{
	return	dcRSqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

f32		dcResizer( f32 scale, DCvec& v )
{
	return	scale * dcRSqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}


//-----------------------------------------------------------------

DDvoid	dcNormalize( DCvec& in, DCvec& out, DCvec& zero )
{
	f32		ns;
	
	ns = dcNormSqr( in );
	
	if( ns > 0.0f )
		dcVScale( 1.0f / dcSqrt( ns ), in, out );
	else
		out = zero;
	
	// 誤差警告 1/100
	ddASSERT( dcNorm( out ) < 0.99f  ||  dcNorm( out ) > 1.01f );
}

DDvoid	dcNormalize( DCvec& in, DCvec& out )
{
	dcVScale( 1.0f / dcNorm( in ), in, out );
	
	// 誤差警告 1/100
	ddASSERT( dcNorm( out ) < 0.99f  ||  dcNorm( out ) > 1.01f );
}

DDvoid	dcNormalize( DCvec& v )
{
	dcNormalize( v, v );
}

//-----------------------------------------------------------------

DDvoid	dcVLoad( f32 x, f32 y, f32 z, DCvec& u )
{
	u.x = x;
	u.y = y;
	u.z = z;
}

DDvoid	dcVLoad( DCvec& u, f32 x, f32 y, f32 z )
{
	u.x = x;
	u.y = y;
	u.z = z;
}

DDvoid	dcVNegate( DCvec& u )
{
	u.x = -u.x;
	u.y = -u.y;
	u.z = -u.z;
}

DDvoid	dcVNegate( DCvec& u, DCvec& v )
{
	v.x = -u.x;
	v.y = -u.y;
	v.z = -u.z;
}

DDvoid	dcVAdd( DCvec& u, DCvec& v, DCvec& w )
{
	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
}

DDvoid	dcVAdd( f32 s, DCvec& u, DCvec& v, DCvec& w )
{
	w.x = s * u.x + v.x;
	w.y = s * u.y + v.y;
	w.z = s * u.z + v.z;
}

DDvoid	dcVAdd( DCvec& u, f32 s, DCvec& v, DCvec& w )
{
	w.x = u.x + s * v.x;
	w.y = u.y + s * v.y;
	w.z = u.z + s * v.z;
}

DDvoid	dcVSub( DCvec& u, DCvec& v, DCvec& w )
{
	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
}

DDvoid	dcVSub( f32 s, DCvec& u, DCvec& v, DCvec& w )
{
	w.x = s * u.x - v.x;
	w.y = s * u.y - v.y;
	w.z = s * u.z - v.z;
}

DDvoid	dcVSub( DCvec& u, f32 s, DCvec& v, DCvec& w )
{
	w.x = u.x - s * v.x;
	w.y = u.y - s * v.y;
	w.z = u.z - s * v.z;
}

DDvoid	dcVScale( f32 s, DCvec& u )
{
	u.x *= s;
	u.y *= s;
	u.z *= s;
}

DDvoid	dcVScale( f32 s, DCvec& u, DCvec& v )
{
	v.x = s * u.x;
	v.y = s * u.y;
	v.z = s * u.z;
}

f32			dcDot( DCvec& u, DCvec& v )
{
	return	u.x * v.x + u.y * v.y + u.z * v.z;
}

DDvoid	dcCross( DCvec& u, DCvec& v, DCvec& w )
{
	DCvec		t;
	
	t.x = u.y * v.z - u.z * v.y;
	t.y = u.z * v.x - u.x * v.z;
	t.z = u.x * v.y - u.y * v.x;
	
	w = t;
}

DDvoid	dcCrossShaft( DCvec s, DCvec d, DCvec& r )
{
	f32			norm;
	f32			dot;
	
	dcNormalize( s );
	dcNormalize( d );
	
	// zero check
	ddNAN( s.x );
	ddNAN( d.x );
	
	dcCross( s, d, r );
	
	dot = dcDot( s, d );
	
	// under 15
	if( dot > COS15 )
		return;
	
	// normalize to angle norm
	norm = dcNormSqr( r );
	
	if( norm >= SQR( _65536 ) )
	{
		dot = dcClamp( +1.0f, -1.0f, dot );
		
		dcVScale( dcArcCos( dot ) / dcSqrt( norm ), r );
		
		return;
	}
	
	// 正反対 直行piV
	dcVLoad( r, +s.z, -s.x * 2.0f, +s.y );
	
	dcCross( s, r, r );
	
	norm = dcNorm( r );
	
	dcVScale( PI / norm, r );
	
	ddASSERT( norm < _65536 );
	
	return;
}

//-----------------------------------------------------------------

// random vector 大きさ１
DDvoid	dcRandVU( DCvec& v )
{
	f32		ay;
	f32		ax;
	
	ay = dcRandFS( PI );
	ax = dcRandFS( PI );
	
	v.x = +dcSin( ay );
	v.z = +dcCos( ay );
	
	v.y = v.z * -dcSin( ax );
	v.z = v.z * +dcCos( ax );
}

// 大きさ0_1 ( non zero )
DDvoid	dcRandV( DCvec& v )
{
	dcRandV( dcRandFS(), v );
}

// 大きさscale
DDvoid	dcRandV( f32 scale, DCvec& v )
{
	dcRandVU( v );
	
	dcVScale( scale, v );
}

