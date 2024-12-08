#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

//preliminary
void instructions(){
    cout << "" << endl;
}
string inputname(){
    string inname;
    cout << "Com'è stato chiamato il file contenente le misure: " << endl;
    cin >> inname;
    cout << endl;
    return inname;
}
vector<string> measuresname(){
    vector<string> v;
    cout << "Inserire i nomi delle colonne della tabella: " << endl;
    string tmp;
    while(cin >> tmp && tmp!="fine"){
        v.push_back(tmp);
    }
    cout << endl;
    return v;
}
vector<double> order(){
    vector<double> o;
    cout << "Inserire l'ordine di grandezza desiderarato per ciascuna colonna: " << endl;
    string tmp;
    while(cin >> tmp && tmp!="fine"){
        double tmps = stod(tmp);
        o.push_back(tmps);
    }
    cout << endl;
    return o;
}
string errateyn(){
    string yn;
    cout << "Sono presenti delle misure errate all'interno della tabella da trascrivere ?" << endl;
    cin >> yn;
    cout << endl;
    cin.ignore();
    return yn;
}
vector<int> misurerr(){
    vector<int> e;
    cout << "Inserire il numero delle righe in cui si trovano le misure errate: " << endl;
    int tmp;
    string tmps;
    while(cin >> tmp && tmps!="fine"){
        e.push_back(tmp);
        cin.ignore();
    }
    return e;
}
stringstream caption(){
    stringstream c;
    string tmp;
    cout << "Inserire a seguito la caption della tabella: " << endl;
    getline(cin, tmp);
    c << tmp;
    cout << endl;
    return c;
}
string outputname(){
    string outname;
    cout << "Come si desidera chiamare il file di output: " << endl;
    cin >> outname;
    cout << endl;
    return outname;
}

//open+copy data
vector<double> read(string inname){
    ifstream input;
    input.open(inname, ios::in);
    if(!input.is_open()){
        cout << endl;
        cout << "Apertura file non riuscita." << endl;
        input.clear();
    }
    vector<double> tmp;
    double mom;
    while(input >> mom){
        tmp.push_back(mom);
    }
    input.close();
    return tmp;
}

//sstream
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
    nametext << "$ " << v[v.size()-1] << " $\\\\";
    return nametext.str();
}
void convert(const std::vector<std::string>& v, std::vector<double>& m, const std::vector<double>& o) {
    // Assumiamo che il numero di colonne sia `v.size()`
    size_t num_colonne = v.size();

    if (o.size() != num_colonne) {
        std::cerr << "Errore: il vettore degli ordini 'o' deve avere la stessa dimensione di 'v'.\n";
        return;
    }

    // Itera su tutte le righe del file
    for (size_t i = 0; i < m.size(); i += num_colonne * 2) {
        for (size_t j = 0; j < num_colonne; ++j) {
            // Calcola gli indici della misura e dell'errore
            size_t misura_idx = i + j * 2;
            size_t errore_idx = misura_idx + 1;

            // Calcola l'ordine corrente della misura
            int ordine_corrente_misura = static_cast<int>(std::floor(std::log10(std::abs(m[misura_idx]))));
            int differenza_misura = static_cast<int>(o[j]) - ordine_corrente_misura;
            m[misura_idx] = m[misura_idx] * std::pow(10, -differenza_misura);

            // Calcola l'ordine corrente dell'errore
            int ordine_corrente_errore = static_cast<int>(std::floor(std::log10(std::abs(m[errore_idx]))));
            int differenza_errore = static_cast<int>(o[j]) - ordine_corrente_errore;
            m[errore_idx] = m[errore_idx] * std::pow(10, -differenza_errore);
        }
    }
}





string measures(vector<double> &m, vector<string> &v, vector<double> &o){
    stringstream datatext;
    for(int i=0; i<m.size()-v.size(); i+=v.size()){
        datatext << "        \\hline" << endl;
        datatext << "        ";
        for(int k=i; k<i+v.size()-1; k+=2){
            datatext << "$ (" << m[k] << " \\pm " << m[k+1] << ") \\cdot $ & ";
        }
        datatext << "$ " << m[i+1] << " $\\\\" << endl;
    }
    datatext << "        \\hline" << endl;
    datatext << "        ";
    for(int i=m.size()-v.size(); i<m.size()-1; i++){
        datatext << "$ " << m[i] << " $ & ";
    }
    datatext << "$ " << m[m.size()-1] << " $\\\\";
    return datatext.str();
}
string measures(vector<double> &m, vector<string> &v, vector<double> &o, vector<int> &e){
    stringstream datatext;
    datatext << "        \\hline" << endl;
    datatext << "        ";
    for(int i=0; i<m.size()-1; i++){
        datatext << "$ " << m[i] << " $ & ";
    }
    datatext << "$ " << m[m.size()-1] << " $\\\\";
    return datatext.str();
}
string endtabular(){
    stringstream tabulartext;
    tabulartext << "        \\hline" << endl;
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