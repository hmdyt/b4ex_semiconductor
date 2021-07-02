vector<vector<Double_t>> constructWaveFormsVector(TString file_path = "/data/hamada/semiconductor/week1/Cs_002_0.dat"){
    ifstream ifs(file_path);
    TString buffer1, buffer2, buffer_trash;
    bool is_wf_data = false;

    vector<vector<Double_t>> wfs;
    vector<Double_t> wf_tmp;
    while(ifs >> buffer1 >> buffer2){
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
    return wfs;
}