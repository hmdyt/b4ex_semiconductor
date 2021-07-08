vector<pair<Double_t, Double_t>> fitLowAm(){
	// get hist
	TH1D *hist = convertWaveFormToHist("Am_007");

	// init fitting parameters
	const Double_t FIT_RANGE_MIN_1 = 300;
	const Double_t FIT_RANGE_MAX_1 = 700;
	const Double_t FIT_RANGE_MIN_2 = 1300;
	const Double_t FIT_RANGE_MAX_2 = 1500;

	// init TF1
	TF1 *func1 = new TF1("func1", "gaus(0) + gaus(3)", FIT_RANGE_MIN_1, FIT_RANGE_MAX_1);
	TF1 *func2 = new TF1("func2", "gaus(0)", FIT_RANGE_MIN_2, FIT_RANGE_MAX_2);

	// set paranames
	func1->SetParName(0, "Const1");
	func1->SetParName(1, "Mean1");
	func1->SetParName(2, "Sigma1");
	func1->SetParName(3, "Const2");
	func1->SetParName(4, "Mean2");
	func1->SetParName(5, "Sigma2");
	func2->SetParName(0, "Const");
	func2->SetParName(1, "Mean");
	func2->SetParName(2, "Sigma");
	
	// set parameters
	func1->SetParameter(0, 120);
	func1->SetParameter(1, 450);
	func1->SetParameter(2, 50);
	func1->SetParameter(3, 50);
	func1->SetParameter(4, 600);
	func1->SetParameter(5, 20);
	func2->SetParameter(0, 100);
	func2->SetParameter(1, 1400);
	func2->SetParameter(2, 50);

	// execute fitting
	hist->Fit(func1, "RQ0");
	hist->Fit(func2, "+RQ0");

	// save as img
    TCanvas* c = new TCanvas();
    hist->Draw();
    func1->Draw("SAME");
	func2->Draw("SAME");
    c->SaveAs("img/week1/low_gain_clb/Am_007.svg");
    c->SaveAs("img/week1/low_gain_clb/Am_007.pdf");

	// return fit parameter
	vector<pair<Double_t, Double_t>> res;
	for (Int_t i = 0; i < 3; i++){
		if(i < 2){
			res.push_back(make_pair(
				func1->GetParameter(3 * i + 1),
				func1->GetParError(3 * + 1)
				));
		}
		else{
			res.push_back(make_pair(
				func2->GetParameter(1),
				func2->GetParError(1)
				));
		}
	};
	return res;
}
