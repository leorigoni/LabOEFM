#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>  // Include per std::istringstream
#include "TCanvas.h"
#include "TGraph.h"
#include "TLine.h"
#include "TMarker.h"
#include "TAxis.h"

int main() {
    // Definizione delle variabili
    std::vector<double> x_values;
    std::vector<double> y_values;
    double x, y;

    // Lettura del file di dati
    std::ifstream infile("dati.txt");
    if (!infile) {
        std::cerr << "Errore: impossibile aprire il file dati.txt" << std::endl;
        return 1;
    }

    // Lettura dei valori x dalla prima linea
    std::string data_line;  // Cambiato il nome per evitare conflitti
    if (std::getline(infile, data_line)) {
        std::istringstream iss(data_line);
        while (iss >> x) {
            x_values.push_back(x);
        }
    }

    // Lettura dei valori y dalla seconda linea
    if (std::getline(infile, data_line)) {  // Usato il nuovo nome
        std::istringstream iss(data_line);
        while (iss >> y) {
            y_values.push_back(y);
        }
    }

    infile.close();

    // Verifica che il numero di punti x e y sia uguale
    if (x_values.size() != y_values.size()) {
        std::cerr << "Errore: il numero di punti x e y non corrisponde" << std::endl;
        return 1;
    }

    // Creazione del grafico
    TCanvas *canvas = new TCanvas("canvas", "Grafico con ROOT", 800, 800);
    TGraph *graph = new TGraph(x_values.size(), &x_values[0], &y_values[0]);
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlack);
    graph->SetMarkerSize(0.5);
    graph->SetTitle(" ");

    // Impostare il range dell'asse Y
    graph->GetYaxis()->SetRangeUser(0, 9e-39);
    // Impostare il range dell'asse X dinamicamente
    /*double x_min = *std::min_element(x_values.begin(), x_values.end());
    double x_max = *std::max_element(x_values.begin(), x_values.end());
    graph->GetXaxis()->SetRangeUser(x_min, x_max);*/
    
    graph->Draw("AP");
    canvas->SetGrid();

    // Trovare il punto con y minima e colorarlo di rosso
    auto min_y_iter = std::min_element(y_values.begin(), y_values.end());
    int min_y_index = std::distance(y_values.begin(), min_y_iter);
    TMarker *min_marker = new TMarker(x_values[min_y_index], y_values[min_y_index], 20);
    min_marker->SetMarkerColor(kRed);
    min_marker->SetMarkerSize(0.5);
    min_marker->Draw();

    // Aggiungere una retta verde a x = 1.602176634e-19
    double x_pos = 1.602176634e-19;

    // Creare la retta che si estende da y=0 fino al massimo di y
    TLine *line_object = new TLine(x_pos, 0,
                                    x_pos, 9e-39);
    line_object->SetLineColor(kGreen);
    line_object->SetLineWidth(1);
    line_object->Draw();

    // Aggiungere una retta verde a x = 1.602176634e-19
    double x_errp = 1.6066E-19;

    // Creare la retta che si estende da y=0 fino al massimo di y
    TLine *line_objectp = new TLine(x_errp, 1.6e-39,
                                    x_errp, 2.6e-39);
    line_objectp->SetLineColor(kRed);
    line_objectp->SetLineWidth(1);
    line_objectp->Draw();

    // Aggiungere una retta verde a x = 1.602176634e-19
    double x_errm = 1.5834E-19;

    // Creare la retta che si estende da y=0 fino al massimo di y
    TLine *line_objecmt = new TLine(x_errm, 1.6e-39,
                                    x_errm, 2.6e-39);
    line_objecmt->SetLineColor(kRed);
    line_objecmt->SetLineWidth(1);
    line_objecmt->Draw();

    // Impostare la notazione scientifica per l'asse Y
    graph->GetYaxis()->SetTitleOffset(0.8);
    graph->GetYaxis()->SetTitleSize(0.03);
    graph->GetYaxis()->SetLabelSize(0.02);
    graph->GetYaxis()->SetTitle("S(q#alpha) [C^{2}]");
    graph->GetXaxis()->SetTitleOffset(0.8);
    graph->GetXaxis()->SetTitleSize(0.03);
    graph->GetXaxis()->SetLabelSize(0.02);
    graph->GetXaxis()->SetTitle("q#alpha [C]");

    // Visualizzazione del grafico
    canvas->Update();
    canvas->SaveAs("grafico.pdf");

    return 0;
}
