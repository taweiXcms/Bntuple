#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>

#include "loop.h"

#define REAL 1 //1:real data; 0:MC

class bNtuple
{
public:
  float mass;
  float pt;
  float d0;
  float px;
  float py;
  float vx;
  float vy;
  float d0Err;
  float chi2ndf;
  float dtheta;

  float trk1Pt;
  float trk1Dxy;
  float trk1D0Err;
  float trk1PixelHit;
  float trk1StripHit;
  float trk1Chi2ndf;

  float trk2Pt;
  float trk2Dxy;
  float trk2D0Err;
  float trk2PixelHit;
  float trk2StripHit;
  float trk2Chi2ndf;
  float gen;  

  void buildBranch(TTree* nt){
    nt->Branch("mass",&mass);
    nt->Branch("pt",&pt);
    nt->Branch("gen",&gen);
    nt->Branch("px",&px);
    nt->Branch("py",&py);
    nt->Branch("d0",&d0);
    nt->Branch("vx",&vx);
    nt->Branch("vy",&vy);
    nt->Branch("d0Err",&d0Err);
    nt->Branch("chi2ndf",&chi2ndf);
    nt->Branch("dtheta",&dtheta);

    nt->Branch("trk1Pt",&trk1Pt);
    nt->Branch("trk1Dxy",&trk1Dxy);
    nt->Branch("trk1D0Err",&trk1D0Err);
    nt->Branch("trk1PixelHit",&trk1PixelHit);
    nt->Branch("trk1StripHit",&trk1StripHit);
    nt->Branch("trk1Chi2ndf",&trk1Chi2ndf);

    nt->Branch("trk2Pt",&trk2Pt);
    nt->Branch("trk2Dxy",&trk2Dxy);
    nt->Branch("trk2D0Err",&trk2D0Err);
    nt->Branch("trk2PixelHit",&trk2PixelHit);
    nt->Branch("trk2StripHit",&trk2StripHit);
    nt->Branch("trk2Chi2ndf",&trk2Chi2ndf);
  }
};

void fillTree(bNtuple* b, TVector3* bP, TVector3* bVtx, int j)
{
         bP->SetXYZ(BInfo_px[j],BInfo_py[j],BInfo_pz[j]*0);
         bVtx->SetXYZ(BInfo_vtxX[j]-EvtInfo_PVx,
                       BInfo_vtxY[j]-EvtInfo_PVy,
                       BInfo_vtxZ[j]*0-EvtInfo_PVz*0);
         b->dtheta = bP->Angle(*bVtx);
         b->pt = sqrt(BInfo_px[j]*BInfo_px[j]+BInfo_py[j]*BInfo_py[j]);
	 b->px = BInfo_px[j];
	 b->py = BInfo_py[j];
         b->d0 = sqrt((BInfo_vtxX[j]-EvtInfo_PVx)*(BInfo_vtxX[j]-EvtInfo_PVx)+(BInfo_vtxY[j]-EvtInfo_PVy)*(BInfo_vtxY[j]-EvtInfo_PVy));
	 b->vx = BInfo_vtxX[j] - EvtInfo_PVx;
	 b->vy = BInfo_vtxY[j] - EvtInfo_PVy;
         b->d0Err = sqrt(BInfo_vtxXE[j]*BInfo_vtxXE[j]+BInfo_vtxYE[j]*BInfo_vtxYE[j]);
         b->mass = BInfo_mass[j];
         b->chi2ndf = BInfo_vtxchi2[j]/BInfo_vtxdof[j];
	 
	 b->trk1Dxy = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
	 b->trk1D0Err = TrackInfo_d0error[BInfo_rftk1_index[j]];
         b->trk1PixelHit = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
         b->trk1StripHit = TrackInfo_striphit[BInfo_rftk1_index[j]];
         b->trk1Pt = TrackInfo_pt[BInfo_rftk1_index[j]];
         b->trk1Chi2ndf = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];

         b->gen=0;

         // Gen info: check each daughter
         int bGenIdxK=-1;
         int bGenIdxMu1=-1;
         int bGenIdxMu2=-1;

         // check Kaon
         if (TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
         {
            //cout << TrackInfo_geninfo_index[BInfo_rftk1_index[j]] <<" "<< (GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])<<endl;
            int level =0;
            if (fabs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==321) level = 1;
            if (GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1) {
               if (fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==521)
               level = 2;
               bGenIdxK=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
            }
            b->gen=level;
         }

         if (MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]>-1)
         {  
      //      cout <<fabs(GenInfo_pdgId[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]])<<endl;
            int level =0;
            if (fabs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]])==13) level = 1;
            if (GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]>-1) {
               if (GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]>-1) {
                  if (fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]])==521)
                  level = 2;
                  bGenIdxMu1=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]];
               }
            }
            b->gen+=level*100;
         }

         if (MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]>-1)
         {  
            int level =0;
            if (fabs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]])==13) level = 1;
            if (GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]>-1) {
               if (GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]>-1) {
                  if (fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]])==521)
                  level = 2;
                  bGenIdxMu2=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]];
               }
            }
            b->gen+=level*10;
         }
	 
         if (bGenIdxMu1!=-1&&bGenIdxMu1==bGenIdxMu2&&bGenIdxK==bGenIdxMu2) b->gen+=2000;

	 if(BInfo_type[j]==1 || BInfo_type[j]==2)
	   {
	     b->trk2Dxy = 0;
	     b->trk2D0Err = 0;
	     b->trk2PixelHit = 0;
	     b->trk2StripHit = 0;
	     b->trk2Pt = 0;
	     b->trk2Chi2ndf = 0;
	   }

	 else
           {
             b->trk2Dxy = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
             b->trk2D0Err = TrackInfo_d0error[BInfo_rftk2_index[j]];
             b->trk2PixelHit = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
             b->trk2StripHit = TrackInfo_striphit[BInfo_rftk2_index[j]];
             b->trk2Pt = TrackInfo_pt[BInfo_rftk2_index[j]];
             b->trk2Chi2ndf = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
           }
	 
}

void loop(){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
//   from TTree root/root
//   found on file: merged_pPbData_20131114.root
//////////////////////////////////////////////////////////

   char* infname;
   char* outfname;

   if(REAL)
     {
      cout<<"--- REAL DATA ---"<<endl;
      infname = "sample/test.root";
      outfname = "nt_data.root";
     }
   else
     {
      cout<<"--- MC ---"<<endl;
      infname = "Bfinder_all_MC_Kp.root";
      outfname = "nt_mc.root";
     }

   //File type
   TFile *f = new TFile(infname);
   TTree *root = (TTree*)f->Get("demo/root");

   //Chain type
   //TChain* root = new TChain("demo/root");
   //root->Add("/mnt/hadoop/cms/store/user/twang/HI_Btuple/20131202_PPMuon_Run2013A-PromptReco-v1_RECO/Bfinder_all_*");

   setBranch(root);
   TFile *outf = new TFile(outfname,"recreate");

   int ifchannel[7];
   ifchannel[0] = 1; //jpsi+Kp
   ifchannel[1] = 1; //jpsi+pi
   ifchannel[2] = 1; //jpsi+Ks(pi+,pi-)
   ifchannel[3] = 1; //jpsi+K*(K+,pi-)
   ifchannel[4] = 1; //jpsi+K*(K-,pi+)
   ifchannel[5] = 1; //jpsi+phi
   ifchannel[6] = 1; //jpsi+pi pi <= psi', X(3872), Bs->J/psi f0
   bNtuple* b0 = new bNtuple;
   bNtuple* b1 = new bNtuple;
   bNtuple* b2 = new bNtuple;
   bNtuple* b3 = new bNtuple;
   bNtuple* b4 = new bNtuple;
   bNtuple* b5 = new bNtuple;
   bNtuple* b6 = new bNtuple;
      
       TTree* nt0 = new TTree("ntKp","");
       b0->buildBranch(nt0);
       TTree* nt1 = new TTree("ntpi","");
       b1->buildBranch(nt1);
       TTree* nt2 = new TTree("ntKs","");
       b2->buildBranch(nt2);
       TTree* nt3 = new TTree("ntKstar1","");
       b3->buildBranch(nt3);
       TTree* nt4 = new TTree("ntKstar2","");
       b4->buildBranch(nt4);
       TTree* nt5 = new TTree("ntphi","");
       b5->buildBranch(nt5);
       TTree* nt6 = new TTree("ntmix","");
       b6->buildBranch(nt6);

   Long64_t nentries = root->GetEntries();
   Long64_t nbytes = 0;
   TVector3* bP = new TVector3;
   TVector3* bVtx = new TVector3;

   for (Long64_t i=0; i<nentries;i++) {
      nbytes += root->GetEntry(i);
      if (i%10000==0) cout <<i<<" / "<<nentries<<endl;
      for (int j=0;j<BInfo_size;j++) {
	if(BInfo_type[j]>7) continue;
	if (ifchannel[BInfo_type[j]-1]!=1) continue;
	if(BInfo_type[j]==1)
	  {
	    fillTree(b0,bP,bVtx,j);
	    nt0->Fill();
	  }
	if(BInfo_type[j]==2)
	  {
	    fillTree(b1,bP,bVtx,j);
	    nt1->Fill();
	  }
	if(BInfo_type[j]==3)
	  {
	    fillTree(b2,bP,bVtx,j);
	    nt2->Fill();
	  }
	if(BInfo_type[j]==4)
	  {
	    fillTree(b3,bP,bVtx,j);
	    nt3->Fill();
	  }
	if(BInfo_type[j]==5)
	  {
	    fillTree(b4,bP,bVtx,j);
	    nt4->Fill();
	  }
	if(BInfo_type[j]==6)
	  {
	    fillTree(b5,bP,bVtx,j);
	    nt5->Fill();
	  }
	if(BInfo_type[j]==7)
	  {
	    fillTree(b6,bP,bVtx,j);
	    nt6->Fill();
	  }
	
	 
      }
   }

  nt0->SetAlias("LD","4.239e-03*abs(trk1Dxy)/trk1D0Err +chi2ndf*1.168e-03+trk1Chi2ndf*4.045e-04+trk1PixelHit*1.595e-04+trk1StripHit*3.943e-05");
  outf->Write();
  outf->Close();
}

