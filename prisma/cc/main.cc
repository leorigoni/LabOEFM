#include <iostream>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TPaveText.h>

int main() {
    // Dati forniti
    double x[] = {2.98E-06, 3.00E-06, 3.35E-06, 4.06E-06, 5.27E-06, 6.02E-06, 6.11E-06};
    double y[] = {3.1886, 3.1895, 3.2090, 3.2551, 3.3303, 3.3847, 3.3920};
    double yErr[] = {2.12E-03, 1.94E-03, 1.96E-03, 2.00E-03, 2.08E-03, 2.14E-03, 2.15E-03};
    int n = sizeof(x) / sizeof(x[0]); // Numero di punti

    // Creazione del grafico con errori
    TGraphErrors *graph = new TGraphErrors(n, x, y, nullptr, yErr); // nullptr per assenza di errori su X
    graph->SetTitle("Regressione Lineare con Errori;X;Y");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.5);

    // Creazione della funzione di regressione lineare
    TF1 *fitFunction = new TF1("fitFunction", "pol1", x[0], x[n-1]); // 'pol1' è una funzione lineare

    // Fitting
    graph->Fit(fitFunction);

    // Stampare i risultati sul terminale
    double p0 = fitFunction->GetParameter(0); // Intercetta
    double p1 = fitFunction->GetParameter(1); // Coefficiente angolare
    double p0Err = fitFunction->GetParError(0);
    double p1Err = fitFunction->GetParError(1);
    double chi2 = fitFunction->GetChisquare();
    int ndf = fitFunction->GetNDF();

    std::cout << "Minimizer is Linear / Migrad" << std::endl;
    std::cout << "Chi2                      = " << chi2 << std::endl;
    std::cout << "NDf                       = " << ndf << std::endl;
    std::cout << "p0                        = " << p0 << "   +/-   " << p0Err << std::endl;
    std::cout << "p1                        = " << p1 << "   +/-   " << p1Err << std::endl;

    // Creazione di un canvas per visualizzare il grafico
    TCanvas *canvas = new TCanvas("canvas", "Regressione Lineare con Errori", 800, 600);
    canvas->SetGrid(); // Aggiungere una griglia
    graph->Draw("AP"); // 'A' per il frame dell'asse, 'P' per i punti

    // Aggiunta della mini-leggenda con i risultati del fitting
    TPaveText *pt = new TPaveText(0.15, 0.75, 0.37, 0.85, "NDC"); // Posizionamento in coordinate normalizzate
    pt->SetFillColor(0);
    pt->AddText("Minimizer is Linear / Migrad");
    pt->AddText(Form("Chi2  =  %.5e", chi2));
    pt->AddText(Form("NDf  =  %d", ndf));
    pt->AddText(Form("p0 =  %.5f  +/-  %.5f", p0, p0Err));
    pt->AddText(Form("p1 =  %.5f  +/-  %.5f", p1, p1Err));
    pt->Draw();

    // Mostra i risultati
    canvas->Update();
    canvas->SaveAs("regressione_lineare_con_errori.pdf"); // Salvare il grafico come PDF

    return 0;
}
