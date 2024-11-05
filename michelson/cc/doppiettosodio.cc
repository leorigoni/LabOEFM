#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TF1.h"

struct Measurement {
    double value;
    double error;
};

int main() {
    std::ifstream inputFile("doppiettosodio.txt");
    if (!inputFile) {
        std::cerr << "Errore: non posso aprire il file lambdalaser.txt" << std::endl;
        return 1;
    }

    std::vector<Measurement> measurements;
    double value, error;

    // Caricamento dei dati dal file
    while (inputFile >> value >> error) {
        measurements.push_back({value, error});
    }

    if (measurements.size() < 12) {
        std::cerr << "Errore: il file deve contenere almeno 13 misure." << std::endl;
        return 1;
    }

    TCanvas* c1 = new TCanvas("c1", "Doppietto Sodio Measurements", 800, 600);
    TGraphErrors* graph = new TGraphErrors(12);

    // Creazione del grafico con le prime 12 misure
    for (int i = 0; i < 11; ++i) {
        graph->SetPoint(i, i + 1, measurements[i].value);
        graph->SetPointError(i, 0, measurements[i].error);
    }

    graph->SetMarkerStyle(21);
    graph->SetMarkerSize(0.8);
    graph->SetTitle(" ;n.;#delta#lambda [m]");
    graph->Draw("AP");

    // Calcolo della media pesata
    double weightedError=measurements[11].error;
    double weightedMeanValue=measurements[11].value;

    // Disegna la linea orizzontale per la media pesata
    TLine* line = new TLine(0, weightedMeanValue, 12, weightedMeanValue);
    line->SetLineColor(kGreen);
    line->SetLineStyle(1);
    line->Draw("same");
        TLine* line1 = new TLine(0, weightedMeanValue+weightedError, 12, weightedMeanValue+weightedError);
    line1->SetLineColor(kRed);
    line1->SetLineStyle(2);
    line1->Draw("same");
        TLine* line2 = new TLine(0, weightedMeanValue-weightedError, 12, weightedMeanValue-weightedError);
    line2->SetLineColor(kRed);
    line2->SetLineStyle(2);
    line2->Draw("same");

    // Mostra la media pesata come punto con barre di errore sottili
    //TGraphErrors* meanPoint = new TGraphErrors(1);
    //meanPoint->SetPoint(0, 6.5, weightedMeanValue);
    //meanPoint->SetPointError(0, 5.5, weightedError);
    //meanPoint->SetMarkerStyle(21);
    //meanPoint->SetMarkerColor(kBlue);
    //meanPoint->Draw("P same");

    // Salvataggio del grafico in un file PDF
    c1->SaveAs("graphsodio.pdf");

    delete c1;
    delete graph;
    delete line;
    delete line1;
    delete line2;

    return 0;
}
