#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMarker.h>
#include <TAxis.h>

int main() {
    // Creazione della canvas
    TCanvas *c1 = new TCanvas("c1", "Experimental elementary charge vs Elemental charge", 800, 600);

    // Dati sperimentali
    double x_exp[1] = {1}; // Asse x dummy (per collocare il punto sperimentale)
    double y_exp[1] = {1.5952E-19}; // Valore della carica elementare sperimentale
    double y_error[1] = {1.1567E-21}; // Errore sperimentale

    // Dati teorici
    double x_theory[1] = {1}; // Asse x dummy per il punto teorico
    double y_theory[1] = {1.6020e-19}; // Valore teorico della carica elementare

    // Creazione del grafico per i dati sperimentali con errore
    TGraphErrors *graph_exp = new TGraphErrors(1, x_exp, y_exp, 0, y_error);
    graph_exp->SetMarkerStyle(21);
    graph_exp->SetMarkerColor(kRed);
    graph_exp->SetMarkerSize(1);
    graph_exp->SetLineColor(kBlack);
    graph_exp->SetLineWidth(1);

    // Imposta il titolo e le etichette degli assi
    graph_exp->SetTitle("");
    graph_exp->GetXaxis()->SetTitle("");
    graph_exp->GetYaxis()->SetTitleOffset(1.7);
    graph_exp->GetYaxis()->SetTitleSize(0.03);
    graph_exp->GetYaxis()->SetTitle("q [C]");
    graph_exp->GetYaxis()->SetRangeUser(1.5800e-19, 1.6100e-19);
    graph_exp->GetXaxis()->SetLimits(0, 2);

    // Disegna il grafico con errore
    graph_exp->Draw("AP");

    // Creazione di un marker per il valore teorico
    TGraph *graph_theory = new TGraph(1, x_theory, y_theory);
    graph_theory->SetMarkerStyle(20);
    graph_theory->SetMarkerColor(kGreen);
    graph_theory->SetMarkerSize(1);
    graph_theory->Draw("P SAME");

    // Aggiunta della legenda
    TLegend *legend = new TLegend(0.57, 0.1, 0.9, 0.3);
    legend->AddEntry(graph_exp, "exp. elementary charge", "p");
    legend->AddEntry(graph_theory, "elementary charge", "p");
    legend->Draw();

    // Aggiunta delle etichette per i valori
    TLatex latex;
    latex.SetTextSize(0.03);
    latex.DrawLatex(1.05, 1.6060e-19, "1.6060E-19 C");
    latex.DrawLatex(1.05, 1.6020e-19, "1.6020E-19 C");

    // Aggiunta della griglia solo sull'asse y
    c1->SetGridy();

    // Mostra la canvas
    c1->Update();
    c1->SaveAs("grafico2.pdf");
}

