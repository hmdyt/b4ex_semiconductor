vector<vector<Double_t>> combineSubRuns(TString run_name = "Cs_002", const TString DATA_PATH = "/data/hamada/semiconductor/week1/"){

    // fetch waveforms
    vector<vector<Double_t>> waveforms, waveform_tmp;
    int sub_run_num = 0;
    while(checkFileExistence(DATA_PATH + run_name + "_" +(TString)to_string(sub_run_num) + ".dat")){
        cout << "start reading waveforms (sub run" + (TString) to_string(sub_run_num) + ")" << endl;
        waveform_tmp = constructWaveFormsVector(DATA_PATH + run_name + "_" + (TString)to_string(sub_run_num) + ".dat");
        waveforms.insert(waveforms.end(), waveform_tmp.begin(), waveform_tmp.end());
        sub_run_num++;
    }
    return waveforms;
}