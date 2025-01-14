#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TF1.h"
#include "TAxis.h"
#include "TLegend.h"

struct Measurement {
    double value;
    double error;
};

int main() {
    std::ifstream inputFile("maxmax.txt");
    if (!inputFile) {
        std::cerr << "Errore: non posso aprire il file maxmax.txt" << std::endl;
        return 1;
    }

    std::vector<Measurement> measurements;
    double value, error;

    // Caricamento dei dati dal file
    while (inputFile >> value >> error) {
        measurements.push_back({value, error});
    }

    if (measurements.size() < 4) {
        std::cerr << "Errore: il file deve contenere almeno 13 misure." << std::endl;
        return 1;
    }

    TCanvas* c1 = new TCanvas("c1", "Lambda Laser Measurements", 800, 600);
    TGraphErrors* graph = new TGraphErrors(3);

    // Creazione del grafico con le prime 12 misure
    for (int i = 0; i < 3; ++i) {
        graph->SetPoint(i, i + 1, measurements[i].value);
        graph->SetPointError(i, 0, measurements[i].error);
    }

    gPad->SetGrid();
    graph->SetMarkerStyle(21);
    graph->SetMarkerSize(0.8);
    graph->GetXaxis()->SetLimits(0, 4);
    graph->GetXaxis()->SetRangeUser(0, 4);
    graph->GetYaxis()->SetLimits(2.85e08, 3.2e08);
    graph->GetYaxis()->SetRangeUser(2.85e08, 3.2e08);
    graph->SetTitle(" ;n.;c [m/s]");
    graph->Draw("AP");

    // Calcolo della media pesata
    double weightedError=measurements[3].error;
    double weightedMeanValue=measurements[3].value;

    // Disegna la linea orizzontale per la media pesata
    TLine* line = new TLine(0, weightedMeanValue, 4, weightedMeanValue);
    line->SetLineColor(kGreen);
    line->SetLineStyle(1);
    line->Draw("same");
        TLine* line1 = new TLine(0, weightedMeanValue+weightedError, 4, weightedMeanValue+weightedError);
    line1->SetLineColor(kRed);
    line1->SetLineStyle(2);
    line1->Draw("same");
        TLine* line2 = new TLine(0, weightedMeanValue-weightedError, 4, weightedMeanValue-weightedError);
    line2->SetLineColor(kRed);
    line2->SetLineStyle(2);
    line2->Draw("same");
        TLine* line3 = new TLine(0, 299792458, 4, 299792458);
    line3->SetLineColor(kBlue);
    line3->SetLineStyle(1);
    line3->Draw("same");

    // Mostra la media pesata come punto con barre di errore sottili
    //TGraphErrors* meanPoint = new TGraphErrors(1);
    //meanPoint->SetPoint(0, 6.5, weightedMeanValue);
    //meanPoint->SetPointError(0, 5.5, weightedError);
    //meanPoint->SetMarkerStyle(21);
    //meanPoint->SetMarkerColor(kBlue);
    //meanPoint->Draw("P same");

    // Crea la legenda
    TLegend* legend = new TLegend(0.7, 0.77, 0.9, 0.9);
    legend->AddEntry(graph, "Misure + Errore", "p"); // "p" indica i punti
    legend->AddEntry(line, "Media pesata", "l"); // "l" indica una linea
    legend->AddEntry(line1, "Errore Media pesata", "l");
    legend->AddEntry(line3, "Valor Vero", "l");

    // Disegna la legenda
    legend->Draw();

    // Salvataggio del grafico in un file PDF
    c1->SaveAs("finale.pdf");

    delete c1;
    delete graph;
    delete line;
    delete line1;
    delete line2;

    return 0;
}
