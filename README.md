# ShinySymbols : ポケモン剣盾 固定シンボルの色違い厳選を自動化するArduinoプログラム集
ポケットモンスターソードシールドで固定シンボルの色違いマイコン自動化

ポケモン剣盾 冠の雪原、鎧の孤島、ワイルドエリアで固定シンボルの厳選を自動化

基本的には [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さまより内容を展開しています。

## 現在対応している場所

[ポケモン徹底攻略](https://yakkun.com/swsh/)さまより番号を対応させています

- ワイルドエリア
    - ナックル丘陵のギギアル、ギギギアル
- ヨロイ島
    - 鍛錬平原 (10)
- カンムリ雪原
    - 巨人の寝床 (23)
    - 巨人の寝床 (26)
    - 巨人の寝床 (43)
    - ボールレイクの湖畔（12）
    - 三つまたヶ原 (2)

## 注意事項

- 自動化の失敗や自動化によるセーブデータの問題には一切責任を負いません
- `Switch Lite` のバージョン13でしか検証していません。日付変更の部分が通常の `Switch` と異なるはずなので注意してください。
    - [ここの4が9になる](https://github.com/hungrykirby/ShinySymbols/blob/7af2e9419c47604bfc05aed68c342e692e957afa/modules.cpp#L185)かも（ただし、Switchを持っていないので検証できない）。

## 使い方

狙う色違いと天気を合わせた上で初期位置で自転車に乗っておく

ランクマバグの状態（日付変更を行ってもペナルティが発生しない状態）にしておく。

手持ちの先頭を **けむりだま** 持ちの **かがくへんかガス** ガラルマタドガスにする。

`Arduino` をSwitchにさす。

基本的には [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) こちらと準備物や初期設定は同じです。

## 準備するもの

### ソフトウェア

- Arduino IDE
- ( VisualStudio Code : Arduinoエディターが使いにくい人向け)

### ハードウエア

- HID機能を持った `Arduino Pro Micro` っぽいもの
- `Arduino` をつなぐケーブル

[HID機能について](https://qiita.com/MergeCells/items/17bdc1c1fb35949195b5)

> Arduino LeonardoはPCなどとUSB接続したとき，自身をHIDとして認識させる機能が標準で備わっている．HID（ヒューマン・インターフェイス・デバイス）とはUSB接続のキーボードやマウス，ゲームパッドのような入出力装置だと思っておけば差し支えない．

### ポケモン

- とくせい「かがくへんかガス」覚えている技「おきみやげ」のみのガラルマタドガス※
- ( その他厳選したいポケモンに合わせてメロメロボディ持ちやトレース持ちなど )

※特性に関するバトル最初の文字が「かがくへんかガス」に固定される。「いかく」「プレッシャー」「きんちょうかん」などで時間差が生まれるのを防ぐ。捕まえるポケモンによってはマストではない。ただし、今回の実装ではいちいち手持ちを変えるのがめんどくさいため、すべてガラルマタドガスを先頭にする想定で作成している。
※技が「おきみやげ」なのは [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さんの記事に譲ります。イエッサンだととくせい「トレース」＋わざ「いやしのねがい」があって便利ですが、上記の理由でガラルマタドガスを採用しています。

#### 便利だったポケモン

- ワンパチ：とくせい「たまひろい」でバトルで1回ボールを回収してくれる
- エルレイド：もちもの「ぼうじんゴーグル」わざ「さいみんじゅつ」「トリック」「でんじは」「みねうち」　トリックでぼうじんゴーグルを押し付けてあられ無効みたいにできる
- ユクシー：ユクシー自身でスキルスワップとあくびを覚えるため、霧や雷雨でも相手を浮かせて眠らすことができる。トリックも覚えられるため、「ねらいのまと」を押し付けてエルレイドのみねうちをゴーストタイプ相手にも通せる。
- きせきガラルサニーゴ：ドラパルトのとっしんやマンムーのあばれるを無効化してくれるので事故が減る。ドラパルトのりゅうのまいやハッサムのつるぎのまいを黒い霧でなかったことにできるのもよい
- ゴースト（未検証）：とくせい「ふゆう」でスキルスワップとさいみんじゅつ、ふういん、ほろびのうたを覚えるため、器用に動ける。特にふういんでほろびのうたを封じれるのが強い。


## 自動化対象の初期位置と注意事項
### ナックル丘陵のギギアル、ギギギアル
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ギギアル|晴れ| `KLANG_SUNNY` ||
|ギギギアル|日照り| `KLANG_DROUGHT` ||


#### 初期位置
ナックル丘陵上ならどこでもいい。空を飛んだ場所でOK

#### 注意事項
まれに予期しないタイミングでケンホロウが空から飛んでくるため、別の作業中などすぐに中断できる状態で自動化するのが望ましい。

対象ポケモンの動きが大きく、エンカウントできないときがある。その場合他のポケモンにぶつからないような適当な位置に移動するように実装はしているが、ポケモンの多い地点なので確実ではないかもしれない。

### 鍛錬平原 (10)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ハッサム|砂嵐| `SCIZOR` ||
|レントラー|雷雨| `LUXRAY` ||
|ドレディア|日照り| `LILLIGANT` |はなびらのまいで混乱する|
|ムーランド|晴れ| `STOUTLAND` |自傷技あり|
|ププリン|霧| `WIGGLYTUFF` ||
|キリキザン|曇り| `BISHARP` ||
|キングラー|雨| `KINGLER` ||


#### 初期位置
鍛錬平原の空を飛んだ場所（掘り出しおやじの前）でOK

#### 注意事項
特になし。

### 巨人の寝床 (26)

- ブラッキー
- ニドリーナ
- ドータクン
- エレブー
- クイタラン
- フリージオ
- オニゴーリ
- リーフィア

### 巨人の寝床 (23)

- ニンフィア
- アブソル
- オニシズクモ
- イシヘンジン（ソード）
- カビゴン
- チルタリス
- サンダース
- ニドキング

### ボールレイクの湖畔（12）

- ココドラ

### 三つまたヶ原 (2)

- ドラパルト
- エレキブル
- チルタリス

### 鍛錬平原 (10)



## 参考リンク

- [ワイルドエリア·ヨロイ島天候お知らせbot](https://twitter.com/poke_weatherbot) 直近のワイルドエリアの天気を調べた
- [ますたーの備忘録](https://tangential-star.hatenablog.jp/archive/category/%E3%83%9D%E3%82%B1%E3%83%A2%E3%83%B3%E5%89%A3%E7%9B%BEArduino%E8%87%AA%E5%8B%95%E5%8C%96) 事前準備等はこちらが参考になりました。
