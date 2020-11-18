
#ifndef	__doRorDomain_h__
#define	__doRorDomain_h__

#include	"ddComputer.h"

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// ドメイン種別
enum	DORDtype
{
	DORD_TYPE_SPHERE,					// 球
	DORD_TYPE_TRIANGLES,			// 複数三角
	DORD_TYPE_TOTAL
};


// SENS　マテリアル
enum	DORDsensMaterial
{
	DORD_SENS_MATERIAL_00,					// デフォルト
	DORD_SENS_MATERIAL_01_SAND,			// 砂
	
	DORD_SENS_MATERIAL_TOTAL
};


// SENS　ビヘイビア
enum	DORDsensBehavior
{
	DORD_SENS_BEHAVIOR_00_NONE,			// 何も無し
	DORD_SENS_BEHAVIOR_01_SLIDE,		// すべる床
	
	DORD_SENS_BEHAVIOR_TOTAL
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------

struct	DORDsens
{
	u8			Material;			// DORDsensMaterial
	u8			Behavior;			// DORDsensBehavior
};


struct	DORDvertex
{
	f32			X;
	f32			Y;
	f32			Z;
};


struct	DORDtriangle
{
	f32			W;						// 法線 W
	s16			N[ 3 ];				// 法線ベクトル ( S1D14 )
	u16			V[ 3 ];				// 頂点インデックス 法線正面に時計回り
};


struct	DORDtriangles
{
	u16							TNumber;				// 三角ポリゴン数
	u16							VNumber;				// 頂点リスト内の頂点数
	DORDtriangle*		TriangleList;		// トライアングルリスト先頭アドレス
	DORDvertex*			VertexList;			// 参照する頂点リスト先頭アドレス
	DORDsens				Sens;						// マテリアル情報
};


struct	DORDsphere
{
	DORDvertex	C;						// 中心座標
	f32					R;						// 半径
};


struct	DORDresult
{
	DCvec				Normal;				// 地形の法線
	f32					Length;				// 残りの長さ、または半径
	DORDsens		Sens;					// マテリアル情報
	DDenum			RorID;				// 地形RorIDナンバー
};


struct	DORDdomain
{
	DORDsphere*			S;
	DORDtriangles*	T;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// ドメイン　基底クラス

class	DORorDomain
{
	public:
						 DORorDomain( DDvoid );
		virtual	~DORorDomain( DDvoid );
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result ) = 0;
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result ) = 0;
	
	public:
		DORorDomain*			dordGetChild( DDvoid ){ return dordmChild; }
		DORorDomain*			dordGetNext ( DDvoid ){ return dordmNext;  }
	
	protected:
		DORorDomain*			dordmChild;
		DORorDomain*			dordmNext;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// ドメイン　球

class	DORDSphere : public DORorDomain
{
	public:
						 DORDSphere( DORDsphere& Sphere,        DORorDomain* Child, DORorDomain* Next );
						 DORDSphere( DCvec& Center, f32 Radius, DORorDomain* Child, DORorDomain* Next );
		virtual	~DORDSphere( DDvoid );
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result );
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result );
	
	protected:
						DDbool		dordEvaA     ( DCvec& P, DCvec& A, DORDresult& Result );
						DDbool		dordEvaS     ( DCvec& P,           DORDresult& Result );
	
	private:
		DORDsphere				dordsmSphere;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
// ドメイン　三角

class	DORDTriangles : public DORorDomain
{
	public:
						 DORDTriangles( DORDtriangles& Triangles, DORorDomain* Next );
		virtual	~DORDTriangles( DDvoid ){}
	
	public:
		virtual	DDbool		dordEvaArrow ( DCvec& P, DCvec& A, DORDresult& Result );
		virtual	DDbool		dordEvaSphere( DCvec& P,           DORDresult& Result );
	
	protected:
		DDbool						dordEvaA   ( DCvec& P, DCvec& A, DORDresult& Result );
		DDbool						dordEvaS   ( DCvec& P,           DORDresult& Result );
		DDbool						dordEvaAOne( DCvec& CP,                    DCvec& V0, DCvec& V1, DCvec& N );
		DDbool						dordEvaSOne( DCvec& P, DORDresult& Result, DCvec& V0, DCvec& V1, DCvec& N );
	
	private:
		DORDtriangles*		dordtmTriangles;
};


#endif
