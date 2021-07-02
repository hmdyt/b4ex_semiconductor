void drawWaveForm(
    TString run_name = "Cs_002",
    Int_t i_event = 100,
    TString DATA_PATH = "/data/hamada/semiconductor/week1/"
){
    // fetch waveforms
    vector<vector<Double_t>> waveforms, waveform_tmp;
    int sub_run_num = 0;
    while(checkFileExistence(DATA_PATH + run_name + "_" +(TString)to_string(sub_run_num) + ".dat")){
        waveform_tmp = constructWaveFormsVector(DATA_PATH + run_name + "_" + (TString)to_string(sub_run_num) + ".dat");
        waveforms.insert(waveforms.end(), waveform_tmp.begin(), waveform_tmp.end());
        sub_run_num++;
    }

    TGraph* g = new TGraph();
    g->SetMarkerSize(8);
    for (Int_t i = 0; i < 1024; i++){
        g->SetPoint(i, i, waveforms[i_event][i]);
    }

    TCanvas* c = new TCanvas();
    g->Draw();
    c->Draw();
}


void drawManyWaveForms(
    TString run_name = "Cs_002",
    Int_t i_event_ini = 0,
    Int_t i_event_fin = 10,
    TString DATA_PATH = "/data/hamada/semiconductor/week1/"
){
    for (Int_t i = i_event_ini; i <i_event_fin - i_event_ini ; i++){
        drawWaveForm(run_name, i);
    }
}