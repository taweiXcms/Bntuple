#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loopcand.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916

void fillTree(TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, int j, int typesize, float track_mass1, float track_mass2, int REAL)
{

  //Event Info
  Event = EvtInfo_EvtNo;
  Run = EvtInfo_RunNo;

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
  bVtx->SetXYZ(BInfo_vtxX[j]-EvtInfo_PVx,
	       BInfo_vtxY[j]-EvtInfo_PVy,
	       BInfo_vtxZ[j]*0-EvtInfo_PVz*0);
  b4P->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);

  bindex = typesize;
  y = b4P->Rapidity();
  dtheta = bP->Angle(*bVtx);
  pt = BInfo_pt[j];
  eta = BInfo_eta[j];
  phi = BInfo_phi[j];
  chi2cl = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
  d0 = sqrt((BInfo_vtxX[j]-EvtInfo_PVx)*(BInfo_vtxX[j]-EvtInfo_PVx)+(BInfo_vtxY[j]-EvtInfo_PVy)*(BInfo_vtxY[j]-EvtInfo_PVy));
  vx = BInfo_vtxX[j] - EvtInfo_PVx;
  vy = BInfo_vtxY[j] - EvtInfo_PVy;
  d0Err = sqrt(BInfo_vtxXE[j]*BInfo_vtxXE[j]+BInfo_vtxYE[j]*BInfo_vtxYE[j]);
  mass = BInfo_mass[j];
  tktkmass = BInfo_tktk_mass[j];
  chi2ndf = BInfo_vtxchi2[j]/BInfo_vtxdof[j];
  lxy = ((BInfo_vtxX[j]-EvtInfo_PVx)*BInfo_px[j] + (BInfo_vtxY[j]-EvtInfo_PVy)*BInfo_py[j])/BInfo_pt[j];
  isbestchi2 = 0;
  isbesttktkmass = 0;
  kstar = 0;
  if(BInfo_type[j]==4) kstar=1;
  else if(BInfo_type[j]==5) kstar=2;

  //muon section
  mu1Striplayer = MuonInfo_i_nStripLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Pixellayer = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1Chi2ndf = MuonInfo_i_chi2[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dxy = MuonInfo_dxyPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  mu1dz = MuonInfo_dzPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&16) mu1TrackerMuArbitrated = 1;
  else mu1TrackerMuArbitrated = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&4096) mu1StationTight = 1;
  else mu1StationTight = 0;

  mu2Striplayer = MuonInfo_i_nStripLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Pixellayer = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2Chi2ndf = MuonInfo_i_chi2[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dxy = MuonInfo_dxyPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  mu2dz = MuonInfo_dzPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&16) mu2TrackerMuArbitrated = 1;
  else mu2TrackerMuArbitrated = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&4096) mu2StationTight = 1;
  else mu2StationTight = 0;
  
  float mu1px,mu1py,mu1pz,mu1E;
  float mu2px,mu2py,mu2pz,mu2E;

  mu1px = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1py = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  mu1pz = MuonInfo_pt[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu1px,mu1py,mu1pz,MUON_MASS);
  mu1E = b4P->E();
  mu1eta = b4P->Eta();
  mu1phi = b4P->Phi();
  mu1y = b4P->Rapidity();
  mu1pt = b4P->Pt();
  mu1p = b4P->P();

  mu2px = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*cos(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2py = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sin(MuonInfo_phi[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  mu2pz = MuonInfo_pt[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]*sinh(MuonInfo_eta[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]);
  b4P->SetXYZM(mu2px,mu2py,mu2pz,MUON_MASS);
  mu2E = b4P->E();
  mu2eta = b4P->Eta();
  mu2phi = b4P->Phi();
  mu2y = b4P->Rapidity();
  mu2pt = b4P->Pt();
  mu2p = b4P->P();

  b4P->SetPxPyPzE(mu1px+mu2px,
		  mu1py+mu2py,
		  mu1pz+mu2pz,
		  mu1E+mu2E);
  mumumass = b4P->Mag();
  mumueta = b4P->Eta();
  mumuphi = b4P->Phi();
  mumuy = b4P->Rapidity();
  mumupt = b4P->Pt();


  //jpsi section
  ujmass = BInfo_uj_mass[BInfo_rfuj_index[j]];
  ujvProb = TMath::Prob(BInfo_uj_vtxchi2[BInfo_rfuj_index[j]],BInfo_uj_vtxdof[BInfo_rfuj_index[j]]);
  b4P->SetXYZM(BInfo_uj_px[BInfo_rfuj_index[j]],
	       BInfo_uj_py[BInfo_rfuj_index[j]],
	       BInfo_uj_pz[BInfo_rfuj_index[j]],
	       BInfo_uj_mass[BInfo_rfuj_index[j]]);
  ujpt = b4P->Pt();
  ujeta = b4P->PseudoRapidity();
  ujphi = b4P->Phi();
  ujy = b4P->Rapidity();
  ujlxy = ((BInfo_uj_vtxX[BInfo_rfuj_index[j]]-EvtInfo_PVx)*BInfo_uj_px[BInfo_rfuj_index[j]] + (BInfo_uj_vtxY[BInfo_rfuj_index[j]]-EvtInfo_PVy)*BInfo_uj_py[BInfo_rfuj_index[j]])/ujpt;

  //track section
  float tk1px,tk1py,tk1pz,tk1E;
  float tk2px,tk2py,tk2pz,tk2E;

  if(BInfo_type[j]==1 || BInfo_type[j]==2)
    {
      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass1);
      trk1Dxy = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
      trk1D0Err = TrackInfo_d0error[BInfo_rftk1_index[j]];
      trk1PixelHit = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
      trk1StripHit = TrackInfo_striphit[BInfo_rftk1_index[j]];
      trk1Pt = TrackInfo_pt[BInfo_rftk1_index[j]];
      trk1Chi2ndf = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
      trk1Eta = TrackInfo_eta[BInfo_rftk1_index[j]];
      trk1Phi = TrackInfo_phi[BInfo_rftk1_index[j]];
      trk1Y = b4P->Rapidity();

      trk2Dxy = -1;
      trk2D0Err = -1;
      trk2PixelHit = -1;
      trk2StripHit = -1;
      trk2Pt = -1;
      trk2Chi2ndf = -1;
      trk2Eta = -20;
      trk2Phi = -20;
      trk2Y = -1;

      tktkmass = -1;
      tktkvProb = -1;
      tktkpt = -1;
      tktketa = -20;
      tktkphi = -20;
      tktky = -1;
      doubletmass = -1;
      doubletpt = -1;
      doubleteta = -20;
      doubletphi = -20;
      doublety = -1;
    }  
  else if(BInfo_type[j]==5)
    {
      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk2_index[j]],TrackInfo_eta[BInfo_rftk2_index[j]],TrackInfo_phi[BInfo_rftk2_index[j]],track_mass1);
      trk1Dxy = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
      trk1D0Err = TrackInfo_d0error[BInfo_rftk2_index[j]];
      trk1PixelHit = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
      trk1StripHit = TrackInfo_striphit[BInfo_rftk2_index[j]];
      trk1Pt = TrackInfo_pt[BInfo_rftk2_index[j]];
      trk1Chi2ndf = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
      trk1Eta = TrackInfo_eta[BInfo_rftk2_index[j]];
      trk1Phi = TrackInfo_phi[BInfo_rftk2_index[j]];
      trk1Y = b4P->Rapidity();
      tk1px = b4P->Px();
      tk1py = b4P->Py();
      tk1pz = b4P->Pz();
      tk1E = b4P->E();

      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass2);
      trk2Dxy = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
      trk2D0Err = TrackInfo_d0error[BInfo_rftk1_index[j]];
      trk2PixelHit = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
      trk2StripHit = TrackInfo_striphit[BInfo_rftk1_index[j]];
      trk2Pt = TrackInfo_pt[BInfo_rftk1_index[j]];
      trk2Chi2ndf = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
      trk2Eta = TrackInfo_eta[BInfo_rftk1_index[j]];
      trk2Phi = TrackInfo_phi[BInfo_rftk1_index[j]];
      trk2Y = b4P->Rapidity();
      tk2px = b4P->Px();
      tk2py = b4P->Py();
      tk2pz = b4P->Pz();
      tk2E = b4P->E();

      b4P->SetPxPyPzE(tk1px+tk2px,
		      tk1py+tk2py,
		      tk1pz+tk2pz,
		      tk1E+tk2E);
      tktkmass = b4P->Mag();
      tktketa = b4P->Eta();
      tktkphi = b4P->Phi();
      tktky = b4P->Rapidity();
      tktkpt = b4P->Pt();
      tktkvProb = TMath::Prob(BInfo_tktk_vtxchi2[j],BInfo_tktk_vtxdof[j]);
      doubletmass = BInfo_tktk_mass[j];
      b4P->SetXYZM(BInfo_tktk_px[j],BInfo_tktk_py[j],BInfo_tktk_pz[j],BInfo_tktk_mass[j]);
      doubletpt = b4P->Pt();
      doubleteta = b4P->PseudoRapidity();
      doubletphi = b4P->Phi();
      doublety = b4P->Rapidity();
    }
  else
    {
      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass1);
      trk1Dxy = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
      trk1D0Err = TrackInfo_d0error[BInfo_rftk1_index[j]];
      trk1PixelHit = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
      trk1StripHit = TrackInfo_striphit[BInfo_rftk1_index[j]];
      trk1Pt = TrackInfo_pt[BInfo_rftk1_index[j]];
      trk1Chi2ndf = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
      trk1Eta = TrackInfo_eta[BInfo_rftk1_index[j]];
      trk1Phi = TrackInfo_phi[BInfo_rftk1_index[j]];
      trk1Y = b4P->Rapidity();
      tk1px = b4P->Px();
      tk1py = b4P->Py();
      tk1pz = b4P->Pz();
      tk1E = b4P->E();

      b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk2_index[j]],TrackInfo_eta[BInfo_rftk2_index[j]],TrackInfo_phi[BInfo_rftk2_index[j]],track_mass2);
      trk2Dxy = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
      trk2D0Err = TrackInfo_d0error[BInfo_rftk2_index[j]];
      trk2PixelHit = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
      trk2StripHit = TrackInfo_striphit[BInfo_rftk2_index[j]];
      trk2Pt = TrackInfo_pt[BInfo_rftk2_index[j]];
      trk2Chi2ndf = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
      trk2Eta = TrackInfo_eta[BInfo_rftk2_index[j]];
      trk2Phi = TrackInfo_phi[BInfo_rftk2_index[j]];
      trk2Y = b4P->Rapidity();
      tk2px = b4P->Px();
      tk2py = b4P->Py();
      tk2pz = b4P->Pz();
      tk2E = b4P->E();

      b4P->SetPxPyPzE(tk1px+tk2px,
		      tk1py+tk2py,
		      tk1pz+tk2pz,
		      tk1E+tk2E);
      tktkmass = b4P->Mag();
      tktketa = b4P->Eta();
      tktkphi = b4P->Phi();
      tktky = b4P->Rapidity();
      tktkpt = b4P->Pt();
      tktkvProb = TMath::Prob(BInfo_tktk_vtxchi2[j],BInfo_tktk_vtxdof[j]);
      doubletmass = BInfo_tktk_mass[j];
      b4P->SetXYZM(BInfo_tktk_px[j],BInfo_tktk_py[j],BInfo_tktk_pz[j],BInfo_tktk_mass[j]);
      doubletpt = b4P->Pt();
      doubleteta = b4P->PseudoRapidity();
      doubletphi = b4P->Phi();
      doublety = b4P->Rapidity();
    }

  //gen info judgement

  if(!REAL)
    {
      gen = 0;//gen init
      genIndex = -1;//gen init
      genpt = -1;
      geneta = -20;
      geny = -1;
      int mGenIdxTk1=-1;
      int mGenIdxTk2=-1;
      int bGenIdxTk1=-1;
      int bGenIdxTk2=-1;
      int bGenIdxMu1=-1;
      int bGenIdxMu2=-1;
      
      
      float BId,MId,tk1Id,tk2Id;
      //tk1:positive, tk2:negtive
      if(BInfo_type[j]==1)
	{
	  BId = 521;//B+-
	  MId = -1;
	  tk1Id = 321;//K+-
	  tk2Id = -1;
	}
      if(BInfo_type[j]==2)
	{
	  BId = 521;//B+-
	  MId = -1;
	  tk1Id = 211;//pi+-
	  tk2Id = -1;
	}
      if(BInfo_type[j]==3)
	{
	  BId = 511;//B0
	  MId = 310;//Ks
	  tk1Id = 211;//pi+
	  tk2Id = 211;//pi-
	}
      if(BInfo_type[j]==4)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 321;//K+
	  tk2Id = 211;//pi-
	}
      if(BInfo_type[j]==5)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 211;//pi+
	  tk2Id = 321;//K-
	}
      if(BInfo_type[j]==6)
	{
	  BId = 531;//Bs
	  MId = 333;//phi
	  tk1Id = 321;//K+
	  tk2Id = 321;//K-
	}
      
      int twoTks,kStar,flagkstar=0;
      if(BInfo_type[j]==1 || BInfo_type[j]==2) twoTks=0;
      else twoTks=1;
      if(BInfo_type[j]==4 || BInfo_type[j]==5) kStar=1;
      else kStar=0;

      // tk1
      if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	{
	  int level =0;
	  if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk1Id)
	    {
	      level = 1;
	      if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		{
		  if(!twoTks)//one trk channel
		    {
		      mGenIdxTk1=0;
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==BId)
			{
			  level = 3;
			  bGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}		  
		    }
		  else//two trk channel
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  gen=level;
	}
      
      //tk2
      if(!twoTks)//one trk channel
	{
	  gen+=30;
	  mGenIdxTk2=0;
	  bGenIdxTk2=0;
	}
      else//two trk channel
	{
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      int level =0;
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk2Id)
		{
		  level = 1;
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	      gen+=(level*10);
	    }
	}

     
      //mu1
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]])==13) level=1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu1=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////=1
		    }
		} 
	    }
	  gen+=(level*100);
	}
      
      //mu2
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(abs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]])==13) level = 1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu2=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////////=2
		    }
		}
	    }
	  gen+=(level*1000);
	}
      
      int level=0;
      if(mGenIdxTk1!=-1 && mGenIdxTk2!=-1)
	{
	  if(!twoTks) level=1;
	  else
	    {
	      if(mGenIdxTk1==mGenIdxTk2) level=1;
	    }
	}
      if(bGenIdxMu1!=-1 && bGenIdxMu1==bGenIdxMu2 && bGenIdxMu1==bGenIdxTk1)
	{
	  if(!twoTks)
	    {
	      level=2;
	      genIndex = bGenIdxMu1;
	    }
	  else if(bGenIdxMu1==bGenIdxTk2)
	    {
	      level=2;
	      genIndex = bGenIdxMu1;
	    }
	}
      gen+=(level*10000);

      //kstar#############################################################################
      if(kStar)
	{
	  //tk1
	  if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	    {
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk2Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  flagkstar++;//////////////////////////////////////////////=3
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  
	  //tk2
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      if(abs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk1Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(abs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(abs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  flagkstar++;////////////////////////////////////////////////////=4
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	    }
	  if(flagkstar==4)
	    {
	      if((bGenIdxMu1!=-1) 
		 && (bGenIdxMu1==bGenIdxMu2)
		 && (bGenIdxMu1==bGenIdxTk1)
		 && (bGenIdxMu1==bGenIdxTk2)
		 )
		{
		  gen=41000;
		}
	    }
	}//kstar End#############################################################################

      int tgenIndex=genIndex;
      if(gen==22233)
	{
	  genpt = GenInfo_pt[tgenIndex];
	  geneta = GenInfo_eta[tgenIndex];
	  b4P->SetXYZM(GenInfo_pt[tgenIndex]*cos(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sin(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sinh(GenInfo_eta[tgenIndex]),
		       GenInfo_mass[tgenIndex]);
	  geny = b4P->Rapidity();
	}
    }
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

float calTktkmass(int j,TLorentzVector* b4P,float track_mass1,float track_mass2)
{
  float tk1px,tk1py,tk1pz,tk1E;
  float tk2px,tk2py,tk2pz,tk2E;  
  
  b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk1_index[j]],TrackInfo_eta[BInfo_rftk1_index[j]],TrackInfo_phi[BInfo_rftk1_index[j]],track_mass1);
  tk1px = b4P->Px();
  tk1py = b4P->Py();
  tk1pz = b4P->Pz();
  tk1E = b4P->E();
  
  b4P->SetPtEtaPhiM(TrackInfo_pt[BInfo_rftk2_index[j]],TrackInfo_eta[BInfo_rftk2_index[j]],TrackInfo_phi[BInfo_rftk2_index[j]],track_mass2);
  tk2px = b4P->Px();
  tk2py = b4P->Py();
  tk2pz = b4P->Pz();
  tk2E = b4P->E();
  
  b4P->SetPxPyPzE(tk1px+tk2px,
		  tk1py+tk2py,
		  tk1pz+tk2pz,
		  tk1E+tk2E);
  return b4P->Mag();
}

void loopcand(string infile="/export/d00/scratch/jwang/Bfinder_BoostedMC_20140318_Kp_TriggerMatchingMuon.root", string outfile="/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kp_TriggerMatchingMuon_CandBase_skim.root", bool REAL=0){
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
  ifchannel[1] = 1; //jpsi+pi
  ifchannel[2] = 1; //jpsi+Ks(pi+,pi-)
  ifchannel[3] = 1; //jpsi+K*(K+,pi-)
  ifchannel[4] = 1; //jpsi+K*(K-,pi+)
  ifchannel[5] = 1; //jpsi+phi
  ifchannel[6] = 1; //jpsi+pi pi <= psi', X(3872), Bs->J/psi f0
  
  TTree* nt0 = new TTree("ntKp","");
  buildBranch(nt0);
  TTree* nt1 = new TTree("ntpi","");
  buildBranch(nt1);
  TTree* nt2 = new TTree("ntKs","");
  buildBranch(nt2);
  TTree* nt3 = new TTree("ntKstar","");
  buildBranch(nt3);
  TTree* nt5 = new TTree("ntphi","");
  buildBranch(nt5);
  TTree* nt6 = new TTree("ntmix","");
  buildBranch(nt6);  
  TTree* ntGen = new TTree("ntGen","");
  buildGenBranch(ntGen);

  cout<<"--- Tree building finished ---"<<endl;
  
  Long64_t nentries = root->GetEntries();
  //nentries = 1000;
  Long64_t nbytes = 0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector* b4Pout = new TLorentzVector;
  TLorentzVector bGen;
  int type,flag;
  int flagEvt=0;  
  int offsetHltTree=0;
  
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += root->GetEntry(i);
    flagEvt=0;
    while (flagEvt==0)
    {
       hlt->GetEntry(i+offsetHltTree);
       //cout <<offsetHltTree<<" "<<Bfr_HLT_Event<<" "<<EvtInfo_EvtNo<<endl;
       if (Bfr_HLT_Event==EvtInfo_EvtNo && Bfr_HLT_Run==EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
    } 

    if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;

    int type1size=0,type2size=0,type3size=0,type4size=0,type5size=0,type6size=0,type7size=0;
    float best_1,best_2,best_3,best_4,best_5,best_6,best_7;
    float best2_1,best2_2,best2_3,best2_4,best2_5,best2_6,best2_7;
    float temy;
    int bestindex_1,bestindex_2,bestindex_3,bestindex_4,bestindex_5,bestindex_6,bestindex_7;
    int best2index_1,best2index_2,best2index_3,best2index_4,best2index_5,best2index_6,best2index_7;

    best_1=-1;
    bestindex_1=-1;
    best2_1=10000.;
    best2index_1=-1;
    best_2=-1;
    bestindex_2=-1;
    best2_2=10000.;
    best2index_2=-1;
    best_3=-1;
    bestindex_3=-1;
    best2_3=10000.;
    best2index_3=-1;
    best_4=-1;
    bestindex_4=-1;
    best2_4=10000.;
    best2index_4=-1;
    best_5=-1;
    bestindex_5=-1;
    best2_5=10000.;
    best2index_5=-1;
    best_6=-1;
    bestindex_6=-1;
    best2_6=10000.;
    best2index_6=-1;
    best_7=-1;
    bestindex_7=-1;
    best2_7=10000.;
    best2index_7=-1;

    float trktrkmass;
    for (int j=0;j<BInfo_size;j++) 
      {
	if(BInfo_type[j]>7) continue;
	if (ifchannel[BInfo_type[j]-1]!=1) continue;
	//skim{{{
	b4Pout->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);
	temy = b4Pout->Rapidity();
	if(REAL)
	  {
	    if(!(((EvtInfo_RunNo>=210498&&EvtInfo_RunNo<=211256&&abs(temy+0.465)<1.93)||(EvtInfo_RunNo>=211313&&EvtInfo_RunNo<=211631&&abs(temy-0.465)<1.93)))) continue;
	  }
	else
	  {
	    if(abs(temy+0.465)>=1.93) continue;
	  }
	if(BInfo_mass[j]<5 || BInfo_mass[j]>6) continue;
	if(BInfo_pt[j]<10.) continue;
	//}}}
	if(BInfo_type[j]==1)
	  {
	    //if(TrackInfo_pt[BInfo_rftk1_index[j]]<0.9) continue;
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_1)
	      {
		best_1 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_1 = type1size;
	      }
	    type1size++;
	  }
	if(BInfo_type[j]==2)
	  {
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_2)
	      {
		best_2 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_2 = type2size;
	      }
	    type2size++;
	  }
	if(BInfo_type[j]==3)
	  {
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_3)
	      {
		best_3 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_3 = type3size;
	      }
	    trktrkmass = calTktkmass(j,b4Pout,PION_MASS,PION_MASS);
	    if(abs(trktrkmass-KSHORT_MASS)<best2_3)
	      {
		best2_3 = abs(trktrkmass-KSHORT_MASS);
		best2index_3 = type3size;
	      }
	    type3size++;
	  }
	if(BInfo_type[j]==4 || BInfo_type[j]==5)
	  {
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_4)
	      {
		best_4 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_4 = type4size;
	      }
	    if(BInfo_type[j]==4) trktrkmass=calTktkmass(j,b4Pout,KAON_MASS,PION_MASS);
	    if(BInfo_type[j]==5) trktrkmass=calTktkmass(j,b4Pout,PION_MASS,KAON_MASS);
	    if(abs(trktrkmass-KSTAR_MASS)<best2_4)
	      {
		best2_4 = abs(trktrkmass-KSTAR_MASS);
		best2index_4 = type4size;
	      }
	    type4size++;
	  }
	if(BInfo_type[j]==6)
	  {	    
	    //if(TrackInfo_pt[BInfo_rftk1_index[j]]<0.7) continue;
	    //if(TrackInfo_pt[BInfo_rftk2_index[j]]<0.7) continue;
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_6)
	      {
		best_6 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_6 = type6size;
	      }
	    trktrkmass = calTktkmass(j,b4Pout,KAON_MASS,KAON_MASS);
	    if(abs(trktrkmass-PHI_MASS)<best2_6)
	      {
		best2_6 = abs(trktrkmass-PHI_MASS);
		best2index_6 = type6size;
	      }
	    type6size++;
	  }
	if(BInfo_type[j]==7)
	  {
	    if(TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j])>best_7)
	      {
		best_7 = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
		bestindex_7 = type7size;
	      }
	    type7size++;
	  }
      }

    //#######################################################

    type1size=0;
    type2size=0;
    type3size=0;
    type4size=0;
    type5size=0;
    type6size=0;
    type7size=0;

    for (int j=0;j<BInfo_size;j++) 
      {
	if(BInfo_type[j]>7) continue;
	if (ifchannel[BInfo_type[j]-1]!=1) continue;
	//skim{{{
	b4Pout->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);
	temy = b4Pout->Rapidity();
	if(REAL)
	  {
	    if(!(((EvtInfo_RunNo>=210498&&EvtInfo_RunNo<=211256&&abs(temy+0.465)<1.93)||(EvtInfo_RunNo>=211313&&EvtInfo_RunNo<=211631&&abs(temy-0.465)<1.93)))) continue;
	  }
	else
	  {
	    if(abs(temy+0.465)>=1.93) continue;
	  }
	if(BInfo_mass[j]<5 || BInfo_mass[j]>6) continue;
	if(BInfo_pt[j]<10.) continue;
	//}}}

	if(BInfo_type[j]==1)
	  {
	    //if(TrackInfo_pt[BInfo_rftk1_index[j]]<0.9) continue;
	    fillTree(bP,bVtx,b4P,j,type1size,KAON_MASS,0,REAL);
	    if(type1size==bestindex_1) isbestchi2=1;
	    nt0->Fill();
	    type1size++;
	  }
	if(BInfo_type[j]==2)
	  {
	    fillTree(bP,bVtx,b4P,j,type2size,PION_MASS,0,REAL);
	    if(type2size==bestindex_2) isbestchi2=1;
	    nt1->Fill();
	    type2size++;
	  }

	if(BInfo_type[j]==3)
	  {
	    fillTree(bP,bVtx,b4P,j,type3size,PION_MASS,PION_MASS,REAL);
	    if(type3size==bestindex_3) isbestchi2=1;
	    if(type3size==best2index_3) isbesttktkmass=1;
	    nt2->Fill();
	    type3size++;
	  }

	if(BInfo_type[j]==4 || BInfo_type[j]==5)
	  {
	    fillTree(bP,bVtx,b4P,j,type4size,KAON_MASS,PION_MASS,REAL);
	    if(type4size==bestindex_4) isbestchi2=1;
	    if(type4size==best2index_4) isbesttktkmass=1;
	    nt3->Fill();
	    type4size++;
	  }

	if(BInfo_type[j]==6)
	  {
	    //if(TrackInfo_pt[BInfo_rftk1_index[j]]<0.7) continue;
	    //if(TrackInfo_pt[BInfo_rftk2_index[j]]<0.7) continue;
	    fillTree(bP,bVtx,b4P,j,type6size,KAON_MASS,KAON_MASS,REAL);
	    if(type6size==bestindex_6) isbestchi2=1;
	    if(type6size==best2index_6) isbesttktkmass=1;
	    nt5->Fill();
	    type6size++;
	  }

	if(BInfo_type[j]==7)
	  {
	    fillTree(bP,bVtx,b4P,j,type7size,PION_MASS,PION_MASS,REAL);
	    if(type7size==bestindex_7) isbestchi2=1;
	    nt6->Fill();
	    type7size++;
	  }       
      }

    
    if(!REAL)
      {
	Gensize = 0;
	for (int j=0;j<GenInfo_size;j++)
	  {
	    bGen.SetPtEtaPhiM(GenInfo_pt[j],GenInfo_eta[j],GenInfo_phi[j],GenInfo_mass[j]);
	    flag=0;
	    for(type=1;type<8;type++)
	      {
		if (signalGen(type,j)) {
                  flag=type;
		  break;
                }
	      }
            if(flag!=0)
              {
                Genmu1pt = GenInfo_pt[GenInfo_da1[GenInfo_da1[j]]];
                Genmu1eta = GenInfo_eta[GenInfo_da1[GenInfo_da1[j]]];
                Genmu1p = Genmu1pt*cosh(Genmu1eta);
                Genmu2pt = GenInfo_pt[GenInfo_da2[GenInfo_da1[j]]];
                Genmu2eta = GenInfo_eta[GenInfo_da2[GenInfo_da1[j]]];
                Genmu2p = Genmu2pt*cosh(Genmu2eta);
		if(flag==1||flag==2)
		  {
		    Gentk1pt = GenInfo_pt[GenInfo_da2[j]];
		    Gentk1eta = GenInfo_eta[GenInfo_da2[j]];
		  }
		else
		  {
		    Gentk1pt = GenInfo_pt[GenInfo_da1[GenInfo_da2[j]]];
		    Gentk1eta = GenInfo_eta[GenInfo_da1[GenInfo_da2[j]]];
		    Gentk2pt = GenInfo_pt[GenInfo_da2[GenInfo_da2[j]]];
		    Gentk2eta = GenInfo_eta[GenInfo_da2[GenInfo_da2[j]]];
		  }
              }
	    Gensize = GenInfo_size;
	    Geny = bGen.Rapidity();
	    Geneta = bGen.Eta();
	    Genphi = bGen.Phi();
	    Genpt = bGen.Pt();
	    GenpdgId = GenInfo_pdgId[j];
	    GenisSignal = flag;
	    ntGen->Fill();
	  }

      }
    
  }

  outf->Write();
  outf->Close();
}


