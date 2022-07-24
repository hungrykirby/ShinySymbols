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
- `Switch Lite` のバージョン13、14でしか検証していません。日付変更の部分が通常の `Switch` と異なるはずなので注意してください。
    - [ここの4が9になる](https://github.com/hungrykirby/ShinySymbols/blob/7af2e9419c47604bfc05aed68c342e692e957afa/modules.cpp#L185)かも（ただし、Switchを持っていないので検証できない）。

## 使い方

狙う色違いと天気を合わせた上で初期位置で自転車に乗っておく

ランクマバグの状態（日付変更を行ってもペナルティが発生しない状態）にしておく。

手持ちの先頭を **けむりだま** 持ちの **かがくへんかガス** ガラルマタドガスにする。

`Arduino` をSwitchにさす。

基本的には [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) こちらと準備物や初期設定は同じです。

## 準備するもの

### ソフトウェア

- `Arduino IDE`
- ( VisualStudio Code : `Arduino` エディターが使いにくい人向け)

### ハードウエア

- HID機能を持った `Arduino Pro Micro` っぽいもの
- `Arduino` をつなぐケーブル

[HID機能について](https://qiita.com/MergeCells/items/17bdc1c1fb35949195b5)

> Arduino LeonardoはPCなどとUSB接続したとき，自身をHIDとして認識させる機能が標準で備わっている．HID（ヒューマン・インターフェイス・デバイス）とはUSB接続のキーボードやマウス，ゲームパッドのような入出力装置だと思っておけば差し支えない．

### ポケモン

- とくせい *かがくへんかガス* 覚えている技 *おきみやげ* のみの *ガラルマタドガス* ※
- ( その他厳選したいポケモンに合わせて *メロメロボディ* 持ちやトレース持ちなど )

※特性に関するバトル最初の文字が **かがくへんかガス** に固定される。 *いかく* *プレッシャー* *きんちょうかん* などで時間差が生まれるのを防ぐ。捕まえるポケモンによってはマストではない。ただし、今回の実装ではいちいち手持ちを変えるのがめんどくさいため、すべて *ガラルマタドガス* を先頭にする想定で作成している。

※技が *おきみやげ* なのは [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さんの記事に譲ります。 *イエッサン* だととくせい *トレース* ＋わざ *いやしのねがい* があって便利ですが、上記の理由でガラルマタドガスを採用しています。

#### 便利だったポケモン

- ワンパチ：とくせい *たまひろい* でバトルで1回ボールを回収してくれる
- エルレイド：もちもの *ぼうじんゴーグル* わざ *さいみんじゅつ* *トリック* *でんじは* *みねうち*　*トリック*で *ぼうじんゴーグル* を押し付けてあられ無効みたいにできる
- ユクシー：ユクシー自身で *スキルスワップ* と *あくび* を覚えるため、霧や雷雨でも相手を浮かせて眠らすことができる。 *トリック* も覚えられるため、 *ねらいのまと* を押し付けてエルレイドの *みねうち* をゴーストタイプ相手にも通せる。
- きせきガラルサニーゴ：ドラパルトの *とっしん* やマンムーの *あばれる* を無効化してくれるので事故が減る。ドラパルトの *りゅうのまい* やハッサムの *つるぎのまい* を *黒い霧* でなかったことにできるのもよい
- ゴースト（未検証）：とくせい *ふゆう* で *スキルスワップ* と *さいみんじゅつ* *ふういん* *ほろびのうた* を覚えるため、器用に動ける。特に *ふういん* で *ほろびのうた* を封じれるのが強い。


## 自動化対象の初期位置と注意事項
### ナックル丘陵のギギアル、ギギギアル
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ギギアル|晴れ| `KLANG_SUNNY` ||
|ギギギアル|日照り| `KLANG_DROUGHT` |検証中|


#### 初期位置
ナックル丘陵上ならどこでもいい。空を飛んだ場所でOK

#### 注意事項
まれに予期しないタイミングでケンホロウが空から飛んでくるため、別の作業中などすぐに中断できる状態で自動化するのが望ましい。

対象ポケモンの動きが大きく、エンカウントできないときがある。その場合他のポケモンにぶつからないような適当な位置に移動するように実装はしているが、ポケモンの多い地点なので確実ではないかもしれない。

---

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

エンカウントできない確立が低く（ポケモンの方向を見て動かないため）、周りのポケモンも多くない。

---

### 鍛錬平原 (10)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|エアームド|砂嵐| `SKARMORY` | エアームド接近を待つ間に別ポケモン（ストライク等）が接近してくる |
|レアコイル|雷雨| `MAGNETON` ||
|ヒノヤコマ|日照り| `FLETCHINDER` ||
|ストライク|晴れ|  ||
|フワライド|霧|  ||
|ココロモリ|曇り| `SWOOBAT` | 無理っぽそう |
|ペリッパー|雨|  ||

#### 初期位置
鍛錬平原の空を飛んだ場所（掘り出しおやじの前）でOK

#### 注意事項
リスクのある固定シンボル。基本的に浮遊しているのでベルを鳴らしながら地面で待つという手法をとった。

そのため別のポケモンが近づいてくる、エンカウントまでの時間にばらつきがあるなどのリスクがある。基本的には他の作業をしながらすぐに動けるときに自動化する必要がある。

---

### 巨人の寝床 (26)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ブラッキー|曇り| `UMBREON` |くろいまなざしを覚えているので交代できなくなるリスクがある|
|ニドリーナ|霧| `NIDORINA` ||
|ドータクン|雨| --- |未検証|
|エレブー|雷雨| `ELECTABUZZ` ||
|クイタラン|日照り| `HEATMOR` ||
|フリージオ|雪| `CRYOGONAL` ||
|オニゴーリ|吹雪| --- |未検証|
|リーフィア|晴れ| `LEAFEON` ||

#### 初期位置
巨人の寝床内ならどこでもいい。

おじさんの前だと雪中渓谷に入ってしまうため、少し動く必要がある。

#### 注意事項
特になし。

ポケモンに向かって動くためエンカウントできない確立がそれなりにある（体感20回に1回程度）。そのため、やや効率が悪い。

---

### 巨人の寝床 (23)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ニンフィア|霧| `SYLVEON` |スキルスワップが不確定要素|
|アブソル|| --- |未検証|
|オニシズクモ|雨|`ARAQUANID` ||
|イシヘンジン（ソード）|| --- |未検証|
|カビゴン|| --- |未検証|
|チルタリス|| --- |未検証|
|サンダース|雷雨| `JOLTEON` |手前にいるオニシズクモにエンカウントしてしまうことがある。<br>オニシズクモにエンカウントしてもループ破綻しないが厳選効率は悪い|
|ニドキング|| `NIDOKING_NEDOKO23` |未検証|

#### 初期位置
巨人の寝床内ならどこでもいい。

おじさんの前だと雪中渓谷に入ってしまうため、少し動く必要がある。

#### 注意事項
1ループが1分を超えることが多いため長時間やるなら午前0時スタートが無難。

サンダースは手前のオニシズクモにエンカウントすることがあり、ループ破綻しないが厳選効率が悪い。
そこで出たオニシズクモが色違いだった場合にループが止まるかは未検証。

アブソル、カビゴン、チルタリス、ニドキングは別の場所のほうが厳選効率がいいので未検証。オニシズクモもおそらくもっといい厳選場所がありそう。

---

### ボールレイクの湖畔（12）
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ココドラ|雷雨| `ARON_RAIU` |自傷技あり|

#### 初期位置
湖畔の洞窟内。ダイ木の丘で空を飛んだ直後（何も操作していない状態）でも開始できるが湖畔の洞窟から始めるやり方でしかほぼ検証していない。

#### 注意事項
自傷技がある（すてみタックル）。またてっぺきを覚えておりややめんどくさい。

ヘビーボールだとかなり高い確立で捕まる感覚がある。

すべての天候でココドラが出るシンボルだが、雷雨以外は試していない。

パルスワンやオニシズクモが周囲をかなり動いているので、エンカウントできなかったとき、戦闘が終わったと湖畔の洞窟に入るようにした。

---

### 三つまたヶ原 (2)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ドラパルト|雨| `DRAGAPULT_AME` |自傷技あり|
|エレキブル|雷雨| `ELECTIVIRE` ||
|チルタリス|| --- |未検証|

#### 初期位置
三つまたヶ原。空を飛ぶ直後からできるので単純。

#### 注意事項
ドラパルトは自傷技がある（とっしん）。またりゅうのまいを覚えておりとくせいがクリアボディのときもあるため、くろいきりを覚えた物理受けきせきサニーゴがいると心強い。

ゴーストタイプなのでスキルスワップでねらいのまとを押し付けたい。

単純にドラパルトの色違い、色証がほしいだけなら乱数のほうが楽。

---

### 巨人の寝床 (28)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|デンチュラ|雷雨| `GALVANTULA` ||
|オニゴーリ|雪| `GLALIE` |検証中<br>エンカウントできなかったときの挙動が不安定|
|チルタリス|曇り| `ALTARIA` |ほろびのうたあり|
|ドータクン|雨| `BRONZONG` ||
|アブソル|吹雪| `ABSOL` |未検証<br>ほろびのうたあり|
|バイウールー|晴れ| `DUBWOOL` |自傷技あり|
|アイアント|日照| `DURANT` ||
|ピクシー|霧| `CLEFABLE` |ゆびをふるが不確定要素|

#### 初期位置
巨人の寝床内ならどこでもいい。

おじさんの前だと雪中渓谷に入ってしまうため、少し動く必要がある。

#### 注意事項

この固定シンボルは *雪中渓谷* に空を飛ぶをしたところからまっすぐ向かうと *雪中渓谷* の天候を受けてしまうため、あえて一度遠ざかる動きをしている。

アブソルは[別リポジトリ](https://github.com/hungrykirby/absol)で作成したものがある。

*雪中渓谷* には雷雨が存在しないため、まっすぐ向かうとデンチュラにエンカウントできない。ただ、アブソルは *雪中渓谷* が雪かつ *巨人の寝床* が晴れまたは曇りだと、あられのダメージをなくせるので上記リポジトリは一定の意味がある（ただし、ガラルマタドガスで検証していない）。

チルタリスとアブソルはほろびのうたをしてくるため、厳選モチベーションがすごく下がる。初手で打たれたらどうしようもない。

---

### 巨人の寝床 (43)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|オーロンゲ|霧| `GRIMMSNARL` ||
|ニドキング|雨| `NIDOKING_NEDOKO43` ||
|ニドキング|日照| `NIDOQUEEN_NEDOKO43` ||

#### 初期位置
巨人の寝床内ならどこでもいい。

おじさんの前だと雪中渓谷に入ってしまうため、少し動く必要がある。

#### 注意事項
エンカウントできないことがある。草むらからけっこうポケモンが出てくるため、エンカウントできなかったときの動きを大きくしている。

---

### 滑り出し雪原 (12)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|マンムー|日照り| `MAMOSWINE` |あばれるで混乱する|
|オニゴーリ|吹雪| `GLALIE_SUBERIDASHI` ||
|カビゴン|晴れ| `SNORLAX` ||
|ルージュラ|霧| `JYNX` ||
|フリージオ|雪| `CRYOGONAL_SUBERIDASHI` ||
|マニューラ|曇り| `WEAVILE` ||

#### 初期位置
滑り出し雪原の空を飛んだ場所（ダイマックス巣穴の前）でOK

#### 注意事項
特になし。

マンムーの暴れるがつらいので体力を削りすぎないかあばれるより前にゴーストタイプに入れ替えておく方がよい

---

### 滑り出し雪原 (8)
#### 出現ポケモン

|ポケモン|天気|定数|備考|
|:--|:--|:--|:--|
|ユキメノコ|吹雪| `FLOSLASS` ||

#### 初期位置
滑り出し雪原の空を飛んだ場所（ダイマックス巣穴の前）でOK

#### 注意事項
特になし。

ユキメノコの色がほとんど変わらないので困る

## 参考リンク

- [ワイルドエリア·ヨロイ島天候お知らせbot](https://twitter.com/poke_weatherbot) 直近のワイルドエリアの天気を調べた
- [ますたーの備忘録](https://tangential-star.hatenablog.jp/archive/category/%E3%83%9D%E3%82%B1%E3%83%A2%E3%83%B3%E5%89%A3%E7%9B%BEArduino%E8%87%AA%E5%8B%95%E5%8C%96) 事前準備等はこちらが参考になりました。
- [【剣盾乱数調整】野生シンボル乱数調整のやり方【色証乱数】](https://larvesta10.hatenablog.com/entry/2021/12/13/204342) 乱数調整はここで勉強しました。
- [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) 根本のロジックはこちらから
- [ポケモン徹底攻略（剣盾）](https://yakkun.com/swsh/) 固定シンボルの情報はこちらより集めています。
