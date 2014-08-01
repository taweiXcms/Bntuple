#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000


const int nBins = 40;
double trkPtCut=0.9;


void Acceptance(){

  TH1D* LoopGen(TTree*,double,double);
  TH1D* LoopAccNum(TTree*,double,double);
  TH1D* LoopAccNum(TTree*,double,double);
  
  TString infnamemc="/data/bmeson/MC/nt_MixMC_20140503_Kp__TriggerMatchingMuon_EvtBase_skim.root";
  TFile *filemc = new TFile(infnamemc.Data());
  TTree *nt_mc = (TTree*) filemc->Get("ntKp");
  TTree *nt_mcgen = (TTree*)filemc->Get("ntGen");
  nt_mcgen->AddFriend(nt_mc);
  
  TH1D *hDenAcc=(TH1D*)LoopGen(nt_mcgen,10.,60.);
  TH1D *hNumAcc=(TH1D*)LoopAccNum(nt_mc,10.,60.);
  TH1D *hAcc=(TH1D*)hNumAcc->Clone();
  
  hAcc->Divide(hDenAcc);
  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(3,1);
  canvas->cd(1);
  hDenAcc->Draw();
  canvas->cd(2);
  hNumAcc->Draw();
  canvas->cd(3);
  hAcc->SetMinimum(0);
  hAcc->SetMaximum(1.);
  hAcc->Draw();
  canvas->SaveAs("canvas.eps");
  
}


TH1D* LoopGen(TTree* ntuple,double ptmin,double ptmax){

  int Run,size;
  bool cut_yvsRun,cut_pt;
  Float_t gen[NUM_BX];
  Float_t pdgId[NUM_BX];
  Float_t isSignal[NUM_BX];
  Float_t y[NUM_BX];
  Float_t pt[NUM_BX];
  
  ntuple->SetBranchAddress("size",&size);
  ntuple->SetBranchAddress("Run",&Run);
  ntuple->SetBranchAddress("gen",gen);
  ntuple->SetBranchAddress("pdgId",pdgId);
  ntuple->SetBranchAddress("isSignal",isSignal);
  ntuple->SetBranchAddress("y",y);
  ntuple->SetBranchAddress("pt",pt);

  TH1D *hPtMCGen = new TH1D("hPtMCGen","",nBins,10.,60.);

  Int_t entries = (Int_t)ntuple->GetEntries();
  cout<<"number of entries loopgen"<<entries<<endl;
  
  for (int i=0; i<entries; i++) {
    ntuple->GetEntry(i);
        
    for(int j=0;j<size;j++){
    
      cut_yvsRun=((Run<=1&&abs(y[j]+0.465)<1.93)||(Run>1&&abs(y[j]-0.465)<1.93))&&abs(pdgId[j])==521&&isSignal[j]==1;
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      if(cut_pt&&cut_yvsRun) hPtMCGen->Fill(pt[j]);
          	  
  	}//loop over candidates
  }// loop over events

  return hPtMCGen; 
}


TH1D* LoopAccNum(TTree* ntuple,double ptmin,double ptmax){

  bool cut_yvsRun,cut_pt,cut_HLT_PAMu3_v1,cut_trk1Pt,cut_mu1acc,cut_mu2acc;

  int Run,HLT_PAMu3_v1,size,Event;
  Float_t pt[NUM_BX];
  Float_t y[NUM_BX];
  Float_t trk1Pt[NUM_BX];
  Float_t gen[NUM_BX];
  
  Float_t mu1eta[NUM_BX];
  Float_t mu2eta[NUM_BX];
  Float_t mu1pt[NUM_BX];
  Float_t mu2pt[NUM_BX];
  Float_t mu1p[NUM_BX];
  Float_t mu2p[NUM_BX];

  ntuple->SetBranchAddress("Run",&Run);
  ntuple->SetBranchAddress("y",y);
  ntuple->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  ntuple->SetBranchAddress("size",&size);
  ntuple->SetBranchAddress("mu1eta",mu1eta);
  ntuple->SetBranchAddress("mu2eta",mu2eta);
  ntuple->SetBranchAddress("mu1pt",mu1pt);
  ntuple->SetBranchAddress("mu2pt",mu2pt);
  ntuple->SetBranchAddress("mu1p",mu1p);
  ntuple->SetBranchAddress("mu2p",mu2p);
  ntuple->SetBranchAddress("trk1Pt",trk1Pt);
  ntuple->SetBranchAddress("Event",&Event);
  ntuple->SetBranchAddress("pt",pt);
  ntuple->SetBranchAddress("gen",gen);

  TH1D *hPtMC = new TH1D("hPtMC","",nBins,10.,60.);

  Int_t entries = (Int_t)ntuple->GetEntries();
  
  for (int i=0; i<entries; i++) {
    ntuple->GetEntry(i);
            
    for(int j=0;j<size;j++){
    
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      if(!cut_pt) continue;
      
      cut_yvsRun=((Run<=1&&abs(y[j]+0.465)<1.93)||(Run>1&&abs(y[j]-0.465)<1.93))&&gen[j]==23333;	  
	  cut_mu1acc=(abs(mu1eta[j])<1.3&&mu1pt[j]>3.3)||(abs(mu1eta[j])>1.3&&abs(mu1eta[j])<2.2&&mu1p[j]>2.9)||(abs(mu1eta[j])>2.2&&abs(mu1eta[j])<2.4&&mu1pt[j]>0.8);
	  cut_mu2acc=(abs(mu2eta[j])<1.3&&mu2pt[j]>3.3)||(abs(mu2eta[j])>1.3&&abs(mu2eta[j])<2.2&&mu2p[j]>2.9)||(abs(mu2eta[j])>2.2&&abs(mu2eta[j])<2.4&&mu2pt[j]>0.8);
	  cut_trk1Pt=(trk1Pt[j]>trkPtCut);
	  
      if(cut_yvsRun&&cut_mu1acc&&cut_mu2acc&&cut_trk1Pt){
              
        hPtMC->Fill(pt[j]);
      }  
  	}//loop over candidates  
  }// loop over events
  return hPtMC; 
}
