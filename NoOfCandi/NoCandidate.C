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

void dimuonLoop(float ptmin, float ptmax, float ymin, float ymax, int i)
{
  TFile *infMC = new TFile(inputmc);
  TTree *ntMC = (TTree*) infMC->Get("ntKp");

  setBranch(ntMC);

  TCanvas *c = new TCanvas(Form("c%i",i),"",600,600);
  //if (logy) c->SetLogy();

  int bins=10;  
  TH1D* hMCTruth = new TH1D("hMCTruth","",bins-1,1,bins);
  TH1D* hMC = new TH1D("hMC","",bins-1,1,bins);
  //TH1D* hMCProb = new TH1D("hMCProb","",bins-1,1,bins);
  
  int j=0,k=0;
  int nentries = ntMC->GetEntries();
  int realsize=0;
  int ifmatching=0;
  for(j=0;j<nentries;j++)
    {
      if(j%100000==0) cout<<"Processing: "<<j<<" / "<<nentries<<endl;
      ntMC->GetEntry(j);
      realsize=0;
      ifmatching=0;
      for(k=0;k<size;k++)
	{
	  if(pt[k]>ptmin&&pt[k]<ptmax&&y[k]>ymin&&y[k]<ymax&&(HLT_PAMu3_v1)&&abs(mumumass[k]-3.096916)<0.15&&mass[k]>5&&mass[k]<6&&trk1Pt[k]>0.9&&chi2cl[k]>1.32e-02&&(d0[k]/d0Err[k])>3.41&&cos(dtheta[k])>-3.46e-01&&mu1pt[k]>1.5&&mu2pt[k]>1.5)
	    {
	      realsize++;
	      if(gen[k]==23333 && isbestchi2[k]==1)
		{
		  ifmatching=1;
		}
	    }
	}

      if(realsize!=0)
	{
	  hMC->Fill(realsize);
	  if(ifmatching!=0)
	    {
	      hMCTruth->Fill(realsize);
	    }
	}
    }

  hMC->Sumw2();
  hMCTruth->Sumw2();
  hMCTruth->Divide(hMC);
  hMCTruth->Sumw2();

  hMCTruth->SetXTitle("# of candidate");
  hMCTruth->SetYTitle("Matching Probability");
  hMCTruth->SetTitleOffset(1.5,"Y");
  hMCTruth->SetStats(0);

  hMCTruth->Draw();

  c->SaveAs("CandidateResult/Bplus_candidates_compare_sigreg.pdf");

  /*

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
  
  TLegend *leg = new TLegend(0.50,0.75,0.70,0.87);
  leg->AddEntry(hData,"data","f");
  leg->AddEntry(hMC,"MC","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");
  TLegend *leg1 = new TLegend(0.60,0.7,0.90,0.9);
  leg1->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->Draw("same");

  c->SaveAs("CandidateResult/Bplus_candidates_compare_sigreg.pdf");
  */
}

void NoCandidateMP()
{
  const int nBins = 1;
  double ptBins[nBins+1] = {10,60};
  //const int nBins = 5;
  //double ptBins[nBins+1] = {10,15,20,25,30,60};
  //const int nBins=5;
  //double yBins[nBins+1] = {-3,-2,-1,0,1,2};
  int i=0;
  for(i=0;i<nBins;i++)
    {
      dimuonLoop(ptBins[i],ptBins[i+1],-2.4,2.4,i+1);
      //dimuonLoop(10.,60.,yBins[i],yBins[i+1],i+1);
    }
}
