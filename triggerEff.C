#include <TGraphAsymmErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCut.h>
#include <TCanvas.h>
#include "utilities.h"


TGraphAsymmErrors *calcEff(TH1* h1, TH1* h2,char *hName="hEff")
{
   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors();
   gEfficiency->BayesDivide(h2,h1);
   return gEfficiency;
}

TGraphAsymmErrors *triggerEff(TTree *t,TCut sel, TCut cut)
{
   TH1F *h = new TH1F("h","",20,0,50);
   TH1F *hCut = new TH1F("hCut","",20,0,50);
   t->Draw("pt>>h",sel);
   t->Draw("pt>>hCut",sel&&cut);
   TGraphAsymmErrors *g = calcEff(h,hCut);
   
   return g;

}

void triggerEff(char *infname,char *type = "ntKp")
{
   TFile *inf= new TFile(infname);
   TTree *t = (TTree*) inf->Get(type);
   TCut sel="gen==22233&&abs(y+0.465)<1.93"; 
   
   TGraphAsymmErrors *gDoubleMuOpen = triggerEff(t,sel,"HLT_PAL1DoubleMuOpen_v1");
   TGraphAsymmErrors *gMu3 = triggerEff(t,sel,"HLT_PAMu3_v1");
   TGraphAsymmErrors *gMu3OrOpen = triggerEff(t,sel,"HLT_PAMu3_v1||HLT_PAL1DoubleMuOpen_v1");
   
   TCanvas *c = new TCanvas("c","",600,600);
     
   TH1F *htemp = new TH1F("htemp","",20,0,50);
   htemp->Draw();

   gDoubleMuOpen->Draw("p same");
   
   gMu3->SetLineColor(2);
   gMu3->SetMarkerColor(2);
   gMu3->Draw("p same");
   
   gMu3OrOpen->SetLineColor(4);
   gMu3OrOpen->SetMarkerColor(4);
   gMu3OrOpen->Draw("p same");
   
   htemp->SetXTitle("Reconstructed B p_{T} (GeV/c)");
   htemp->SetYTitle("Trigger Efficiency");
   
   TLegend *leg = myLegend(0.4,0.2,0.9,0.5);
   leg->AddEntry(gDoubleMuOpen,"HLT_PAL1DoubleMuOpen","pl");
   leg->AddEntry(gMu3,"HLT_PAMu3","pl");
   leg->AddEntry(gMu3OrOpen,"HLT_PAMu3||DoubleMuOpen","pl");
   leg->Draw();
   
}
