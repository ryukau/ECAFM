# ECAFM
Elementary Cellular Automatonを利用したFMシンセサイザ。Qt5.5を使用。

## 使い方
Randomボタンを押して音を探すことができる。気に入った音はSaveボタンで保存できる。
wavファイルとして、ECAFMと同じディレクトリに作られるrenderディレクトリに保存される。

Duration、MaxStepの値で音の長さ、Pitchの値で音の高さ、Ratio、Harmonicsで音の質感を変更できる。
がさがさした音になったら、HarmoTypeをSoftにすると少し落ち着いた音になる。
Rule、Seedで時間に伴う音の変化を決めることができる。

## 構成
2オペレータFMで、FMインデックス（変調の度合い）は3.0で固定。

### オペレータについて
Pitchから基音を設定、倍音をHarmonicsの数だけ用意。
各倍音はElementary CAのセルに相当、あるステップで0ならその倍音をミュート、1なら発音する。
時間がDuration進むごとに1ステップ増加。1ステップ増加ごとにElementary CAが1世代進む。

下図はオペレータの概略。

![ECAFMのオペレータ](ECAFM.png)

## 機能

### Duration(msec/step)
1ステップあたりの時間。単位はミリ秒。

### MaxStep
レンダリングするステップ数。

### Pitch
キャリアの基音の音程。

### Ratio
キャリアの周波数を1としたときの、モジュレータとの周波数比。

### Harmonics
倍音の数。1世代あたりのElementary CAのセルの数。

### HarmoType
倍音の足し合わせ方。n番目の倍音の音量について、
- Hard: 1.0
- Soft: 0.5^n

### Smooth(msec)
ステップ間のスムーシング。値を増やすと、音の変化がより緩やかになる。

### Rule
Elementary CAのルール。

### Seed
Elementary CAの初期状態を決める乱数のシード値。

### Random
HarmoType以外の値についてランダマイズを行う。

### Render
レンダリングを行う。

### Play
レンダリングされた音を再生する。

### Save
レンダリングされた音を保存する。保存先はECAFMの実行ファイルと同じディレクトリに作られるrenderディレクトリ。
