TH1D* standardizedByTimeAm(TString run_name = "Am_alpha_001"){
    // fetch hist
    TH1D *hist = convertWaveFormToHist(run_name, true, true);

    // calibration const
    Double_t measurement_time;
    if (run_name == "Am_alpha_001"){
        measurement_time = 3624;
    }
    else {
        measurement_time = 5763;
    }
    auto f_clb = [](Double_t a, Double_t x){
        return x / a;
    };

    // make time standardization hist
    Double_t BIN_NUM = hist->GetXaxis()->GetNbins();
    for (Int_t i= 0; i < BIN_NUM; i++){
    Double_t N_Entry = hist->GetBinContent(i);
    hist->SetBinContent(i, f_clb(measurement_time, N_Entry));
    }
    hist->GetXaxis()->SetTitle("Entries / Time");

    return hist;
}