
// deal dominator computer


#ifndef	__ddComputer_h__
#define	__ddComputer_h__

#include	<math.h>
#include	"ddJacket.h"

//---------------------------------------------------------------
//---------------------------------------------------------------

#define	PI													( 3.14159265358979323846f )
#define	DPI													( 2.0f * PI )

#define	SIN00												( 0.000000f )
#define	SIN05												( 0.087156f )
#define	SIN10												( 0.173648f )
#define	SIN15												( 0.258819f )
#define	SIN20												( 0.342020f )
#define	SIN25												( 0.422618f )
#define	SIN30												( 0.500000f )
#define	SIN35												( 0.573577f )
#define	SIN40												( 0.642788f )
#define	SIN45												( 0.707107f )
#define	SIN50												( 0.766044f )
#define	SIN55												( 0.819152f )
#define	SIN60												( 0.866025f )
#define	SIN65												( 0.906308f )
#define	SIN70												( 0.939693f )
#define	SIN75												( 0.965926f )
#define	SIN80												( 0.984808f )
#define	SIN85												( 0.996195f )
#define	SIN90												( 1.000000f )

#define	COS_1												( 0.999847695f )
#define	COS03												( 0.998629534f )

#define	COS00												SIN90
#define	COS05												SIN85
#define	COS10												SIN80
#define	COS15												SIN75
#define	COS20												SIN70
#define	COS25												SIN65
#define	COS30												SIN60
#define	COS35												SIN55
#define	COS40												SIN50
#define	COS45												SIN45
#define	COS50												SIN40
#define	COS55												SIN35
#define	COS60												SIN30
#define	COS65												SIN25
#define	COS70												SIN20
#define	COS75												SIN15
#define	COS80												SIN10
#define	COS85												SIN05
#define	COS90												SIN00

#define	_2													( 1.0f /     2.f )
#define	_3													( 1.0f /     3.f )
#define	_4													( 1.0f /     4.f )
#define	_5													( 1.0f /     5.f )
#define	_6													( 1.0f /     6.f )
#define	_7													( 1.0f /     7.f )
#define	_8													( 1.0f /     8.f )
#define	_9													( 1.0f /     9.f )
#define	_10													( 1.0f /    10.f )
#define	_11													( 1.0f /    11.f )
#define	_12													( 1.0f /    12.f )
#define	_13													( 1.0f /    13.f )
#define	_14													( 1.0f /    14.f )
#define	_15													( 1.0f /    15.f )
#define	_16													( 1.0f /    16.f )
#define	_24													( 1.0f /    24.f )
#define	_32													( 1.0f /    32.f )
#define	_48													( 1.0f /    48.f )
#define	_64													( 1.0f /    64.f )
#define	_96													( 1.0f /    96.f )
#define	_128												( 1.0f /   128.f )
#define	_192												( 1.0f /   192.f )
#define	_256												( 1.0f /   256.f )
#define	_384												( 1.0f /   384.f )
#define	_512												( 1.0f /   512.f )
#define	_768												( 1.0f /   768.f )
#define	_1024												( 1.0f /  1024.f )
#define	_2048												( 1.0f /  2048.f )
#define	_4096												( 1.0f /  4096.f )
#define	_8192												( 1.0f /  8192.f )
#define	_16384											( 1.0f / 16384.f )
#define	_32768											( 1.0f / 32768.f )
#define	_65536											( 1.0f / 65536.f )

#define	_PI													( 1.0f /  PI )
#define	_DPI												( 1.0f / DPI )

#define	_2PI												( PI /     2.f )
#define	_3PI												( PI /     3.f )
#define	_4PI												( PI /     4.f )
#define	_5PI												( PI /     5.f )
#define	_6PI												( PI /     6.f )
#define	_7PI												( PI /     7.f )
#define	_8PI												( PI /     8.f )
#define	_9PI												( PI /     9.f )
#define	_10PI												( PI /    10.f )
#define	_11PI												( PI /    11.f )
#define	_12PI												( PI /    12.f )
#define	_13PI												( PI /    13.f )
#define	_14PI												( PI /    14.f )
#define	_15PI												( PI /    15.f )
#define	_16PI												( PI /    16.f )
#define	_24PI												( PI /    24.f )
#define	_32PI												( PI /    32.f )
#define	_48PI												( PI /    48.f )
#define	_64PI												( PI /    64.f )
#define	_96PI												( PI /    96.f )
#define	_128PI											( PI /   128.f )
#define	_192PI											( PI /   192.f )
#define	_256PI											( PI /   256.f )
#define	_384PI											( PI /   384.f )
#define	_512PI											( PI /   512.f )
#define	_768PI											( PI /   768.f )
#define	_1024PI											( PI /  1024.f )
#define	_2048PI											( PI /  2048.f )
#define	_4096PI											( PI /  4096.f )
#define	_8192PI											( PI /  8192.f )
#define	_16384PI										( PI / 16384.f )
#define	_32768PI										( PI / 32768.f )
#define	_65536PI										( PI / 65536.f )

#define	BIT( PARAM )								( ( u32 )1 << ( PARAM ) )
#define	SQR( PARAM )								( ( PARAM ) * ( PARAM ) )

#define	RPC( PARAM )								( 1.0f / ( PARAM ) )
#define	R2D( PARAM )								( ( PARAM ) * ( 180.0f /     PI ) )
#define	D2R( PARAM )								( ( PARAM ) * (     PI / 180.0f ) )

#define FPSI												( 60 )
#define FPSF												( 60.0f )
#define	_FPSF												( 1.0f / FPSF )
#define	SEC( PARAM )								( (ARuint)( FPSF * ( PARAM ) ) )

//--------------------------------------------------------------
//--------------------------------------------------------------

typedef struct DCvec : public D3DXVECTOR3
{
	public:
		
		DCvec( DDvoid )								:	D3DXVECTOR3() {};
		DCvec( CONST f32* pf )				: D3DXVECTOR3( pf ) {};
		DCvec( CONST DCvec& cv )			: D3DXVECTOR3( cv ) {};
		DCvec( f32 x, f32 y, f32 z )	: D3DXVECTOR3( x, y, z ) {};
		
} DCvec, DCvector;

//--------------------------------------------------------------

typedef struct DCquat : public D3DXQUATERNION
{
	public:
		
		DCquat( DDvoid )											: D3DXQUATERNION() {};
		DCquat( CONST f32* f )								: D3DXQUATERNION( f ) {};
		DCquat( f32 x, f32 y, f32 z, f32 w )	: D3DXQUATERNION( x, y, z, w ) {};
		
} DCquat, DCquaternion;

//--------------------------------------------------------------

class DCmtx : public D3DXMATRIX
{
	public:
		
		DCmtx( DDvoid )							:	D3DXMATRIX() {};
		DCmtx( CONST f32*   pf )		: D3DXMATRIX( pf ) {};
		DCmtx( CONST DCmtx& cm )		: D3DXMATRIX( cm ) {};
		
		DCmtx(	f32 __11, f32 __12, f32 __13, f32 __14,
						f32 __21, f32 __22, f32 __23, f32 __24,
						f32 __31, f32 __32, f32 __33, f32 __34,
						f32 __41, f32 __42, f32 __43, f32 __44	) :
		D3DXMATRIX( __11, __12, __13, __14,
								__21, __22, __23, __24,
								__31, __32, __33, __34,
								__41, __42, __43, __44	) {};

	//---------------------
	
	public:
		f32&				dcM( u32 i, u32 j ){ return m[ i ][ j ]; }
		D3DMATRIX&	dcDM ( DDvoid ){ return *( ( D3DMATRIX*  )&m[ 0 ][ 0 ] ); }
		D3DXMATRIX&	dcDXM( DDvoid ){ return *( ( D3DXMATRIX* )&m[ 0 ][ 0 ] ); }
	
	public:
		DCvec&	dcOrigin( DDvoid )     { return *( (DCvec*)&dcM( 3, 0 ) ); }
		DDvoid	dcOrigin( DCvec& o )   { o.x = m[ 3 ][ 0 ];  o.y = m[ 3 ][ 1 ];  o.z = m[ 3 ][ 2 ]; }
		
		DDvoid	dcSetOrigin( DCvec& o ){ m[ 3 ][ 0 ] =  o.x; m[ 3 ][ 1 ] =  o.y; m[ 3 ][ 2 ] =  o.z; }
		DDvoid	dcAddOrigin( DCvec& p ){ m[ 3 ][ 0 ] += p.x; m[ 3 ][ 1 ] += p.y; m[ 3 ][ 2 ] += p.z; }
		DDvoid	dcSubOrigin( DCvec& p ){ m[ 3 ][ 0 ] -= p.x; m[ 3 ][ 1 ] -= p.y; m[ 3 ][ 2 ] -= p.z; }
	
	public:
		DCvec&	dcGX( DDvoid ){ return *( (DCvec*)&dcM( 0, 0 ) ); }
		DCvec&	dcGY( DDvoid ){ return *( (DCvec*)&dcM( 1, 0 ) ); }
		DCvec&	dcGZ( DDvoid ){ return *( (DCvec*)&dcM( 2, 0 ) ); }
		
		DDvoid	dcGX   ( DCvec& x ){ x.x = m[ 0 ][ 0 ]; x.y = m[ 0 ][ 1 ]; x.z = m[ 0 ][ 2 ]; }
		DDvoid	dcGY   ( DCvec& y ){ y.x = m[ 1 ][ 0 ]; y.y = m[ 1 ][ 1 ]; y.z = m[ 1 ][ 2 ]; }
		DDvoid	dcGZ   ( DCvec& z ){ z.x = m[ 2 ][ 0 ]; z.y = m[ 2 ][ 1 ]; z.z = m[ 2 ][ 2 ]; }
		
		DDvoid	dcSetGX( DCvec& x ){ m[ 0 ][ 0 ] = x.x; m[ 0 ][ 1 ] = x.y; m[ 0 ][ 2 ] = x.z; }
		DDvoid	dcSetGY( DCvec& y ){ m[ 1 ][ 0 ] = y.x; m[ 1 ][ 1 ] = y.y; m[ 1 ][ 2 ] = y.z; }
		DDvoid	dcSetGZ( DCvec& z ){ m[ 2 ][ 0 ] = z.x; m[ 2 ][ 1 ] = z.y; m[ 2 ][ 2 ] = z.z; }
	
	public:
		DDvoid	dcSubGX   ( DCvec& x ){ x.x = m[ 0 ][ 0 ]; x.y = m[ 1 ][ 0 ]; x.z = m[ 2 ][ 0 ]; }
		DDvoid	dcSubGY   ( DCvec& y ){ y.x = m[ 0 ][ 1 ]; y.y = m[ 1 ][ 1 ]; y.z = m[ 2 ][ 1 ]; }
		DDvoid	dcSubGZ   ( DCvec& z ){ z.x = m[ 0 ][ 2 ]; z.y = m[ 1 ][ 2 ]; z.z = m[ 2 ][ 2 ]; }
		
		DDvoid	dcSetSubGX( DCvec& x ){ m[ 0 ][ 0 ] = x.x; m[ 1 ][ 0 ] = x.y; m[ 2 ][ 0 ] = x.z; }
		DDvoid	dcSetSubGY( DCvec& y ){ m[ 0 ][ 1 ] = y.x; m[ 1 ][ 1 ] = y.y; m[ 2 ][ 1 ] = y.z; }
		DDvoid	dcSetSubGZ( DCvec& z ){ m[ 0 ][ 2 ] = z.x; m[ 1 ][ 2 ] = z.y; m[ 2 ][ 2 ] = z.z; }
	
	public:
		DDvoid	dcLoadM( DCmtx& M ){ dcDM() = M.dcDM(); }
		
		DDvoid	dcLoadM33( DCmtx& M )
		{
			m[0][0] = M.m[0][0];		m[0][1] = M.m[0][1];		m[0][2] = M.m[0][2];
			m[1][0] = M.m[1][0];		m[1][1] = M.m[1][1];		m[1][2] = M.m[1][2];
			m[2][0] = M.m[2][0];		m[2][1] = M.m[2][1];		m[2][2] = M.m[2][2];
		}
		
		DDvoid	dcMakeM( DCvec& p, DCmtx& r )
		{
			dcSetOrigin( p );
			dcLoadM33  ( r );
			m[0][3] = 0.0f;			m[1][3] = 0.0f;			m[2][3] = 0.0f;			m[3][3] = 1.0f;
		}
		
	public:
		DDvoid	dcTranspose( DCmtx& M ){ (DDvoid)D3DXMatrixTranspose( &M, &dcDXM() ); }
		DDvoid	dcInverse  ( DCmtx& M ){ (DDvoid)D3DXMatrixInverse( &M, NULL, &dcDXM() ); }
		DDvoid	dcCTInverse( DCmtx& M );
	
	public:
		DDvoid	dcIdentity( DDvoid ){ (DDvoid)D3DXMatrixIdentity( &dcDXM() ); }
		DDvoid	dcUnit		( DDvoid ){	dcIdentity();	}
	
	public:
		DDvoid	dcLoadTranslate( f32 x, f32 y, f32 z ){ (DDvoid)D3DXMatrixTranslation( &dcDXM(),   x,   y,   z ); }
		DDvoid	dcLoadTranslate( DCvec& p )           { (DDvoid)D3DXMatrixTranslation( &dcDXM(), p.x, p.y, p.z ); }
		
		DDvoid	dcTranslate( f32 x, f32 y, f32 z )
		{
			work.dcLoadTranslate( x, y, z );
			dcINxM( work );
		}
		DDvoid	dcTranslate( DCvec& p )
		{
			work.dcLoadTranslate( p );
			dcINxM( work );
		}
		
	public:
		DDvoid	dcLoadRotateAxis( f32 a, f32 x, f32 y, f32 z );
		DDvoid	dcLoadRotateAxis( f32 a, DCvec& v ){ dcLoadRotateAxis( a, v.x, v.y, v.z ); }
		
		DDvoid	dcLoadRotateX( f32 x ){ (DDvoid)D3DXMatrixRotationX( &dcDXM(), x ); }
		DDvoid	dcLoadRotateY( f32 y ){ (DDvoid)D3DXMatrixRotationY( &dcDXM(), y ); }
		DDvoid	dcLoadRotateZ( f32 z ){ (DDvoid)D3DXMatrixRotationZ( &dcDXM(), z ); }
		
		DDvoid	dcLoadRotateZXY( f32 x, f32 y, f32 z );
		DDvoid	dcLoadRotateZXY( DCvec& r ){ dcLoadRotateZXY( r.x, r.y, r.z ); }
		
		DDvoid	dcRotateAxis( f32 a, f32 x, f32 y, f32 z )
		{
			work.dcLoadRotateAxis( a, x, y, z );
			dcINxM( work );
		}
		DDvoid	dcRotateAxis( f32 a, DCvec& v )
		{
			dcRotateAxis( a, v.x, v.y, v.z );
		}
		DDvoid	dcRotateX( f32 x )
		{
			work.dcLoadRotateX( x );
			dcINxM( work );
		}
		DDvoid	dcRotateY( f32 y )
		{
			work.dcLoadRotateY( y );
			dcINxM( work );
		}
		DDvoid	dcRotateZ( f32 z )
		{
			work.dcLoadRotateZ( z );
			dcINxM( work );
		}
		DDvoid	dcRotateZXY( f32 x, f32 y, f32 z )
		{
			work.dcLoadRotateZXY( x, y, z );
			dcINxM( work );
		}
		DDvoid	dcRotateZXY( DCvec& r )
		{
			dcRotateZXY( r.x, r.y, r.z );
		}
		
	public:
		DDvoid	dcLoadScale( f32 s )              { (DDvoid)D3DXMatrixScaling( &dcDXM(), s, s, s ); }
		DDvoid	dcLoadScale( f32 x, f32 y, f32 z ){ (DDvoid)D3DXMatrixScaling( &dcDXM(), x, y, z ); }
		DDvoid	dcLoadScale( DCvec& s )           { (DDvoid)D3DXMatrixScaling( &dcDXM(), s.x, s.y, s.z ); }
		
		DDvoid	dcLoadScaleX( f32 x ){ (DDvoid)D3DXMatrixScaling( &dcDXM(),    x, 1.0f, 1.0f ); }
		DDvoid	dcLoadScaleY( f32 y ){ (DDvoid)D3DXMatrixScaling( &dcDXM(), 1.0f,    y, 1.0f ); }
		DDvoid	dcLoadScaleZ( f32 z ){ (DDvoid)D3DXMatrixScaling( &dcDXM(), 1.0f, 1.0f,    z ); }
		
		DDvoid	dcScale( f32 s )
		{
			work.dcLoadScale( s );
			dcINxM( work );
		}
		DDvoid	dcScale( f32 x, f32 y, f32 z )
		{
			work.dcLoadScale( x, y, z );
			dcINxM( work );
		}
		DDvoid	dcScale( DCvec& s )
		{
			work.dcLoadScale( s );
			dcINxM( work );
		}
		
		DDvoid	dcScaleX( f32 x )
		{
			work.dcLoadScaleX( x );
			dcINxM( work );
		}
		DDvoid	dcScaleY( f32 y )
		{
			work.dcLoadScaleY( y );
			dcINxM( work );
		}
		DDvoid	dcScaleZ( f32 z )
		{
			work.dcLoadScaleZ( z );
			dcINxM( work );
		}

	public:
		DDvoid	dcLoadQuat( DCquat& q ){ (DDvoid)D3DXMatrixRotationQuaternion( &dcDXM(), &q ); }
		
		DDvoid	dcQuat( DCquat& q )
		{
			work.dcLoadQuat( q );
			dcINxM( work );
		}
		
	public:
		DDvoid	dcShaft( DCvec& v );
		DDvoid	dcAngular( DCvec& v );
		
	//--------------------------------------------------
	// モデル空間のVをスクリーン空間に変換したV'の計算例
	// V' = V x World x View x Project x Viewport
	//--------------------------------------------------
	public:
		// post
		DDvoid	dcVxM  ( DCvec& v )          { D3DXVec3TransformCoord ( &v, &v, &dcDXM() ); }
		DDvoid	dcVxM  ( DCvec& i, DCvec& o ){ D3DXVec3TransformCoord ( &o, &i, &dcDXM() ); }
		DDvoid	dcVxM33( DCvec& v )          { D3DXVec3TransformNormal( &v, &v, &dcDXM() ); }
		DDvoid	dcVxM33( DCvec& i, DCvec& o ){ D3DXVec3TransformNormal( &o, &i, &dcDXM() ); }
		// anti R
		DDvoid	dcM33xV( DCvec& v );
		DDvoid	dcM33xV( DCvec& i, DCvec& o );
	
	public:
		DDvoid	dcMxIN( DCmtx& i ){ D3DXMatrixMultiply( &dcDXM(), &dcDXM(), &i ); }
		DDvoid	dcINxM( DCmtx& i ){ D3DXMatrixMultiply( &dcDXM(), &i, &dcDXM() ); }
	
	protected:
		static	DCmtx		work;
};

//---------------------------------------------------------------
//---------------------------------------------------------------

inline	f32		dcAbs( f32 x ){ return fabsf( x ); }

inline	f32		dcSqrt ( f32 x ){ return (f32)( sqrt( (double)x ) ); }
inline	f32		dcRSqrt( f32 x ){ return (f32)( 1.0 / sqrt( (double)x ) ); }

inline	f32		dcExp( f32 x ){ return expf( x ); }
inline	f32		dcLog( f32 x ){ return logf( x ); }
inline	f32		dcPow( f32 x, f32 y ){ return powf( x, y ); }

inline	f32		dcSin( f32 x ){ return sinf( x ); }
inline	f32		dcCos( f32 x ){ return cosf( x ); }
inline	f32		dcTan( f32 x ){ return tanf( x ); }

inline	f32		dcArcSin( f32 x ){ return	asinf( x ); }
inline	f32		dcArcCos( f32 x ){ return	acosf( x ); }
inline	f32		dcArcTan( f32 x ){ return	atanf( x ); }
inline	f32		dcArcTan( f32 x, f32 y ){ return atan2f( x, y ); }

//---------------------------------------------------------------
//---------------------------------------------------------------

typedef	union
{
	s32			i;
	f32			f;
}IntFlt32;

// cast( F32 to S22 ) 四捨五入( ただし0.5捨 )
s32			dcFS( f32 f );
f32			dcSF( s32 i );

// cast( F32 to S1D14 ) decimal 14 bit [ -2.0f( -32768 ) _ +1.99993896f( 32767 ) ]
s16			dcFS1D14( f32 f );
f32			dcS1D14F( s16 d );

DDvoid	dcVS1D14( DCvec& v,   s16* d );
DDvoid	dcS1D14V(   s16* d, DCvec& v );

f32			dcNan( DDvoid );

//---------------------------------------------------------------

f32		dcMaxClampZero( f32 x );
f32		dcMinClampZero( f32 x );

inline	f32		dcMaxClamp( f32 max, f32 x ){ return ( dcMaxClampZero( x - max ) + max ); }
inline	f32		dcMinClamp( f32 min, f32 x ){ return ( dcMinClampZero( x - min ) + min ); }

inline	f32		dcClamp( f32 max, f32 min, f32 x )
{
	x = dcMaxClamp( max, x );
	x = dcMinClamp( min, x );
	return	x;
}

// 符号( 正 = +1 : 負 = -1 )
f32		dcStep( f32 x );

inline	f32		dcSign( f32 x )
{
	if( x == 0.0f )	return	+0.0f;
	else						return	dcStep( x );
}

//---------------------------------------------------------------
//---------------------------------------------------------------

DDvoid	dcRandSetSeed( s32 seed );

s32			dcRand( DDvoid );
s32			dcRand( u32 mask );

s32			dcDomino( s32& seed );
s32			dcDomino( s32& seed, u32 mask );

f32			dcRandFS( DDvoid );
f32			dcRandFS( f32 ratio );

f32			dcRandFU( DDvoid );
f32			dcRandFU( f32 ratio );

//---------------------------------------------------------------
//---------------------------------------------------------------

extern	const		f32		dcGrounds[ 9 ];

inline	DCvec&	dcZero( DDvoid ){ return *( (DCvec*)( dcGrounds + 0 ) ); }

inline	DCvec&	dcXp( DDvoid ){ return *( (DCvec*)( dcGrounds + 3 ) ); }
inline	DCvec&	dcXn( DDvoid ){ return *( (DCvec*)( dcGrounds + 6 ) ); }

inline	DCvec&	dcYp( DDvoid ){ return *( (DCvec*)( dcGrounds + 2 ) ); }
inline	DCvec&	dcYn( DDvoid ){ return *( (DCvec*)( dcGrounds + 5 ) ); }

inline	DCvec&	dcZp( DDvoid ){ return *( (DCvec*)( dcGrounds + 1 ) ); }
inline	DCvec&	dcZn( DDvoid ){ return *( (DCvec*)( dcGrounds + 4 ) ); }

//---------------------------------------------------------------
//---------------------------------------------------------------

f32			dcNorm   ( DCvec& v );
f32			dcNorm   ( DCvec& u, DCvec& v );
f32			dcNormSqr( DCvec& u );
f32			dcNormSqr( DCvec& u, DCvec& v );

f32			dcNormalizer( DCvec& v );
f32			dcResizer   ( DCvec& v );

//---------------------------------------------------------------

DDvoid	dcNormalize( DCvec& in, DCvec& out, DCvec& zero );
DDvoid	dcNormalize( DCvec& in, DCvec& out );
DDvoid	dcNormalize( DCvec& v );

inline	DDvoid	dcVUnit( DCvec& in, DCvec& out, DCvec& zero ){ dcNormalize( in, out, zero ); }
inline	DDvoid	dcVUnit( DCvec& in, DCvec& out )             { dcNormalize( in, out );       }
inline	DDvoid	dcVUnit( DCvec& v )                          { dcNormalize( v );             }

//---------------------------------------------------------------

DDvoid	dcVLoad( f32 x, f32 y, f32 z, DCvec& u );
DDvoid	dcVLoad( DCvec& u, f32 x, f32 y, f32 z );

DDvoid	dcVNegate( DCvec& u );
DDvoid	dcVNegate( DCvec& u, DCvec& v );

DDvoid	dcVAdd( DCvec& u, DCvec& v, DCvec& w );
DDvoid	dcVAdd( f32 s, DCvec& u, DCvec& v, DCvec& w );
DDvoid	dcVAdd( DCvec& u, f32 s, DCvec& v, DCvec& w );

DDvoid	dcVSub( DCvec& u, DCvec& v, DCvec& w );
DDvoid	dcVSub( f32 s, DCvec& u, DCvec& v, DCvec& w );
DDvoid	dcVSub( DCvec& u, f32 s, DCvec& v, DCvec& w );

DDvoid	dcVScale( f32 s, DCvec& u );
DDvoid	dcVScale( f32 s, DCvec& u, DCvec& v );

f32			dcDot  ( DCvec& u, DCvec& v );
DDvoid	dcCross( DCvec& u, DCvec& v, DCvec& w );

DDvoid	dcCrossShaft( DCvec s, DCvec d, DCvec& r );

//---------------------------------------------------------------

DDvoid	dcRandVU( DCvec& v );
DDvoid	dcRandV ( DCvec& v );
DDvoid	dcRandV ( f32 scale, DCvec& v );

#endif
