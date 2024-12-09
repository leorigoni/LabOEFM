#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

//struct
struct misura{
    double mis=0.0;
    double err=0.0;
    int ord_m=0;
    int ord_e=0;
    int new_o=0;
    int prec=0;
    bool cw=0;
};

//Preliminary
void instructions(){
    cout << endl;
    cout << "Il seguente programma è utile per creare in maniera semplice e veloce tabelle in LaTeX," << endl;
    cout << "a partire da un singolo file contenete le misure e fornendo le diverse variabili richieste in seguito." << endl;
    cout << endl;
    cout << "N.B." << endl;
    cout << "-si precisa che il file di input delle misure deve essere strutturato come nel seguente esempio:" << endl;
    cout << endl;
    cout << "5.825e+03 3.545e+00 2.500e-04 2.000e-05 3.079e+08 2.464e+07" << endl;
    cout << "5.825e+03 3.545e+00 2.600e-04 2.000e-05 2.961e+08 2.278e+07" << endl;
    cout << "5.265e+03 3.545e+00 2.800e-04 2.000e-05 2.485e+08 1.775e+07" << endl;
    cout << "5.228e+03 3.545e+00 2.800e-04 2.000e-05 2.468e+08 1.763e+07" << endl;
    cout << endl;
    cout << "con alternate le colonne di misure-errore e le virgole trasformate tutte in punti." << endl;
    cout << endl;
}
string inputname(){
    string inname;
    cout << endl;
    cout << "Com'è stato chiamato il file contenente le misure ?" << endl;
    cin >> inname;
    cout << endl;
    inname=inname+".txt";
    return inname;
}
vector<vector<misura>> read(string inname){
    ifstream input(inname, ios::in);
    if(!input.is_open()){
        cout << "Errore: Impossibile aprire il file." << endl;
        return {};
    }
    vector<vector<misura>> m;
    string line;
    vector<vector<double>> misure, errori;
    while(getline(input, line)){
        istringstream iss(line);
        double mis, err;
        vector<double> tmp_mis, tmp_err;
        while(iss>>mis>>err){
            tmp_mis.push_back(mis);
            tmp_err.push_back(err);
        }
        if(!tmp_mis.empty()){
            misure.push_back(tmp_mis);
            errori.push_back(tmp_err);
        }
    }
    int n_colonne=misure[0].size();
    m.resize(n_colonne);
    for(int j=0; j<n_colonne; ++j){
        for(int i=0; i<misure.size(); ++i){
            m[j].push_back({misure[i][j], errori[i][j]});
        }
    }
    input.close();
    return m;
}
vector<string> measuresname(vector<vector<misura>> &m){
    vector<string> v;
    cout << "Inserire i nomi delle colonne della tabella, in LaTeX:" << endl;
    cout << "(ricordarsi di usare '~' per gli spazi)" << endl;
    for(int i=0; i<m.size(); i++){
        string tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    cout << endl;
    return v;
}
void neworder(vector<vector<misura>> &m){
    cout << "Inserire l'ordine di grandezza desiderato per ciascuna colonna, (es. 6):" << endl;
    for(int i=0; i<m.size(); i++){
        int tmp;
        cin >> tmp;
        for(auto &misura:m[i]){
            misura.new_o=tmp;
        }
    }
    cout << endl;
}
void setprec(vector<vector<misura>> &m){
    cout << "Inserire il numero di cifre significative dopo la virgola desiderate, (es. 3):" << endl;
    for(int i=0; i<m.size(); i++){
        int tmp;
        cin >> tmp;
        for(auto &misura:m[i]){
            misura.prec=tmp;
        }
    }
    cout << endl;
}
void correctwrong(vector<vector<misura>>& m){
    cout << "Inserire l'ordine delle righe con misure errate, (es. 4):" << endl;
    cout << "(scrivere 'fine' per terminare, 'no' se non sono presenti misure errate)" << endl;
    while(true){
        string tmps;
        cin >> tmps;
        if(tmps=="fine"){
            break;
        }else if(tmps=="no"){
            break;
        }else{
            try{
                int tmp=stoi(tmps);
                if(tmp<1 || tmp>m[0].size()){
                    cout << "Errore: Riga fuori dall'intervallo valido!" << endl;
                }else{
                    int i=tmp-1;
                    for(auto &col:m){
                        col[i].cw = true;
                    }
                }
            }catch(const invalid_argument&){ 
                cout << "Errore: Inserito un valore non valido. Riprova." << endl;
            }
        }
    }
    cout << endl;
}
stringstream caption(){
    stringstream c;
    string tmp;
    cin.ignore();
    cout << "Inserire a seguito la caption della tabella: " << endl;
    getline(cin, tmp);
    c << tmp;
    cout << endl;
    return c;
}
string outputname(){
    string outname;
    cout << "Come si desidera chiamare il file di output ?" << endl;
    cin >> outname;
    cout << endl;
    return outname;
}

//Computing
void oldorder(vector<vector<misura>> &m){
    for(int i=0; i<m.size(); i++){
        for(int k=0; k<m[i].size(); k++){
            misura &tmp=m[i][k];
            tmp.ord_m=static_cast<int>(log10(fabs(tmp.mis)));
            tmp.ord_e=static_cast<int>(log10(fabs(tmp.err)));
        }
    }
}
void convert(vector<vector<misura>> &m){
    for(auto &col:m){
        for(auto &tmp:col){
            tmp.mis=tmp.mis*pow(10, -tmp.ord_m)*pow(10, -fabs(tmp.new_o-tmp.ord_m));
            tmp.err=tmp.err*pow(10, -tmp.ord_e)*pow(10, -fabs(tmp.new_o-tmp.ord_e));
        }
    }
}

//Writing
string top(){
    stringstream toptext;
    toptext << "\\begin{table}[H]" << endl;
    toptext << "    \\centering";
    return toptext.str();
}
string columns(vector<string> &v){
    stringstream columntext;
    columntext << "        \\begin{tabular}{";
    for(int i=0; i<v.size(); i++){
        columntext << "|c";
    }
    columntext << "|}";
    return columntext.str();
}
string header(vector<string> &v){
    stringstream nametext;
    nametext << "        \\hline" << endl;
    nametext << "        ";
    for(int i=0; i<v.size()-1; i++){
        nametext << "$ " << v[i] << " $ & ";
    }
    nametext << "$ " << v[v.size()-1] << " $\\\\" << endl;
    nametext << "        \\hline";
    return nametext.str();
}
string measures(vector<vector<misura>> &m){
    stringstream measurestext;
    for(int i=0; i<m[0].size(); i++){
        measurestext << "       ";
        for(int k=0; k<m.size(); k++){
            const auto &tmp=m[k][i];
            if(tmp.cw==0){
                if(tmp.new_o!=0){
                    measurestext << " $ (" << fixed << setprecision(tmp.prec) << tmp.mis 
                                          << " \\pm " << fixed << setprecision(tmp.prec) << tmp.err 
                                          << ") \\cdot 10^{" << tmp.new_o << "} $";
                }else{
                    measurestext << " $ " << fixed << setprecision(tmp.prec) << tmp.mis 
                                          << " \\pm " << fixed << setprecision(tmp.prec) << tmp.err << " $";
                }
                if(k<m.size()-1){
                    measurestext << " &";
                }
            }else if(tmp.cw==1){
                if(tmp.new_o!=0){
                measurestext << " \\textcolor{red}{$ (" << fixed << setprecision(tmp.prec) << tmp.mis 
                                      << " \\pm " << fixed << setprecision(tmp.prec) << tmp.err 
                                      << ") \\cdot 10^{" << tmp.new_o << "} $}";
                }else{
                    measurestext << " \\textcolor{red}{$ " << fixed << setprecision(tmp.prec) << tmp.mis 
                                          << " \\pm " << fixed << setprecision(tmp.prec) << tmp.err << " $}";
                }
                if(k<m.size()-1){
                    measurestext << " &";
                } 
            }
        }
        measurestext << "\\\\" << endl;
        measurestext << "        \\hline" << endl;               
    }
    return measurestext.str();
}
string endtabular(){
    stringstream tabulartext;
    tabulartext << "        \\end{tabular}";
    return tabulartext.str();
}
string caption(string c){
    stringstream captiontext;
    captiontext << "    \\caption{" << c << "}";
    return captiontext.str();
}
string endtable(){
    stringstream tabletext;
    tabletext << "\\end{table}";
    return tabletext.str();
}