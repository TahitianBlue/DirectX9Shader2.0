
// depth shadow vertex shader pass 1

//	座標変換
//	モデルテクスチャ自動生成( XZ成分 )
//	影テクスチャ座標出力
//	反射付きライティング

vs_2_0

// 入力レジスタ
dcl_position0			v0
dcl_normal0				v4

// 定数レジスタ
// c0_c3		変換行列
// c4				光線ベクトル
// c5.x			裏面反射率 * 0.5f
// c8_c11		影テクスチャ座標への変換行列

// 定数			c31		0.5f,		-,			-, 			-
def					c31,	0.5f,		0.0f,		0.0f,		0.0f

// c32			diffuse color
// c33			ambient color

//----------------------------------------------------------------
//----------------------------------------------------------------

// transform

m4x4		oPos,		v0,			c0			// vertex transform

// texture

// model texture uv
add			oT0.xy,	v0.xz,	c31.xx	// local XZ + 0.5f => tex UV

// shadow texture xyzw
m4x4		oT1,		v0,			c8			// 座標v0を 影行列c8_c11で変換

// lighting

// 光度
dp3			r0.x,		v4,			c4			// 反転光度 = dot( 法線v4, 光線c4 )
mov			r0.x,		-r0.x						// 正光度 = -反転光度
abs			r0.y,		r0.x						// 絶対値光度

// 正面光度
add			r0.z,		r0.x,		r0.y		// 光度 + 絶対値光度 = 光度*2 : 0
mul			r0.z,		r0.z,		c31.x		// 光度*2 * 0.5f = 光度 : 0

// 裏面光度
add			r0.w,		r0.x,		-r0.y		// 光度 - 絶対値光度 = 0 : -光度*2
mul			r0.w,		-r0.w,	c5.x		// 光度*2 * RefCo*0.5f = 0 : 裏面光度

// 合計光度
add			r0.y,		r0.z,		r0.w		// 正面光度 + 裏面光度 ( どちらかだけ )

// output diffuse
mul			r1.rgb,	r0.y,		c32.rgb	// 合計光度 x dif.RGB
mul			r1.a,		r0.x,		c32.a		// 正面光度 x dif.A
add			oD0,		r1,			c33			// 頂点色oD0 = DIF + AMB


