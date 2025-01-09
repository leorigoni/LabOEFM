#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TText.h>
#include <TAxis.h>
#include <iostream>
#include <iomanip>
#include <sstream>

int main() {
    // Valore vero di e/m
    const double e_over_m = 1.758e11; // C/kg

    // Array per i punti x
    double x[3] = {1, 2, 3};
    double y[3] = {1.70E+11, 1.63E+11, 1.68E+11};
    double ex[3] = {0, 0, 0}; // Nessun errore su x
    double ey[3] = {6.06E+09, 5.51E+09, 5.72E+09};

    // Creazione del canvas
    TCanvas *c1 = new TCanvas("c1", "e/m Plot", 800, 600);

    // Creazione del grafico con errori
    TGraphErrors *graph = new TGraphErrors(3, x, y, ex, ey);
    graph->SetTitle("Misura di e/m; n; e/m [C/kg]");
    graph->SetMarkerStyle(20); // Segnalino circolare
    graph->SetMarkerColor(kRed); // Colore rosso per i segnalini
    graph->SetLineColor(kBlack); // Colore nero per le barre d'errore
    graph->SetLineWidth(1);
    graph->Draw("AP");

    // Disegno della linea orizzontale verde per il valore vero di e/m
    TLine *line = new TLine(0.8, e_over_m, 3.2, e_over_m);
    line->SetLineColor(kGreen);
    line->SetLineWidth(2);
    line->Draw("same");

    // Aggiunta della griglia sull'asse y
    c1->SetGridy();

    // Aggiornamento degli assi con i titoli richiesti
    graph->GetXaxis()->SetTitle("n");
    graph->GetYaxis()->SetTitle("e/m [C/kg]");

    // Aggiunta delle etichette accanto ai pallini rossi
    for (int i = 0; i < 3; i++) {
        std::ostringstream label;
        label << std::scientific << std::setprecision(2) << y[i];
        TText *text = new TText(x[i] + 0.02, y[i] + 0.04, label.str().c_str());
        text->SetTextSize(0.02);
        text->SetTextColor(kBlack);
        text->Draw();
    }

    // Salvataggio del grafico in un file PDF
    c1->SaveAs("grafico.pdf");

    return 0;
}
