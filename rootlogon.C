void loadMacro(const TString macro_name){
    // load
    const int ret = gROOT->LoadMacro(macro_name);

    if (ret == 0){
        // load success
        cout << "loaded " + macro_name << endl;
    } else {
        //load failed
        cout << "faild " + macro_name << endl;
        exit(1);
    }
}

void rootlogon(){
    // message
    cout << "executed rootlogon" << endl;

    // week1
    loadMacro("src/week1/checkFileExistence.C");
    loadMacro("src/week1/constructWaveFormsVector.C");
    loadMacro("src/week1/determineWaveHeight.C");
    loadMacro("src/week1/convertWaveFormToHist.C");
    loadMacro("src/week1/saveAllRunAsImg.C");
    loadMacro("src/week1/fitLowAm.C");
    loadMacro("src/week1/fitLowCs.C");
    loadMacro("src/week1/drawLowGainCalibration.C");
}
