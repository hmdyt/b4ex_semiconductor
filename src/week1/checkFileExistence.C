bool checkFileExistence(TString path){
    ifstream ifs(path);
    return ifs.is_open();
}