TH1D* convertWaveFormToHist(TString file_name = "Cs_002_0"){
    ifstream ifs("/data/hamada/semiconductor/week1/" + file_name + ".dat");
    TString buffer1, buffer2, buffer_trash;
    Double_t candi;
    bool is_wf_data = false;
    TH1D* hist = new TH1D(
        "hist",
        "hist;ADC value;Event",
        1024,
        0,
        4096
    );

    vector<vector<Double_t>> wfs;
    vector<Double_t> wf_tmp;
    int counter = 0;
    while(ifs >> buffer1 >> buffer2){
        counter++;
        if (buffer1 == "#Ev."){ ifs >> buffer_trash; }
        if (buffer1 == "#Write"){
            is_wf_data = false;
            wfs.push_back(wf_tmp);
            wf_tmp = {};
        }
        if (is_wf_data){
            wf_tmp.push_back((Double_t) stod((string) buffer1));
        }
        if (buffer1 == "#CH1") is_wf_data = true;
    }

    Double_t wf_max;
    for (Int_t i = 0; i < wfs.size(); i++){
        wf_max = 0;
        for (Int_t j = 0; j < wfs[i].size(); j++){
            wf_max = max(wf_max, wfs[i][j]);
        }
        hist->Fill(wf_max);
    }
    return hist;
}