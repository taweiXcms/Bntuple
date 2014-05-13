#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <stdio.h>

//### new2 : without j/psi rapidity and pt cut
//### new4 : woth j/psi 3GeV pt cut for prompt embedded J/psi MC
void TnPHisto_MC_new4() {

TFile* hout = new TFile("TNPHisto_TagMu3_TrgProbeMu3_MC_new4.root","RECREATE");

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

Double_t MuTrgetabin1[7] = {0.000, 0.007, 0.56, 0.75, 0.76, 0.92, 1.00};
Double_t MuTrgetabin1Err[7] = {0.005, 0.005, 0.04, 0.05, 0.06, 0.08, 1.00};
Double_t MuTrgetabin2[7] = {0.00000, 0.00000, 0.28, 0.74, 1.00, 0.92, 1.00};
Double_t MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.04, 0.05, 0.01, 0.08, 1.00};
Double_t MuTrgetabin3[7] = {0.000,0.004,0.51,0.93,0.86,1.00,1.0};
Double_t MuTrgetabin3Err[7] = {0.004,0.003,0.04,0.03,0.03,0.02,1.0};

Double_t MuIDetabin1[7] = {0.32,0.80,0.87,0.98,0.98,1.00,1.0};
Double_t MuIDetabin1Err[7] = {0.03,0.02,0.03,0.02,0.02,0.05,1.0};
Double_t MuIDetabin2[7] = {0.00000,0.00000,0.79,1.000,1.00,0.92,1.0};
Double_t MuIDetabin2Err[7] = {0.00000,0.00000,0.04,0.008,0.02,0.07,1.0};
Double_t MuIDetabin3[7] = {0.47,0.82,0.93,1.000,1.00,1.00,1.0};
Double_t MuIDetabin3Err[7] = {0.04,0.02,0.02,0.006,0.01,0.04,1.0};

Double_t MuTrketabin1[7] = {0.7,0.92,0.98,0.92,0.94,1.00,1.0};
Double_t MuTrketabin1Err[7] = {0.2,0.04,0.05,0.04,0.06,0.04,0.7};
Double_t MuTrketabin2[7] = {0.00000,1.0,1.00,1.00,0.960676,1.00,1.0};
Double_t MuTrketabin2Err[7] = {0.00000,0.2,0.05,0.01,0.000009,0.05,1.0};
Double_t MuTrketabin3[7] = {1.0,0.97,0.89,0.93,0.89,1.00,1.0};
Double_t MuTrketabin3Err[7] = {0.2,0.04,0.03,0.05,0.07,0.05,1.0};

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
