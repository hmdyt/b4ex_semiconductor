TCanvas* overWriteHistOfAmAlpha(){
    // fetch hist
    TH1D *hist1 = standardizedByTimeAm("Am_alpha_001");
    TH1D *hist2 = standardizedByTimeAm("Am_alpha_002");

    // TLegend
    TString Hist1_Title = hist1->GetTitle();
    TString Hist2_Title = hist2->GetTitle();
    TLegend *legend = new TLegend(0.68, 0.84, 0.99, 0.93);
    legend->AddEntry(hist1, Hist1_Title, "pl");
    legend->AddEntry(hist2, Hist2_Title, "pl");

    // set Title & set Line color
    hist1->SetTitle("Am_alpha; ADC Value; Entries / Time");
    hist1->SetLineColor(4);
    hist1->SetStats(0);

    // set fitting range
    Double_t FIT_RANGE_MIN_1 = 16;
    Double_t FIT_RANGE_MAX_1 = 26;
    Double_t FIT_RANGE_MIN_2 = 18;
    Double_t FIT_RANGE_MAX_2 = 22;

    // init TF1
    TF1 *func1 = new TF1("func", "gaus", FIT_RANGE_MIN_1, FIT_RANGE_MAX_1);
    TF1 *func2 = new TF1("func", "gaus", FIT_RANGE_MIN_2, FIT_RANGE_MAX_2);

    // set parameters
    func1->SetParameters(0.005, 20, 2);
    func2->SetParameters(0.025, 20, 4);

    // fit
    hist1->Fit(func1, "RQ0");
    hist2->Fit(func2, "RQ0");

    // draw
    TCanvas* c1 = new TCanvas();
    hist1->Draw();
    hist2->Draw("SAME");
    func1->Draw("SAME");
    func2->Draw("SAME");
    legend->Draw("SAME");

    return c1;
}