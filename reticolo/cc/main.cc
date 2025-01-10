#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TPaveText.h>
#include <TStyle.h>
#include <TAxis.h>

void DrawGraph(int index, double x[], double y[], double ex[], double ey[], int n, TCanvas* c) {
    c->cd(index);  // Imposta il riquadro giusto nel canvas
    gPad->SetGrid();  // Imposta la griglia

    // Creazione del grafico con errori
    TGraphErrors *graph = new TGraphErrors(n, x, y, ex, ey);
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kRed);
    graph->SetMarkerSize(0.8);

    // Impostiamo i titoli degli assi prima di fare il disegno
    graph->GetXaxis()->SetTitle("k");
    graph->GetYaxis()->SetTitle("d⋅sin(θ) [nm]");

    // Funzione di regressione lineare
    TString fitTitle = Form("Lambda %d", index);
    TF1 *fitFunc = new TF1("fitFunc", "pol1", 0.0, 6.0);
    fitFunc->SetTitle(fitTitle);
    fitFunc->SetLineColor(kGreen);
    fitFunc->SetLineWidth(1);

    // Fit del grafico
    graph->Fit(fitFunc, "Q");

    // Disegno del grafico e degli elementi in ordine desiderato
    fitFunc->Draw();  // Disegna la retta prima (sotto tutto)
    graph->Draw("P SAME");  // Disegna i punti sopra la retta
    graph->Draw("E SAME");  // Disegna le barre di errore sopra i punti

    // Creazione della legenda
    TPaveText *pt = new TPaveText(0.15, 0.75, 0.45, 0.85, "NDC");
    pt->AddText("Parametri Fit:");
    pt->AddText(Form("m = %.3f", fitFunc->GetParameter(1)));  // Pendenza (m)
    pt->AddText(Form("q = %.3f", fitFunc->GetParameter(0)));  // Intercetta (q)
    pt->SetFillColor(0);
    pt->Draw();
}


int main() {
    // Dati forniti
    const int numSets = 8;
    const int n = 10;
    double x[numSets][n] = {
        {1, 2, 3, 4, 5, 3, 3, 3, 3, 3}, // Set 1
        {1, 2, 3, 4, 5, 3, 3, 3, 3, 3}, // Set 2
        {1, 2, 3, 4, 5, 6, 3, 3, 3, 3}, // Set 3
        {1, 2, 3, 4, 5, 3, 3, 3, 3, 3}, // Set 4
        {1, 2, 3, 4, 5, 6, 3, 3, 3, 3}, // Set 5
        {1, 2, 3, 4, 5, 3, 3, 3, 3, 3}, // Set 6
        {1, 2, 3, 4, 5, 3, 3, 3, 3, 3}, // Set 7
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2}  // Set 8
    };
    double y[numSets][n] = {
        {404, 809, 1210, 1620, 2020, 1210, 1210, 1210, 1210, 1220}, // Set 1
        {408, 816, 1220, 1630, 2040, 1220, 1220, 1220, 1220, 1220}, // Set 2
        {435, 871, 1310, 1740, 2180, 2610, 1310, 1310, 1310, 1310}, // Set 3
        {494, 984, 1480, 1970, 2450, 1480, 1480, 1470, 1470, 1470}, // Set 4
        {546, 1090, 1640, 2180, 2730, 3260, 1640, 1640, 1640, 1640}, // Set 5
        {580, 1160, 1730, 2310, 2880, 1730, 1730, 1730, 1730, 1730}, // Set 6
        {580, 1160, 1740, 2320, 2890, 1740, 1740, 1740, 1740, 1740}, // Set 7
        {693, 1380, 1380, 1380, 1380, 1380, 1380, 1380, 1380, 1380}  // Set 8
    };
    double ex[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double ey[numSets][n] = {
        {2.07, 2.08, 2.08, 2.09, 2.11, 2.08, 2.08, 2.08, 2.08, 2.08}, // Set 1
        {2.07, 2.08, 2.08, 2.09, 2.11, 2.08, 2.08, 2.08, 2.08, 2.08}, // Set 2
        {2.07, 2.08, 2.09, 2.10, 2.11, 2.13, 2.09, 2.09, 2.09, 2.09}, // Set 3
        {2.07, 2.08, 2.09, 2.11, 2.13, 2.09, 2.09, 2.09, 2.09, 2.09}, // Set 4
        {2.07, 2.08, 2.09, 2.11, 2.14, 2.17, 2.09, 2.09, 2.09, 2.09}, // Set 5
        {2.07, 2.08, 2.10, 2.12, 2.15, 2.10, 2.10, 2.10, 2.10, 2.10}, // Set 6
        {2.07, 2.08, 2.10, 2.12, 2.15, 2.10, 2.10, 2.10, 2.10, 2.10}, // Set 7
        {2.07, 2.09, 2.09, 2.09, 2.09, 2.09, 2.09, 2.09, 2.09, 2.09}  // Set 8
    };

    // Creazione del canvas
    TCanvas *c1 = new TCanvas("c1", "Regressioni Lineari", 1200, 800);
    c1->Divide(4, 2); // Divide il canvas in 4x2 riquadri

    // Disegna ogni set di dati in un riquadro separato
    for (int i = 0; i < numSets; ++i) {
        DrawGraph(i+1, x[i], y[i], ex, ey[i], n, c1);
    }
    c1->Update();

    // Salvataggio del grafico in un file PDF
    c1->SaveAs("regressioni.pdf");

    return 0;
}
