#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loopNonpromptBplus.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void fillTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, int j, int typesize, float track_mass1, float track_mass2, int REAL){

  //Event Info
  Event = EvtInfo_EvtNo;
  Run = EvtInfo_RunNo;
  size = typesize+1;
  besttktkmass = 0;
  bestchi2 = 0;

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

  //B Info
  bP->SetXYZ(BInfo_px[j],BInfo_py[j],BInfo_pz[j]*0);
  bVtx->SetXYZ(BInfo_vtxX[j]-EvtInfo_PVx,BInfo_vtxY[j]-EvtInfo_PVy,BInfo_vtxZ[j]*0-EvtInfo_PVz*0);
  b4P->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);

  bindex[typesize] = typesize;
  y[typesize] = b4P->Rapidity();
  dtheta[typesize] = bP->Angle(*bVtx);
  pt[typesize] = BInfo_pt[j];
  eta[typesize] = BInfo_eta[j];
  phi[typesize] = BInfo_phi[j];
  chi2cl[typesize] = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
  d0[typesize] = sqrt((BInfo_vtxX[j]-EvtInfo_PVx)*(BInfo_vtxX[j]-EvtInfo_PVx)+(BInfo_vtxY[j]-EvtInfo_PVy)*(BInfo_vtxY[j]-EvtInfo_PVy));
  vx[typesize] = BInfo_vtxX[j] - EvtInfo_PVx;
  vy[typesize] = BInfo_vtxY[j] - EvtInfo_PVy;
  d0Err[typesize] = sqrt(BInfo_vtxXE[j]*BInfo_vtxXE[j]+BInfo_vtxYE[j]*BInfo_vtxYE[j]);
  mass[typesize] = BInfo_mass[j];
  tktkmass[typesize] = BInfo_tktk_mass[j];
  chi2ndf[typesize] = BInfo_vtxchi2[j]/BInfo_vtxdof[j];
  lxy[typesize] = ((BInfo_vtxX[j]-EvtInfo_PVx)*BInfo_px[j] + (BInfo_vtxY[j]-EvtInfo_PVy)*BInfo_py[j])/BInfo_pt[j];
  isbestchi2[typesize] = 0;
  isbesttktkmass[typesize] = 0;
  kstar[typesize] = 0;
  if(BInfo_type[j]==4) kstar[typesize]=1;
  else if(BInfo_type[j]==5) kstar[typesize]=2;

  //muon section
  mu1Striplayer[typesize] = MuonInfo_i_nStripLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Pixellayer[typesize] = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Chi2ndf[typesize] = MuonInfo_i_chi2[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dxy[typesize] = MuonInfo_dxyPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dz[typesize] = MuonInfo_dzPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&16) mu1TrackerMuArbitrated[typesize] = 1;
  else mu1TrackerMuArbitrated[typesize] = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&4096) mu1StationTight[typesize] = 1;
  else mu1StationTight[typesize] = 0;

  mu2Striplayer[typesize] = MuonInfo_i_nStripLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Pixellayer[typesize] = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Chi2ndf[typesize] = MuonInfo_i_chi2[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dxy[typesize] = MuonInfo_dxyPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dz[typesize] = MuonInfo_dzPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&16) mu2TrackerMuArbitrated[typesize] = 1;
  else mu2TrackerMuArbitrated[typesize] = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&4096) mu2StationTight[typesize] = 1;
  else mu2StationTight[typesize] = 0;
  
  float mu1px,mu1py,mu1pz,mu1E;
  float mu2px,mu2py,mu2pz,mu2E;

  mu1px = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1py = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1pz = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu1px,mu1py,mu1pz,MUON_MASS);
  mu1E = b4P->E();
  mu1eta[typesize] = b4P->Eta();
  mu1y[typesize] = b4P->Rapidity();
  mu1pt[typesize] = b4P->Pt();
  mu1p[typesize] = b4P->P();

  mu2px = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2py = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2pz = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu2px,mu2py,mu2pz,MUON_MASS);
  mu2E = b4P->E();
  mu2eta[typesize] = b4P->Eta();
  mu2y[typesize] = b4P->Rapidity();
  mu2pt[typesize] = b4P->Pt();
  mu2p[typesize] = b4P->P();

  b4P->SetPxPyPzE(mu1px+mu2px,mu1py+mu2py,mu1pz+mu2pz,mu1E+mu2E);
  mumumass[typesize] = b4P->Mag();
  mumueta[typesize] = b4P->Eta();
  mumuy[typesize] = b4P->Rapidity();
  mumupt[typesize] = b4P->Pt();


  //jpsi section
  ujmass[typesize] = BInfo_uj_mass[BInfo_rfuj_index[j]];
  ujvProb[typesize] = TMath::Prob(BInfo_uj_vtxchi2[BInfo_rfuj_index[j]],BInfo_uj_vtxdof[BInfo_rfuj_index[j]]);
  b4P->SetXYZM(BInfo_uj_px[BInfo_rfuj_index[j]],BInfo_uj_py[BInfo_rfuj_index[j]],BInfo_uj_pz[BInfo_rfuj_index[j]],BInfo_uj_mass[BInfo_rfuj_index[j]]);
  ujpt[typesize] = b4P->Pt();
  ujeta[typesize] = b4P->PseudoRapidity();
  ujy[typesize] = b4P->Rapidity();
  ujlxy[typesize] = ((BInfo_uj_vtxX[BInfo_rfuj_index[j]]-EvtInfo_PVx)*BInfo_uj_px[BInfo_rfuj_index[j]] + (BInfo_uj_vtxY[BInfo_rfuj_index[j]]-EvtInfo_PVy)*BInfo_uj_py[BInfo_rfuj_index[j]])/ujpt[typesize];

  //track section
  float tk1px,tk1py,tk1pz,tk1E;
  float tk2px,tk2py,tk2pz,tk2E;

  b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass1);
  trk1Dxy[typesize] = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
  trk1D0Err[typesize] = TrackInfo_d0error[BInfo_rftk1_index[j]];
  trk1PixelHit[typesize] = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
  trk1StripHit[typesize] = TrackInfo_striphit[BInfo_rftk1_index[j]];
  trk1Pt[typesize] = TrackInfo_pt[BInfo_rftk1_index[j]];
  trk1Chi2ndf[typesize] = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
  trk1Eta[typesize] = TrackInfo_eta[BInfo_rftk1_index[j]];
  trk1Y[typesize] = b4P->Rapidity();

  trk2Dxy[typesize] = -1;
  trk2D0Err[typesize] = -1;
  trk2PixelHit[typesize] = -1;
  trk2StripHit[typesize] = -1;
  trk2Pt[typesize] = -1;
  trk2Chi2ndf[typesize] = -1;
  trk2Eta[typesize] = -1;
  trk2Y[typesize] = -1;

  tktkmass[typesize] = -1;
  tktkvProb[typesize] = -1;
  tktkpt[typesize] = -1;
  tktketa[typesize] = -1;
  tktky[typesize] = -1;
  doubletmass[typesize] = -1;
  doubletpt[typesize] = -1;
  doubleteta[typesize] = -1;
  doublety[typesize] = -1;

  if(!REAL){
    genBplusToPhiK[typesize] = 0;//gen init
    genB0[typesize] = 0;//gen init
	
	int trk1geninfo=TrackInfo_geninfo_index[BInfo_rftk1_index[j]];
	int pdgtrk1=abs(GenInfo_pdgId[trk1geninfo]); 
	int mothertrk1geninfo=GenInfo_mo1[trk1geninfo];
	int pdgmothertrk1=abs(GenInfo_pdgId[mothertrk1geninfo]);
	int grandmothertrk1geninfo=GenInfo_mo1[mothertrk1geninfo];
	int pdggrandmothertrk1=abs(GenInfo_pdgId[grandmothertrk1geninfo]);
    
    int muon1geninfo=MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
    int pdgmuon1=abs(GenInfo_pdgId[muon1geninfo]);
    int mothermuon1geninfo=GenInfo_mo1[muon1geninfo];
    int grandmothermuon1geninfo=GenInfo_mo1[mothermuon1geninfo];
    int pdggrandmothermuon1=abs(GenInfo_pdgId[grandmothermuon1geninfo]);
    
    int muon2geninfo=MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
    int pdgmuon2=abs(GenInfo_pdgId[muon2geninfo]);
    int mothermuon2geninfo=GenInfo_mo1[muon2geninfo];
    int grandmothermuon2geninfo=GenInfo_mo1[mothermuon2geninfo];
    int pdggrandmothermuon2=abs(GenInfo_pdgId[grandmothermuon2geninfo]);
    
    bool isbplustophik=IsBplusToPhiK(trk1geninfo,pdgtrk1,mothertrk1geninfo,pdgmothertrk1,grandmothertrk1geninfo,pdggrandmothertrk1,
                                    muon1geninfo,pdgmuon1,mothermuon1geninfo,grandmothermuon1geninfo,pdggrandmothermuon1,
                                    muon2geninfo,pdgmuon2,mothermuon2geninfo,grandmothermuon2geninfo,pdggrandmothermuon2);
    bool isb0=IsB0(trk1geninfo,pdgtrk1,mothertrk1geninfo,pdgmothertrk1,grandmothertrk1geninfo,pdggrandmothertrk1,
                                    muon1geninfo,pdgmuon1,mothermuon1geninfo,grandmothermuon1geninfo,pdggrandmothermuon1,
                                    muon2geninfo,pdgmuon2,mothermuon2geninfo,grandmothermuon2geninfo,pdggrandmothermuon2);

    
    
    genBplusToPhiK[typesize]=(int)(isbplustophik);
    genB0[typesize]=(int)(isb0); 
    
  }//end is not real
}//end fillTree


bool IsBplusToPhiK(int mytrk1geninfo,int mypdgtrk1,int mymothertrk1geninfo,int mypdgmothertrk1,int mygrandmothertrk1geninfo,int mypdggrandmothertrk1,
                   int mymuon1geninfo,int mypdgmuon1,int mymothermuon1geninfo,int mygrandmothermuon1geninfo,int mypdggrandmothermuon1, 
                   int mymuon2geninfo,int mypdgmuon2,int mymothermuon2geninfo,int mygrandmothermuon2geninfo,int mypdggrandmothermuon2){
  
  int mGenIdxTk1=-1;
  int mGenIdxTk2=-1;
  int bGenIdxTk1=-1;
  int bGenIdxTk2=-1;
  int bGenIdxMu1=-1;
  int bGenIdxMu2=-1;

    //tk1:positive, tk2:negtive
    
  int BplusId = 521;//B+-
  int trkKaonId = 321;//K+-
  int trkMuon = 13;//K+-


  bool okTrk1=false;
  bool okMuon1=false;
  bool okMuon2=false;
  bool okTotal=false;

  if(mytrk1geninfo>-1){
	if(mypdgtrk1==trkKaonId){
	  if(mymothertrk1geninfo>-1){
		if(mypdgmothertrk1==BplusId){
		  bGenIdxTk1=mymothertrk1geninfo;
		  okTrk1=true;
		}//if compatible with Bid	  
	  }//if GenInfo_mo1>-1
	}//is trk1d==pdg
  }//end trk1geninfo  
    
  //mu1
  if(mymuon1geninfo>-1){  
	if(mypdgmuon1==trkMuon){
	  if(mymothermuon1geninfo>-1){
	    if(mygrandmothermuon1geninfo>-1){
		  if(mypdggrandmothermuon1==BplusId){
		    bGenIdxMu1=mygrandmothermuon1geninfo;
		    okMuon1=true;
		  }//if compatible with Bid	  
		}//if GenInfo_mo1_mo1>-1
	  }//if GenInfo_mo1>-1
	}//is muon1==pdg
  }//end muon1geninfo 
    
  if(mymuon2geninfo>-1){  
	if(mypdgmuon2==trkMuon){
	  if(mymothermuon2geninfo>-1){
	    if(mygrandmothermuon2geninfo>-1){
		  if(mypdggrandmothermuon2==BplusId){
		    bGenIdxMu2=mygrandmothermuon2geninfo;
		    okMuon2=true;
		  }//if compatible with Bid	  
		}//if GenInfo_mo1_mo1>-1 
	  }//if GenInfo_mo1>-1
	}//is muon2==pdg
  }//end muon2geninfo 
  
  if(okMuon2&&okMuon1&&okTrk1){
    if(bGenIdxMu1!=-1 && bGenIdxMu1!=-1 && bGenIdxMu1==bGenIdxMu2 && bGenIdxMu1==bGenIdxTk1){
      okTotal=true;
    }
  }
  return okTotal;
}

bool IsB0(int mytrk1geninfo,int mypdgtrk1,int mymothertrk1geninfo,int mypdgmothertrk1,int mygrandmothertrk1geninfo,int mypdggrandmothertrk1,
                   int mymuon1geninfo,int mypdgmuon1,int mymothermuon1geninfo,int mygrandmothermuon1geninfo,int mypdggrandmothermuon1, 
                   int mymuon2geninfo,int mypdgmuon2,int mymothermuon2geninfo,int mygrandmothermuon2geninfo,int mypdggrandmothermuon2){
  
  int mGenIdxTk1=-1;
  int mGenIdxTk2=-1;
  int bGenIdxTk1=-1;
  int bGenIdxTk2=-1;
  int bGenIdxMu1=-1;
  int bGenIdxMu2=-1;

    //tk1:positive, tk2:negtive
    
  int BzeroId = 511;//B0
  int BsubsId = 531;//Bsubs

  bool okTrk1=false;
  bool okMuon1=false;
  bool okMuon2=false;
  bool okTotal=false;
  
  
  if(mypdgmothertrk1==BzeroId || mypdggrandmothertrk1==BzeroId || mypdgmothertrk1==BsubsId || mypdggrandmothertrk1==BsubsId  ) okTotal=true;
  return okTotal;
}


void loopNonpromptBplus(string infile="/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140418_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root", string outfile="../../output/myoutputBplus.root", bool REAL=0){
//////////////////////////////////////////////////////////Phi
//   This file has been automatically generated 
//     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
//   from TTree root/root
//   found on file: merged_pPbData_20131114.root
//////////////////////////////////////////////////////////

  const char* infname;
  const char* outfname;

  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else cout<<"--- MC ---"<<endl;
  
  infname = infile.c_str();
  outfname = outfile.c_str();

  //File type
  TFile *f = new TFile(infname);
  TTree *root = (TTree*)f->Get("demo/root");
  TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
  if (root->GetEntries()!=hlt->GetEntries()) {
     cout <<"Inconsistent number of entries!!!"<<endl;
     cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
     cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
  }

  TFile *outf = new TFile(outfname,"recreate");

  setBranch(root);
  setHltBranch(hlt);
    
  int ifchannel[7];
  ifchannel[0] = 1; //jpsi+Kp
  
  TTree* nt0 = new TTree("ntKp","");
  buildBranch(nt0);

  cout<<"--- Tree building finished ---"<<endl;
  
  Long64_t nentries = root->GetEntries();
  nentries = 200000;
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
  
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += root->GetEntry(i);
    flagEvt=0;
    while (flagEvt==0){
      hlt->GetEntry(i+offsetHltTree);
      //cout <<offsetHltTree<<" "<<Bfr_HLT_Event<<" "<<EvtInfo_EvtNo<<endl;
      if (Bfr_HLT_Event==EvtInfo_EvtNo && Bfr_HLT_Run==EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
    } 

    if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;

    int type1size=0,type2size=0,type3size=0,type4size=0,type5size=0,type6size=0,type7size=0;
    float best,best2,temy;
    int bestindex,best2index;
    size=0;
    best=-1;
    bestindex=-1;
    best2=10000.;
    best2index=-1;

    for (int j=0;j<BInfo_size;j++){
   	  if(BInfo_type[j]>7) continue;
	  if (ifchannel[BInfo_type[j]-1]!=1) continue;
	  //skim{{{
	  b4Pout->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);
	  temy = b4Pout->Rapidity();
	  if(REAL){
	    if(!(((EvtInfo_RunNo>=210498&&EvtInfo_RunNo<=211256&&abs(temy+0.465)<1.93)||(EvtInfo_RunNo>=211313&&EvtInfo_RunNo<=211631&&abs(temy-0.465)<1.93)))) continue;
	  }
	  else{
	    if(abs(temy+0.465)>=1.93) continue;
	  }
	  if(BInfo_mass[j]<5 || BInfo_mass[j]>6) continue;
	  if(BInfo_pt[j]<10.) continue;
	  //}}}
	  if(BInfo_type[j]==1){
	    if(TrackInfo_pt[BInfo_rftk1_index[j]]<0.9) continue;
	    fillTree(bP,bVtx,b4P,j,type1size,KAON_MASS,0,REAL);
	    if(chi2cl[type1size]>best){
	  	  best = chi2cl[type1size];
		  bestindex = type1size;
	    }
	    type1size++;
	  }
    }
    if(size>0){
      bestchi2 = bestindex;
      isbestchi2[bestindex] = 1;
    }
    nt0->Fill();

  }
  outf->Write();
  outf->Close();
}
