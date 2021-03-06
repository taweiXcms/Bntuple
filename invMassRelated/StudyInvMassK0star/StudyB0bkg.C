#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000


void StudyB0bkg(Int_t icut=1){

  
  //TString infname="/data/bmeson/data/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";

  TString infname="/afs/cern.ch/work/g/ginnocen/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root";
  //TString infname="/data/bmeson/data/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
  TFile *inf = new TFile(infname.Data());
  TTree *nt = (TTree*) inf->Get("ntKstar");
    
  Float_t trkPtCut=0.7;
  Float_t chi2clCut=1.65*0.1;
  Float_t d0d0ErrCut=4.16;
  Float_t cosdthetaCut=7.50*0.1;
  Float_t mumumassCut=0.15;

  Float_t tktkmassCut;
  
  cout<<"CUT CONFIGURATION number "<<icut<<endl; 
  if(icut==1) tktkmassCut=0.01;
  if(icut==2) tktkmassCut=0.02;
  if(icut==3) tktkmassCut=0.03;
  if(icut==4) tktkmassCut=0.04;
  if(icut==5) tktkmassCut=0.05;
  if(icut==6) tktkmassCut=0.10;
  if(icut==7) tktkmassCut=0.13;
  if(icut==8) tktkmassCut=0.15;
  if(icut==9) tktkmassCut=0.18;
  if(icut==10) tktkmassCut=0.20;

  //const int nBins = 1;
  //double ptBins[nBins+1] = {10,60};

  std::vector<int> isbestchi2clarrayindex;
  std::vector<int> isbestchi2clarrayvalue;
  std::vector<int> numberofcandperevents;

  int Run,HLT_PAMu3_v1,size,Event;
  
  Float_t pt[NUM_BX];
  Float_t mumumass[NUM_BX];
  Float_t y[NUM_BX];
  Float_t mass[NUM_BX];
  Float_t trk1Pt[NUM_BX];
  Float_t trk2Pt[NUM_BX];
  Float_t chi2cl[NUM_BX];
  Float_t d0[NUM_BX];
  Float_t d0Err[NUM_BX];
  Float_t dtheta[NUM_BX];
  Float_t tktkmass[NUM_BX];
  Int_t isbestchi2[NUM_BX];


  nt->SetBranchAddress("Run",&Run);
  nt->SetBranchAddress("y",y);
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  nt->SetBranchAddress("size",&size);
  nt->SetBranchAddress("mumumass",mumumass);
  nt->SetBranchAddress("mass",mass);
  nt->SetBranchAddress("isbestchi2",isbestchi2);
  nt->SetBranchAddress("trk1Pt",trk1Pt);
  nt->SetBranchAddress("trk2Pt",trk2Pt);
  nt->SetBranchAddress("chi2cl",chi2cl);
  nt->SetBranchAddress("d0Err",d0Err);
  nt->SetBranchAddress("d0",d0);
  nt->SetBranchAddress("dtheta",dtheta);
  nt->SetBranchAddress("tktkmass",tktkmass);
  nt->SetBranchAddress("Event",&Event);
  nt->SetBranchAddress("pt",pt);
  
  TH1D *hInvMassSelected = new TH1D("hInvMassSelected","hInvMassSelected",30,5.03,5.93);
  TH1D *hInvMassSelectedWrongMethod = new TH1D("hInvMassSelectedWrongMethod","hInvMassSelectedWrongMethod",30,5.03,5.93);
  TH1D *hInvMassAll = new TH1D("hInvMassAll","hInvMassAll",30,5.03,5.93);
  
  Int_t entries = (Int_t)nt->GetEntries();
  //entries=5000000;
  
  bool cut_yvsRun,cut_pt,cut_mumumass,cut_HLT_PAMu3_v1,cut_mass;
  bool cut_trk1Pt,cut_trk2Pt,cut_chi2cl,cut_d0d0err;
  bool cut_dtheta,cut_tktkmass,cut_isbestchi2;
  
  int bestchi2index;
  int ncandperevent;
  Float_t bestchi2;
  
  for (int i=0; i<entries; i++) {
    nt->GetEntry(i);
        
    bestchi2index=-999;
    bestchi2=-999.;
    ncandperevent=0;
    
    for(int j=0;j<size;j++){
  
	  cut_yvsRun=((Run>1&&Run<12&&abs(y[j]-0.465)<1.93)||(Run<=1&&abs(y[j]+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93));
   	  cut_pt=((pt[j]>10.)&&(pt[j]<60.));
	  cut_HLT_PAMu3_v1=(HLT_PAMu3_v1);
	  cut_mass=((mass[j]>5.)&&(mass[j]<6.));
	  cut_trk1Pt=(trk1Pt[j]>trkPtCut);
	  cut_trk2Pt=(trk2Pt[j]>trkPtCut);
	  cut_chi2cl=(chi2cl[j]>chi2clCut);
	  cut_d0d0err=((d0[j]/d0Err[j])>d0d0ErrCut);
  	  cut_dtheta=(cos(dtheta[j])>cosdthetaCut);
  	  cut_mumumass=abs(mumumass[j]-3.096916)<mumumassCut;
  	  cut_tktkmass=abs(tktkmass[j]-0.89594)<tktkmassCut;
  	  cut_isbestchi2=(isbestchi2[j]==1);
  	  
  	  hInvMassAll->Fill(mass[j]);
  	  
      if(cut_yvsRun&&cut_pt&&cut_HLT_PAMu3_v1&&cut_mass&&cut_trk1Pt&&cut_trk2Pt&&cut_chi2cl&&cut_d0d0err&&cut_dtheta&&cut_mumumass&&cut_tktkmass){
        if(cut_isbestchi2) hInvMassSelectedWrongMethod->Fill(mass[j]);
        ncandperevent++;
        //cout<<"index="<<j<<", chi2cl="<<chi2cl[j]<<endl;
        if(chi2cl[j]>bestchi2) {bestchi2=chi2cl[j]; bestchi2index=j;}
          	  
  	  }//candidate seleection
  	}//loop over candidates
  	hInvMassSelected->Fill(mass[bestchi2index]);

  }// loop over events
  
  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  hInvMassSelected->Draw("e");
  canvas->cd(2);
  hInvMassSelectedWrongMethod->Draw("ep");
  canvas->SaveAs(Form("Results/canvas_CutId%d.eps",icut));
  TFile*fileoutput=new TFile(Form("Results/file_CutId%d.eps",icut),"recreate");
  fileoutput->cd();
  hInvMassSelected->Write();
  hInvMassSelectedWrongMethod->Write();
  fileoutput->Close();
  
  
}
