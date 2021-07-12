TCanvas* fitAmAlpha(TString run_name = "Am_alpha_001"){
    //fetch hist
    TH1D *hist = convertWaveFormToHist(run_name);
    // init const
    const Double_t FIT_RANGE_MIN = 14;
    const Double_t FIT_RANGE_MAX = 26;

    // init fit
    TF1 *func = new TF1("func", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);

    // set parname
    func->SetParName(0, "Const");
    func->SetParName(1, "Mean");
    func->SetParName(2, "Sigma");

    // set parameter
    func->SetParameter(0, 90);
    func->SetParameter(1, 20);
    func->SetParameter(2, 5);

    // draw
    auto c1 = new TCanvas();
    hist->Fit(func, "RQ0");
    hist->Draw();
    func->Draw("SAME");

    // get fit parameters
    Double_t Mean = func->GetParameter(1);
    Double_t Mean_Error = func->GetParError(1);
    cout << "Mean " << Mean << "\n" << "Mean_Error" << Mean_Error << endl;

    hist->SetStats(1);
    gStyle->SetOptFit(10100);

    return c1;
}