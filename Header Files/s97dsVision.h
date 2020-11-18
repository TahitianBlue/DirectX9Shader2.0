
#ifndef	__s97dsVision_h__
#define	__s97dsVision_h__

#include	"dsVision.h"
#include	"ddComputer.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

enum	S97DVbloomTex
{
	S97DV_BLOOM_TEX_0,
	S97DV_BLOOM_TEX_1,
	S97DV_BLOOM_TEX_TOTAL,
};

enum	S97DVcrossTex
{
	S97DV_CROSS_TEX_BASE,
	S97DV_CROSS_TEX_WORK,
	S97DV_CROSS_TEX_RESULT,
	S97DV_CROSS_TEX_TOTAL,
};

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S97DSVision : public DSVision
{
	public:
						 S97DSVision( DDvoid ){}
	 virtual	~S97DSVision( DDvoid ){}
	
	public:
		virtual	DDvoid	dvVisionInitial( DDvoid );
		virtual	DDvoid	dvVisionDispose( DDvoid );
		virtual	DDvoid	dvVisionProcess( DDvoid );
	
	//-----------------------------------------------
	
	protected:
		// HDR scene color を元に高光度部分を抽出しぼかしフィルタ処理
		DDvoid		dvColorHDRAbstract( f32 Sub, f32 Mul );
		DDvoid		dvColorHDRBloom( f32 Mul, s32 Count );
		
		// HDR scene alpha を元に高光度部分を抽出しクロスフィルタ処理
		DDvoid		dvAlphaHDRAbstract( f32 AlphaSub );
		DDvoid		dvAlphaHDRCross( f32 X, f32 Y, s32 Count );
		
		// FrameBuffer = Scene + HDR bloom + HDR cross
		DDvoid		dvFrameMargeSceneHDR( f32 SceneSharpness, f32 BloomMul, f32 CrossMul );
	
	//-----------------------------------------------
	
	private:
		LPDIRECT3DSURFACE9				mpBackBufferSurface;
		
		// texture
		LPDIRECT3DTEXTURE9				mpShadowTexture;			// G16R16
		LPDIRECT3DSURFACE9				mpShadowZBuffer;
		LPDIRECT3DTEXTURE9				mpSceneTexture;
		LPDIRECT3DTEXTURE9				mpHDRTexture[ S97DV_BLOOM_TEX_TOTAL ];		// color bloom [ double buffer ]
		s32												mHDRTexLatest;														// latest render tex number
		LPDIRECT3DTEXTURE9				mpCrossTexture[ S97DV_CROSS_TEX_TOTAL ];	// alpha cross [ base, work, result ]
		DDbool										mCrossResultVirgin;												// 1st time alpha blend disable
		
		LPDIRECT3DTEXTURE9				mpBallTex;
		LPDIRECT3DTEXTURE9				mpCubeTex;
		LPDIRECT3DCUBETEXTURE9		mpLobbyCubeTexture;
		
		// shader
		LPDIRECT3DVERTEXSHADER9		mVS_DepthShadowP0;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP0;
		
		LPDIRECT3DVERTEXSHADER9		mVS_DepthShadowP1;
		LPDIRECT3DVERTEXSHADER9		mVS_DepthShadowP1Stealth;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP1;
		LPDIRECT3DPIXELSHADER9		mPS_DepthShadowP1CubeEnvMap;
		
		LPDIRECT3DVERTEXSHADER9		mVS_HDRFilter;
		LPDIRECT3DPIXELSHADER9		mPS_HDRFilter;
		
		LPDIRECT3DVERTEXSHADER9		mVS_AlphaHDRFilter;
		LPDIRECT3DPIXELSHADER9		mPS_AlphaHDRFilter;
		
		LPDIRECT3DVERTEXSHADER9		mVS_4TextureFilter;
		LPDIRECT3DPIXELSHADER9		mPS_4TextureFilter;
		
		LPDIRECT3DVERTEXSHADER9		mVS_8TextureFilter;
		LPDIRECT3DPIXELSHADER9		mPS_8TextureFilter;
		LPDIRECT3DPIXELSHADER9		mPS_8TextureFilterMul;
		
		LPDIRECT3DVERTEXSHADER9		mVS_Ortho;
		LPDIRECT3DPIXELSHADER9		mPS_Ortho;
		LPDIRECT3DPIXELSHADER9		mPS_OrthoMul;
		
		LPDIRECT3DVERTEXSHADER9		mVS_OrthoDif;
		LPDIRECT3DPIXELSHADER9		mPS_OrthoDif;
	
	private:
		DCmtx					mLM;			// light matrix Yn vector
		DCmtx					mVM;			// view  matrix zn position
		DCvec					mLV;			// light velocity
		DCvec					mVV;			// view  velocity
		
		s32						mCount;		// no input counter
		DDbool				mStealth;	// stealth sphere render
};

#endif
