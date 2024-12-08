#include"funzioni.h"

int main(){
//preliminary
    instructions();
    string inname=inputname();
    vector<string> v=measuresname();
    vector<double> o=order();
    string yn=errateyn();
    vector<int> e;
    if(yn=="si"||yn=="s"||yn=="yes"||yn=="y"){
        e=misurerr();
    }
    stringstream c=caption();
    string outname=outputname();

    vector<vector<double> m> n;

//input file
    inname=inname+".txt";
    vector<double> m=read(inname);
    cout << m[0] <<  endl;
    convert(v, m, o);
    cout << m[0] <<  endl;

//output file
    ofstream output;
    outname=outname+".tex";
    output.open(outname, ios::out);
    output << top() << endl;
    output << columns(v) << endl;
    output << header(v) << endl;
    if(yn=="si"||yn=="s"||yn=="yes"||yn=="y"){
        output << measures(m, v, o, e) << endl;
    }else{
        output << measures(m, v, o) << endl;
    }
    output << endtabular() << endl;
    output << caption(c.str()) << endl;
    output << endtable() << endl;
    cout << "Tebella creata, da TABSLAYER, nel file: " << outname << endl;
}