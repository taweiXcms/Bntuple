#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <stdio.h>

//### new2 : without j/psi rapidity and pt cut
void TnPHisto_MC_new3() {

TFile* hout = new TFile("TNPHisto_TagMu3_TrgProbeMu3_MC_new3.root","RECREATE");

Double_t MuPtBins[8] = {0.0,1.5,3.0,4.5,6.0,9.0,20.0,30.0};

// etabin 1 : -2.4,-0.8, etabin 2 : -0.8,0.8, etabin 3 : 0.8,1.46
TH1D* hMuTrgetabin1 = new TH1D("hMuTrgetabin1",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);
TH1D* hMuTrgetabin2 = new TH1D("hMuTrgetabin2",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);
TH1D* hMuTrgetabin3 = new TH1D("hMuTrgetabin3",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);

TH1D* hMuIDetabin1 = new TH1D("hMuIDetabin1",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);
TH1D* hMuIDetabin2 = new TH1D("hMuIDetabin2",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);
TH1D* hMuIDetabin3 = new TH1D("hMuIDetabin3",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);

TH1D* hMuTrketabin1 = new TH1D("hMuTrketabin1",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);
TH1D* hMuTrketabin2 = new TH1D("hMuTrketabin2",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);
TH1D* hMuTrketabin3 = new TH1D("hMuTrketabin3",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);


Double_t MuTrgetabin1[7] = {0.0000, 0.004, 0.477, 0.775, 0.83, 0.857, 0.86};
Double_t MuTrgetabin1Err[7] = {0.0005, 0.001, 0.010, 0.007, 0.01, 0.009, 0.05};
Double_t MuTrgetabin2[7] = {0.00000, 0.00000, 0.27, 0.72, 0.957, 0.958, 0.90};
Double_t MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.01, 0.01, 0.006, 0.009, 0.05};
Double_t MuTrgetabin3[7] = {0.0000,0.006,0.5060,0.80,0.87,0.845,0.7};
Double_t MuTrgetabin3Err[7] = {0.0006,0.002,0.0009,0.01,0.01,0.003,0.1};

Double_t MuIDetabin1[7] = {0.43,0.797,0.928,0.969,0.968,0.984,0.93};
Double_t MuIDetabin1Err[7] = {0.01,0.006,0.006,0.005,0.007,0.004,0.07};
Double_t MuIDetabin2[7] = {0.00000,0.00000,0.804,0.967,0.980,0.979,0.97};
Double_t MuIDetabin2Err[7] = {0.00000,0.00000,0.010,0.006,0.005,0.007,0.02};
Double_t MuIDetabin3[7] = {0.46,0.794,0.913,0.971,0.989,0.993,1.00};
Double_t MuIDetabin3Err[7] = {0.01,0.009,0.007,0.007,0.006,0.008,0.05};

Double_t MuTrketabin1[7] = {0.0,0.87,0.93,0.94,0.91,0.97,1.00};
Double_t MuTrketabin1Err[7] = {0.8,0.02,0.01,0.01,0.01,0.01,0.04};
Double_t MuTrketabin2[7] = {0.00,1.0,0.94,0.95,0.953,0.95,0.96};
Double_t MuTrketabin2Err[7] = {0.09,0.6,0.02,0.01,0.009,0.01,0.05};
Double_t MuTrketabin3[7] = {1.0,0.88,0.91,0.92,0.94,0.93,1.00};
Double_t MuTrketabin3Err[7] = {0.2,0.02,0.01,0.02,0.01,0.03,0.07};

for(Int_t i=1;i<8;i++) {
	hMuTrgetabin1->SetBinContent(i,MuTrgetabin1[i-1]);
	hMuTrgetabin2->SetBinContent(i,MuTrgetabin2[i-1]);
	hMuTrgetabin3->SetBinContent(i,MuTrgetabin3[i-1]);
	hMuIDetabin1->SetBinContent(i,MuIDetabin1[i-1]);
	hMuIDetabin2->SetBinContent(i,MuIDetabin2[i-1]);
	hMuIDetabin3->SetBinContent(i,MuIDetabin3[i-1]);
	hMuTrketabin1->SetBinContent(i,MuTrketabin1[i-1]);
	hMuTrketabin2->SetBinContent(i,MuTrketabin2[i-1]);
	hMuTrketabin3->SetBinContent(i,MuTrketabin3[i-1]);
	hMuTrgetabin1->SetBinError(i,MuTrgetabin1Err[i-1]);
	hMuTrgetabin2->SetBinError(i,MuTrgetabin2Err[i-1]);
	hMuTrgetabin3->SetBinError(i,MuTrgetabin3Err[i-1]);
	hMuIDetabin1->SetBinError(i,MuIDetabin1Err[i-1]);
	hMuIDetabin2->SetBinError(i,MuIDetabin2Err[i-1]);
	hMuIDetabin3->SetBinError(i,MuIDetabin3Err[i-1]);
	hMuTrketabin1->SetBinError(i,MuTrketabin1Err[i-1]);
	hMuTrketabin2->SetBinError(i,MuTrketabin2Err[i-1]);
	hMuTrketabin3->SetBinError(i,MuTrketabin3Err[i-1]);
}

hout->Write();
hout->Close();
}
