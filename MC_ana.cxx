#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
void PrintProgressBar(int index, int total)
{
	if (index % 10000 == 0)
	{
		TString print_bar = " [";
		for (int bar = 0; bar < 20; bar++)
		{
			double current_fraction = double(bar) / 20.0;
			if (double(index) / double(total) > current_fraction)
				print_bar.Append("/");
			else
				print_bar.Append(".");
		}
		print_bar.Append("] ");
		std::cout << print_bar << 100. * (double(index) / double(total)) << "%\r" << std::flush;
	}
}
/*
	 void infile2chain(TString _infilelist, TChain *&_fchain, TString chainname)
	 {

	 _fchain = new TChain(chainname);
	 ifstream infile(_infilelist, ios::in);
	 string line;
	 while (getline(infile, line)){
	 _fchain->Add(line.c_str());
	 }
	 infile.close();
	 }
	 */

void MC_ana()
{
	bool isMC = 1;

	TChain *chain = new TChain("output");
	ifstream input("input.txt", ios::in);
	while (true)
	{
		string file_name;
		getline(input, file_name);
		chain->Add(file_name.c_str());

		if (input.eof())
			break;
	}
	/*	
				TString recolist = "input.txt";
				TChain *chain;
				infile2chain(recolist, chain, "output");
				*/
	chain->SetBranchStatus("*", 0);

	vector<double> *ph_t = 0;
	vector<double> *ph_pt = 0;
	vector<double> *ph_eta = 0;
	vector<double> *ph_etas2 = 0;
	vector<double> *ph_phi = 0;
	vector<double> *ph_E = 0;
	vector<double> *el_pt = 0;
	vector<double> *el_eta = 0;
	vector<double> *el_phi = 0;
	vector<double> *el_E = 0;
	vector<double> *mu_pt = 0;
	vector<double> *mu_eta = 0;

	int HLT_e24_lhmedium_L1EM20VH;
	int HLT_e60_lhmedium;
	int HLT_e120_lhloose;
	int HLT_e26_lhtight_nod0_ivarloose;
	int HLT_e60_lhmedium_nod0;
	int HLT_e140_lhloose_nod0;
	int HLT_mu20_iloose_L1MU15;
	int HLT_mu50;
	int HLT_mu26_ivarmedium;

	int runNumber;
	int m_mcChannelNumber;
	double m_met;
	double mu;

	chain->SetBranchStatus("mu", 1);
	chain->SetBranchStatus("runNumber", 1);
	chain->SetBranchStatus("m_mcChannelNumber", 1);
	chain->SetBranchStatus("m_met", 1);
	chain->SetBranchStatus("ph_t", 1);
	chain->SetBranchStatus("ph_pt", 1);
	chain->SetBranchStatus("ph_eta", 1);
	chain->SetBranchStatus("ph_etas2", 1);
	chain->SetBranchStatus("ph_phi", 1);
	chain->SetBranchStatus("ph_E", 1);
	chain->SetBranchStatus("el_pt", 1);
	chain->SetBranchStatus("el_eta", 1);
	chain->SetBranchStatus("el_phi", 1);
	chain->SetBranchStatus("el_E", 1);
	chain->SetBranchStatus("mu_pt", 1);
	chain->SetBranchStatus("mu_eta", 1);

	if (!isMC)
		chain->SetBranchStatus("HLT_e24_lhmedium_L1EM20VH", 1);
	else
		chain->SetBranchStatus("HLT_e24_lhmedium_iloose_EM20VH", 1);
	chain->SetBranchStatus("HLT_e60_lhmedium", 1);
	chain->SetBranchStatus("HLT_e120_lhloose", 1);
	chain->SetBranchStatus("HLT_e26_lhtight_nod0_ivarloose", 1);
	chain->SetBranchStatus("HLT_e60_lhmedium_nod0", 1);
	chain->SetBranchStatus("HLT_e140_lhloose_nod0", 1);
	chain->SetBranchStatus("HLT_mu20_iloose_L1MU15", 1);
	chain->SetBranchStatus("HLT_mu50", 1);
	chain->SetBranchStatus("HLT_mu26_ivarmedium", 1);

	chain->SetBranchAddress("mu", &mu);
	chain->SetBranchAddress("runNumber", &runNumber);
	chain->SetBranchAddress("m_mcChannelNumber", &m_mcChannelNumber);
	chain->SetBranchAddress("m_met", &m_met);
	chain->SetBranchAddress("ph_t", &ph_t);
	chain->SetBranchAddress("ph_pt", &ph_pt);
	chain->SetBranchAddress("ph_eta", &ph_eta);
	chain->SetBranchAddress("ph_etas2", &ph_etas2);
	chain->SetBranchAddress("ph_phi", &ph_phi);
	chain->SetBranchAddress("ph_E", &ph_E);
	chain->SetBranchAddress("el_pt", &el_pt);
	chain->SetBranchAddress("el_eta", &el_eta);
	chain->SetBranchAddress("el_phi", &el_phi);
	chain->SetBranchAddress("el_E", &el_E);
	chain->SetBranchAddress("mu_pt", &mu_pt);
	chain->SetBranchAddress("mu_eta", &mu_eta);

	if (!isMC)
		chain->SetBranchAddress("HLT_e24_lhmedium_L1EM20VH", &HLT_e24_lhmedium_L1EM20VH);
	else
		chain->SetBranchAddress("HLT_e24_lhmedium_iloose_EM20VH", &HLT_e24_lhmedium_L1EM20VH);
	chain->SetBranchAddress("HLT_e60_lhmedium", &HLT_e60_lhmedium);
	chain->SetBranchAddress("HLT_e120_lhloose", &HLT_e120_lhloose);
	chain->SetBranchAddress("HLT_e26_lhtight_nod0_ivarloose", &HLT_e26_lhtight_nod0_ivarloose);
	chain->SetBranchAddress("HLT_e60_lhmedium_nod0", &HLT_e60_lhmedium_nod0);
	chain->SetBranchAddress("HLT_e140_lhloose_nod0", &HLT_e140_lhloose_nod0);
	chain->SetBranchAddress("HLT_mu20_iloose_L1MU15", &HLT_mu20_iloose_L1MU15);
	chain->SetBranchAddress("HLT_mu50", &HLT_mu50);
	chain->SetBranchAddress("HLT_mu26_ivarmedium", &HLT_mu26_ivarmedium);

	Long64_t nentries = chain->GetEntries();

	double binningx[13] = {0, 15, 25, 35, 45, 55, 65, 80};

	TH1F *total = new TH1F("Total", "Total", 7, binningx);
	total->GetXaxis()->SetTitle("mu");
	total->GetYaxis()->SetTitle("Events");

	TH1F *selected = new TH1F("Selected", "Selected", 7, binningx);
	selected->GetXaxis()->SetTitle("mu");
	selected->GetYaxis()->SetTitle("Events");

	TObjArray *hist = new TObjArray(0);
	hist->Add(total);
	hist->Add(selected);
	float weight = 1.;

	map<int, int> count;
	vector<TString> cutNames = {"inc", "trigger", "pT Trigger", "photon", "offZ", "met", "Timing"};
	/*
		//Entries passing selection
		ofstream entries;
		entries.open("Entries.txt");
		*/
	for (Long64_t jentry = 0; jentry < nentries; jentry++)
	{
		PrintProgressBar(jentry, nentries);

		ph_t->clear();
		ph_pt->clear();
		ph_eta->clear();
		ph_etas2->clear();
		ph_phi->clear();
		ph_E->clear();
		el_pt->clear();
		el_eta->clear();
		el_phi->clear();
		el_E->clear();
		mu_pt->clear();
		mu_eta->clear();
		//read event
		chain->GetEntry(jentry);

		//set weigth
		float lumi = 1;
		float sum = 1;
		float xs_br = 1;
		if (isMC)
		{
			if (runNumber == 284500)
				lumi = 36.1;
			if (runNumber == 300000)
				lumi = 43.2;
			if (runNumber == 310000)
				lumi = 58.5;
			if (m_mcChannelNumber == 449616 || m_mcChannelNumber == 449619 || m_mcChannelNumber == 449631 || m_mcChannelNumber == 449636)
				xs_br = 292.7236;
			if (m_mcChannelNumber == 449643 || m_mcChannelNumber == 449646 || m_mcChannelNumber == 449658 || m_mcChannelNumber == 449663)
				xs_br = 59.4776;
			if (m_mcChannelNumber == 449670 || m_mcChannelNumber == 449673 || m_mcChannelNumber == 449685 || m_mcChannelNumber == 449690)
				xs_br = 193.1544;
			sum = 10000;
		}
		double weight = lumi * xs_br / sum;

		total->Fill(mu, weight);

		//pass 1 lepton 1 photon
		if ((((int)el_pt->size() >= 1 && (*el_pt)[0] > 10.0) || ((int)mu_pt->size() >= 1 && (*mu_pt)[0] > 10.0)) && (int)ph_pt->size() >= 1 && (*ph_pt)[0] > 10.0)
			count[0] += 1;
		else
			continue;

		//trigger for electron >= 1 or muon >= 1
		bool trig_el = false;
		bool trig_mu = false;
		if (
			(runNumber < 290000 && (HLT_e24_lhmedium_L1EM20VH || HLT_e60_lhmedium || HLT_e120_lhloose)) ||
			(runNumber > 290000 && (HLT_e26_lhtight_nod0_ivarloose || HLT_e60_lhmedium_nod0 || HLT_e140_lhloose_nod0)))
			trig_el = true;

		if ((runNumber < 290000 && (HLT_mu20_iloose_L1MU15 || HLT_mu50)) ||
			(runNumber > 290000 && (HLT_mu26_ivarmedium || HLT_mu50)))
			trig_mu = true;

		if (trig_el || trig_mu)
			count[1] += 1;
		else
			continue;

		//select good electrons
		vector<int> nE;
		nE.clear();
		for (int i = 0; i < el_pt->size(); i++)
		{
			if ((*el_pt)[i] > 10 && fabs((*el_eta)[i]) < 2.47 && (fabs((*el_eta)[i]) < 1.37 || fabs((*el_eta)[i]) > 1.52))
			{
				nE.push_back(i);
			}
		}

		//select good muons
		vector<int> nM;
		nM.clear();
		for (int i = 0; i < mu_pt->size(); i++)
		{
			if ((*mu_pt)[i] > 10 && fabs((*mu_eta)[i]) < 2.7)
			{
				nM.push_back(i);
			}
		}

		//pT Trigger
		if ((trig_el && nE.size() >= 1 && (*el_pt)[nE[0]] > 27) || (trig_mu && nM.size() && (*mu_pt)[nM[0]] > 27))
			count[2] += 1;
		else
			continue;

		//select good photons
		vector<int> nP;
		nP.clear(); //nE: index of good photons
		for (int i = 0; i < ph_pt->size(); i++)
		{
			if ((*ph_pt)[i] > 10 && fabs((*ph_etas2)[i]) < 2.37 && (fabs((*ph_etas2)[i]) < 1.37 || fabs((*ph_etas2)[i]) > 1.52)) //no pt>10 in your code
			{
				nP.push_back(i);
			}
		}
		if (nP.size() < 1)
			continue;

		//barrel photon
		int flag = 0;
		for (int i = 0; i < nP.size(); i++)
		{
			if (fabs((*ph_etas2)[nP[i]]) < 1.37)
				flag++;
		}
		if (flag < 1)
			continue;
		count[3] += 1;

		//Off-Z-mass cut
		if (trig_el && nP.size() >= 1 && nE.size() == 1 && nM.size() == 0)
		{
			const double Zmass = 91.18;

			TLorentzVector ele, ph;
			ele.SetPtEtaPhiE((*el_pt)[nE[0]], (*el_eta)[nE[0]], (*el_phi)[nE[0]], (*el_E)[nE[0]]);
			ph.SetPtEtaPhiE((*ph_pt)[nP[0]], (*ph_eta)[nP[0]], (*ph_phi)[nP[0]], (*ph_E)[nP[0]]);

			TLorentzVector ele_ph;
			ele_ph = ele + ph;

			if (fabs(ele_ph.M() - Zmass) > 15)
				count[4] += 1;
			else
				continue;
		}
		else
			count[4] += 1;

		//Restriction on Met
		if (m_met <= 50)
			continue;
		count[5] += 1;

		//Timing selection
		if ((*ph_t)[nP[0]] <= 1.)
			continue;
		count[6] += 1;

		selected->Fill(mu, weight);
		//
		//Write the index of passing entries
		//			entries << jentry  << endl;
	}
	//   entries.close();

	TFile output("mu_T_1.root", "RECREATE");
	hist->Write();
	output.Close();

	//print the number of pass events after certain cut
	for (int i = 0; i < 7; i++)
	{
		cout << cutNames[i] << "\t" << count[i] << endl;
	}
}
