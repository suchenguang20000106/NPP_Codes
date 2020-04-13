#include "TH2.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <string>
#include "TFile.h"
using namespace std;

void eff(char filename[], char pdfname[])
{
		TFile* file = new TFile(filename);
		TH1F *Selected = (TH1F*) file -> Get("Selected");
		TH1F *Total = (TH1F*) file -> Get("Total");
		TH1F *eff = (TH1F*) Selected -> Clone();
		eff -> Divide(Selected, Total, 1., 1., "B");

		eff -> SetTitle("Efficiency");
		eff -> GetXaxis() -> SetTitle("mu");
		eff -> GetYaxis() -> SetTitle("Efficiency");
		eff -> SetStats(kFALSE);

		TCanvas *c = new TCanvas();
		eff -> Draw();
		c -> SaveAs(pdfname);
}

