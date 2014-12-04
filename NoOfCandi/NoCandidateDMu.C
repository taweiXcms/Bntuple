#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <iostream>
#include <TMath.h>
#include "NoCandidate.h"

TString inputdata="/afs/cern.ch/work/w/wangj/public/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/afs/cern.ch/work/w/wangj/public/nt_20140801_mixed_fromQMBFinder_Kp.root";

TString cut="((HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e-01)&&mu1pt>1.5&&mu2pt>1.5";
TString particle="B^{+}";

void dimuonLoop(float ptmin, float ptmax, float ymin, float ymax)
{
  TFile *infMC = new TFile(inputmc);
  TTree *ntMC = (TTree*) infMC->Get("ntKp");
  TFile *infData = new TFile(inputdata);
  TTree *ntData = (TTree*) infData->Get("ntKp");

  TH1D* hMC = new TH1D("hMC","",7,0.5,4.0);
  TH1D* hData = new TH1D("hData","",7,0.5,4.0);

  setBranch(ntMC);

  int j=0,k=0;
  int nentries = ntMC->GetEntries();
  double realsize=0;
  int dimu05=0,dimu10=0,dimu15=0,dimu20=0,dimu25=0,dimu30=0,dimu35=0;

  TCanvas *c = new TCanvas("c","",600,600);
  for(j=0;j<nentries;j++)
    {
      if(j%100000==0) cout<<"Processing: "<<j<<" / "<<nentries<<endl;
      ntMC->GetEntry(j);
      for(k=0;k<size;k++)
	{
	  if(pt[k]>ptmin&&pt[k]<ptmax&&y[k]>ymin&&y[k]<ymax&&(HLT_PAMu3_v1)&&abs(mumumass[k]-3.096916)<0.15&&mass[k]>5&&mass[k]<6&&trk1Pt[k]>0.9&&chi2cl[k]>1.32e-02&&(d0[k]/d0Err[k])>3.41&&cos(dtheta[k])>-3.46e-01&&gen[k]==23333)
	    {
	      realsize++;
	      /*
	      if(abs(mumumass[k]-3.096916)<0.05) dimu05++;
	      if(abs(mumumass[k]-3.096916)<0.10) dimu10++;
	      if(abs(mumumass[k]-3.096916)<0.15) dimu15++;
	      if(abs(mumumass[k]-3.096916)<0.20) dimu20++;
	      if(abs(mumumass[k]-3.096916)<0.25) dimu25++;
	      if(abs(mumumass[k]-3.096916)<0.30) dimu30++;
	      if(abs(mumumass[k]-3.096916)<0.35) dimu35++;
	      */
	      if(mu1pt[k]>0.5&&mu2pt[k]>0.5) dimu05++;
	      if(mu1pt[k]>1.0&&mu2pt[k]>1.0) dimu10++;
	      if(mu1pt[k]>1.5&&mu2pt[k]>1.5) dimu15++;
	      if(mu1pt[k]>2.0&&mu2pt[k]>2.0) dimu20++;
	      if(mu1pt[k]>2.5&&mu2pt[k]>2.5) dimu25++;
	      if(mu1pt[k]>3.0&&mu2pt[k]>3.0) dimu30++;
	      if(mu1pt[k]>3.5&&mu2pt[k]>3.5) dimu35++;
	    }
	}
    }

  cout<<endl;
  hMC->SetBinContent(1,1-dimu05/realsize);  cout<<"MC 0.5: "<<1-dimu05/realsize<<endl;
  hMC->SetBinContent(2,1-dimu10/realsize);  cout<<"MC 1.0: "<<1-dimu10/realsize<<endl;
  hMC->SetBinContent(3,1-dimu15/realsize);  cout<<"MC 1.5: "<<1-dimu15/realsize<<endl;
  hMC->SetBinContent(4,1-dimu20/realsize);  cout<<"MC 2.0: "<<1-dimu20/realsize<<endl;
  hMC->SetBinContent(5,1-dimu25/realsize);  cout<<"MC 2.5: "<<1-dimu25/realsize<<endl;
  hMC->SetBinContent(6,1-dimu30/realsize);  cout<<"MC 3.0: "<<1-dimu30/realsize<<endl;
  hMC->SetBinContent(7,1-dimu35/realsize);  cout<<"MC 3.5: "<<1-dimu35/realsize<<endl;
  cout<<endl;

  setBranch(ntData);  
  TCanvas *c1 = new TCanvas("c1","",600,600);

  int nentriesData = ntData->GetEntries();
  double realsizeData=0;
  double dimu05Data=0,dimu10Data=0,dimu15Data=0,dimu20Data=0,dimu25Data=0,dimu30Data=0,dimu35Data=0;  

  for(j=0;j<nentriesData;j++)
    {
      if(j%5000000==0) cout<<"Processing: "<<j<<" / "<<nentriesData<<endl;
      ntData->GetEntry(j);
      for(k=0;k<size;k++)
	{
	  if(pt[k]>ptmin&&pt[k]<ptmax&&y[k]>ymin&&y[k]<ymax&&(HLT_PAMu3_v1)&&abs(mumumass[k]-3.096916)<0.15&&mass[k]>5&&mass[k]<6&&trk1Pt[k]>0.9&&chi2cl[k]>1.32e-02&&(d0[k]/d0Err[k])>3.41&&cos(dtheta[k]) >-3.46e-01&&abs(mass[k]-5.279)<0.04)
	    {
	      realsizeData++;
	      /*	      
	      if(abs(mumumass[k]-3.096916)<0.05) dimu05Data++;
	      if(abs(mumumass[k]-3.096916)<0.10) dimu10Data++;
	      if(abs(mumumass[k]-3.096916)<0.15) dimu15Data++;
	      if(abs(mumumass[k]-3.096916)<0.20) dimu20Data++;
	      if(abs(mumumass[k]-3.096916)<0.25) dimu25Data++;
	      if(abs(mumumass[k]-3.096916)<0.30) dimu30Data++;
	      if(abs(mumumass[k]-3.096916)<0.35) dimu35Data++;
	      */
	      if(mu1pt[k]>0.5&&mu2pt[k]>0.5) dimu05Data++;
	      if(mu1pt[k]>1.0&&mu2pt[k]>1.0) dimu10Data++;
	      if(mu1pt[k]>1.5&&mu2pt[k]>1.5) dimu15Data++;
	      if(mu1pt[k]>2.0&&mu2pt[k]>2.0) dimu20Data++;
	      if(mu1pt[k]>2.5&&mu2pt[k]>2.5) dimu25Data++;
	      if(mu1pt[k]>3.0&&mu2pt[k]>3.0) dimu30Data++;
	      if(mu1pt[k]>3.5&&mu2pt[k]>3.5) dimu35Data++;	      

	    }
	}
    }

  cout<<endl;
  hData->SetBinContent(1,1-dimu05Data/realsizeData);  cout<<"Data 0.5: "<<1-dimu05Data/realsizeData<<endl;
  hData->SetBinContent(2,1-dimu10Data/realsizeData);  cout<<"Data 1.0: "<<1-dimu10Data/realsizeData<<endl;
  hData->SetBinContent(3,1-dimu15Data/realsizeData);  cout<<"Data 1.5: "<<1-dimu15Data/realsizeData<<endl;
  hData->SetBinContent(4,1-dimu20Data/realsizeData);  cout<<"Data 2.0: "<<1-dimu20Data/realsizeData<<endl;
  hData->SetBinContent(5,1-dimu25Data/realsizeData);  cout<<"Data 2.5: "<<1-dimu25Data/realsizeData<<endl;
  hData->SetBinContent(6,1-dimu30Data/realsizeData);  cout<<"Data 3.0: "<<1-dimu30Data/realsizeData<<endl;
  hData->SetBinContent(7,1-dimu35Data/realsizeData);  cout<<"Data 3.5: "<<1-dimu35Data/realsizeData<<endl;
  cout<<endl;

  int m=0;

  hData->SetXTitle("#mu p_{T} larger than (GeV)");
  hData->SetYTitle("Probability of losing candidate");
  hData->SetTitleOffset(1.5,"Y");
  if(hData->GetMaximum()>hMC->GetMaximum()) hData->SetMaximum(hData->GetMaximum()*1.2);
  else hData->SetMaximum(hMC->GetMaximum()*1.2);
  
  hData->SetLineColor(kBlue+1);
  hData->SetFillStyle(1001);
  hData->SetFillColor(kBlue-9);
  hData->SetLineWidth(3);
  hData->SetStats(0);
  
  hMC->SetLineColor(kRed);
  hMC->SetFillStyle(3004);
  hMC->SetFillColor(kRed);
  hMC->SetLineWidth(3);
  hMC->SetStats(0);
  
  hData->Draw();
  hMC->Draw("same");
  
  TLegend *legi = new TLegend(0.13,0.72,0.33,0.84);
  legi->AddEntry(hData,"data","f");
  legi->AddEntry(hMC,"MC","f");
  legi->SetBorderSize(0);
  legi->SetFillStyle(0);
  legi->Draw("same");
  TLegend *leg1i = new TLegend(0.20,0.7,0.50,0.9);
  leg1i->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1i->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1i->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1i->SetBorderSize(0);
  leg1i->SetFillStyle(0);
  leg1i->Draw("same");
  
  c1->SaveAs("CandidateResult/Bplus_candidates_compare_mupt.pdf");

}

void NoCandidateDMu()
{
  dimuonLoop(10,60,-2.4,2.4);
  //dimuonLoop(10.,60.,yBins[i],yBins[i+1],i+1);
}
