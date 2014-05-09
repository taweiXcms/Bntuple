#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <stdio.h>

void TnPHisto_DATA_new1() {

TFile* hout = new TFile("TNPHisto_TagMu3_TrgProbeMu3_DATA_new1.root","RECREATE");

Double_t MuPtBins[8] = {0.0,1.5,3.0,4.5,6.0,9.0,20.0,30.0};

// etabin 1 : -2.4,-0.8, etabin 2 : -0.8,0.8, etabin 3 : 0.8,2.4
TH1D* hMuTrgetabin1 = new TH1D("hMuTrgetabin1",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);
TH1D* hMuTrgetabin2 = new TH1D("hMuTrgetabin2",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);
TH1D* hMuTrgetabin3 = new TH1D("hMuTrgetabin3",";#mu p_{T} (GeV/c);Single #mu trigger efficiency",7,MuPtBins);

TH1D* hMuIDetabin1 = new TH1D("hMuIDetabin1",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);
TH1D* hMuIDetabin2 = new TH1D("hMuIDetabin2",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);
TH1D* hMuIDetabin3 = new TH1D("hMuIDetabin3",";#mu p_{T} (GeV/c);Single #mu ID efficiency",7,MuPtBins);

TH1D* hMuTrketabin1 = new TH1D("hMuTrketabin1",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);
TH1D* hMuTrketabin2 = new TH1D("hMuTrketabin2",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);
TH1D* hMuTrketabin3 = new TH1D("hMuTrketabin3",";#mu p_{T} (GeV/c);Single #mu tracking efficiency",7,MuPtBins);


Double_t MuTrgetabin1[7] = {0.0001, 0.0070, 0.574, 0.855, 0.895, 0.887, 0.86};
Double_t MuTrgetabin1Err[7] = {0.0002, 0.0006, 0.003, 0.003, 0.003, 0.005, 0.03};
Double_t MuTrgetabin2[7] = {0.00000, 0.00000, 0.370, 0.810, 0.968, 0.969, 0.99};
Double_t MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.003, 0.003, 0.002, 0.003, 0.01};
Double_t MuTrgetabin3[7] = {0.00000,0.0066,0.657,0.893,0.929,0.926,0.97};
Double_t MuTrgetabin3Err[7] = {0.00005,0.0005,0.003,0.003,0.003,0.005,0.02};

Double_t MuIDetabin1[7] = {0.668,0.883,0.949,0.981,0.986,0.987,0.983};
Double_t MuIDetabin1Err[7] = {0.009,0.003,0.002,0.001,0.001,0.002,0.007};
Double_t MuIDetabin2[7] = {0.00000,0.00000,0.853,0.976,0.985,0.984,0.999999999};
Double_t MuIDetabin2Err[7] = {0.00000,0.00000,0.003,0.001,0.001,0.002,0.0000000003};
Double_t MuIDetabin3[7] = {0.499,0.805,0.942,0.978,0.986,0.993,0.97};
Double_t MuIDetabin3Err[7] = {0.006,0.003,0.002,0.002,0.002,0.002,0.02};

Double_t MuTrketabin1[7] = {0.95,0.939,0.953,0.958,0.962,0.952,0.92};
Double_t MuTrketabin1Err[7] = {0.10,0.004,0.003,0.003,0.004,0.007,0.08};
Double_t MuTrketabin2[7] = {0.0,0.0,0.929,0.965,0.966,0.971,0.95};
Double_t MuTrketabin2Err[7] = {0.5,0.7,0.007,0.003,0.003,0.004,0.02};
Double_t MuTrketabin3[7] = {1.0,0.951,0.958,0.959,0.965,0.968,0.9};
Double_t MuTrketabin3Err[7] = {0.1,0.006,0.003,0.003,0.004,0.009,0.1};

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
