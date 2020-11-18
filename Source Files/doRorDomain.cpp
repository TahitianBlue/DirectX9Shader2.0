
#include	"doRorDomain.h"


//--------------------------------------------------------------------
//--------------------------------------------------------------------

DORorDomain::DORorDomain( DDvoid )
{
	dordmChild = NULL;
	dordmNext  = NULL;
}

//--------------------------------------------------------------------

DORorDomain::~DORorDomain( DDvoid )
{
	if( dordmChild )
		delete	dordmChild;
	
	if( dordmNext )
		delete	dordmNext;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

DORDSphere::DORDSphere( DORDsphere& Sphere, DORorDomain* Child, DORorDomain* Next )
{
	dordsmSphere = Sphere;
	
	dordmChild = Child;
	dordmNext  = Next;
}

DORDSphere::DORDSphere( DCvec& Center, f32 Radius, DORorDomain* Child, DORorDomain* Next )
{
	dordsmSphere.C.X = Center.x;
	dordsmSphere.C.Y = Center.y;
	dordsmSphere.C.Z = Center.z;
	dordsmSphere.R   = Radius;
	
	dordmChild = Child;
	dordmNext  = Next;
}


DORDSphere::~DORDSphere( DDvoid )
{
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

DDbool	DORDSphere::dordEvaArrow( DCvec& P, DCvec& A, DORDresult& Result )
{
	DDbool	flag = false;
	
	if( dordEvaA( P, A, Result ) )
		flag = dordmChild -> dordEvaArrow( P, A, Result );
	
	if( dordmNext )
		flag = ( dordmNext -> dordEvaArrow( P, A, Result )  ||  flag );
	
	return	flag;
}

//--------------------------------------------------------------------

DDbool	DORDSphere::dordEvaA( DCvec& P, DCvec& A, DORDresult& Result )
{
	DCvec				pcv;
	DCvec				v;
	f32					rr;
	f32					vv;
	f32					radius;
	f32					scalar;
	f32					length;
	
	dcVSub( (DCvec&)dordsmSphere.C, P, pcv );
	
	radius = dordsmSphere.R;
	scalar = dcDot( pcv, A );
	length = Result.Length;
	
	if( scalar > -radius  &&  scalar < length + radius )
	{
		dcVSub( dcClamp( length, 0.0f, scalar ), A, pcv, v );
		
		vv = dcNormSqr( v );
		rr = radius * radius;
		
		return	( vv <= rr );
	}
	return	false;
}

//--------------------------------------------------------------------

DDbool	DORDSphere::dordEvaSphere( DCvec& P, DORDresult& Result )
{
	DDbool	flag = false;
	
	if( dordEvaS( P, Result ) )
		flag = dordmChild -> dordEvaSphere( P, Result );
	
	if( dordmNext )
		flag = ( dordmNext -> dordEvaSphere( P, Result )  ||  flag );
	
	return	flag;
}

//--------------------------------------------------------------------

DDbool	DORDSphere::dordEvaS( DCvec& P, DORDresult& Result )
{
	f32			d;
	f32			r;
	
	d = dcNormSqr( (DCvec&)dordsmSphere.C, P );
	r = Result.Length + dordsmSphere.R;
	r = SQR( r );
	
	return	( d <= r );
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------

DORDTriangles::DORDTriangles( DORDtriangles& Triangles, DORorDomain* Next )
{
	dordtmTriangles = &Triangles;
	
	dordmNext = Next;
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaArrow( DCvec& P, DCvec& A, DORDresult& Result )
{
	DDbool		flag;
	
	flag = dordEvaA( P, A, Result );
	
	if( dordmNext )
		flag = ( dordEvaArrow( P, A, Result )  ||  flag );
	
	return	flag;
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaA( DCvec& P, DCvec& A, DORDresult& Result )
{
	f32							inLength;
	f32							testC;
	f32							testL;
	DCvec						n;
	DCvec						cp;
	DCvec*					vertex;
	DORDtriangle*		triangle;
	
	
	inLength = Result.Length;
	
	vertex   = (DCvec*)dordtmTriangles -> VertexList;
	
	// vertex pointer check
	ddASSERT( vertex == NULL );
	
	
	for( s32 i = 0 ; i < dordtmTriangles -> TNumber ; i++ )
	{
		triangle = &dordtmTriangles -> TriangleList[ i ];
		
		// triangle pointer check
		ddASSERT( triangle == NULL );
		
		dcS1D14V( triangle -> N, n );
		
		testC = dcDot( A, n );
		
		if( testC < 0.0f )
		{
			testL = ( (-triangle -> W) - dcDot( P, n ) ) / testC;
			
			if( testL >= 0.0f && testL < Result.Length )
			{
				// projected
				dcVAdd( P, testL, A, cp );
				
				// 0 - 1
				if( dordEvaAOne( cp, vertex[ triangle->V[ 0 ] ], vertex[ triangle->V[ 1 ] ], n ) )
					continue;
				
				// 1 - 2
				if( dordEvaAOne( cp, vertex[ triangle->V[ 1 ] ], vertex[ triangle->V[ 2 ] ], n ) )
					continue;
				
				// 2 - 0
				if( dordEvaAOne( cp, vertex[ triangle->V[ 2 ] ], vertex[ triangle->V[ 0 ] ], n ) )
					continue;
				
				// save result
				Result.Length = testL;
				Result.Normal = n;
				Result.Sens   = dordtmTriangles -> Sens;
			}
		}
	}
	
	return ( Result.Length < inLength );
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaAOne( DCvec& CP, DCvec& V0, DCvec& V1, DCvec& N )
{
	DCvec			va;
	DCvec			vb;
	DCvec			v;
	
	dcVSub( V1, V0, va );
	dcVSub( CP, V0, vb );
	
	dcCross( va, vb, v );
	
	return	( dcDot( v, N ) > 0.0f );
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaSphere( DCvec& P, DORDresult& Result )
{
	DDbool			flag;
	
	flag = dordEvaS( P, Result );
	
	if( dordmNext )
		flag = ( dordEvaSphere( P, Result )  ||  flag );
	
	return	flag;
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaS( DCvec& P, DORDresult& Result )
{
	f32							inRadius;
	f32							testL;
	DCvec						n;
	DCvec*					vertex;
	DORDtriangle*		triangle;
	
	
	inRadius = Result.Length;
	
	vertex   = (DCvec*)dordtmTriangles -> VertexList;
	
	// vertex pointer check
	ddASSERT( vertex == NULL );
	
	
	for( s32 i = 0 ; i < dordtmTriangles -> TNumber ; i++ )
	{
		triangle = &dordtmTriangles -> TriangleList[ i ];
		
		// triangle pointer check
		ddASSERT( triangle == NULL );
		
		dcS1D14V( triangle -> N, n );
		
		testL = dcDot( P, n ) + triangle -> W;		// 法線上での原点からＰまでの距離 + 法線上での平面点から原点までの距離
		
		if( testL < 0.0f || testL >= Result.Length )	continue;
		
		//--------------------
		
		// 0 - 1
		if( dordEvaSOne( P, Result, vertex[ triangle->V[ 0 ] ], vertex[ triangle->V[ 1 ] ], n ) )
			continue;
		
		// 1 - 2
		if( dordEvaSOne( P, Result, vertex[ triangle->V[ 1 ] ], vertex[ triangle->V[ 2 ] ], n ) )
			continue;
		
		// 2 - 0
		if( dordEvaSOne( P, Result, vertex[ triangle->V[ 2 ] ], vertex[ triangle->V[ 0 ] ], n ) )
			continue;
		
		// save result
		Result.Length = testL;
		Result.Normal = n;
		Result.Sens   = dordtmTriangles -> Sens;
	}
	
	return	( Result.Length < inRadius );
}

//--------------------------------------------------------------------

DDbool	DORDTriangles::dordEvaSOne( DCvec& P, DORDresult& Result, DCvec& V0, DCvec& V1, DCvec& N )
{
	DCvec				va;
	DCvec				vb;
	DCvec				v;
	f32					edgeL;
	f32					edgeC;
	f32					edgeR;
	
	dcVSub( V1, V0, va );
	dcVSub(  P, V0, vb );
	
	dcCross( va, vb, v );
	
	if( dcDot( v, N ) > 0.0f )
	{
		edgeL = dcNorm( va );
		
		// zero triangle check
		ddASSERT( edgeL == 0.0f );
		
		dcVScale( 1.0f / edgeL, va );
		
		edgeC = dcDot( vb, va );
		
		if( edgeC > -Result.Length  &&  edgeC < edgeL + Result.Length )
		{
			dcVAdd( V0, dcClamp( edgeL, 0.0f, edgeC ), va, v );
			
			dcVSub( P, v, v );
			
			edgeR = dcNorm( v );
			
			if( edgeR < Result.Length )
			{
				// zero divide check
				ddASSERT( edgeR == 0.0f );
				
				dcVScale( 1.0f / edgeR, v, Result.Normal );
				Result.Length = edgeR;
				Result.Sens   = dordtmTriangles -> Sens;
			}
		}
		
		return	true;
	}
	return	false;
}

