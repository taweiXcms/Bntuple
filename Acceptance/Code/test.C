#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000

void test(){

  TString selmcgen="abs(y)<2.4&&abs(pdgId)==521&&isSignal==1";
  TH1D *hYGenFirstRuns = new TH1D("hYGenFirstRuns","hYGenFirstRuns",100,-10,10);
  TH1D *hYGenLastRuns = new TH1D("hYGenLastRuns","hYGenLastRuns",100,-10,10);


  TString infnamemc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Kp.root";
  TFile *filemc = new TFile(infnamemc.Data());
  TTree *nt_mcgen = (TTree*)filemc->Get("ntGen");
  TTree *nt = (TTree*)filemc->Get("ntKp");
  
  
  Float_t y[NUM_BX];
  Float_t pt[NUM_BX];
  Float_t pdgId[NUM_BX];
  Float_t isSignal[NUM_BX];

  int Run,size;
  
  nt_mcgen->SetBranchAddress("y",y);
  nt->SetBranchAddress("Run",&Run);
  nt_mcgen->SetBranchAddress("size",&size);
  nt_mcgen->SetBranchAddress("pdgId",&pdgId);
  nt_mcgen->SetBranchAddress("isSignal",&isSignal);

  
  Int_t entries = (Int_t)nt_mcgen->GetEntries();
  cout<<"QUI"<<nt<<endl;
    
    
    for (int i=0; i<entries; i++) {
    nt_mcgen->GetEntry(i);        
    nt->GetEntry(i);        
    for(int j=0;j<size;j++){
    
      if(Run<=1&&isSignal[j]==1&&pdgId[j]==521)hYGenFirstRuns->Fill(y[j]);
      if(Run>1&&isSignal[j]==1&&pdgId[j]==521)hYGenLastRuns->Fill(y[j]);
  }}
    
  
  TCanvas*canv=new TCanvas("canv","canv",600,600);
  canv->cd();
  hYGenLastRuns->SetLineColor(2);
  hYGenFirstRuns->Draw();
  hYGenLastRuns->Draw("same");

  canv->SaveAs("canv.pdf");

}