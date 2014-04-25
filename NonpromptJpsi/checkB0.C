#include "TFile.h"
#include "TTree.h"
#include <iostream>


void checkB0(){
 
  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");
  
   TH1F*hproject=new TH1F("hproject","hproject",1000,5,6);
   TString cut_kpi="abs(y+0.465)<1.93&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01"; 
   TString seldata_kpi=Form("abs(y+0.465)<1.93&&%s",cut_kpi.Data());
  
  TH1F*h=new TH1F("h","h",1000,5,6);
  Float_t mumumass[4096];
  Float_t y[4096];
  Float_t mass[4096];
  Float_t trk1Pt[4096];
  Float_t trk2Pt[4096];
  Float_t chi2cl[4096];
  Float_t d0[4096];
  Float_t d0Err[4096];
  Float_t dtheta[4096];
  Float_t tktkmass[4096];
  Int_t isbestchi2[4096];
  Int_t HLT_PAMu3_v1[4096];

  nt->SetBranchAddress("y",&y);
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  nt->SetBranchAddress("mumumass",&mumumass);
  nt->SetBranchAddress("mass",&mass);
  nt->SetBranchAddress("isbestchi2",&isbestchi2);
  nt->SetBranchAddress("trk1Pt",&trk1Pt);
  nt->SetBranchAddress("trk2Pt",&trk2Pt);
  nt->SetBranchAddress("chi2cl",&chi2cl);
  nt->SetBranchAddress("d0Err",&d0Err);
  nt->SetBranchAddress("d0",&d0);
  nt->SetBranchAddress("dtheta",&dtheta);
  nt->SetBranchAddress("tktkmass",&tktkmass);

  Int_t nentries = (Int_t)nt->GetEntries();

  for (Int_t i=0; i<nentries; i++) {
    nt->GetEntry(i);

    bool cut1=(abs(y[0]+0.465)<1.93);
    bool cut2=(HLT_PAMu3_v1[0]==1);
    bool cut3=(TMath::Abs(mumumass[0]-3.096916));
    bool cut4=(mass[0]>5.);
    bool cut5=(mass[0]<6.);
    bool cut6=(isbestchi2[0]==0);
    bool cut7=(trk1Pt[0]>0.7);
    bool cut8=(trk2Pt[0]>0.7);
    bool cut9=(chi2cl[0]>1.65e-01);
    bool cut10=((d0[0]/d0Err[0])>4.16);
    bool cut11=(cos(dtheta[0])>7.50e-01);
    bool cut12=(TMath::Abs(tktkmass[0]-0.89594)<2.33e-01);
    
    if(cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11&&cut12){

    h->Fill(mass[0]);
    cout<<y[0]<<endl;
}
  }//end for
  h->Draw();
  TCanvas*canvas=new TCanvas("canvas","canvas",800,400);
  canvas->Divide(2,1);
  canvas->cd(1);
    h->Draw();
canvas->cd(2);
    hproject->Draw("same");

}//end macro
