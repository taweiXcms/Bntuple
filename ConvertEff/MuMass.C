#include <iostream>                                                                                                                                                                                         
#include <utility>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TNtuple.h>
TString inputdata_kp="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kp_TriggerMatchingMuon.root";
TString inputdata_kstar="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kstar_TriggerMatchingMuon.root";
TString inputdata_phi="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Phi_TriggerMatchingMuon.root";
TString selmcgen="(abs(y+0.465)<1.93)&&isSignal>=1&&pt>10&&pt<60";
TLegend *myLegend(double x1,double y1,double x2, double y2);
void MuMass(){
  TFile *inf1 = new TFile(inputdata_kp.Data());
  TFile *inf2 = new TFile(inputdata_kstar.Data());
  TFile *inf3 = new TFile(inputdata_phi.Data());
  TH1F *h11 = new TH1F("h11","",50,0,30);
  TH1F *h12 = new TH1F("h12","",50,0,30);
  TH1F *h21 = new TH1F("h21","",50,0,30);
  TH1F *h22 = new TH1F("h22","",50,0,30);
  TH1F *h31 = new TH1F("h31","",50,0,30);
  TH1F *h32 = new TH1F("h32","",50,0,30);
  TTree *nt1;
  TTree *nt2;
  TTree *nt3;
  nt1 = (TTree*)inf1->Get("ntGen");                                                                                                                                                                    
  nt2 = (TTree*)inf2->Get("ntGen");                                                                                                                                                                    
  nt3 = (TTree*)inf3->Get("ntGen");                                                                                                                                                                    

  nt1->Project("h11","mu1pt",selmcgen);
  nt1->Project("h12","mu2pt",selmcgen);
  nt2->Project("h21","mu1pt",selmcgen);
  nt2->Project("h22","mu2pt",selmcgen);
  nt3->Project("h31","mu1pt",selmcgen);
  nt3->Project("h32","mu2pt",selmcgen);
  h11->Add(h12);
  h21->Add(h22);
  h31->Add(h32);

  h11->Scale(1/h11->Integral());
  h21->Scale(1/h21->Integral());
  h31->Scale(1/h31->Integral());

  TCanvas *c= new TCanvas("c","",600,600);                                   
  c->cd();
  h11->SetMarkerColor(2);
  h21->SetMarkerColor(3);
  h31->SetMarkerColor(4);
  h11->Draw("p");
  h21->Draw("same p");
  h31->Draw("same p");

  TLegend *leg = myLegend(0.50,0.5,0.86,0.92);                                             
  leg->AddEntry(h11,"Bp ","p");
  leg->AddEntry(h21,"B0 ","p");
  leg->AddEntry(h31,"Bs ","p");
  leg->Draw();
  c->SaveAs("MuMass.pdf");
}
TLegend *myLegend(double x1,double y1,double x2, double y2)                                                                                                                                                 
{
    TLegend *leg = new TLegend(x1,y1,x2,y2);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    return leg;
}
