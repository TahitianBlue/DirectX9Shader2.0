
#ifndef	__s98dsVision_h__
#define	__s98dsVision_h__

#include	"dsVision.h"
#include	"ddComputer.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S98DSVision : public DSVision
{
	public:
						 S98DSVision( DDvoid ){}
	 virtual	~S98DSVision( DDvoid ){}
	
	public:
		virtual	DDvoid	dvVisionInitial( DDvoid );
		virtual	DDvoid	dvVisionDispose( DDvoid );
		virtual	DDvoid	dvVisionProcess( DDvoid );
	
	//-----------------------------------------------
	private:
		IDirect3DTexture9*				mpRenderTexture;
		LPDIRECT3DSURFACE9				mpRenderZBuffer;
		
		IDirect3DTexture9*				mpBallTex;
		IDirect3DTexture9*				mpCubeTex;
		
		LPDIRECT3DVERTEXSHADER9		mVS_DepthShadowP0;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP0;
		
		LPDIRECT3DVERTEXSHADER9		mVS_DepthShadowP1;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP1;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP1Soft;
	
	private:
		DCmtx					mLM;			// light matrix Yn vector
		DCmtx					mVM;			// view  matrix zn position
		DCvec					mLV;			// light velocity
		DCvec					mVV;			// view  velocity
		
		s32						mCount;				// no input counter
		DDbool				mSoftShadow;	// soft shadow mode
};

#endif
