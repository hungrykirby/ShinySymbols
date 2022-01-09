# ShinySymbols : ポケモン剣盾 固定シンボルの色違い厳選を自動化するArduinoプログラム集
ポケットモンスターソードシールドで固定シンボルの色違いマイコン自動化

ポケモン剣盾 冠の雪原、鎧の孤島、ワイルドエリアで固定シンボルの厳選を自動化

基本的には [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さまより内容を展開しています。

## 現在対応しているポケモン

[ポケモン徹底攻略](https://yakkun.com/swsh/)さまより番号を対応させています

▼検証済み

|ポケモン|地域|地点|天気|検証日（例）|
|:--|:--|:--|:--|:--|
|ニンフィア|カンムリ雪原|巨人の寝床 (23)|霧|12/07|
|ハッサム|ヨロイ島|鍛錬平原 (10)|砂嵐|12/11|
|キングラー|ヨロイ島|鍛錬平原 (10)|雨|1/2|
|レントラー|ヨロイ島|鍛錬平原 (10)|雷雨|12/31|
|ドレディア|ヨロイ島|鍛錬平原 (10)|日照|12/24|
|ムーランド|ヨロイ島|鍛錬平原 (10)|晴れ|1/4|
|プクリン|ヨロイ島|鍛錬平原 (10)|霧|1/1|

▼検証中

|ポケモン|地域|地点|天気|検証日（例）|
|:--|:--|:--|:--|:--|
|ココドラ|カンムリ雪原|ボールレイクの湖畔（12）|雷雨|1/3|
|オニシズクモ|カンムリ雪原|巨人の寝床 (23)|雨|1/4|
|ドラパルト|カンムリ雪原|三つまたヶ原 (2)|雨|--/--|
|エレキブル|カンムリ雪原|三つまたヶ原 (2)|雷雨|--/--|


### 更新予定

すでに検証済みだが別リポジトリやフォルダで作ったもの

|ポケモン|地域|地点|天気|検証日|
|:--|:--|:--|:--|:--|
|ドータクン<br>アブソル<br>アイアント<br>デンチュラ|カンムリ雪原|巨人の寝床 (28)|||
|ギギアル|ワイルドエリア|ナックル丘陵 (10)|||

### 更新予定2

[ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さまに記載されているうち

- メタグロス
- マンムー、カビゴン
- ツボツボ

も対応するかも（でも上記記事が詳しいのでモチベーションはない）

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

※特性に関するバトル最初の文字が「かがくへんかガス」に固定される。「いかく」「プレッシャー」「きんちょうかん」などで時間差が生まれるのを防ぐ。捕まえるポケモンによってはマストではない。
※技が「おきみやげ」なのは [ミドリカワセミさんの苔むした日記帳](https://kokenikki.blogspot.com/2021/09/poke09extra.html) さんの記事に譲ります。イエッサンだととくせい「トレース」＋わざ「いやしのねがい」があって便利ですが、上記の理由でガラルマタドガスを採用しています。

#### 便利だったポケモン

- ワンパチ：とくせい「たまひろい」でバトルで1回ボールを回収してくれる
- エルレイド：もちもの「ぼうじんゴーグル」わざ「さいみんじゅつ」「トリック」「でんじは」「みねうち」　トリックでぼうじんゴーグルを押し付けてあられ無効みたいにできる
- ユクシー：ニンフィアがスキルスワップを使ってくるのでミストフィールド下であくびが通ることがある
- ユクシー：ユクシー自身でスキルスワップとあくびを覚えるため、霧や雷雨でも相手を浮かせて眠らすことができる。トリックも覚えられる
- きせきガラルサニーゴ：ドラパルトのとっしんやマンムーのあばれるを無効化してくれるので事故が減る。ドラパルトのりゅうのまいやハッサムのつるぎのまいを黒い霧でなかったことにできるのもよい
- ゴースト（未検証）：とくせい「ふゆう」でスキルスワップとさいみんじゅつ、ふういん、ほろびのうたを覚えるため、器用に動ける。特にふういんでほろびのうたを封じれるのが強い。


## 参考：各地点の出現ポケモン
### 巨人の寝床 (28)

- ニンフィア
- アブソル
- オニスズクモ
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

### 鍛錬平原 (10)

- ハッサム
- キングラー
- プクリン
- ムーランド
- レントラー
- ドレディア
- キリキザン

## 参考リンク

- [ワイルドエリア·ヨロイ島天候お知らせbot](https://twitter.com/poke_weatherbot) 直近のワイルドエリアの天気を調べた
- [ますたーの備忘録](https://tangential-star.hatenablog.jp/archive/category/%E3%83%9D%E3%82%B1%E3%83%A2%E3%83%B3%E5%89%A3%E7%9B%BEArduino%E8%87%AA%E5%8B%95%E5%8C%96) 事前準備等はこちらが参考になりました。
