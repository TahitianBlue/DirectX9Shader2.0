## DirectX9 ピクセルシェーダ2.0テスト

https://github.com/TahitianBlue/DirectX9Shader2.0/blob/master/SelfShadowSharpEdge.jpg
https://github.com/TahitianBlue/DirectX9Shader2.0/blob/master/SelfShadowSoftEdge.jpg

２００４年１月～２月制作。当時ＰＣでピクセルシェーダ2.0が利用できるようになり新しいグラフィック表現を実験していたもの。

ゲームパッド操作によりカメラ位置、光源位置、ボールへの引力発生、シェーダ変更できます。

USBゲームパッドを接続していないと落ちてしまう場合があります。その場合はいくつかあるexeファイルのうち、"NoPad"となっているものを起動してみてください。(内容は同じ物ですが、細かな設定を変更してあります)

### 開発環境
* VC++ 6.0
* Athron 1800+
* ATi Radeon 9600

### 疑似HDRクロスフィルタ
HDRCrossFilter.jpg
強い光を放つ部分から放射状の光の線が拡散する表現

* 整数カラー精度６０fpsでの描画
* 明るい部分を高輝度とみなして拡散フィルタリング
* テクスチャマルチサンプリングを用いて引き伸ばし

### キューブ環境マップ
HDRCrossFilter.jpg
イメージベースドライティングのテスト

### セルフシャドウ
SelfShadowSharpEdge.jpg

* Zバッファシャドウマップによるセルフシャドウ

SelfShadowSoftEdge.jpg

* ソフトシャドウ（エッジをぼかすマルチサンプリング）

