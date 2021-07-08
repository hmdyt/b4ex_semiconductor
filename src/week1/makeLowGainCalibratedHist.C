TH1D* makeLowGainCalibratedHist(TString run_name = "Am_007", bool use_cache = true){
    // init hist
    Double_t RANGE_MIN = 0;
    Double_t RANGE_MAX = 100;
    Double_t BIN_NUM = 1024;
    TH1D* hist = new TH1D(run_name + "_calibrated", run_name + "_calibrated;Energy [keV];Event", BIN_NUM, RANGE_MIN, RANGE_MAX);

    // if the macro find a correct cache, return it
    const TString CACHE_PATH = "/data/hamada/semiconductor/week1/" + run_name + "_calibrated.root";
    if (use_cache && checkFileExistence(CACHE_PATH)){
        return (TH1D*)TFile::Open(CACHE_PATH)->Get(run_name + "_calibrated");
    }

    // fetch calibration constant
    pair<Double_t, Double_t> tmp_pair = drawLowGainCalibration();
    Double_t a = tmp_pair.first;
    Double_t b = tmp_pair.second;
    auto f_clb = [](Double_t a, Double_t b, Double_t x){
        return (x - b) / a;
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

    // save as run_name.root
    TFile* cache_file = new TFile(CACHE_PATH, "recreate");
    hist->Write();
    cache_file->Close();

    return hist;
}