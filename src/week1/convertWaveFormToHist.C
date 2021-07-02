TH1D* convertWaveFormToHist(TString run_name = "Cs_002"){
    // init const
    const TString DATA_PATH = "/data/hamada/semiconductor/week1/";

    // init hist
    TH1D* hist = new TH1D(
        run_name,
        run_name + ";ADC value;Event",
        1024,
        0,
        2048 * 1.5
    );

    // fetch waveforms
    vector<vector<Double_t>> waveforms, waveform_tmp;
    int sub_run_num = 0;
    while(checkFileExistence(DATA_PATH + run_name + "_" +(TString)to_string(sub_run_num) + ".dat")){
        cout << "start reading waveforms (sub run" + (TString) to_string(sub_run_num) + ")" << endl;
        waveform_tmp = constructWaveFormsVector(DATA_PATH + run_name + "_" + (TString)to_string(sub_run_num) + ".dat");
        waveforms.insert(waveforms.end(), waveform_tmp.begin(), waveform_tmp.end());
        sub_run_num++;
    }


    // fill into hist
    cout << "start filling" << endl;
    Double_t wf_max;
    for (Int_t i = 0; i < waveforms.size(); i++){
        hist->Fill(determineWaveHeight(waveforms[i], 0, 400));
        if (i % 1000 == 0 && i != 0){ cout << i << endl; }
    }
    return hist;
}