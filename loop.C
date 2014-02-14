#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>

#include "loop.h"

#define REAL 0 //1:real data; 0:MC

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


  void buildBranch(TTree* nt){
    nt->Branch("mass",&mass);
    nt->Branch("pt",&pt);
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
      infname = "/net/hidsk0001/d00/scratch/yjlee/bmeson/merged_pPbData_20131114.root";
      outfname = "nt_data.root";
     }
   else
     {
      cout<<"--- MC ---"<<endl;
      infname = "/net/hisrv0001/home/jwang/myPublic/Bfinder_all_full_20140212/Bfinder_all_MC_Kp.root";
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
   ifchannel[1] = 0; //jpsi+pi
   ifchannel[2] = 0; //jpsi+Ks(pi+,pi-)
   ifchannel[3] = 0; //jpsi+K*(K+,pi-)
   ifchannel[4] = 0; //jpsi+K*(K-,pi+)
   ifchannel[5] = 0; //jpsi+phi
   ifchannel[6] = 0; //jpsi+pi pi <= psi', X(3872), Bs->J/psi f0
   
   if(ifchannel[0]==1)
     {
       bNtuple* b0 = new bNtuple;
       TTree* nt0 = new TTree("ntKp","");
       b0->buildBranch(nt0);
     }
   if(ifchannel[1]==1)
     {
       bNtuple* b1 = new bNtuple;
       TTree* nt1 = new TTree("ntpi","");
       b1->buildBranch(nt1);
     }
   if(ifchannel[2]==1)
     {
       bNtuple* b2 = new bNtuple;
       TTree* nt2 = new TTree("ntKs","");
       b2->buildBranch(nt2);
     }
   if(ifchannel[3]==1)
     {
       bNtuple* b3 = new bNtuple;
       TTree* nt3 = new TTree("ntKstar1","");
       b3->buildBranch(nt3);
     }
   if(ifchannel[4]==1)
     {
       bNtuple* b4 = new bNtuple;
       TTree* nt4 = new TTree("ntKstar2","");
       b4->buildBranch(nt4);
     }
   if(ifchannel[5]==1)
     {
       bNtuple* b5 = new bNtuple;
       TTree* nt5 = new TTree("ntphi","");
       b5->buildBranch(nt5);
     }
   if(ifchannel[6]==1)
     {
       bNtuple* b6 = new bNtuple;
       TTree* nt6 = new TTree("ntmix","");
       b6->buildBranch(nt6);
     }

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

  outf->Write();
  outf->Close();
}
