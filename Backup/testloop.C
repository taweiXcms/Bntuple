#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1D.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loop.h"
#include <iostream>
#include <iomanip>

#define TEST 0
#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void testloop()
{
  TFile *f = new TFile("/data/bmeson/MC/Bfinder_BoostedMC_20140930_hckim-HIJINGemb_inclBtoPsiMuMu.root");
  TTree *root = (TTree*)f->Get("demo/root");
  TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
  if (root->GetEntries()!=hlt->GetEntries()) 
    {
      cout <<"Inconsistent number of entries!!! "<<endl;
      cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
      cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
    }

  setBranch(root);  
  Long64_t nentries = root->GetEntries();
  nentries = 100;
  Long64_t nbytes = 0;
  int offsetHltTree=0;
  if(TEST)
    {
      //TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
      TH1D *hx = new TH1D("hx","",802,-2,800);
      root->Project("hx","GenInfo.size","");
      hx->Draw();
    }

  if(!TEST)
    {
      int i,j;
      for(i=0;i<nentries;i++)
	{
	  nbytes += root->GetEntry(i);
	  if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<" "<<GenInfo_size<<endl;
	  for(j=0;j<GenInfo_size;j++)
	    {
	      if(abs(GenInfo_pdgId[j])==323)
		{
		  cout<<" -There are K*+(892): "<<GenInfo_index[j]<<endl;
		  if(GenInfo_mo1[j]>-1)
		    {
		      cout<<setw(20)<<left<<" --There are B: "<<setw(5)<<left<<GenInfo_nMo[j]<<endl;
		      cout<<setw(20)<<left<<" --Index: "<<setw(5)<<left<<GenInfo_mo1[j]<<setw(10)<<left<<" pdgId: "<<GenInfo_pdgId[GenInfo_mo1[j]]<<endl;
		      if(GenInfo_nDa[j]>1)
			{
			  cout<<setw(20)<<left<<" --There are Decay: "<<setw(5)<<left<<GenInfo_nDa[j]<<endl;
			  cout<<setw(20)<<left<<" --Jpsi Index: "<<setw(5)<<left<<GenInfo_da1[j]<<setw(10)<<left<<" pdgId: "<<GenInfo_pdgId[GenInfo_da1[j]]<<endl;
			  cout<<setw(20)<<left<<" --K Index: "<<setw(5)<<left<<GenInfo_da2[j]<<setw(10)<<left<<" pdgId: "<<GenInfo_pdgId[GenInfo_da2[j]]<<endl;
			  if(GenInfo_nDa[GenInfo_da1[GenInfo_mo1[j]]]>1)
			    {
			      cout<<setw(20)<<left<<" ---There are Muons: "<<setw(5)<<left<<GenInfo_nDa[GenInfo_da1[GenInfo_mo1[j]]]<<endl;
			      cout<<setw(20)<<left<<" ---Mu1 Index: "<<setw(5)<<left<<GenInfo_da1[GenInfo_da1[GenInfo_mo1[j]]]<<setw(10)<<left<<" pdgId: "<<GenInfo_pdgId[GenInfo_da1[GenInfo_da1[GenInfo_mo1[j]]]]<<endl;
			      cout<<setw(20)<<left<<" ---Mu2 Index: "<<setw(5)<<left<<GenInfo_da2[GenInfo_da1[GenInfo_mo1[j]]]<<setw(10)<<left<<" pdgId: "<<GenInfo_pdgId[GenInfo_da2[GenInfo_da1[GenInfo_mo1[j]]]]<<endl;
			    }
			}
		    }
		}
	    }
	}
    }
}
