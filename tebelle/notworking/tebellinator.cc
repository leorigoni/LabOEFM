#include"funzioni2.0.h"

int main(){
//preliminary
    instructions();
    string inname=inputname();
    vector<string> v=measuresname();
    vector<double> no=neworder();
    string yn=errateyn();
    vector<int> e=misurerr(yn);
    stringstream c=caption();
    string outname=outputname();

//input file
    inname=inname+".txt";
    vector<vector<double>> m=read(v, inname);
    vector<int> oo=oldorder(m);
    cout << m[0][0] << " " << m[1][0] << endl;
    convert(m, o);
    cout << m[0][0] << " " << m[1][0] << endl;

//output file
    ofstream output;
    outname=outname+".tex";
    output.open(outname, ios::out);
    output << top() << endl;
    output << columns(v) << endl;
    output << header(v) << endl;
    output << measure(m, e) << endl;
    output << endtabular() << endl;
    output << caption(c.str()) << endl;
    output << endtable() << endl;
    cout << "Tebella creata, da Trombelle, nel file: " << outname << endl;
    return 0;
}