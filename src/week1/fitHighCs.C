vector<pair<Double_t, Double_t>> fitHighCs(){
    // const
    const Double_t FIT_RANGE_MIN = 1600;
    const Double_t FIT_RANGE_MAX = 1950;

    // fetch hist
    TH1D* hist = convertWaveFormToHist("Cs_015");

    // init fit function
    TF1* func = new TF1("func", "gaus", FIT_RANGE_MIN, FIT_RANGE_MAX);
    func->SetParName(0, "Const");
    func->SetParName(1, "Mean");
    func->SetParName(2, "Sigma");

    // init initial parameters
    // Const Mean Sigma
    func->SetParameters(100, 1800, 300);

    // execute fitting
    hist->Fit(func, "R");

    // return
    // res = {{mean, mean_error}, {mean, mean_error}, ...}
    vector<pair<Double_t, Double_t>> res;
    res.push_back(
        make_pair(
            func->GetParameter(1),
            func->GetParError(1)
        )
    );
    return res;
}