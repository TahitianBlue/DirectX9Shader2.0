
// HDR filter vertex shader

//	高光度部分を抽出して縦横半分(1/4サイズ)のテクスチャを生成
//	HDR texture D3DFMT_A1R5G5B5 を想定

vs_2_0

// 入力レジスタ
dcl_position0			v0				// 座標変換せずにPSへ出力
dcl_texcoord0			v8				// テクスチャ座標０

// 定数レジスタ
//	c0		texture offset 1.0f / 幅 ( +X, +Y, -X, -Y )

//----------------------------------------------------------------
//----------------------------------------------------------------

// 座標

mov			oPos,		v0								// 変換せずに座標出力

// テクスチャ

// 左上 ( -X, -Y )
add			oT0.xy,	v8.xy,	c0.zw

// 左下 ( -X, +Y )
add			oT1.xy,	v8.xy,	c0.zy

// 右上 ( +X, -Y )
add			oT2.xy,	v8.xy,	c0.xw

// 右下 ( +X, +Y )
add			oT3.xy,	v8.xy,	c0.xy

