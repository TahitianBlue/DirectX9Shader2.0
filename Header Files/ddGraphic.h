
// deal dominator graphic
//			direct graphic ƒ‰ƒbƒp[

#ifndef	__ddGraphic_h__
#define	__ddGraphic_h__

#include	"ddComputer.h"

//--------------------------------------------------------------
//--------------------------------------------------------------

#define	WIDTH				( 640.f )			// Width
#define	HEIGHT			( 480.f )			// Height
/*
#define	WIDTH				( 1280.f )		// Width
#define	HEIGHT			( 1024.f )		// Height
*/
//--------------------------------------------------------------
//--------------------------------------------------------------

enum	DGdrawMode
{
	DG_DRAW_MODE_DEFAULT,			// disable vertex/pixel shader
	DG_DRAW_MODE_M44,					// Matrix44 ( Local > World > View > Pers > Screen )
	DG_DRAW_MODE_M44L,				// Matrix44, Light( Local Vector )
	DG_DRAW_MODE_M44LS44,			// Matrix44, Light, Shadow44( Local > World > Light > Pers > Tex )
	DG_DRAW_MODE_M44LS44W44,	// Matrix44, Light, Shadow44, World44( Local > World )
	DG_DRAW_MODE_TOTAL
};

//--------------------------------------------------------------
//--------------------------------------------------------------

// vertex format

// pos, tex
typedef	struct	_DDG_VTXFMT_PT_
{
	f32			x, y, z;
	f32			tu0, tv0;
}DDG_VTXFMT_PT;

// pos, dif
typedef	struct	_DDG_VTXFMT_PD_
{
	f32			x, y, z;
	DWORD		dif;
}DDG_VTXFMT_PD;

//--------------------------------------------------------------
//--------------------------------------------------------------

class	DDGraphic
{
	private:
						 DDGraphic( DDvoid ){}
		virtual	~DDGraphic( DDvoid ){}
	
	private:
		DDGraphic( DDGraphic& ){ ddASSERT( true ); }
	
	//------------------------------------
	
	// initial / dispose
	public:
		static	DDbool		dgGraphicInitial( DDvoid );
		static	DDbool		dgGraphicDispose( DDvoid );
	
	//------------------------------------
	
	public:
		static	D3DPRESENT_PARAMETERS&	dgParam   ( DDvoid ){ return mParam; }
		static	D3DDISPLAYMODE&					dgDispMode( DDvoid ){ return mDispMode; }
	
	// direct 3D ( interface & device )
	public:
		static	LPDIRECT3D9					dgI( DDvoid ){ return mD3D; }
		static	LPDIRECT3DDEVICE9		dgD( DDvoid ){ return mD3DD; }
	
	// shader ( vertex & pixel )
	public:
		static	DDvoid		dgSetVS( LPDIRECT3DVERTEXSHADER9 vs );
		static	DDvoid		dgSetPS( LPDIRECT3DPIXELSHADER9  ps );
		
		static	DDvoid		dgSetDrawMode( DGdrawMode mode ){ mDrawMode = mode; }
	
	// matrix
	public:
		static	DCmtx&		dgVM ( DDvoid ){ return mVM; }
		static	DCmtx&		dgPM ( DDvoid ){ return mPM; }
		static	DCmtx&		dgVPM( DDvoid ){ return mVPM; }
		static	DCmtx&		dgSM ( DDvoid ){ return mSM; }
	
	// light
	public:
		static	DCvec&		dgLightV( DDvoid ){ return mLightV; }
	
	//------------------------------------
	
	// draw model
	public:
		static	DDvoid		dgDraw( DCmtx& M, LPD3DXMESH Mesh, s32 SubSet );
	
	// rendering utility
	public:
		static	DDvoid		dgRenderOrthoFullScreen( DDvoid );
		static	DDvoid		dgRenderOrthoFullScreen( f32 Xofs, f32 Yofs );
		static	DDvoid		dgRenderOrthoOuterFrame( f32 RWidth, f32 RHeight, DWORD Diffuse );
	
	//------------------------------------
	
	// member
	private:
		// direct 3D
		static	D3DPRESENT_PARAMETERS			mParam;
		static	D3DDISPLAYMODE						mDispMode;
		
		// direct 3D ( interface and device )
		static	LPDIRECT3D9								mD3D;
		static	LPDIRECT3DDEVICE9					mD3DD;
		
		// shader
		static	LPDIRECT3DVERTEXSHADER9		mVS;
		static	LPDIRECT3DPIXELSHADER9		mPS;
		
		static	DGdrawMode								mDrawMode;
		
		// matrix
		static	DCmtx				mVM;				// to view transform matrix
		static	DCmtx				mPM;				// to perspective ( and screend ) transform matrix
		static	DCmtx				mVPM;				// VM * PM
		static	DCmtx				mSM;				// shadow matrix ( World >> Light >> Pers >> Tex )
		
		// light
		static	DCvec				mLightV;		// light vector on world
	
	
	// primitive vertex list
	private:
		static	DDG_VTXFMT_PT		mOrthoScreenTriangleStripList[];		// full screen copy
		static	DDG_VTXFMT_PT		mOrthoOffsetTriangleStripList[];		// offset screen copy
		static	DDG_VTXFMT_PD		mOrthoOuterFrameLineStripList[];		// outer frame 1 dot erazer
};


//--------------------------------------------------------------
//--------------------------------------------------------------

inline	LPDIRECT3D9				dggI( DDvoid )
{
	return	DDGraphic::dgI();
}

//--------------------------------------------------------------

inline	LPDIRECT3DDEVICE9	dggD( DDvoid )
{
	return	DDGraphic::dgD();
}


#endif
