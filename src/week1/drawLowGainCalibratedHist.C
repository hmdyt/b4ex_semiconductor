void drawLowGainCalibratedHist(TString run_name = "Am_007"){
    // fetch hist
    Double_t RANGE_MIN = 0;
    Double_t RANGE_MAX = 100;
    Double_t BIN_NUM = 1024;
    TH1D* hist = new TH1D("hist", "Calibrated_Low_Gain " + run_name + " Hist", BIN_NUM, RANGE_MIN, RANGE_MAX);

    // fetch calibration constant
    pair<Double_t, Double_t> tmp_pair = drawLowGainCalibration();
    Double_t a = tmp_pair.first;
    Double_t b = tmp_pair.second;
    auto f_clb = [](Double_t a, Double_t b, Double_t x){
        return (x  - b) / a;
    };

    // get conbined waveform
    vector<vector<Double_t>> waveforms = combineSubRuns(run_name);

    // fill into hist
    cout << "start filling" << endl;
    for (Int_t i = 0; i < waveforms.size(); i++){
        hist->Fill(f_clb(
            a,
            b,
            determineWaveHeight(waveforms[i], 0, 400)
        ));
        if (i % 1000 == 0 && i != 0){ cout << i << endl; }
    }

    hist->Draw();
}