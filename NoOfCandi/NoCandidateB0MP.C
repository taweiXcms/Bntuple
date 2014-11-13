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
TString inputmc="/afs/cern.ch/work/w/wangj/public/nt_20140801_mixed_fromQMBFinder_Kstar.root";

TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>9.94e-02&&(d0/d0Err)>6.08&&cos(dtheta)>7.93e-01&&abs(tktkmass-0.89594)<0.10&&tktkmassKK>1.04&&mu1pt>1.5&&mu2pt>1.5"; 
TString particle="B^{0}";

void dimuonLoop(float ptmin, float ptmax, float ymin, float ymax)
{
  TFile *infMC = new TFile(inputmc);
  TTree *ntMC = (TTree*) infMC->Get("ntKstar");
  TFile *infData = new TFile(inputdata);
  TTree *ntData = (TTree*) infData->Get("ntKstar");

  setBranch(ntMC);
  setBranch(ntData);

  int bins=10;
  TH1D* hMCTruth = new TH1D("hMCTruth","",bins-1,1,bins);
  TH1D* hMCBase = new TH1D("hMCBase","",bins-1,1,bins);
  TH1D* hMC = new TH1D("hMC","",bins-1,1,bins);
  TH1D* hData = new TH1D("hData","",bins-1,1,bins);
  TH1D* hSigregMC = new TH1D("hSigregMC","",bins-1,1,bins);
  TH1D* hSigregData = new TH1D("hSigregData","",bins-1,1,bins);
  
  int j=0,k=0;
  int nentries = ntMC->GetEntries();
  int realsize=0,realsizeSigreg=0;
  int ifmatching=0;

  TCanvas *c = new TCanvas("c","",600,600);
  for(j=0;j<nentries;j++)
    {
      if(j%100000==0) cout<<"Processing: "<<j<<" / "<<nentries<<endl;
      ntMC->GetEntry(j);
      realsize=0;
      realsizeSigreg=0;
      ifmatching=0;
      for(k=0;k<size;k++)
	{
	  if(pt[k]>ptmin&&pt[k]<ptmax&&y[k]>ymin&&y[k]<ymax&&(HLT_PAMu3_v1)&&abs(mumumass[k]-3.096916)<0.15&&mass[k]>5&&mass[k]<6&&trk1Pt[k]>0.7&&trk2Pt[k]>0.7&&chi2cl[k]>9.94e-02&&(d0[k]/d0Err[k])>6.08&&cos(dtheta[k])>7.93e-01&&abs(tktkmass[k]-0.89594)<0.10&&mu1pt[k]>1.5&&mu2pt[k]>1.5)
	    {
	      realsize++;
	      if((gen[k]==23333||gen[k]==41000) && isbestchi2[k]==1)
		{
		  ifmatching=1;
		}
	      if(abs(mass[k]-5.279)<0.04)
		{
		  realsizeSigreg++;
		}
	    }
	}
      
      if(realsize!=0)
	{
	  hMCBase->Fill(realsize);
	  hMC->Fill(realsize);
	  if(ifmatching!=0)
	    {
	      hMCTruth->Fill(realsize);
	    }
	}
      if(realsizeSigreg!=0)
	{
	  hSigregMC->Fill(realsizeSigreg);
	}
    }
  
  hMCBase->Sumw2();
  hMCTruth->Sumw2();
  hMCTruth->Divide(hMCBase);
  hMCTruth->Sumw2();

  hMCTruth->SetMinimum(0);
  hMCTruth->SetMaximum(3.);
  hMCTruth->SetMarkerStyle(8);
  hMCTruth->SetStats(0);
  hMCTruth->SetMaximum(3.3);
  hMCTruth->SetMinimum(0);

  hMCTruth->SetXTitle("# of candidate");
  hMCTruth->SetYTitle("Matching Probability");
  hMCTruth->SetTitleOffset(1.5,"Y");
  
  hMCTruth->Draw("lep");
  
  TLegend *lege = new TLegend(0.11,0.75,0.50,0.9);
  lege->AddEntry(hMCTruth,"Matching prob","lep");
  lege->SetBorderSize(0);
  lege->SetFillStyle(0);
  lege->Draw("same");
  TLegend *leg1e = new TLegend(0.60,0.7,0.90,0.9);
  leg1e->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1e->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1e->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1e->SetBorderSize(0);
  leg1e->SetFillStyle(0);
  leg1e->Draw("same");
  
  c->SaveAs("CandidateResult/Bzero_candidates_eff_incl.pdf");

  //
  
  
  TCanvas *c1 = new TCanvas("c1","",600,600);

  int nentriesData = ntData->GetEntries();
  int realsizeData=0,realsizeSigregData=0;
  
  for(j=0;j<nentriesData;j++)
    {
      if(j%5000000==0) cout<<"Processing: "<<j<<" / "<<nentriesData<<endl;
      ntData->GetEntry(j);
      realsizeData=0;
      realsizeSigregData=0;
      for(k=0;k<size;k++)
	{
	  if(pt[k]>ptmin&&pt[k]<ptmax&&y[k]>ymin&&y[k]<ymax&&(HLT_PAMu3_v1)&&abs(mumumass[k]-3.096916)<0.15&&mass[k]>5&&mass[k]<6&&trk1Pt[k]>0.7&&trk2Pt[k]>0.7&&chi2cl[k]>9.94e-02&&(d0[k]/d0Err[k])>6.08&&cos(dtheta[k])>7.93e-01&&abs(tktkmass[k]-0.89594)<0.10&&mu1pt[k]>1.5&&mu2pt[k]>1.5)
	    {
	      realsizeData++;
	      if(abs(mass[k]-5.279)<0.04)
		{
		  realsizeSigregData++;
		}
	    }
	}
      if(realsizeData!=0)
	{
	  hData->Fill(realsizeData);
	}
      if(realsizeSigregData!=0)
	{
	  hSigregData->Fill(realsizeSigregData);
	}
    }

  int m=0;
  double normData=0,normMC=0;
  normData = hData->GetEntries();
  normMC = hMC->GetEntries();
  cout<<normData<<" "<<normMC<<endl;
  
  hData->Scale(1./normData);
  hMC->Scale(1./normMC); 

  float nmData=0,amData=0,smData=0;
  float nmMC=0,amMC=0,smMC=0;
  for(m=0;m<bins;m++)
    {
      nmData+=hData->GetBinContent(m+1)*(m+1);
      smData+=hData->GetBinContent(m+1);
      nmMC+=hMC->GetBinContent(m+1)*(m+1);
      smMC+=hMC->GetBinContent(m+1);
    }
  amData=nmData/smData;
  amMC=nmMC/smMC;
  cout<<smData<<"  "<<amData<<endl;
  cout<<smMC<<"  "<<amMC<<endl;

  hData->SetXTitle("# of candidate");
  hData->SetYTitle("#Probability");
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
  
  TLegend *legi = new TLegend(0.50,0.75,0.70,0.87);
  legi->AddEntry(hData,"data","f");
  legi->AddEntry(hMC,"MC","f");
  legi->SetBorderSize(0);
  legi->SetFillStyle(0);
  legi->Draw("same");
  TLegend *leg1i = new TLegend(0.60,0.7,0.90,0.9);
  leg1i->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1i->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1i->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1i->SetBorderSize(0);
  leg1i->SetFillStyle(0);
  leg1i->Draw("same");
  
  c1->SaveAs("CandidateResult/Bzero_candidates_compare_incl.pdf");

  //

  TCanvas *c2 = new TCanvas("c2","",600,600);

  double normSigregData=0,normSigregMC=0;
  normSigregData = hSigregData->GetEntries();
  normSigregMC = hSigregMC->GetEntries();
  cout<<normSigregData<<" "<<normSigregMC<<endl;

  hSigregData->Scale(1./normSigregData);
  hSigregMC->Scale(1./normSigregMC);

  float nmDataSR=0,amDataSR=0,smDataSR=0;
  float nmMCSR=0,amMCSR=0,smMCSR=0;
  for(m=0;m<bins;m++)
    {
      nmDataSR+=hSigregData->GetBinContent(m+1)*(m+1);
      smDataSR+=hSigregData->GetBinContent(m+1);
      nmMCSR+=hSigregMC->GetBinContent(m+1)*(m+1);
      smMCSR+=hSigregMC->GetBinContent(m+1);
    }
  amDataSR=nmDataSR/smDataSR;
  amMCSR=nmMCSR/smMCSR;
  cout<<smDataSR<<"  "<<amDataSR<<endl;
  cout<<smMCSR<<"  "<<amMCSR<<endl;

  hSigregData->SetXTitle("# of candidate");
  hSigregData->SetYTitle("#Probability");
  hSigregData->SetTitleOffset(1.5,"Y");
  if(hSigregData->GetMaximum()>hSigregMC->GetMaximum()) hSigregData->SetMaximum(hSigregData->GetMaximum()*1.2);
  else hSigregData->SetMaximum(hSigregMC->GetMaximum()*1.2);

  hSigregData->SetLineColor(kBlue+1);
  hSigregData->SetFillStyle(1001);
  hSigregData->SetFillColor(kBlue-9);
  hSigregData->SetLineWidth(3);
  hSigregData->SetStats(0);

  hSigregMC->SetLineColor(kRed);
  hSigregMC->SetFillStyle(3004);
  hSigregMC->SetFillColor(kRed);
  hSigregMC->SetLineWidth(3);
  hSigregMC->SetStats(0);

  hSigregData->Draw();
  hSigregMC->Draw("same");

  TLegend *legr = new TLegend(0.50,0.75,0.70,0.87);
  legr->AddEntry(hSigregData,"data","f");
  legr->AddEntry(hSigregMC,"MC","f");
  legr->SetBorderSize(0);
  legr->SetFillStyle(0);
  legr->Draw("same");
  TLegend *leg1r = new TLegend(0.60,0.7,0.90,0.9);
  leg1r->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1r->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1r->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1r->SetBorderSize(0);
  leg1r->SetFillStyle(0);
  leg1r->Draw("same");

  c2->SaveAs("CandidateResult/Bzero_candidates_compare_sigreg.pdf");

}

void NoCandidateB0MP()
{
  dimuonLoop(10,60,-2.4,2.4);
  //dimuonLoop(10.,60.,yBins[i],yBins[i+1],i+1);
}
