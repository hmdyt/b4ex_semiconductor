Double_t determineWaveHeight(
    vector<Double_t> waveform,
    Int_t horizontal_ini = 0,
    Int_t horizontal_fin = 200
){  
    // init target tgraph
    TGraph* fit_target = new TGraph();
    for (Int_t i = horizontal_ini; i < horizontal_fin - horizontal_ini; i++){
        fit_target->SetPoint(i, i, waveform[i]);
    }

    // init fitting function
    TF1* pol0 = new TF1("pol0", "[0]", horizontal_ini, horizontal_fin);
    pol0->SetParName(0, "ground");

    // execute fitting
    fit_target->Fit(pol0, "RQ");
    Double_t ground = pol0->GetParameter(0);

    // search max height from waveform
    Double_t max_waveform = - pow(10, 10);
    for (Int_t i = 0; i < waveform.size(); i++){
        max_waveform = max(max_waveform, waveform[i]);
    }

    // return 
    return max_waveform - ground;
}