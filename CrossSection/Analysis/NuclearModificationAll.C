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
Double_t  Bs_yPercSigmapPbSystTotHigh[Bs_nbins]={0.212};
Double_t  Bs_yPercSigmapPbSystTotLow[Bs_nbins]={0.212};
Double_t  Bs_commonErrorP = TMath::Sqrt(0.22*0.22+0.035*0.035);
Double_t  Bs_commonErrorN = TMath::Sqrt(0.24*0.24+0.035*0.035);
Double_t  Bs_FFsysterror=0.6/10.4;
Double_t  Bs_tagandprobcorrection[Bs_nbins]={1.041};

TString   B0_particle="Bzero";
const int B0_nbins=3;
Double_t  B0_xbins[B0_nbins]={12.5,17.5,40};
Double_t  B0_exl[B0_nbins]={2.5,2.5,20};
Double_t  B0_exl0[B0_nbins]={0.,0.,0.};
Double_t  B0_yPercSigmapPbSystTotHigh[B0_nbins]={0.178,0.174,0.172};
Double_t  B0_yPercSigmapPbSystTotLow[B0_nbins]={0.178,0.174,0.172};
Double_t  B0_commonErrorP = TMath::Sqrt(0.035*0.035+0.046*0.046);
Double_t  B0_commonErrorN = TMath::Sqrt(0.035*0.035+0.046*0.046);
Double_t  B0_FFsysterror=0.7/40.2;
Double_t  B0_tagandprobcorrection[B0_nbins]={1.052,1.032,1.016};

TString   Bp_particle="Bplus";
const int Bp_nbins=5;
Double_t  Bp_xbins[Bp_nbins]={12.5,17.5,22.5,27.5,45.};
Double_t  Bp_exl[Bp_nbins]={2.5,2.5,2.5,2.5,15.};
Double_t  Bp_exl0[Bp_nbins]={0.,0.,0.,0.,0.};
Double_t  Bp_yPercSigmapPbSystTotHigh[Bp_nbins]={0.143,0.137,0.136,0.134,0.134};
Double_t  Bp_yPercSigmapPbSystTotLow[Bp_nbins]={0.143,0.137,0.136,0.134,0.134};
Double_t  Bp_commonErrorP = TMath::Sqrt(0.035*0.035+0.031*0.031);
Double_t  Bp_commonErrorN = TMath::Sqrt(0.035*0.035+0.031*0.031);
Double_t  Bp_FFsysterror=0.7/40.1;
Double_t  Bp_tagandprobcorrection[Bp_nbins]={1.049,1.030,1.019,1.012,1.006};



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
		Double_t tagandprobcorrection[]
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

	gSigmasyst->SetFillColor(0);
	gSigmasyst->SetFillStyle(0);

	gSigmasyst->SetFillColor(0);
	gSigmasyst->SetFillStyle(0);
	gSigmasyst->Draw("2same");


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

	TFile *fout=new TFile(Form("../Results%s/fileRpA%s.root",particle.Data(),particle.Data()),"recreate");  
	fout->cd();
	gSigmasyst->SetName("gSigmasyst");
	gSigmasyst->Write();
	gaeBplusReference->Write();
	hSigmapPbStat->Write();
}
