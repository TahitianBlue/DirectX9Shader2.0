
#ifndef	__s99dsVision_h__
#define	__s99dsVision_h__

#include	"dsVision.h"
#include	"ddComputer.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------

class	S99DSVision : public DSVision
{
	public:
						 S99DSVision( DDvoid ){}
	 virtual	~S99DSVision( DDvoid ){}
	
	public:
		virtual	DDvoid	dvVisionInitial( DDvoid );
		virtual	DDvoid	dvVisionDispose( DDvoid );
		virtual	DDvoid	dvVisionProcess( DDvoid );
	
	//-----------------------------------------------
	private:
		IDirect3DTexture9*				mpRenderTexture;
		IDirect3DTexture9*				mpRenderZBuffer;
		
		f32												mRY;
		
		LPDIRECT3DVERTEXSHADER9		mVShader;
};

#endif
