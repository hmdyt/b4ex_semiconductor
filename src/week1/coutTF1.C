void coutTF1(TF1* f){
    Double_t NDF = f->GetNDF();
    Double_t Chi2 = f->GetChisquare();
    Int_t par_num = f->GetNpar();

    const Double_t* parameters = f->GetParameters();
    const Double_t* par_errors = f->GetParErrors();

    cout << "================" << endl;
    for (Int_t i = 0; i < par_num; i++){
        cout << f->GetParName(i) << ": " << parameters[i] << " +/- " << par_errors[i] << endl;
    }
    cout << "Chi2 / NDF = " << Chi2 << " / " << NDF << endl;
    cout << "================" << endl;

}