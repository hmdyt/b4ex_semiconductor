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
    loadMacro("src/week1/combineSubRuns.C");
    loadMacro("src/week1/convertWaveFormToHist.C");
    loadMacro("src/week1/drawWaveForm.C");
    loadMacro("src/week1/fitLowAm.C");
    loadMacro("src/week1/fitLowCs.C");
    loadMacro("src/week1/fitHighAm.C");
    loadMacro("src/week1/fitHighCs.C");
    loadMacro("src/week1/drawLowGainCalibration.C");
    loadMacro("src/week1/drawHighGainCalibration.C");
    loadMacro("src/week1/fitAmAlpha.C");
    loadMacro("src/week1/makeLowGainCalibratedHist.C");
    loadMacro("src/week1/makeHighGainCalibratedHist.C");
    loadMacro("src/week1/standardizedByTimeAm.C");
    loadMacro("src/week1/overWriteHistOfAmAlpha.C");
    loadMacro("src/week1/saveAllRunAsImg.C");
}
