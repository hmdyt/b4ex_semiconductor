vector<pair<Double_t, Double_t>> fitHighAm(){
    // const
    const Double_t FIT_RANGE_MIN = 700;
    const Double_t FIT_RANGE_MAX = 1550;

    // fetch hist
    TH1D* hist = convertWaveFormToHist("Am_009");

    // init fit function
    TF1* func = new TF1("func", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", FIT_RANGE_MIN, FIT_RANGE_MAX);
    for (Int_t i = 0; i < 4; i++){
        func->SetParName(3*i + 0, TString::Itoa(i, 10) + "th Const");
        func->SetParName(3*i + 1, TString::Itoa(i, 10) + "th Mean");
        func->SetParName(3*i + 2, TString::Itoa(i, 10) + "th Sigma");
    }

    // init initial parameters
    // Const Mean Sigma
    vector<Double_t> initial_parameters = {
        180, 752 , 100,
        500, 953 , 100,
        300, 1144, 100,
        100, 1427, 100
    };
    for (Int_t i = 0; i < initial_parameters.size(); i++){
        func->SetParameter(i, initial_parameters[i]);
    }

    // limit parameter range
    /*
    func->SetParLimits(0 , 0   , 1000); // const
    func->SetParLimits(1 , 0   , 1000); // mean
    func->SetParLimits(2 , 0   , 100 ); // sigma
    func->SetParLimits(3 , 0   , 1000); // const
    func->SetParLimits(4 , 900 , 1200); // mean
    func->SetParLimits(5 , 0   , 100 ); // sigma
    func->SetParLimits(6 , 0   , 1000); // const
    func->SetParLimits(7 , 1100, 1300); // mean
    func->SetParLimits(8 , 0   , 100 ); // sigma
    func->SetParLimits(9 , 0   , 1000); // const
    func->SetParLimits(10, 1400, 1600); // mean
    func->SetParLimits(11, 0   , 100 ); // sigma
    */
    func->SetParLimits(1 , 600 , 900 ); // mean
    func->SetParLimits(4 , 800 , 1000); // mean
    func->SetParLimits(7 , 1000, 1300); // mean
    func->SetParLimits(10, 1300, 1600); // mean

    // execute fitting without drawing and outputting paras
    hist->Fit(func, "RQ0");

    // init each gaus
    // fit
    TF1* func0 = new TF1("func_0", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);
    TF1* func1 = new TF1("func_1", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);
    TF1* func2 = new TF1("func_2", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);
    TF1* func3 = new TF1("func_3", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);

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

    // save as img
    TCanvas* c = new TCanvas();
    hist->Draw();
    func->Draw("SAME");
    func0->Draw("SAME");
    func1->Draw("SAME");
    func2->Draw("SAME");
    func3->Draw("SAME");
    saveAsFitParameters(c, "img/week1/high_gain_clb/Am_009");

    // cout 
    coutTF1(func);

    // return 
    // res = {{mean, mean_error}, {mean, mean_error}, ...}
    vector<pair<Double_t, Double_t>> res;
    for (Int_t i = 0; i < 4; i++){
        res.push_back(
            make_pair(
                func->GetParameter(3*i + 1),
                func->GetParError(3*i + 1)
            )
        );
    }
    return res;
}