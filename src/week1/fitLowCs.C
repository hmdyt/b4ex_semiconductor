vector<pair<Double_t, Double_t>> fitLowCs(){
	// get hist
	TH1D* hist = convertWaveFormToHist("Cs_006");

	// init fitting parameters
	const Double_t FIT_RANGE_MIN = 700;
	const Double_t FIT_RANGE_MAX = 800;

	// init TF1
	TF1* func = new TF1("func", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);

	// set paranames
	func->SetParName(0, "Const");
	func->SetParName(1, "Mean");
	func->SetParName(2, "Sigma");

	// set parameters
	func->SetParameter(0, 100);
	func->SetParameter(1, 750);
	func->SetParameter(2, 20);

	// execute fitting
	hist->Fit(func, "RQ0");

	// save as img
    TCanvas* c = new TCanvas();
    hist->Draw();
    func->Draw("SAME");
    c->SaveAs("img/week1/low_gain_clb/Cs_006.svg");
    c->SaveAs("img/week1/low_gain_clb/Cs_006.pdf");

	// return
	Double_t mean = func->GetParameter(1);
	Double_t mean_error = func->GetParError(1);
	vector<pair<Double_t, Double_t>> res;
	res.push_back(make_pair(mean, mean_error));

	return res;

}
