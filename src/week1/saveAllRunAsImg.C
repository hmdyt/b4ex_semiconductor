void saveAllPlaneHist(bool use_cache = false){
    vector<TString> sources = {"Am", "Cs", "Bg"};
    const TString DATA_PATH_WEEK1 = "/data/hamada/semiconductor/week1/";

    // week1
    // check existence for XX_001 to max run number of each source
    // and execute the corresponded function
    int run_num_week1;
    TString run_name;
    ostringstream run_num_week1_padded;
    for (Int_t i = 0; i < sources.size(); i++){
        run_num_week1 = 1;
        // 0 padding clear
        run_num_week1_padded.str("");
        run_num_week1_padded.clear(std::stringstream::goodbit);
        // 0 padding
        run_num_week1_padded << std::setw(3) << std::setfill('0') << run_num_week1;
        while (checkFileExistence(DATA_PATH_WEEK1 + sources[i] + "_" + (TString) run_num_week1_padded.str() + "_0.dat")){
            // set run_name
            run_name = sources[i] + "_" + (TString) run_num_week1_padded.str();
            cout << run_name << endl;
            // save
            TCanvas* c = new TCanvas();
            convertWaveFormToHist(run_name, use_cache)->Draw();
            c->SaveAs("img/week1/plane_hist/" + run_name + ".svg");
            c->SaveAs("img/week1/plane_hist/" + run_name + ".pdf");
            // increment
            run_num_week1 += 1;
            // 0 padding clear
            run_num_week1_padded.str("");
            run_num_week1_padded.clear(std::stringstream::goodbit);
            // 0 padding
            run_num_week1_padded << std::setw(3) << std::setfill('0') << run_num_week1;
        }
    }
}

void saveCalibratedHist(bool use_cache = false){
    // low gain
    vector<TString> run_names_low_gain = {"Am_007", "Cs_006"};
    for (Int_t i = 0; i < run_names_low_gain.size(); i++){
        TCanvas* c = new TCanvas();
        makeLowGainCalibratedHist(run_names_low_gain[i], use_cache)->Draw();
        c->SaveAs("img/week1/calibrated_hist_low_gain/" + run_names_low_gain[i] + ".svg");
        c->SaveAs("img/week1/calibrated_hist_low_gain/" + run_names_low_gain[i] + ".pdf");
    }

    // high gain
    vector<TString> run_names_high_gain = {"A,_009", "Cs_015"};
    for (Int_t i = 0; i < run_names_high_gain.size(); i++){
        TCanvas* c = new TCanvas();
        makeHighGainCalibratedHist(run_names_high_gain[i], use_cache)->Draw();
        c->SaveAs("img/week1/calibrated_hist_high_gain/" + run_names_high_gain[i] + ".svg");
        c->SaveAs("img/week1/calibrated_hist_high_gain/" + run_names_high_gain[i] + ".pdf");
    }
}

void saveAmAlphaHist(){
    vector<TString> run_name_Am_alpha = {"Am_alpha_001", "Am_alpha_002"};
    for (Int_t i = 0; i < run_name_Am_alpha.size(); i++){
        TString run_name = run_name_Am_alpha[i];
        TCanvas* c1 = new TCanvas();
        convertWaveFormToHist(run_name)->Draw();
        c1->SaveAs("img/week2/" + run_name + "Hist.svg");
        c1->SaveAs("img/week2/" + run_name + "Hist.pdf");
        
        TCanvas* c2 = fitAmAlpha(run_name);
        c2->Draw();
        c2->SaveAs("img/week2/fit" + run_name + "Hist.svg");
        c2->SaveAs("img/week2/fit" + run_name + "Hist.pdf");

        TCanvas* c3 = new TCanvas();
        standardizedByTimeAm(run_name)->Draw();
        c3->SaveAs("img/week2/standardizedByTime" + run_name + "Hist.svg");
        c3->SaveAs("img/week2/standardizedByTime" + run_name + "Hist.pdf");

    }
    TCanvas* c4 = overWriteHistOfAmAlpha();
    c4->Draw();
    c4->SaveAs("img/week2/overWriteHistOfAmAlpha.svg");
    c4->SaveAs("img/week2/overWriteHistOfAmAlpha.pdf");
}

void saveAllRunAsImg(bool use_cache = false){
    saveAllPlaneHist(use_cache);
    saveCalibratedHist(use_cache);
    saveAmAlphaHist();
}