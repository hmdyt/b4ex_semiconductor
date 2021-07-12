pair<Double_t, Double_t> drawHighGainCalibration(bool is_show_origin = true){
    // init Am, Cs theoretical energy
    vector<Double_t> theore_Am_energy = {18, 26};
    vector<Double_t> theore_Cs_energy = {32.9};
    vector<Double_t> theore_energy;
    theore_energy.insert(theore_energy.end(), theore_Am_energy.begin(), theore_Am_energy.end());
    theore_energy.insert(theore_energy.end(), theore_Cs_energy.begin(), theore_Cs_energy.end());

    // fetch Am, Cs mean
    vector<pair<Double_t, Double_t>> fit_Am_mean = fitHighAm();
    vector<pair<Double_t, Double_t>> fit_Cs_mean = fitHighCs();
    vector<pair<Double_t, Double_t>> fit_mean;
    fit_mean.insert(fit_mean.end(), fit_Am_mean.begin(), fit_Am_mean.end());
    fit_mean.insert(fit_mean.end(), fit_Cs_mean.begin(), fit_Cs_mean.end());

    // init TGraphErrors
	// x = measured, y = theoretical
	TGraphErrors* g = new TGraphErrors();
	g->SetTitle("High gain calibration;Energy [keV];ADC Value");

    // init TH2D for axis
	TH2D* axis = new TH2D("axis", "High gain calibration;Energy [keV];ADC Value", 0, 0, 70, 0, 0, 2000);
	axis->SetStats(0);


    // set Am/Cs points
    Double_t x, y, x_error, y_error;
    Int_t n_now_points;
    for (Int_t i = 0; i < theore_energy.size(); i++){
        x       = theore_energy[i];
        x_error = 0;
        y       = fit_mean[i].first;
        y_error = fit_mean[i].second;
        g->SetPoint(i, x, y);
        g->SetPointError(i, x_error, y_error);
    }

    // init canvas
    TCanvas* c = new TCanvas();

    // init fitting function
    TF1* func = new TF1("func", "[0] * x + [1]", 0, 70);
    func->SetParameters(y/x, 0);

    // execute fitting
	g->Fit(func, "R");

    // draw
    if (is_show_origin){
		axis->Draw("AXIS");
		g->Draw("P SAME");
	} else {
		g->Draw("AP");
	}
    g->SetMarkerStyle(22);
    c->Draw();
	c->SaveAs("img/week1/high_gain_clb/final.svg");
	c->SaveAs("img/week1/high_gain_clb/final.pdf");

    // return
	// y = ax + b
	Double_t a = func->GetParameter(0);
	Double_t b = func->GetParameter(1);
	return make_pair(a, b);
}