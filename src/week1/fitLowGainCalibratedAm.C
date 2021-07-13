void fitLowGainCalibratedAm(){
    // fetch hist
    TFile* file = new TFile("/data/hamada/semiconductor/week1/Am_007_calibrated.root");
    TH1D* hist = (TH1D*)file->Get("Am_007_calibrated");
    hist->GetXaxis()->SetRangeUser(0, 35);

    // init TF1
    TF1* f = new TF1("f", "gaus(0)+gaus(3)+gaus(6)", 15, 28);
    f->SetParNames(
        "1st Const", "1st Mean", "1st Sigma",
        "2nd Const", "2nd Mean", "2nd Sigma",
        "3rd Const", "3rd Mean", "3rd Sigma"
    );
    f->SetParameters(
        120, 17.6, 5,
        60, 18, 10,
        20, 26.3, 5
    );

    // fit
    hist->Fit(f, "RQ0");

    // init each gaussian
    TF1* f1 = new TF1("f1", "gaus", 0, 30);
    TF1* f2 = new TF1("f2", "gaus", 0, 30);
    TF1* f3 = new TF1("f3", "gaus", 0, 30);

    f1->SetParameters(
        f->GetParameter(0),
        f->GetParameter(1),
        f->GetParameter(2)
    );
    f2->SetParameters(
        f->GetParameter(3),
        f->GetParameter(4),
        f->GetParameter(5)
    );
    f3->SetParameters(
        f->GetParameter(6),
        f->GetParameter(7),
        f->GetParameter(8)
    );

    // draw
    f->SetLineColor(4);
    TCanvas* c = new TCanvas();
    hist->Draw();
    f->Draw("SAME");
    f1->Draw("SAME");
    f2->Draw("SAME");
    f3->Draw("SAME");
    saveAsFitParameters(c, "img/week1/calibrated_hist_low_gain/Am_007_calibrated_fit_gaus");
}