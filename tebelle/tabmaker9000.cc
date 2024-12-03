#include"funzioni.h"

int main(){
//things
    string inname;
    string outname;
    vector<string> v;
    vector<string> m;
    vector<int> e;
    stringstream c;

//preliminary
    instructions();
    cout << "Com'è stato chiamato il file contenente le misure: " << endl;
    cin >> inname;
    cout << "Inserire i nomi delle colonne della tabella: " << endl;
    string tmp;
    while(cin >> tmp && tmp!="fine"){
        v.push_back(tmp);
    }
    string yn;
    cout << "Sono presenti delle misure errate all'interno della tabella da trascrivere ?" << endl;
    cin >> yn;
    cin.ignore();
    if(yn=="si"||yn=="s"||yn=="yes"||yn=="y"){
        cout << "Inserire il numero delle righe in cui si trovano le misure errate: " << endl;
        int tmp;
        string tmps;
        while(cin >> tmp && tmps!="fine"){
            e.push_back(tmp);
            cin.ignore();
        }
    }
    string mom;
    cout << "Inserire a seguito la caption della tabella: " << endl;
    getline(cin, mom);
    c << mom;
    cout << "Come si desidera chiamare il file di output: " << endl;
    cin >> outname;


//input file
    inname=inname+".txt";
    m=read(inname);

//output file
    ofstream output;
    outname=outname+".tex";
    output.open(outname, ios::out);
    output << top() << endl;
    output << columns(v) << endl;
    output << header(v) << endl;
    if(yn=="si"||yn=="s"||yn=="yes"||yn=="y"){
        output << measures(m, v, e) << endl;
    }else{
        output << measures(m, v) << endl;
    }
    output << endtabular() << endl;
    output << caption(c.str()) << endl;
    output << endtable() << endl;
    cout << "Tebella creata, da TABSLAYER, nel file: " << outname << endl;
}