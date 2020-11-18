
// HDR filter vertex shader

//	高光度部分を抽出して縦横半分(1/4サイズ)のテクスチャを生成

vs_2_0

// 入力レジスタ
dcl_position0			v0				// 座標変換せずにPSへ出力
dcl_texcoord0			v8				// テクスチャ座標０

// 定数レジスタ

//----------------------------------------------------------------
//----------------------------------------------------------------

// 座標

mov			oPos,		v0								// 変換せずに座標出力

// テクスチャ

mov			oT0,		v8


