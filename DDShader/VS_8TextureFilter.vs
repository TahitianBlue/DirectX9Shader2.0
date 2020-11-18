
// ぼかしフィルタ 8 texture filter vertex shader

//	8 texture * 4 sample = 32 texel filter

vs_2_0

// 入力レジスタ
dcl_position0			v0				// 座標変換せずにPSへ出力
dcl_texcoord0			v8				// テクスチャ座標０

// 定数レジスタ
//	[ c0_c7 ]	texture offset [ dot / size ]
//	c0.xy			tex  0 offset
//	c1.xy			tex  1 offset
//	c2.xy			tex  2 offset
//	c3.xy			tex  3 offset
//	c4.xy			tex  4 offset
//	c5.xy			tex  5 offset
//	c6.xy			tex  6 offset
//	c7.xy			tex  7 offset

//----------------------------------------------------------------
//----------------------------------------------------------------

// 座標

mov			oPos,		v0							// 変換せずに座標出力

// テクスチャ

add			oT0.xy,		v8.xy,		c0.xy
add			oT1.xy,		v8.xy,		c1.xy
add			oT2.xy,		v8.xy,		c2.xy
add			oT3.xy,		v8.xy,		c3.xy
add			oT4.xy,		v8.xy,		c4.xy
add			oT5.xy,		v8.xy,		c5.xy
add			oT6.xy,		v8.xy,		c6.xy
add			oT7.xy,		v8.xy,		c7.xy

