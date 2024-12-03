#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;

//intro
void instructions(){
    cout << "" << endl;
}

//open+copy data
vector<string> read(string inname){
    ifstream input;
    input.open(inname, ios::in);
    if(!input.is_open()){
        cout << endl;
        cout << "Apertura file non riuscita." << endl;
        input.clear();
    }
    vector<string> tmp;
    string mom;
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
string measures(vector<string> &m, vector<string> &v){
    stringstream datatext;
    for(int i=0; i<m.size()-v.size(); i+=v.size()){
        datatext << "        \\hline" << endl;
        datatext << "        ";
        for(int k=i; k<i+v.size()-1; k++){
            datatext << "$ " << m[k] << " $ & ";
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
string measures(vector<string> &m, vector<string> &v, vector<int> &e){
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