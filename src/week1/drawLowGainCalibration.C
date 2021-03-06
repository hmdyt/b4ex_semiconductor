pair<Double_t, Double_t> drawLowGainCalibration(bool is_show_origin = false){
	// init Am theoretical energy
	vector<Double_t> theore_Am_energy = {17.4, 20.9, 26.3, 59.5};

	// init Cs theoretical enrgy
	Double_t theore_Cs_energy = 32.9;

	// get Am mean
	vector<pair<Double_t, Double_t>> fit_Am_mean = fitLowAm();

	// get Cs mean
	vector<pair<Double_t, Double_t>> fit_Cs_mean = fitLowCs();

	// construct graph title (temporary)
	TString title = Form(
		"%.1f, %.1f, %.1f",
		theore_Am_energy[0],
		theore_Am_energy[1],
		theore_Am_energy[2]
	);

	// init TGraphErrors
	// x = measured, y = theoretical
	TGraphErrors* g1 = new TGraphErrors();
	g1->SetTitle(title + ";Energy [keV];ADC Value");
	g1->SetMarkerStyle(8);
	g1->SetMarkerSize(1);

	// init TH2D for axis
	TH2D* axis = new TH2D("axis", title + ";Energy [keV]; ADC Value", 0, 0, 70, 0, 0, 2000);
	axis->SetStats(0);

	// set Am points
	for (Int_t i = 0; i < theore_Am_energy.size(); i++){
		g1->SetPoint(i, theore_Am_energy[i], fit_Am_mean[i].first);
		g1->SetPointError(i, 0, fit_Am_mean[i].second);
	}

	// set Cs points
	g1->SetPoint(4, theore_Cs_energy, fit_Cs_mean[0].first);
	g1->SetPointError(4, 0, fit_Cs_mean[0].second);

	// init canvas
	TCanvas* c1 = new TCanvas();

	// init TF1 and fit
	TF1* func = new TF1("func", "[0] * x + [1]", 0, 70);
	func->SetParameters(fit_Am_mean[0].first/theore_Am_energy[0], 0);
	g1->Fit(func, "RQ0");

	// draw
	if (is_show_origin){
		axis->Draw("AXIS");
		g1->Draw("P SAME");
	} else {
		g1->Draw("AP");
	}
	func->Draw("SAME");
	c1->Draw();
	c1->SaveAs("img/week1/low_gain_clb/final.svg");
	c1->SaveAs("img/week1/low_gain_clb/final.pdf");

	// cout
	coutTF1(func);

	// return
	// y = ax + b
	Double_t a = func->GetParameter(0);
	Double_t b = func->GetParameter(1);
	return make_pair(a, b);
}
