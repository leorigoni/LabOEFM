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
vector<double> neworder(){
    vector<double> o;
    cout << "Inserire l'ordine di grandezza desiderarato per ciascuna colonna: " << endl;
    string tmp;
    while(cin >> tmp && tmp!="fine"){
        double tmps=stod(tmp);
        o.push_back(tmps);
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
vector<int> misurerr(string yn){
    vector<int> e;
    if(yn=="si"||yn=="s"||yn=="yes"||yn=="y"){
        cout << "Inserire il numero delle righe in cui si trovano le misure errate: " << endl;
        int tmp;
        string tmps;
        while(cin >> tmp && tmps!="fine"){
            e.push_back(tmp);
            cin.ignore();
        }
        return e;
    }else{
        return e;
    }

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
vector<vector<double>> read(vector<string> &v, string inname){
    ifstream input;
    input.open(inname, ios::in);
    if(!input.is_open()){
        cout << endl;
        cout << "Apertura file non riuscita." << endl;
        input.clear();
    }
    vector<vector<double>> m(v.size()*2);
    double tmp;
    while(true){
        for(int i=0; i<(v.size()*2); i++){
            if (!(input >> tmp)){
                input.close();
                return m;
            }
            m[i].push_back(tmp);
        }
    }
}
vector<int> oldorder(vector<vector<double>> &m){
    for(int i=0; i<m.size(); i++){
        
    }
}
void convert(vector<vector<double>> &m, vector<double> &o){
    for(int i=0; i<m.size(); i++){
        for(int k=0; k<m[i].size(); k++){
            int tmp=static_cast<int>(log10(fabs(m[i][k])));
            int d=o[i]-tmp;
            m[i][k]=m[i][k]*pow(10, d);
        }
    }
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
string measure(vector<vector<double>> &m, vector<int> &e){
    stringstream measuretext;
    for(int i=0; i<m.size(); i++){
        measuretext << "        \\hline" << endl;
        for(int k=0; k<m[i].size(); k+=2){
            if(e.empty()){
                measuretext << "        $ ("
                            << scientific << setprecision(3)
                            << m[i][k] << " \\pm " << m[i][k + 1]
                            << ") $";
                if(k+2<m[i].size()){
                    measuretext << " & ";
                }
            }else{
                break;
            }
        }
    }
    return measuretext.str();
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