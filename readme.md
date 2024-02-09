## DirectX9 ピクセルシェーダ2.0テスト

[![動作YouTube](http://img.youtube.com/vi/M7Ybh4UoAC0/0.jpg)](https://www.youtube.com/watch?v=M7Ybh4UoAC0)

![疑似HDRフィルタ](https://raw.githubusercontent.com/TahitianBlue/DirectX9Shader2.0/master/HDRCrossFilter.jpg)

![ソフトシャドウ](https://raw.githubusercontent.com/TahitianBlue/DirectX9Shader2.0/master/SelfShadowSoftEdge.jpg)

２００４年１月～２月制作の個人研究プロジェクト。当時ＰＣでピクセルシェーダ2.0が利用できるようになり新しいグラフィック表現を実験していたもの。
* ピクセルシェーダテスト（GPUシェーダアセンブラ記述）
* 物理挙動、タスク管理の独自実装

ゲームパッド操作によりカメラ位置、光源位置、ボールへの引力発生、シェーダ変更できます。

USBゲームパッドを接続していないと落ちてしまう場合があります。その場合はいくつかあるexeファイルのうち、"NoPad"となっているものを起動してみてください。(内容は同じ物ですが、細かな設定を変更してあります)

### 開発環境
* VC++ 6.0
* Athron 1800+
* ATi Radeon 9600

### 疑似HDRクロスフィルタ
![疑似HDRフィルタ](https://raw.githubusercontent.com/TahitianBlue/DirectX9Shader2.0/master/HDRCrossFilter.jpg)

強い光を放つ部分から放射状の光の線が拡散する表現

* 整数カラー精度６０fpsでの描画
* 明るい部分を高輝度とみなして拡散フィルタリング
* テクスチャマルチサンプリングを用いて引き伸ばし

### キューブ環境マップ
イメージベースドライティングのテスト。（森の中だった気がする）

### セルフシャドウ

Zバッファシャドウマップによるセルフシャドウ
![ソフトシャドウ](https://raw.githubusercontent.com/TahitianBlue/DirectX9Shader2.0/master/SelfShadowSharpEdge.jpg)

ソフトシャドウ（エッジをぼかすマルチサンプリング追加）
![ソフトシャドウ](https://raw.githubusercontent.com/TahitianBlue/DirectX9Shader2.0/master/SelfShadowSoftEdge.jpg)

### ステルスレンダラー

透明表示。フレームバッファを参照してやや屈折した映像を表現。（画像なし）
