vector<pair<Double_t, Double_t>> fitHighAm(){
    // const
    const Double_t FIT_RANGE_MIN = 900;
    const Double_t FIT_RANGE_MAX = 1800;

    // fetch hist
    TH1D* hist = convertWaveFormToHist("Am_009");

    // init fit function
    TF1* func = new TF1("func", "gaus(0)+gaus(3)+gaus(6)", FIT_RANGE_MIN, FIT_RANGE_MAX);
    for (Int_t i = 0; i < 3; i++){
        func->SetParName(3*i + 0, TString::Itoa(i, 10) + "th Const");
        func->SetParName(3*i + 1, TString::Itoa(i, 10) + "th Mean");
        func->SetParName(3*i + 2, TString::Itoa(i, 10) + "th Sigma");
    }

    // init initial parameters
    // Const Mean Sigma
    func->SetParameters(
        500, 1000, 100,
        400, 1300, 100,
        100, 1500, 100
    );

    // limit parameter range
    func->SetParLimits(0, 0   , 600 );
    func->SetParLimits(1, 900 , 1200);
    func->SetParLimits(2, 0   , 600 );
    func->SetParLimits(3, 0   , 600 );
    func->SetParLimits(4, 1100, 1300);
    func->SetParLimits(5, 0   , 600 );
    func->SetParLimits(6, 0   , 600 );
    func->SetParLimits(7, 1400, 1600);
    func->SetParLimits(8, 0   , 600 );

    // execute fitting without drawing and outputting paras
    hist->Fit(func, "RQ0");

    // save as img
    TCanvas* c = new TCanvas();
    hist->Draw();
    func->Draw("SAME");
    c->SaveAs("img/week1/high_gain_clb/Am_009.svg");
    c->SaveAs("img/week1/high_gain_clb/Am_009.pdf");

    // return 
    // res = {{mean, mean_error}, {mean, mean_error}, ...}
    vector<pair<Double_t, Double_t>> res;
    res.push_back(
        make_pair(
            func->GetParameter(1),
            func->GetParError(1)
        )
    );
    res.push_back(
        make_pair(
            func->GetParameter(7),
            func->GetParError(7)
        )
    );
    return res;
}