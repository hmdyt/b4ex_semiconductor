# src/week1
1週目(2021/07/03~)の解析プログラム
```jsseq
saveAllRunAsImg->convertWaveFormToHist: call many times
convertWaveFormToHist->checkFileExistence: call many times
convertWaveFormToHist->constructWaveFormsVector: call a few times
convertWaveFormToHist->determineWaveHeight: call many times
```

# description
## [checkFileExistence](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/checkFileExistence.C)  
```cpp
bool checkFileExistence(TString path)
```
任意のファイルが存在するかどうかを調べる関数。
- pathに指定したファイルが存在すると, trueを返す
- 存在しないとfalseを返す

## [constructWaveFormsVector](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/constructWaveFormsVector.C)   
```cpp
vector<vector<Double_t>> constructWaveFormsVector(TString file_path)
```
波形データの入った測定ファイルを読み出して二次元vectorに格納する関数。
- file_pathにdatファイルを指定する。
- datファイル内のCH1から波形データ(waveform)を取り出し, イベントごとに1次元vectorへ格納する。
- 指定したファイル内全てのイベントを結合することで二次元vectorになる。
- すなわち, 返り値は以下のようになっている。
    ```cpp
    {
        {a0, b0, c0, d0, ....}, \\ a waveform
        {a1, b1, c1, d1, ....},
        {a2, b2, c2, d2, ....},
        .
        .
        .
    }
    ```

## [determineWaveHeight](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/determineWaveHeight.C)  
```cpp
Double_t determineWaveHeight(
    vector<Double_t> waveform,
    Int_t horizontal_ini,
    Int_t horizontal_fin
)
```
零点を0次関数fitによって決定し, これを用いて波形データの波高を決定する関数。
- waveformに, あるイベントの波形データを指定する。  
- horizontal_ini, finは波形データの0点 (ground)を決定するためのfitの範囲。
- 返り値はfitによって補正された波形データの波高。

## [convertWaveFormToHist](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/convertWaveFormToHist.C)  
```cpp
TH1D* convertWaveFormToHist(TString run_name)
```
あるrunのデータを全て結合したヒストグラムを作る関数。
- run_nameはrun名を指定 (例えば, Cs_002_1ではなくCs_002のように)
- Cs_002_0, Cs_002_1, Cs_002_2のように同じrunでもいくつかのファイルが生成されている場合がある。これを自動で検知し, 結合してヒストグラムにするように処理を書いた。

## [drawWaveForm](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/drawWaveForm.C)  
```cpp
void drawWaveForm(
    TString run_name,
    Int_t   i_event,
    TString DATA_PATH
)
```
あるrunでのあるイベントの波形データをTgraphにdrawする関数
- 本筋には関係のない関数 (voidやし)
- 確認用
- スライドに使うかも

## [saveAllRunAsImg](https://github.com/hmdyt/b4ex_semiconductor/blob/main/src/week1/saveAllRunAsImg.C)  
```cpp
void saveAllRunAsImg()
```
本筋に関係のある全てのヒストグラム, グラフをpdf, svgで保存する関数(にする予定)。
- 解析が進むたびに追記していく
- checkFileExistenceを使っているので測定データの追加へ柔軟に対応できるようになっている
- クソコード