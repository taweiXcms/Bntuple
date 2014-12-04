#include <math.h>
#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TString.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegendEntry.h"
#include "TPad.h"
using namespace std;

  TString   Bs_particle="Bs";
  const int Bs_nbins=1;
  Double_t  Bs_xbins[Bs_nbins]={35};
  Double_t  Bs_exl[Bs_nbins]={25};
  Double_t  Bs_exl0[Bs_nbins]={0.};
  Double_t  Bs_yPercSigmapPbSystTotHigh[Bs_nbins]={0.199};
  Double_t  Bs_yPercSigmapPbSystTotLow[Bs_nbins]={0.199};
  Double_t  Bs_commonErrorP = TMath::Sqrt(0.22*0.22);
  Double_t  Bs_commonErrorN = TMath::Sqrt(0.24*0.24);
  Double_t  Bs_FFsysterror=0.6/10.4;
  Double_t  Bs_tagandprobcorrection[Bs_nbins]={1.041};

  TString   B0_particle="Bzero";
  const int B0_nbins=3;
  Double_t  B0_xbins[B0_nbins]={12.5,17.5,40};
  Double_t  B0_exl[B0_nbins]={2.5,2.5,20};
  Double_t  B0_exl0[B0_nbins]={0.,0.,0.};
  Double_t  B0_yPercSigmapPbSystTotHigh[B0_nbins]={0.230,0.218,0.214};
  Double_t  B0_yPercSigmapPbSystTotLow[B0_nbins]={0.230,0.218,0.214};
  Double_t  B0_commonErrorP = TMath::Sqrt(0.0555*0.0555);
  Double_t  B0_commonErrorN = TMath::Sqrt(0.0555*0.0555);
  Double_t  B0_FFsysterror=0.7/40.2;
  Double_t  B0_tagandprobcorrection[B0_nbins]={1.052,1.032,1.016};

  TString   Bp_particle="Bplus";
  const int Bp_nbins=5;
  Double_t  Bp_xbins[Bp_nbins]={12.5,17.5,22.5,27.5,45.};
  Double_t  Bp_exl[Bp_nbins]={2.5,2.5,2.5,2.5,15.};
  Double_t  Bp_exl0[Bp_nbins]={0.,0.,0.,0.,0.};
  Double_t  Bp_yPercSigmapPbSystTotHigh[Bp_nbins]={0.163,0.150,0.146,0.142,0.140};
  Double_t  Bp_yPercSigmapPbSystTotLow[Bp_nbins]={0.163,0.150,0.146,0.142,0.140};
  Double_t  Bp_commonErrorP = TMath::Sqrt(0.0445*0.0445);
  Double_t  Bp_commonErrorN = TMath::Sqrt(0.0445*0.0445);
  Double_t  Bp_FFsysterror=0.7/40.1;
  Double_t  Bp_tagandprobcorrection[Bp_nbins]={1.049,1.030,1.019,1.012,1.006};

void makeMultiPanelCanvas(TCanvas*& canv, 
const Int_t columns,
const Int_t rows,
bool  setlogy,
const Float_t leftOffset= 0.,
const Float_t bottomOffset= 0.,
const Float_t leftMargin= 0.16,
const Float_t bottomMargin= 0.16,
const Float_t edge=0.05
);

void NuclearModification(
  TString  particle,
  const int      nbins,
  Double_t xbins[],
  Double_t exl[],
  Double_t exl0[],
  Double_t yPercSigmapPbSystTotHigh[],
  Double_t yPercSigmapPbSystTotLow[],
  Double_t commonErrorP,
  Double_t commonErrorN,
  Double_t FFsysterror,
  Double_t tagandprobcorrection[],
  TCanvas *canvasSigma,
  TCanvas *canvasRpA,
  int PadNum
){
  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  TFile*filePPReference=new TFile(Form("../../../fonll/output%s.root",particle.Data()));  
  TGraphAsymmErrors*gaeBplusReference=(TGraphAsymmErrors*)filePPReference->Get(Form("gaeSigmaDecay%s",particle.Data()));
  gaeBplusReference->SetName(Form("gae%sReference",particle.Data()));
  
  TFile*filepPb=new TFile(Form("../Results%s/Sigma%s.root",particle.Data(),particle.Data()));
  TH1F*hSigmapPbStat=(TH1F*)filepPb->Get("hPtSigma");  
  TH1F*hPt=(TH1F*)filepPb->Get("hPt");
  TH1F*hEff=(TH1F*)filepPb->Get("hEff");
  
  double scalingfactor=1e-6;
  double yvalue,xvalue,yerrorhigh,yerrorlow;
  
  for (int i=0;i<nbins;i++){
    hSigmapPbStat->SetBinContent(i+1,scalingfactor*hSigmapPbStat->GetBinContent(i+1));
    hSigmapPbStat->SetBinError(i+1,scalingfactor*hSigmapPbStat->GetBinError(i+1));
    
    yvalue=-1.;
    xvalue=-1.;
    yerrorhigh=-1.;
    yerrorlow=-1.;
    
    gaeBplusReference->GetPoint(i,xvalue,yvalue);
    yerrorhigh=gaeBplusReference->GetEYhigh()[i];
    yerrorlow=gaeBplusReference->GetEYlow()[i];
  
    gaeBplusReference->SetPoint(i,xvalue,yvalue*scalingfactor);
    gaeBplusReference->SetPointEYhigh(i,yerrorhigh*scalingfactor);
    gaeBplusReference->SetPointEYlow(i,yerrorlow*scalingfactor);

  } 
  
  
  for (int i=0;i<nbins;i++){
    hSigmapPbStat->SetBinContent(i+1,(1./tagandprobcorrection[i])*hSigmapPbStat->GetBinContent(i+1));
    hSigmapPbStat->SetBinError(i+1,(1./tagandprobcorrection[i])*hSigmapPbStat->GetBinError(i+1));
  
  } 
  Double_t yRefPP[nbins];                        //value y reference
  Double_t xRefPP[nbins];                        //value x reference
  Double_t yPPsystFONLLhigh[nbins];              //y err syst FONLL high
  Double_t yPPsystFONLLlow[nbins];               //y err syst FONLL low
  Double_t yPercPPsystFONLLhigh[nbins];          //y percentuale err syst FONLL high
  Double_t yPercPPsystFONLLlow[nbins];           //y percentuale err syst FONLL low
    
  Double_t ySigmapPb[nbins];                     //value y pPb 
  Double_t xSigmapPb[nbins];                     //value x pPb
  Double_t ySigmapPbStat[nbins];                 //y err stat pPb
  Double_t yPercSigmapPbStat[nbins];             //y err stat pPb
  
  Double_t yFONLL[nbins];                        //1
  Double_t yRpA[nbins];                          //value y RpA 
  Double_t yRpAStat[nbins];                      //y err stat RpA 
  Double_t yRpAsystFONLLhigh[nbins];             //y err syst FONLL RpA high
  Double_t yRpAsystFONLLlow[nbins];              //y err syst FONLL RpA lzow
  Double_t yPercRpAsystFONLLhigh[nbins];         //y percentuale err syst FONLL RpA high
  Double_t yPercRpAsystFONLLlow[nbins];          //y percentuale err syst FONLL RpA low
    
  Double_t ySigmapPbSystTotHigh[nbins];              //y percentuale err syst pPb TOT
  Double_t ySigmapPbSystTotLow[nbins];              //y percentuale err syst pPb TOT

  Double_t yPercRpPbSystTotHigh[nbins];          //y percentuale err syst RpPb TOT
  Double_t yPercRpPbSystTotLow[nbins];          //y percentuale err syst RpPb TOT
  
  Double_t yRpPbSystTotHigh[nbins];              //y percentuale err syst RpPb TOT
  Double_t yRpPbSystTotLow[nbins];              //y percentuale err syst RpPb TOT

  
  double x,y;
  for (Int_t i=0;i<nbins;i++) {
    gaeBplusReference->GetPoint(i,xRefPP[i],yRefPP[i]);
    yPPsystFONLLhigh[i]=gaeBplusReference->GetEYhigh()[i];
    yPPsystFONLLlow[i]=gaeBplusReference->GetEYlow()[i];
    yPercPPsystFONLLhigh[i]=yPPsystFONLLhigh[i]/yRefPP[i];
    yPercPPsystFONLLlow[i]=yPPsystFONLLlow[i]/yRefPP[i];
    yPercPPsystFONLLhigh[i]=TMath::Sqrt(yPercPPsystFONLLhigh[i]*yPercPPsystFONLLhigh[i]+FFsysterror*FFsysterror);
    yPercPPsystFONLLlow[i]=TMath::Sqrt(yPercPPsystFONLLlow[i]*yPercPPsystFONLLlow[i]+FFsysterror*FFsysterror);
    
  }
  
  for(Int_t i=0;i<nbins;i++) {
    ySigmapPb[i]=hSigmapPbStat->GetBinContent(i+1);
    ySigmapPbStat[i]=hSigmapPbStat->GetBinError(i+1);
    yPercSigmapPbStat[i]=ySigmapPbStat[i]/ySigmapPb[i];
    ySigmapPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*ySigmapPb[i];
    ySigmapPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*ySigmapPb[i];
  }
  
  for(Int_t i=0;i<nbins;i++) {
    yRpA[i]=ySigmapPb[i]/yRefPP[i];
    yRpAStat[i]=ySigmapPbStat[i]/yRefPP[i];
    yFONLL[i]=yRpA[i];
    yPercRpAsystFONLLhigh[i]=(yPercPPsystFONLLlow[i]/(1-yPercPPsystFONLLlow[i]));
    yPercRpAsystFONLLlow[i]=(yPercPPsystFONLLhigh[i]/(1+yPercPPsystFONLLhigh[i]));
    yRpAsystFONLLhigh[i]=yPercRpAsystFONLLhigh[i]*yRpA[i];
    yRpAsystFONLLlow[i]=yPercRpAsystFONLLlow[i]*yRpA[i];

    yRpPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*yRpA[i];
    yRpPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*yRpA[i];   
  }
  
  TGraphAsymmErrors *gSigmasyst = new TGraphAsymmErrors(nbins,xbins,ySigmapPb,exl,exl,ySigmapPbSystTotLow,ySigmapPbSystTotHigh);
  gSigmasyst->SetTitle("Sigma syst uncertainty from pPb");
  gSigmasyst->SetMarkerColor(1);
  gSigmasyst->SetLineColor(1);
  gSigmasyst->SetLineWidth(2);   
  gSigmasyst->SetMarkerStyle(21);
  gSigmasyst->SetMarkerColor(1);

  TGraphAsymmErrors *gSigmastat = new TGraphAsymmErrors(nbins,xbins,ySigmapPb,exl,exl,ySigmapPbStat,ySigmapPbStat);
  gSigmastat->SetTitle("Sigma stat uncertainty from pPb");
  gSigmastat->SetMarkerColor(1);
  gSigmastat->SetLineColor(1);
  gSigmastat->SetLineWidth(1);   
  gSigmastat->SetMarkerStyle(21);
  gSigmastat->SetMarkerColor(1);
  
  gSigmastat->SetFillColor(0);
  gSigmastat->SetFillStyle(0);
  gSigmastat->SetFillStyle(0);
 
  canvasSigma->cd(PadNum);
  canvasSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasSigma->SetFillColor(0);
  canvasSigma->SetBorderMode(0);
  canvasSigma->SetBorderSize(2);
  canvasSigma->SetLeftMargin(0.1451613);
  canvasSigma->SetRightMargin(0.05443548);
  canvasSigma->SetTopMargin(0.08474576);
  canvasSigma->SetBottomMargin(0.1165254);
  canvasSigma->SetFrameBorderMode(0);
  canvasSigma->SetFrameBorderMode(0);
  canvasSigma->SetLogy();
  
  TH2F* hempty=new TH2F("hempty","", 10, 0.1, 65., 10., 0.1, 1e3);    
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  //if(particle=="Bplus") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{+}) (pb GeV^{-1}c)");
  //if(particle=="Bzero") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{0}) (pb GeV^{-1}c)");
  //if(particle=="Bs") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B_{s}) (pb GeV^{-1}c)");
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetYaxis()->SetTitle("d#sigma / dp_{T}( #mub GeV^{-1}c)");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.3);
  hempty->GetXaxis()->SetTitleSize(0.055);
  hempty->GetYaxis()->SetTitleSize(0.055);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.055);
  hempty->GetYaxis()->SetLabelSize(0.055);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
  
  gaeBplusReference->SetMarkerColor(1);
  gaeBplusReference->SetMarkerStyle(21);  
  gaeBplusReference->SetFillColor(5);
  gaeBplusReference->SetFillStyle(1001);
  gaeBplusReference->SetLineColor(1);
  gaeBplusReference->SetLineWidth(5);
  
  
  gSigmastat->SetMarkerColor(1);
  gSigmastat->SetLineColor(1);
  gSigmastat->SetLineWidth(2);   
  gSigmastat->SetMarkerStyle(21);
  gSigmastat->SetMarkerColor(1);

  gaeBplusReference->Draw("2same");
  gSigmastat->SetFillColor(0);
  gSigmastat->Draw("epsame");
  
  //coord.  for legend for sigma in the B+ pannel 
  TLegend *legendSigma=new TLegend(0.468298,0.7045614,0.7678185,0.8757895,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  
  TBox *c = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  c->SetLineColor(5);
  c->SetFillColor(5);
  c->Draw();

  TLegendEntry *ent_SigmapPb=legendSigma->AddEntry(gSigmastat,"pPb","pf");
  ent_SigmapPb->SetTextFont(42);
  ent_SigmapPb->SetLineColor(1);
  ent_SigmapPb->SetMarkerColor(1);

  TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(c,"FONLL pp ref.","f");
  ent_Sigmapp->SetTextFont(42);
  ent_Sigmapp->SetLineColor(5);
  ent_Sigmapp->SetMarkerColor(1);

  gSigmasyst->SetFillColor(0);
  gSigmasyst->SetFillStyle(0);
  
  gSigmasyst->SetFillColor(0);
  gSigmasyst->SetFillStyle(0);
  gSigmasyst->Draw("2same");
  
  TBox *d = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  d->SetLineColor(1);
  d->SetFillColor(0);
  d->Draw();
  
  if(PadNum==0 || PadNum==1){
    legendSigma->Draw("same");
    
    TLatex * tlatex1=new TLatex(0.21,0.88801268,"CMS");
    tlatex1->SetNDC();
    tlatex1->SetTextColor(1);
    tlatex1->SetTextFont(42);
    tlatex1->SetTextSize(0.045);
    tlatex1->Draw();
    
    TLatex * tlatexlumi=new TLatex(0.471371,0.88801268,"L = 34.8 nb^{-1} (pPb 5.02 TeV)");
    tlatexlumi->SetNDC();
    tlatexlumi->SetTextColor(1);
    tlatexlumi->SetTextFont(42);
    tlatexlumi->SetTextSize(0.045);
    tlatexlumi->Draw();
  }

  double xpos=0.8528226;
  double ypos=0.6849894;
  
  TString mypar;
  if(particle=="Bplus") mypar="B^{+}";
  if(particle=="Bzero") mypar="B^{0}";
  if(particle=="Bs") mypar="B_{s}";  
  
  TLatex * tlatex3=new TLatex(xpos,ypos,mypar.Data());
  tlatex3->SetNDC();
  tlatex3->SetTextColor(1);
  tlatex3->SetTextFont(42);
  tlatex3->SetTextSize(0.06);
  tlatex3->Draw();
  
  TGraphAsymmErrors *gRpAstat = new TGraphAsymmErrors(nbins,xbins,yRpA,exl0,exl0,yRpAStat,yRpAStat);
  gRpAstat->SetTitle("RpA stat uncertainty from pPb");
  gRpAstat->SetMarkerStyle(21);
  gRpAstat->SetMarkerColor(1);
  gRpAstat->SetLineColor(1);
  gRpAstat->SetLineWidth(2);  
  gRpAstat->SetFillColor(0);


  TGraphAsymmErrors *gRpAsyst = new TGraphAsymmErrors(nbins,xbins,yRpA,exl,exl,yRpPbSystTotLow,yRpPbSystTotHigh);
  gRpAsyst->SetTitle("RpA syst uncertainty from pPb");
  gRpAsyst->SetName("gRpAsyst");
  gRpAsyst->SetFillColor(0);
  gRpAsyst->SetMarkerSize(0);
  gRpAsyst->SetLineColor(1);
  gRpAsyst->SetLineWidth(2);
  gRpAsyst->SetFillStyle(0);
  
  TGraphAsymmErrors *gRpAsystFONLL = new TGraphAsymmErrors(nbins,xbins,yFONLL,exl,exl,yRpAsystFONLLlow,yRpAsystFONLLhigh);
  gRpAsystFONLL->SetTitle("RpA syst uncertainty from FONLL reference");
  gRpAsystFONLL->SetFillColor(5);
  gRpAsystFONLL->SetLineColor(5);//kAzure-3);
  gRpAsystFONLL->SetMarkerColor(4);//kAzure-3);


  canvasRpA->cd(PadNum);
  canvasRpA->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasRpA->SetFillColor(0);
  canvasRpA->SetBorderMode(0);
  canvasRpA->SetBorderSize(2);
  canvasRpA->SetLeftMargin(0.1451613);
  canvasRpA->SetRightMargin(0.05443548);
  canvasRpA->SetTopMargin(0.08474576);
  canvasRpA->SetBottomMargin(0.1165254);
  canvasRpA->SetFrameBorderMode(0);
  canvasRpA->SetFrameBorderMode(0);
  
  TLegend *legendRpA=new TLegend(0.22,0.66,0.51,0.83,"");
  legendRpA->SetBorderSize(0);
  legendRpA->SetLineColor(0);
  legendRpA->SetFillColor(0);
  legendRpA->SetFillStyle(1001);
  legendRpA->SetTextFont(42);
  legendRpA->SetTextSize(0.045);

  hempty=new TH2F("hempty","",10,0.1, 62. ,10.,0.,2.5);  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}");
  hempty->GetXaxis()->SetTitleOffset(1.3);
  hempty->GetYaxis()->SetTitleOffset(1.1);
  hempty->GetXaxis()->SetTitleSize(0.055);
  hempty->GetYaxis()->SetTitleSize(0.055);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.055);
  hempty->GetYaxis()->SetLabelSize(0.055);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
  
  TLine *l = new TLine(0,1, 65.,1);
  l->SetLineStyle(2);

  gRpAsystFONLL->Draw("2same");
  gRpAsyst->Draw("2esame");
  gRpAstat->Draw("psame");
  
  
  TBox *a = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  a->SetLineColor(1);
  a->SetFillColor(0);
  a->Draw();

  TBox *b = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  b->SetLineColor(1);
  b->SetFillColor(kGray);
  b->Draw();

  TLegendEntry *ent_RpAstat=legendRpA->AddEntry(gRpAstat,"R^{FONLL}_{pA}","pf");
  ent_RpAstat->SetTextFont(42);
  ent_RpAstat->SetLineColor(2);
  ent_RpAstat->SetMarkerColor(2);
  
  TLegendEntry *ent_RpAsystData=legendRpA->AddEntry(b,"Syst. L+BR","f");
  ent_RpAsystData->SetTextFont(42);
  ent_RpAsystData->SetLineColor(2);
  ent_RpAsystData->SetMarkerColor(2);
  
  TLegendEntry *ent_RpAsystFONLL=legendRpA->AddEntry(gRpAsystFONLL,"Syst. err. from FONLL pp ref.","f");
  ent_RpAsystFONLL->SetTextFont(42);
  ent_RpAsystFONLL->SetLineColor(5);
  ent_RpAsystFONLL->SetLineStyle(1);
  ent_RpAsystFONLL->SetMarkerColor(5);
 
  if(PadNum==1||PadNum==0){
    legendRpA->Draw();

    TLatex * tlatex4=new TLatex(0.21,0.88801268,"CMS");
    tlatex4->SetNDC();
    tlatex4->SetTextColor(1);
    tlatex4->SetTextFont(42);
    tlatex4->SetTextSize(0.045);
    tlatex4->Draw();
    
    TLatex * tlatex2=new TLatex(0.471371,0.88801268,"L = 34.8 nb^{-1} (pPb 5.02 TeV)");
    tlatex2->SetNDC();
    tlatex2->SetTextColor(1);
    tlatex2->SetTextFont(42);
    tlatex2->SetTextSize(0.045);
   tlatex2->Draw();
  }
   
  tlatex3->Draw();

  TFile *fout=new TFile(Form("../Results%s/fileRpA%s.root",particle.Data(),particle.Data()),"recreate");  
  fout->cd();
  gSigmasyst->SetName("gSigmasyst");
  gSigmasyst->Write();
  gaeBplusReference->Write();
  hSigmapPbStat->Write();
}

void NuclearModification_DrawOnSamePad(){
  TCanvas *cSigma=new TCanvas("canvasSigma","canvasSigma",1150,400);
  TCanvas *cRpA=new TCanvas("canvasRpA","canvasRpA",1150,400);
  makeMultiPanelCanvas(cSigma, 3, 1, true);
  makeMultiPanelCanvas(cRpA, 3, 1, false);
  NuclearModification(
    Bp_particle,
    Bp_nbins,
    Bp_xbins,
    Bp_exl,
    Bp_exl0,
    Bp_yPercSigmapPbSystTotHigh,
    Bp_yPercSigmapPbSystTotLow,
    Bp_commonErrorP,
    Bp_commonErrorN,
    Bp_FFsysterror,
    Bp_tagandprobcorrection,
    cSigma,
    cRpA,
	1
  );
  NuclearModification(
    B0_particle,
    B0_nbins,
    B0_xbins,
    B0_exl,
    B0_exl0,
    B0_yPercSigmapPbSystTotHigh,
    B0_yPercSigmapPbSystTotLow,
    B0_commonErrorP,
    B0_commonErrorN,
    B0_FFsysterror,
    B0_tagandprobcorrection,
    cSigma,
    cRpA,
	2
  );
  NuclearModification(
    Bs_particle,
    Bs_nbins,
    Bs_xbins,
    Bs_exl,
    Bs_exl0,
    Bs_yPercSigmapPbSystTotHigh,
    Bs_yPercSigmapPbSystTotLow,
    Bs_commonErrorP,
    Bs_commonErrorN,
    Bs_FFsysterror,
    Bs_tagandprobcorrection,
    cSigma,
    cRpA,
	3
  );
  cSigma->SaveAs(Form("../ResultsAll/canvasSigma.pdf"));  
  cRpA->SaveAs(Form("../ResultsAll/canvasRpA.pdf"));  
}

void makeMultiPanelCanvas(TCanvas*& canv, 
const Int_t columns,
const Int_t rows,
bool  setlogy,
const Float_t leftOffset,
const Float_t bottomOffset,
const Float_t leftMargin,
const Float_t bottomMargin,
const Float_t edge
) 
{
  if (canv==0) {
    cout << "makeMultiPanelCanvas","Got null canvas.";
    return;
  }
  canv->Clear();
 //  Float_t pad_width  = 0.;
//   Float_t   pad_height = 0.;
//    Float_t charheight = 0.05;
//   Float_t textsize= 0.05;
  TPad* pad[columns][rows];
  Float_t Xlow[columns];
  Float_t Xup[columns];
  Float_t Ylow[rows];
  Float_t Yup[rows];
  Float_t PadWidth = (1.0-leftOffset)/((1.0/(1.0-leftMargin)) + (1.0/(1.0-edge))+(Float_t)columns-2.0);
  Float_t PadHeight = (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) + (1.0/(1.0-edge))+(Float_t)rows-2.0);
  Xlow[0] = leftOffset;
  Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
  Xup[columns-1] = 1;
  Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);
  Yup[0] = 1;
  Ylow[0] = 1.0-PadHeight/(1.0-edge);
  Ylow[rows-1] = bottomOffset;
  Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);
  for(Int_t i=1;i<columns-1;i++) {
    Xlow[i] = Xup[0] + (i-1)*PadWidth;
    Xup[i] = Xup[0] + (i)*PadWidth;
  }
  Int_t ct = 0;
  for(Int_t i=rows-2;i>0;i--) {
    Ylow[i] = Yup[rows-1] + ct*PadHeight;
    Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
    ct++;
  }
  TString padName;
  for(Int_t i=0;i<columns;i++) {
    for(Int_t j=0;j<rows;j++) {
      canv->cd();
      padName = Form("p_%d_%d",i,j);
      pad[i][j] = new TPad(padName.Data(),padName.Data(),
      Xlow[i],Ylow[j],Xup[i],Yup[j]);
      if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
      else pad[i][j]->SetLeftMargin(0);
      if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
      else pad[i][j]->SetRightMargin(0);
      if(j==0) pad[i][j]->SetTopMargin(edge);
      else pad[i][j]->SetTopMargin(0);
      if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
      else pad[i][j]->SetBottomMargin(0);
      pad[i][j]->Draw();
      pad[i][j]->cd();
      pad[i][j]->SetNumber(columns*j+i+1);
      if(setlogy) pad[i][j]->SetLogy();
    }
  }
}


      
