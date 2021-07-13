void fitHighGainCalibratedAm(){
    TFile* file = new TFile("/data/hamada/semiconductor/week1/Am_009_calibrated.root");
    TH1D* hist = (TH1D*)file->Get("Am_009_calibrated");
    hist->GetXaxis()->SetRangeUser(0, 35);

    // init TF1
    Double_t FIT_MIN = 12;
    Double_t FIT_MAX = 30;
    TF1* func = new TF1("func", "gaus(0) + gaus(3) + gaus(6) + gaus(9)", FIT_MIN, FIT_MAX);

    // set parameters
    vector<Double_t> init_parameters = {
        180, 13.9, 2,
        500, 17.6, 2,
        300, 21.1, 2,
        100, 26.3, 2
    };
    for (Int_t i = 0; i < 4; i++){
        func->SetParName(3 * i + 0, TString::Itoa(i, 10) + " Const");
        func->SetParName(3 * i + 1, TString::Itoa(i, 10) + " Mean");
        func->SetParName(3 * i + 2, TString::Itoa(i, 10) + " Sigma");
    }

    for (Int_t i = 0; i < 4; i++){
        func->SetParameter(3 * i + 0, init_parameters[3 * i + 0]);
        func->SetParameter(3 * i + 1, init_parameters[3 * i + 1]);
        func->SetParameter(3 * i + 2, init_parameters[3 * i + 2]);
    }
    // fit
    hist->Fit(func, "RQ0");

    // fit
    TF1* func0 = new TF1("func_0", "gaus", 12, 30);
    TF1* func1 = new TF1("func_1", "gaus", 12, 30);
    TF1* func2 = new TF1("func_2", "gaus", 12, 30);
    TF1* func3 = new TF1("func_3", "gaus", 12, 30);

    // set parameters
    func0->SetParameters(
        func->GetParameter(0),
        func->GetParameter(1),
        func->GetParameter(2)
    );
    func1->SetParameters(
        func->GetParameter(3),
        func->GetParameter(4),
        func->GetParameter(5)
    );
    func2->SetParameters(
        func->GetParameter(6),
        func->GetParameter(7),
        func->GetParameter(8)
    );
    func3->SetParameters(
        func->GetParameter(9),
        func->GetParameter(10),
        func->GetParameter(11)
    );

    //draw
    TCanvas* c = new TCanvas();
    func->SetLineColor(4);
    hist->Draw();
    func->Draw("SAME");
    func0->Draw("SAME");
    func1->Draw("SAME");
    func2->Draw("SAME");
    func3->Draw("SAME");

    c->SaveAs("img/week1/calibrated_hist_high_gain/Am_009_calibrated_fit_gaus.svg");
    c->SaveAs("img/week1/calibrated_hist_high_gain/Am_009_calibrated_fit_gaus.pdf");
}