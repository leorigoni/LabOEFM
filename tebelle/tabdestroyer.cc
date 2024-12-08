#include"funzioni2.1.h"

int main(){
    //Preliminary
    string inname=inputname();
    vector<vector<misura>> m=read(inname);
    vector<string> v=measuresname(m);
    neworder(m);
    setprec(m);
    correctwrong(m);
    stringstream c=caption();
    string outname=outputname();

    //Computing
    oldorder(m);
    convert(m);

    //Writing
    ofstream output;
    outname=outname+".tex";
    output.open(outname, ios::out);
    output << top() << endl;
    output << columns(v) << endl;
    output << header(v) << endl;
    output << measures(m);
    output << endtabular() << endl;
    output << caption(c.str()) << endl;
    output << endtable() << endl;
    output.close();
    cout << "Tebella creata, da Tebelle, nel file: " << outname << endl;
    
    return 0;
}