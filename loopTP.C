#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loopTP.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void fillTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, int j, int typesize, float track_mass1, float track_mass2, int REAL, int PbpMC)
{

  //Event Info
  Event = EvtInfo_EvtNo;
  Run = EvtInfo_RunNo+10*PbpMC;
  size = typesize+1;

  // Trigger Info
  HLT_PAL1DoubleMu0_v1 = Bfr_HLT_PAL1DoubleMu0_v1;
  HLT_PAL1DoubleMu0_v1_Prescl = Bfr_HLT_PAL1DoubleMu0_v1_Prescl;
  HLT_PADimuon0_NoVertexing_v1 = Bfr_HLT_PADimuon0_NoVertexing_v1;
  HLT_PADimuon0_NoVertexing_v1_Prescl = Bfr_HLT_PADimuon0_NoVertexing_v1_Prescl;
  HLT_PAL1DoubleMu0_HighQ_v1 = Bfr_HLT_PAL1DoubleMu0_HighQ_v1;
  HLT_PAL1DoubleMu0_HighQ_v1_Prescl = Bfr_HLT_PAL1DoubleMu0_HighQ_v1_Prescl;
  HLT_PAL1DoubleMuOpen_v1 = Bfr_HLT_PAL1DoubleMuOpen_v1;
  HLT_PAL1DoubleMuOpen_v1_Prescl = Bfr_HLT_PAL1DoubleMuOpen_v1_Prescl;
  HLT_PAL2DoubleMu3_v1 = Bfr_HLT_PAL2DoubleMu3_v1;
  HLT_PAL2DoubleMu3_v1_Prescl = Bfr_HLT_PAL2DoubleMu3_v1_Prescl;
  HLT_PAMu3_v1 = Bfr_HLT_PAMu3_v1;
  HLT_PAMu3_v1_Prescl = Bfr_HLT_PAMu3_v1_Prescl;
  HLT_PAMu7_v1 = Bfr_HLT_PAMu7_v1;
  HLT_PAMu7_v1_Prescl = Bfr_HLT_PAMu7_v1_Prescl;
  HLT_PAMu12_v1 = Bfr_HLT_PAMu12_v1;
  HLT_PAMu12_v1_Prescl = Bfr_HLT_PAMu12_v1_Prescl;

}

int signalGen(int Btype, int j)
{
  float BId,MId,tk1Id,tk2Id;
  int twoTks;
  //tk1:positive, tk2:negtive
  if(Btype==1)
    {
      BId = 521;//B+-
      MId = -1;
      tk1Id = 321;//K+-
      tk2Id = -1;
      twoTks = 0;
    }
  if(Btype==2)
    {
      BId = 521;//B+-
      MId = -1;
      tk1Id = 211;//pi+-
      tk2Id = -1;
      twoTks = 0;
    }
  if(Btype==3)
    {
      BId = 511;//B0
      MId = 310;//Ks
      tk1Id = 211;//pi+
      tk2Id = -211;//pi-
      twoTks = 1;
    }
  if(Btype==4)
    {
      BId = 511;//B0
      MId = 313;//K*0
      tk1Id = 321;//K+
      tk2Id = -211;//pi-
      twoTks = 1;
    }
  if(Btype==5)
    {
      BId = 511;//B0
      MId = 313;//K*0
      tk1Id = -321;//pi+
      tk2Id = 211;//K-
      twoTks = 1;
    }
  if(Btype==6)
    {
      BId = 531;//Bs
      MId = 333;//phi
      tk1Id = 321;//K+
      tk2Id = -321;//K-
      twoTks = 1;
    }

  int flag=0;
  if (abs(GenInfo_pdgId[j])==BId&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
    {
      if (abs(GenInfo_pdgId[GenInfo_da1[j]]==443))//jpsi
	{
	  if(GenInfo_da1[GenInfo_da1[j]]!=-1&&GenInfo_da2[GenInfo_da1[j]]!=-1)
	    {
	      if(abs(GenInfo_pdgId[GenInfo_da1[GenInfo_da1[j]]])==13&&abs(GenInfo_pdgId[GenInfo_da2[GenInfo_da1[j]]])==13)
		{
		  if(!twoTks)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_da2[j]])==tk1Id) flag++;
		    }
		  else
		    {
		      if (abs(GenInfo_pdgId[GenInfo_da2[j]])==MId) 
			{
			  if(GenInfo_da1[GenInfo_da2[j]]!=-1 && GenInfo_da2[GenInfo_da2[j]]!=-1)
			    {
			      if(GenInfo_pdgId[GenInfo_da1[GenInfo_da2[j]]]==tk1Id && GenInfo_pdgId[GenInfo_da2[GenInfo_da2[j]]]==tk2Id) flag++;
			    }
			}
		    }
		}
	    }
	}
    }
  return flag;
}


int loopTP(string infile="/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140707_BuJpsiK_pPb.root", string
	  outfile="/export/d00/scratch/jwang/nt_BoostedMC_20140708_BuJpsiK_pPb.root.root", bool REAL=1,bool PbpMC=0,int startEntries=0,int
	  nEntries=0, bool doMuonSelection = 0){
//////////////////////////////////////////////////////////Phi
//   This file has been automatically generated 
//     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
//   from TTree root/root
//   found on file: merged_pPbData_20131114.root
//////////////////////////////////////////////////////////

  const char* infname;
  const char* outfname;

  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else {
     cout<<"--- MC ---"<<endl;
     if(PbpMC) cout<<"--- Pbp ---"<<endl;
     else cout<<"--- pPb ---"<<endl;
  }

  infname = infile.c_str();
  outfname = outfile.c_str();

  //File type
  TFile *f = new TFile(infname);
  TTree *root = (TTree*)f->Get("demo/root");
  TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
  if (root->GetEntries()!=hlt->GetEntries()) {
     cout <<"Inconsistent number of entries!!! "<<infile<<endl;
     cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
     cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
  }
  
  TFile *outf = new TFile(outfname,"recreate");

  setBranch(root);
  setHltBranch(hlt);
    
  TTree* nt0 = new TTree("ntJpsi","");
  buildBranch(nt0);

  TTree* ntGen = new TTree("ntGen","");
  buildGenBranch(ntGen);


  cout<<"--- Tree building finished ---"<<endl;
  
  Long64_t nentries = root->GetEntries();
  //nentries = 10000;
  Long64_t nbytes = 0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector* b4Pout = new TLorentzVector;
  TLorentzVector bGen;
  int type,flag;
  int flagEvt=0;  
  int offsetHltTree=0;

  int testevent=0,testcand=0;
  
  if (nEntries!=0) nentries=nEntries;

  TLorentzVector* mu1P4 = new TLorentzVector;
  TLorentzVector* mu2P4 = new TLorentzVector;
  TLorentzVector* JpsiP4 = new TLorentzVector;


  for (Long64_t i=startEntries; i<nentries;i++) {
    nbytes += root->GetEntry(i);
    flagEvt=0;
/*
    while (flagEvt==0)
    {
       hlt->GetEntry(i+offsetHltTree);
       if (Bfr_HLT_Event==EvtInfo_EvtNo && Bfr_HLT_Run==EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
    } 
*/
    if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;

    int type1size=0,type2size=0,type3size=0,type4size=0,type5size=0,type6size=0,type7size=0;
    float best,best2,temy;
    int bestindex,best2index;

    size=0;

    // select the first muon
    for (int muIt1=0;muIt1<MuonInfo_size;muIt1++) {

       // select the second muon
/*
   	 if(!(MuonInfo_isTrackerMuon[mu1] || MuonInfo_isGlobalMuon[mu1])) continue;
	 if(abs(MuonInfo_dxyPV[mu1])>=3. || abs(MuonInfo_dzPV[mu1])>=30.) continue;
	 if(MuonInfo_i_nPixelLayer[mu1]<1.) continue;
	 if(MuonInfo_normchi2[mu1]>1.8) continue;
	 if((MuonInfo_i_nStripLayer[mu1]+MuonInfo_i_nPixelLayer[mu1])<6.) continue;
         if(!(MuonInfo_muqual[mu1]&4096)) continue;
*/

       for (int muIt2=muIt1+1;muIt2<MuonInfo_size;muIt2++) {

/*
	 if(!(MuonInfo_isTrackerMuon[mu2] || MuonInfo_isGlobalMuon[mu2])) continue;
	 if(abs(MuonInfo_dxyPV[mu2])>=3. || abs(MuonInfo_dzPV[mu2])>=30.) continue;
	 if(MuonInfo_i_nPixelLayer[mu2]<1.) continue;
	 if(MuonInfo_normchi2[mu2]>1.8) continue;
	 if((MuonInfo_i_nStripLayer[mu2]+MuonInfo_i_nPixelLayer[mu2])<6.) continue;
	 if(!(MuonInfo_muqual[mu2]&4096)) continue;
*/

         if(MuonInfo_charge[muIt1]==MuonInfo_charge[muIt2]) continue;

         int mu1,mu2;	 
	 // mu1 is charged +1
	 if(MuonInfo_charge[muIt1]>0) {
	    mu1=muIt1;
	    mu2=muIt2;
         } else {
	    mu1=muIt2;
	    mu2=muIt1;
	 
	 }	 
	 
          mu1P4->SetPtEtaPhiM(MuonInfo_pt[mu1],MuonInfo_eta[mu1],MuonInfo_phi[mu1],MUON_MASS);
          mu2P4->SetPtEtaPhiM(MuonInfo_pt[mu2],MuonInfo_eta[mu2],MuonInfo_phi[mu2],MUON_MASS);
          JpsiP4 ->SetPxPyPzE(    mu1P4->Px()+mu2P4->Px(),
                                  mu1P4->Py()+mu2P4->Py(),
                                  mu1P4->Pz()+mu2P4->Pz(),
		   	          mu1P4->E()+mu2P4->E()
		              );

          if (JpsiP4->Mag()>5) continue;
          mass[size]=JpsiP4->Mag();
          pt[size]=JpsiP4->Pt();
          eta[size]=JpsiP4->Eta();
          y[size]=JpsiP4->Y();
          phi[size]=JpsiP4->Phi();
	  isTracker1[size]=(MuonInfo_isTrackerMuon[mu1] || MuonInfo_isGlobalMuon[mu1]);
	  isTracker2[size]=(MuonInfo_isTrackerMuon[mu2] || MuonInfo_isGlobalMuon[mu2]);
	  pt1[size]=MuonInfo_pt[mu1];
	  pt2[size]=MuonInfo_pt[mu2];
	  eta1[size]=MuonInfo_eta[mu1];
	  eta2[size]=MuonInfo_eta[mu2];
	  phi1[size]=MuonInfo_phi[mu1];
	  phi2[size]=MuonInfo_phi[mu2];
	  outerTrackisNonnull1[size]=MuonInfo_outerTrackisNonnull[mu1];
	  outerTrackisNonnull2[size]=MuonInfo_outerTrackisNonnull[mu2];

          id1[size]=1;
  	  if(abs(MuonInfo_dxyPV[mu1])>=3. || abs(MuonInfo_dzPV[mu1])>=30.) id1[size]=0;
	  if(MuonInfo_i_nPixelLayer[mu1]<1.) id1[size]=0;
	  if(MuonInfo_normchi2[mu1]>1.8) id1[size]=0;
	  if((MuonInfo_i_nStripLayer[mu1]+MuonInfo_i_nPixelLayer[mu1])<6.) id1[size]=0;
          if(!(MuonInfo_muqual[mu1]&4096)) id1[size]=0;

          id2[size]=1;
  	  if(abs(MuonInfo_dxyPV[mu2])>=3. || abs(MuonInfo_dzPV[mu2])>=30.) id2[size]=0;
	  if(MuonInfo_i_nPixelLayer[mu2]<1.) id2[size]=0;
	  if(MuonInfo_normchi2[mu2]>1.8) id2[size]=0;
	  if((MuonInfo_i_nStripLayer[mu2]+MuonInfo_i_nPixelLayer[mu2])<6.) id2[size]=0;
          if(!(MuonInfo_muqual[mu2]&4096)) id2[size]=0;


          gen[size]=0;
	  genpt[size]=-1;
	  int level1=0;
	  int level2=0;
          if(MuonInfo_geninfo_index[mu1]>-1) {
	     if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[mu1]])==13) {
	         level1=1;
	      if(GenInfo_mo1[MuonInfo_geninfo_index[mu1]]>-1) {
		  if(GenInfo_pdgId[GenInfo_mo1[MuonInfo_geninfo_index[mu1]]]==443) {
		      level1=2;
	  	  }
	      }
	      gen[size]+=(level1*1);
	     }
          }
	  
          if(MuonInfo_geninfo_index[mu2]>-1) {
	     if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[mu2]])==13) {
	         level2=1;
	      if(GenInfo_mo1[MuonInfo_geninfo_index[mu2]]>-1) {
		  if(GenInfo_pdgId[GenInfo_mo1[MuonInfo_geninfo_index[mu2]]]==443) {
		      level2=2;
		      
	  	  }
	      }
	      gen[size]+=(level2*10);
	     }
	  }
	  
	  if (level1==2&&level2==2) {
	     if (GenInfo_mo1[MuonInfo_geninfo_index[mu2]]==GenInfo_mo1[MuonInfo_geninfo_index[mu1]]) {
	        gen[size]+=100;
		genpt[size]=GenInfo_pt[GenInfo_mo1[MuonInfo_geninfo_index[mu2]]];
	     }
	  }

          size++;
       }
    }
    
    nt0->Fill();

     if(!REAL)
      {
	Gensize = 0;
	for (int j=0;j<GenInfo_size;j++)
	  {
	    if (GenInfo_pdgId[j]!=443) continue;
	    bGen.SetPtEtaPhiM(GenInfo_pt[j],GenInfo_eta[j],GenInfo_phi[j],GenInfo_mass[j]);
	    Geny[j] = bGen.Rapidity();
	    Geneta[j] = bGen.Eta();
	    Genphi[j] = bGen.Phi();
	    Genpt[j] = bGen.Pt();
	    GenpdgId[j] = GenInfo_pdgId[j];
	    Gensize++;
	  }
	ntGen->Fill();
    
	}

  }

  outf->Write();
  outf->Close();
}


