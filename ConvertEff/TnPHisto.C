#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <stdio.h>

void TnPHisto() {

TFile* hout = new TFile("TNPHisto_TagMu3_TrgProbeMu3.root","RECREATE");

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


Double_t MuTrgetabin1[7] = {0.00000, 0.0045, 0.446, 0.754, 0.820, 0.834, 0.79};
Double_t MuTrgetabin1Err[7] = {0.000006, 0.0002, 0.002, 0.002, 0.002, 0.003, 0.02};
Double_t MuTrgetabin2[7] = {0.00000, 0.00000, 0.284, 0.725, 0.947, 0.957, 0.911};
Double_t MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.002, 0.002, 0.001, 0.002, 0.009};
Double_t MuTrgetabin3[7] = {0.00000,0.0034,0.465,0.807,0.882,0.890,0.86};
Double_t MuTrgetabin3Err[7] = {0.00007,0.0003,0.003,0.003,0.003,0.004,0.02};

Double_t MuIDetabin1[7] = {0.533,0.876,0.976,0.984,0.984,0.988,0.991};
Double_t MuIDetabin1Err[7] = {0.005,0.002,0.001,0.001,0.001,0.002,0.006};
Double_t MuIDetabin2[7] = {0.22,0.676,0.833,0.9636,0.9762,0.9788,0.981};
Double_t MuIDetabin2Err[7] = {0.01,0.003,0.001,0.0008,0.0007,0.0009,0.003};
Double_t MuIDetabin3[7] = {0.383,0.807,0.970,0.979,0.979,0.987,0.98};
Double_t MuIDetabin3Err[7] = {0.004,0.002,0.002,0.002,0.002,0.003,0.01};

Double_t MuTrketabin1[7] = {0.78,0.903,0.927,0.938,0.954,0.958,0.95};
Double_t MuTrketabin1Err[7] = {0.03,0.003,0.002,0.003,0.003,0.004,0.02};
Double_t MuTrketabin2[7] = {0.0,0.3,0.936,0.954,0.959,0.966,0.981};
Double_t MuTrketabin2Err[7] = {0.2,0.3,0.004,0.002,0.002,0.002,0.007};
Double_t MuTrketabin3[7] = {1.0,0.938,0.932,0.940,0.948,0.961,0.93};
Double_t MuTrketabin3Err[7] = {0.1,0.005,0.003,0.003,0.003,0.004,0.05};

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
