#include"funzioni.h"

int main(){
    //Preliminary
    instructions();
    string inname=inputname();
    vector<vector<misura>> m=read(inname);
    vector<string> v=measuresname(m);
    scientific(m, v);
    neworder(m);
    setprec(m);
    correctwrong(m);
    stringstream c=caption();
    string outname=outputname();

    //Computing
    oldorder(m);
    newmis(m);

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
    cout << endl;
    cout << m[0][0].new_o << endl;
    cout << m[0][0].yn << endl;
    cout << m[0][0].prec << endl;
    cout << m[0][0].cw << endl;
    
    return 0;
}