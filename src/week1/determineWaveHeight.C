Double_t determineWaveHeight(
    vector<Double_t> waveform,
    Int_t sampling_rate = 1024,
    Int_t horizontal_ini = 0,
    Int_t horizontal_fin = 200
){  
    // init target tgraph
    TGraph* fit_target = new TGraph();
    for (Int_t i = 0; i < waveform.size(); i++){
        if (-100 < waveform[i] && waveform[i] < 50){
            fit_target->SetPoint(i, i, waveform[i]);
        }
    }

    // init fitting function
    TF1* pol0 = new TF1("pol0", "[0]", 0, sampling_rate);
    pol0->SetParName(0, "ground");

    // execute fitting
    fit_target->Fit(pol0, "RQ");
    Double_t ground = pol0->GetParameter(0);

    // search max height from waveform
    Double_t max_waveform = - pow(10, 10);
    for (Int_t i = (Int_t)(sampling_rate/2) * 0.95; i < (Int_t)(sampling_rate/2) * 1.05; i++){
        max_waveform = max(max_waveform, waveform[i]);
    }

    /*
    // test
    TGraph* test_show_g = new TGraph();
    for (Int_t i = 0; i < waveform.size(); i++){
        test_show_g->SetPoint(i, i, waveform[i]);
    }
    TCanvas* c = new TCanvas();
    test_show_g->Draw();
    pol0->Draw("SAME");
    c->Draw();
    */
    // return 
    delete fit_target;
    delete pol0;
    return max_waveform - ground;
}

void test_determine(){
    vector<vector<Double_t>> waveforms = constructWaveFormsVector("/data/hamada/semiconductor/week1/Am_007_0.dat");
    
    for (Int_t i = 0; i < 10; i++){
        determineWaveHeight(waveforms[i]);
    }
}