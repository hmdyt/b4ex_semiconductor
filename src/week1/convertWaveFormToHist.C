TH1D* convertWaveFormToHist(TString run_name = "Cs_002", bool use_cache = true, bool is_alpha_ray = false){
    // init const
    const TString DATA_PATH = "/data/hamada/semiconductor/week1/";

    // if the macro find a correct cache, return it
    const TString CACHE_PATH = DATA_PATH + run_name + ".root";
    if (use_cache && checkFileExistence(CACHE_PATH)){
        return (TH1D*)TFile::Open(CACHE_PATH)->Get(run_name);
    }

    // init hist
    TH1D* hist = new TH1D(
        run_name,
        run_name + ";ADC value;Event",
        1024,
        0,
        is_alpha_ray ? 100 : 2048 * 1.5
    );

    // fetch waveforms
    vector<vector<Double_t>> waveforms = combineSubRuns(run_name);

    // fill into hist
    cout << "start filling" << endl;
    for (Int_t i = 0; i < waveforms.size(); i++){
        hist->Fill(determineWaveHeight(waveforms[i], 0, 400));
        if (i % 1000 == 0 && i != 0){ cout << i << endl; }
    }

    // set range
    int max_bin_range = 1024;
    while(hist->GetBinContent(max_bin_range) == 0){ max_bin_range--; }
    hist->GetXaxis()->SetRange(0, max_bin_range);

    // save as run_name.root
    TFile* cache_file = new TFile(CACHE_PATH, "recreate");
    hist->Write();
    cache_file->Close();

    return hist;
}
