#include "utilities.h"

#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;

//svmithi2
TString inputdata="/data/bmeson/MC/nt_BoostedMC_20140717_NonPromptJpsi.root";
//TString inputdata="/data/bmeson/data/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Kp.root";

//tk pt, chi2
TString cut="abs(y)<2.4&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";
//TString cut="abs(y)<2.4&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";

TString seldata_2y=Form("%s",cut.Data());
TString selmc=Form("gen==23333&&%s",cut.Data());
TString selmcgen="abs(y)<2.4&&abs(pdgId)==521&&isSignal==1";

TString weight = "(27.493+pt*(-0.218769))";

void clean0(TH1D *h){
  for (int i=1;i<=h->GetNbinsX();i++){
    if (h->GetBinContent(i)==0) h->SetBinError(i,1);
  }
}

TF1 *fitSignal(TTree *ntMC,double ptmin,double ptmax){   
   //cout<<cut.Data()<<endl;
   TCanvas *cSignal= new TCanvas("cSignal","",600,600);
   TH1D *hMC = new TH1D("hMC","",50,5,6);

   //   TString iNP="7.26667e+00*Gaus(x,5.10472e+00,2.63158e-02)/(sqrt(2*3.14159)*2.63158e-02)+4.99089e+01*Gaus(x,4.96473e+00,9.56645e-02)/(sqrt(2*3.14159)*9.56645e-02)+3.94417e-01*(3.74282e+01*Gaus(x,5.34796e+00,3.11510e-02)+1.14713e+01*Gaus(x,5.42190e+00,1.00544e-01))";
   TF1 *f = new TF1("f1","[0]*([5]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[5])*Gaus(x,[1],[6])/(sqrt(2*3.14159)*[6]))+[3]+[4]*x");
   ntMC->Project("hMC","mass",Form("%s&&pt>%f&&pt<%f",selmc.Data(),ptmin,ptmax));

   f->SetParLimits(4,-1000,0);
   f->SetParLimits(2,0.01,0.05);
   f->SetParLimits(6,0.01,0.05);
   f->SetParLimits(5,0,1);

   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->SetParameter(6,setparam3);
   f->FixParameter(1,fixparam1);

   hMC->Fit("f1","q","",5,6);
   hMC->Fit("f1","q","",5,6);
   f->ReleaseParameter(1);
   hMC->Fit("f1","L q","",5,6);
   hMC->Fit("f1","L q","",5,6);
   hMC->Fit("f1","L q","",5,6);
   hMC->Fit("f1","L m","",5,6);

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1("backgroundSignal","[0]+[1]*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1("fmassSignal","[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(5),f->GetParameter(6));
   cout<<"[0]Signal: "<<f->GetParameter(0)<<endl;
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

   hMC->SetMarkerStyle(24);
   hMC->SetStats(0);
   hMC->Draw("e");
   hMC->SetXTitle("M_{B} (GeV/c^{2})");
   hMC->SetYTitle("Entries / (20 MeV/c^{2})");
   hMC->GetXaxis()->CenterTitle();
   hMC->GetYaxis()->CenterTitle();
   hMC->SetTitleOffset(1.,"Y");
   hMC->SetAxisRange(0,hMC->GetMaximum()*1.2,"Y");

   background->Draw("same");   

   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   double yield = mass->Integral(5,6)/0.02;

   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
   leg->AddEntry(hMC,"CMS Preliminary","");
   leg->AddEntry(hMC,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(hMC,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(hMC,"B meson","");
   leg2->AddEntry(hMC,Form("N_{B}=%.0f", yield),"");
   leg2->Draw();

   cSignal->SaveAs("NonpromptBplus/BMassSignal.gif");

   return mass;
}


TF1 *fitNP(TTree* nt,double ptmin,double ptmax){   

   TCanvas *cNP= new TCanvas("cNP","",600,600);
   TH1D *hNP = new TH1D("hNP","",50,5,6);

   TString iNP="7.26667*Gaus(x,5.10472e+00,2.63158e-02)/(sqrt(2*3.14159)*2.63158e-02)+4.99089e+01*Gaus(x,4.96473e+00,9.56645e-02)/(sqrt(2*3.14159)*9.56645e-02)+3.94417e-01*(3.74282e+01*Gaus(x,5.34796e+00,3.11510e-02)+1.14713e+01*Gaus(x,5.42190e+00,1.00544e-01))";
   TF1 *f = new TF1("fNP","[0]+[1]*x+[2]*("+iNP+")");
   
   nt->Project("hNP","mass",Form("%s&&pt>%f&&pt<%f&&gen!=23333",seldata_2y.Data(),ptmin,ptmax));   
   //ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata_2y.Data(),ptmin,ptmax));   
   clean0(hNP);
   hNP->Draw();
   f->SetParLimits(1,-1000,0);
   f->SetParLimits(2,0,1000);

   hNP->Fit("fNP","q","",5,6);
   hNP->Fit("fNP","q","",5,6);

   hNP->SetMarkerSize(0.8);
   hNP->SetMarkerStyle(20);

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1("backgroundNP","[0]+[1]*x");
   background->SetParameter(0,f->GetParameter(0));
   background->SetParameter(1,f->GetParameter(1));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1("massNP","[0]*("+iNP+")");
   //cout<<"miaomiaomiao   "<<f->GetParameter(2)<<endl;
   mass->SetParameter(0,f->GetParameter(2));
   cout<<"[0]NP: "<<f->GetParameter(2)<<endl;
   mass->SetLineColor(kGreen+1);
   mass->SetLineStyle(3);
   mass->SetFillStyle(3004);
   mass->SetRange(5,6);

   hNP->SetMarkerStyle(24);
   hNP->SetStats(0);
   hNP->Draw("e");
   hNP->SetXTitle("M_{B} (GeV/c^{2})");
   hNP->SetYTitle("Entries / (20 MeV/c^{2})");
   hNP->GetXaxis()->CenterTitle();
   hNP->GetYaxis()->CenterTitle();
   hNP->SetTitleOffset(1.,"Y");
   hNP->SetAxisRange(0,hNP->GetMaximum()*1.5,"Y");

   background->Draw("same");   
   mass->Draw("same");
   f->Draw("same");

   double yield = mass->Integral(5,6)/0.02;

   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
   leg->AddEntry(hNP,"CMS Preliminary","");
   leg->AddEntry(hNP,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(hNP,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(hNP,"Non-prompt","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Real Non-prompt","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(hNP,"B meson","");
   leg2->AddEntry(hNP,Form("N_{B}=%.0f", yield),"");
   leg2->Draw();

   cNP->SaveAs("NonpromptBplus/BMassNP.gif");

   return mass;
}



void fitBnp(TString infname="",TString infnameMC="", bool doweight=1)
{

  if (doweight==0) weight="1";
  if (infname=="") infname=inputdata.Data();
  if (infnameMC=="") infnameMC=inputmc.Data();

  TFile *infMC = new TFile(infnameMC.Data());
  TTree *ntMC = (TTree*)infMC->Get("ntKp");
  TFile* inf = new TFile(infname.Data());
  TTree *nt = (TTree*)inf->Get("ntKp");
  /*  
  const int nBins = 1;
  double ptBins[nBins+1] = {10,60};
    
  TF1 *fSignal = fitSignal(ntMC,ptBins[0],ptBins[1]);
  double yieldSignal = fSignal->Integral(5,6)/0.02;
  TF1 *fNP = fitNP(nt,ptBins[0],ptBins[1]);
  double yieldNP = fNP->Integral(5,6)/0.02;

  cout<<"Signal: "<<yieldSignal<<endl;
  cout<<"Non-prompt: "<<yieldNP<<endl;
  cout<<"Ratio: "<<yieldSignal/yieldNP<<endl;
  */
    
  cout<<endl;
  cout<<"Calculating the # of events ..."<<endl;
  cout<<endl;
  
  int nESignal=0, nENP=0, N;
  TTree* ntMCgen = (TTree*)infMC->Get("ntGen");
  TTree* ntgen = (TTree*)inf->Get("ntGen");
  nESignal = ntMCgen->GetEntries();
  N = ntgen->GetEntries();
  Int_t gensize;
  Float_t genpdgId[4096],genisSignal[4096];
  int i,j,flag;
  ntgen->SetBranchAddress("size",&gensize);
  ntgen->SetBranchAddress("pdgId",genpdgId);
  ntgen->SetBranchAddress("isSignal",genisSignal);
  for(i=0;i<N;i++)
    {
      if(i%100000==0) cout<<i<<" / "<<N<<endl;
      flag=0;
      ntgen->GetEntry(i);
      for(j=0;j<gensize;j++)
	{
	  if(genisSignal[j]==1)
	    {
	      flag++;
	      break;
	    }
	}
      if(flag>0) nENP++;
    }
  cout<<"# of Event Signal: "<<nESignal<<endl;
  cout<<"# of Event NP: "<<nENP<<endl;
  
}
