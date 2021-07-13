void saveAsFitParameters(TCanvas* c, TString save_file_path){
    gStyle->SetOptFit(0000);
    c->SaveAs(save_file_path + ".svg");
    c->SaveAs(save_file_path + ".pdf");
    gStyle->SetOptFit(1111);
    c->SaveAs(save_file_path + "_withpara.svg");
    c->SaveAs(save_file_path + "_withpara.pdf");
    gStyle->SetOptFit(0000);
}