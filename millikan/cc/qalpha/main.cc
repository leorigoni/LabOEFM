#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TLine.h"
#include "TMarker.h"
#include "TAxis.h"

int main() {
    std::vector<double> x_values;
    std::vector<double> y_values;
    double x, y;

    std::ifstream infile("dati.txt");
    if (!infile) {
        std::cerr << "Errore: impossibile aprire il file dati.txt" << std::endl;
        return 1;
    }

    std::string data_line;
    if (std::getline(infile, data_line)) {
        std::istringstream iss(data_line);
        while (iss >> x) {
            x_values.push_back(x);
        }
    }

    if (std::getline(infile, data_line)) {
        std::istringstream iss(data_line);
        while (iss >> y) {
            y_values.push_back(y);
        }
    }

    infile.close();

    if (x_values.size() != y_values.size()) {
        std::cerr << "Errore: il numero di punti x e y non corrisponde" << std::endl;
        return 1;
    }

    TCanvas *canvas = new TCanvas("canvas", "Grafico con ROOT", 800, 800);
    TGraph *graph = new TGraph(x_values.size(), &x_values[0], &y_values[0]);
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlack);
    graph->SetMarkerSize(0.5);
    graph->SetTitle(" ");
    graph->GetYaxis()->SetRangeUser(2e-39, 10e-39);

    graph->Draw("AP");
    canvas->SetGrid();

    // Aggiungere una retta verde a x = 1.602176634e-19
    double x_pos = 1.602176634e-19;

    // Creare la retta che si estende da y=0 fino al massimo di y
    TLine *line_object = new TLine(x_pos, 2e-39,
                                    x_pos, 10e-39);
    line_object->SetLineColor(kGreen);
    line_object->SetLineWidth(1);
    line_object->Draw();

    auto min_y_iter = std::min_element(y_values.begin(), y_values.end());
    int min_y_index = std::distance(y_values.begin(), min_y_iter);
    TMarker *min_marker = new TMarker(x_values[min_y_index], y_values[min_y_index], 20);
    min_marker->SetMarkerColor(kRed);
    min_marker->SetMarkerSize(0.5);
    min_marker->Draw();

    // Calcolo delle barre di errore
    double x_min = x_values[min_y_index];
    double error_percent = 0.01; // 1% di errore, puoi modificare questo valore
    double x_err = x_min * error_percent;

    double x_errp = x_min + x_err;
    double x_errm = x_min - x_err;

    TLine *line_objectp = new TLine(x_errp, 2.7e-39, x_errp, 3.3e-39);
    line_objectp->SetLineColor(kRed);
    line_objectp->SetLineWidth(1);
    line_objectp->Draw();

    TLine *line_objectm = new TLine(x_errm, 2.7e-39, x_errm, 3.3e-39);
    line_objectm->SetLineColor(kRed);
    line_objectm->SetLineWidth(1);
    line_objectm->Draw();

    graph->GetYaxis()->SetTitleOffset(0.8);
    graph->GetYaxis()->SetTitleSize(0.03);
    graph->GetYaxis()->SetLabelSize(0.02);
    graph->GetYaxis()->SetTitle("S(q#alpha) [C^{2}]");
    graph->GetXaxis()->SetTitleOffset(0.8);
    graph->GetXaxis()->SetTitleSize(0.03);
    graph->GetXaxis()->SetLabelSize(0.02);
    graph->GetXaxis()->SetTitle("q#alpha [C]");

    canvas->Update();
    canvas->SaveAs("grafico.pdf");

    return 0;
}
