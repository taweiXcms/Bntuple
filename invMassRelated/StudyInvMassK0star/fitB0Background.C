#include "utilities.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;
double setparam3=0.03;
double fixparam2=0.04;

const int nBins = 3;
double ptBins[nBins+1] = {10,15,20,60};


TString weight = "27.493+pt*(-0.218769)";
TString cutconfig="newcutopt8";

TFile*finput=new TFile("ResultsLoopBzero/B0outputBkgCutInv10.root");


void fitB0Background(){
  
  TString iNPOld="6.71675e+00*Gaus(x,5.30142e+00,8.42680e-02)/(sqrt(2*3.14159)*8.42680e-02)+4.06744e+01*Gaus(x,5.00954e+00,8.11305e-02)/(sqrt(2*3.14159)*8.11305e-02)+5.99974e-01*(2.376716*Gaus(x,5.640619,0.095530)/(sqrt(2*3.14159)*0.095530)+3.702342*Gaus(x,5.501706,0.046222)/(sqrt(2*3.14159)*0.046222))+1.31767e-01*(61.195688*Gaus(x,5.127566,0.087439)/(sqrt(2*3.14159)*0.087439)+58.943919*Gaus(x,5.246471,0.041983)/(sqrt(2*3.14159)*0.041983))";
  TString iNPNew="[1]*Gaus(x,[2],[3])/(sqrt(2*3.14159)*[3])+4.06744e+01*Gaus(x,5.00954e+00,8.11305e-02)/(sqrt(2*3.14159)*8.11305e-02)+5.99974e-01*(2.376716*Gaus(x,5.640619,0.095530)/(sqrt(2*3.14159)*0.095530)+3.702342*Gaus(x,5.501706,0.046222)/(sqrt(2*3.14159)*0.046222))+1.31767e-01*(61.195688*Gaus(x,5.127566,0.087439)/(sqrt(2*3.14159)*0.087439)+58.943919*Gaus(x,5.246471,0.041983)/(sqrt(2*3.14159)*0.041983))";

  TF1 *fNPOld = new TF1("fNPOld","[0]*("+iNPOld+")");
  TF1 *fNPNew = new TF1("fNPNew","[0]*("+iNPNew+")");
 
  TCanvas *cbkg= new TCanvas("cbkg","",600,600);
  TH1D *hMassBkg = (TH1D*)finput->Get("hMassBkg");
  cbkg->cd();
  hMassBkg->Draw("ep");
  hMassBkg->Fit("fNPNew","q","",5.,6);
  
  fNPNew->Draw("same");
  cbkg->SaveAs("testcanvas.pdf");
  
}
