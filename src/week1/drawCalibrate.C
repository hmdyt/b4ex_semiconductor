void drawCalibrate(){
	// init Am theoretical energy
	vector<Double_t> theore_Am_energy = {13.9, 22, 59.5};

	// init Cs theoretical enrgy
	Double_t theore_Cs_energy = 32.9;

	// get Am mean
	vector<pair<Double_t, Double_t>> fit_Am_mean = fitLowAm();

	// get Cs mean
	vector<pair<Double_t, Double_t>> fit_Cs_mean = fitLowCs();

	// init TGraphErrors
	// x = measured, y = theoretical
	TGraphErrors* g1 = new TGraphErrors();
	g1->SetTitle(";Energy [keV];ADC Value");

	// set Am points
	Double_t x, y, x_error, y_error;
	for (Int_t i = 0; i < theore_Am_energy.size(); i++){
		// prepare points
		x = theore_Am_energy[i];
		x_error = 0;
		y = fit_Am_mean[i].first;
		y_error = fit_Am_mean[i].second;
		// set point
		g1->SetPoint(i, x, y);
		g1->SetPointError(i, x_error, y_error);
	}

	// set Cs points
	// init TGraph
	TGraphErrors* g2 = new TGraphErrors();
	g2->SetPoint(4, theore_Cs_energy, fit_Cs_mean[0].first);
	g2->SetPointError(4, 0, fit_Cs_mean[0].second);

	// init canvas
	TCanvas* c1 = new TCanvas();

	// init TF1 and fit
	TF1* func = new TF1("func", "[0] * x + [1]", 0, 70);
	func->SetParameters(y/x, 0);
	g1->Fit(func, "R");

	// draw
	g1->Draw("AP");
	c1->Draw();
	g2->Draw("Psame");
}
