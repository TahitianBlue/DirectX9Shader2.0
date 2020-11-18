
#include	"gtTestObject.h"
#include	"ddGraphic.h"

//------------------------------------------------------------------
//------------------------------------------------------------------

#define	GTTBOX_TSX			( 640.f * 1.0f )
#define	GTTBOX_TSY			( 480.f * 1.0f )
#define	GTTBOX_TOX			( 30.f * 1.0f )
#define	GTTBOX_TOY			( 00.f * 1.0f )

#define	GTTBOX_D3DFVF_LVERTEX		( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//------------------------------------------------------------------
//------------------------------------------------------------------

// 頂点フォーマット
typedef	struct	_GTTBOX_D3DLVERTEX_
{
	float		x, y, z;
	float		rhw;
	DWORD		color;
	float		tu0, tv0;
}GTTBOX_D3DLVERTEX;


// 頂点データ
GTTBOX_D3DLVERTEX		GTTBoxTestVertex[ 4 ] =
{
	{
		+0.0f * GTTBOX_TSX + GTTBOX_TOX,		+0.0f * GTTBOX_TSY + GTTBOX_TOY,		+0.0f,
		+1.0f,
		0x10ffffff,
		0.0f, 0.0f
	},
	{
		+0.0f * GTTBOX_TSX + GTTBOX_TOX,		+1.0f * GTTBOX_TSY + GTTBOX_TOY,		+0.0f,
		+1.0f,
		0x10ffffff,
		0.0f, 1.0f
	},
	{
		+1.0f * GTTBOX_TSX + GTTBOX_TOX,		+0.0f * GTTBOX_TSY + GTTBOX_TOY,		+0.0f,
		+1.0f,
		0x10ffffff,
		1.0f, 0.0f
	},
	{
		+1.0f * GTTBOX_TSX + GTTBOX_TOX,		+1.0f * GTTBOX_TSY + GTTBOX_TOY,		+0.0f,
		+1.0f,
		0x10ffffff,
		1.0f, 1.0f
	}
};


//------------------------------------------------------------------
// plot coaster
// constract destract
//------------------------------------------------------------------

GTDVCTestObject::GTDVCTestObject( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_EFFECT_TEX_00 ] != NULL );
	
	dvcmList[ DVC_CARD_EFFECT_TEX_00 ] = this;
}

//------------------------------------------------------------------

GTDVCTestObject::~GTDVCTestObject( DDvoid )
{
	ddASSERT( dvcmList[ DVC_CARD_EFFECT_TEX_00 ] != this );
	
	dvcmList[ DVC_CARD_EFFECT_TEX_00 ] = NULL;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDvoid	GTDVCTestObject::dvcIntro( DDvoid )
{
	dggD()->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );
	
	//デバイスに使用する頂点フォーマットをセットする
//dggD()->SetVertexShader( D3DFVF_LVERTEX );				// dx8
	dggD()->SetFVF( GTTBOX_D3DFVF_LVERTEX );
}

//------------------------------------------------------------------

DDvoid	GTDVCTestObject::dvcOutro( DDvoid )
{
}

//------------------------------------------------------------------
// action & plot
//------------------------------------------------------------------

GTTestObject::GTTestObject( DDvoid ) :
	DSAction( DA_ACTOR_ENEMY ),
	DVPlot( DVC_CARD_EFFECT_TEX_00 )
{
}

//------------------------------------------------------------------

GTTestObject::~GTTestObject( DDvoid )
{
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject::daAction( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------
//------------------------------------------------------------------

DDbool	GTTestObject::dvpSight( DDvoid )
{
	return	true;
}

//------------------------------------------------------------------

DDvoid	GTTestObject::dvpPos( DCvec& p )
{
	p = dcZero();
}

//------------------------------------------------------------------

DDvoid	GTTestObject::dvpPlot( DDvoid )
{
	//ストリームを使わないで直接データを渡して描画する
	dggD()->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, GTTBoxTestVertex, sizeof( GTTBOX_D3DLVERTEX ) );
}
