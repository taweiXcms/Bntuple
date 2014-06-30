#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;
double setparam3=0.03;
double fixparam2=0.04;

Float_t trkPtCut=0.7;
Float_t chi2clCut=1.65*0.1;
Float_t d0d0ErrCut=4.16;
Float_t cosdthetaCut=7.50*0.1;
Float_t mumumassCut=0.15;
Float_t tktkmassCut;

bool cut_yvsRun_data,cut_pt_data,cut_mumumass_data,cut_HLT_PAMu3_v1_data,cut_mass_data;
bool cut_trk1Pt_data,cut_trk2Pt_data,cut_chi2cl_data,cut_d0d0err_data;
bool cut_dtheta_data,cut_tktkmass_data,cut_isbestchi2_data;

bool cut_yvsRun_mc,cut_pt_mc,cut_mumumass_mc,cut_HLT_PAMu3_v1_mc,cut_mass_mc;
bool cut_trk1Pt_mc,cut_trk2Pt_mc,cut_chi2cl_mc,cut_d0d0err_mc;
bool cut_dtheta_mc,cut_tktkmass_mc,cut_isbestchi2_mc;

bool cut_yvsRun_mcNP,cut_pt_mcNP,cut_mumumass_mcNP,cut_HLT_PAMu3_v1_mcNP,cut_mass_mcNP;
bool cut_trk1Pt_mcNP,cut_trk2Pt_mcNP,cut_chi2cl_mcNP,cut_d0d0err_mcNP;
bool cut_dtheta_mcNP,cut_tktkmass_mcNP,cut_isbestchi2_mcNP;

int Run_data,HLT_PAMu3_v1_data,size_data,Event_data;
Float_t pt_data[NUM_BX];
Float_t mumumass_data[NUM_BX];
Float_t y_data[NUM_BX];
Float_t mass_data[NUM_BX];
Float_t trk1Pt_data[NUM_BX];
Float_t trk2Pt_data[NUM_BX];
Float_t chi2cl_data[NUM_BX];
Float_t d0_data[NUM_BX];
Float_t d0Err_data[NUM_BX];
Float_t dtheta_data[NUM_BX];
Float_t tktkmass_data[NUM_BX];
Int_t isbestchi2_data[NUM_BX];

int Run_mc,HLT_PAMu3_v1_mc,size_mc,Event_mc;
Float_t pt_mc[NUM_BX];
Float_t mumumass_mc[NUM_BX];
Float_t y_mc[NUM_BX];
Float_t mass_mc[NUM_BX];
Float_t trk1Pt_mc[NUM_BX];
Float_t trk2Pt_mc[NUM_BX];
Float_t chi2cl_mc[NUM_BX];
Float_t d0_mc[NUM_BX];
Float_t d0Err_mc[NUM_BX];
Float_t dtheta_mc[NUM_BX];
Float_t tktkmass_mc[NUM_BX];
Int_t isbestchi2_mc[NUM_BX];
Float_t gen_mc[NUM_BX];

int Run_mcNP,HLT_PAMu3_v1_mcNP,size_mcNP,Event_mcNP;
Float_t pt_mcNP[NUM_BX];
Float_t mumumass_mcNP[NUM_BX];
Float_t y_mcNP[NUM_BX];
Float_t mass_mcNP[NUM_BX];
Float_t trk1Pt_mcNP[NUM_BX];
Float_t trk2Pt_mcNP[NUM_BX];
Float_t chi2cl_mcNP[NUM_BX];
Float_t d0_mcNP[NUM_BX];
Float_t d0Err_mcNP[NUM_BX];
Float_t dtheta_mcNP[NUM_BX];
Float_t tktkmass_mcNP[NUM_BX];
Int_t isbestchi2_mcNP[NUM_BX];
Float_t gen_mcNP[NUM_BX];

int bestchi2index_data;
Float_t bestchi2_data;
  
int bestchi2index_mc;
Float_t bestchi2_mc;
  
int bestchi2index_mcNP;
Float_t bestchi2_mcNP;


void StudyB0bkg_MCdata(Int_t icut=1){

  TString infname_data="/data/bmeson/data/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
  //TString infname_data="/afs/cern.ch/work/g/ginnocen/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root";
  TString infname_mc="/data/bmeson/MC/nt_MixMC_20140503_Kstar__TriggerMatchingMuon_EvtBase_skim.root";
  TString infname_mcNP="/afs/cern.ch/work/g/ginnocen/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root";
  
  TFile *inf_data = new TFile(infname_data.Data());
  TTree *nt_data = (TTree*) inf_data->Get("ntKstar");
  
  TFile *inf_mc = new TFile(infname_mc.Data());
  TTree *nt_mc = (TTree*) inf_mc->Get("ntKstar");
  
  TFile *inf_mcNP = new TFile(infname_mcNP.Data());
  TTree *nt_mcNP = (TTree*) inf_mcNP->Get("ntKstar");

  nt_data->SetBranchAddress("Run",&Run_data);
  nt_data->SetBranchAddress("y",y_data);
  nt_data->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1_data);
  nt_data->SetBranchAddress("size",&size_data);
  nt_data->SetBranchAddress("mumumass",mumumass_data);
  nt_data->SetBranchAddress("mass",mass_data);
  nt_data->SetBranchAddress("isbestchi2",isbestchi2_data);
  nt_data->SetBranchAddress("trk1Pt",trk1Pt_data);
  nt_data->SetBranchAddress("trk2Pt",trk2Pt_data);
  nt_data->SetBranchAddress("chi2cl",chi2cl_data);
  nt_data->SetBranchAddress("d0Err",d0Err_data);
  nt_data->SetBranchAddress("d0",d0_data);
  nt_data->SetBranchAddress("dtheta",dtheta_data);
  nt_data->SetBranchAddress("tktkmass",tktkmass_data);
  nt_data->SetBranchAddress("Event",&Event_data);
  nt_data->SetBranchAddress("pt",pt_data);
  
  nt_mc->SetBranchAddress("Run",&Run_mc);
  nt_mc->SetBranchAddress("y",y_mc);
  nt_mc->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1_mc);
  nt_mc->SetBranchAddress("size",&size_mc);
  nt_mc->SetBranchAddress("mumumass",mumumass_mc);
  nt_mc->SetBranchAddress("mass",mass_mc);
  nt_mc->SetBranchAddress("isbestchi2",isbestchi2_mc);
  nt_mc->SetBranchAddress("trk1Pt",trk1Pt_mc);
  nt_mc->SetBranchAddress("trk2Pt",trk2Pt_mc);
  nt_mc->SetBranchAddress("chi2cl",chi2cl_mc);
  nt_mc->SetBranchAddress("d0Err",d0Err_mc);
  nt_mc->SetBranchAddress("d0",d0_mc);
  nt_mc->SetBranchAddress("dtheta",dtheta_mc);
  nt_mc->SetBranchAddress("tktkmass",tktkmass_mc);
  nt_mc->SetBranchAddress("Event",&Event_mc);
  nt_mc->SetBranchAddress("pt",pt_mc);
  nt_mc->SetBranchAddress("gen",gen_mc);
    
  nt_mcNP->SetBranchAddress("Run",&Run_mcNP);
  nt_mcNP->SetBranchAddress("y",y_mcNP);
  nt_mcNP->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1_mcNP);
  nt_mcNP->SetBranchAddress("size",&size_mcNP);
  nt_mcNP->SetBranchAddress("mumumass",mumumass_mcNP);
  nt_mcNP->SetBranchAddress("mass",mass_mcNP);
  nt_mcNP->SetBranchAddress("isbestchi2",isbestchi2_mcNP);
  nt_mcNP->SetBranchAddress("trk1Pt",trk1Pt_mcNP);
  nt_mcNP->SetBranchAddress("trk2Pt",trk2Pt_mcNP);
  nt_mcNP->SetBranchAddress("chi2cl",chi2cl_mcNP);
  nt_mcNP->SetBranchAddress("d0Err",d0Err_mcNP);
  nt_mcNP->SetBranchAddress("d0",d0_mcNP);
  nt_mcNP->SetBranchAddress("dtheta",dtheta_mcNP);
  nt_mcNP->SetBranchAddress("tktkmass",tktkmass_mcNP);
  nt_mcNP->SetBranchAddress("Event",&Event_mcNP);
  nt_mcNP->SetBranchAddress("pt",pt_mcNP);
  nt_mcNP->SetBranchAddress("gen",gen_mcNP);
  
    
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
  
  TH1D *hInvMassSelected_data = new TH1D("hInvMassSelected_data","hInvMassSelected_data",30,5.03,5.93);
  TH1D *hInvMassSelectedWrongMethod_data = new TH1D("hInvMassSelectedWrongMethod_data","hInvMassSelectedWrongMethod_data",30,5.03,5.93);
  TH1D *hInvMassAll_data = new TH1D("hInvMassAll_data","hInvMassAll_data",30,5.03,5.93);
  
  TH1D *hInvMassSelected_mc = new TH1D("hInvMassSelected_mc","hInvMassSelected_mc",30,5.03,5.93);
  TH1D *hInvMassSelectedWrongMethod_mc = new TH1D("hInvMassSelectedWrongMethod_mc","hInvMassSelectedWrongMethod_mc",30,5.03,5.93);
  TH1D *hInvMassAll_mc = new TH1D("hInvMassAll_mc","hInvMassAll_mc",30,5.03,5.93);

  TH1D *hInvMassSelected_mcNP = new TH1D("hInvMassSelected_mcNP","hInvMassSelected_mcNP",30,5.03,5.93);
  TH1D *hInvMassSelectedWrongMethod_mcNP = new TH1D("hInvMassSelectedWrongMethod_mcNP","hInvMassSelectedWrongMethod_mcNP",30,5.03,5.93);
  TH1D *hInvMassAll_mcNP = new TH1D("hInvMassAll_mcNP","hInvMassAll_mcNP",30,5.03,5.93);

  Int_t entries_data = (Int_t)nt_data->GetEntries();
  Int_t entries_mc = (Int_t)nt_mc->GetEntries();
  Int_t entries_mcNP = (Int_t)nt_mcNP->GetEntries();
  
  entries_data=1;  

  for (int i=0; i<entries_data; i++) {
    nt_data->GetEntry(i);
        
    bestchi2index_data=-999;
    bestchi2_data=-999.;
    
    for(int j=0;j<size_data;j++){
  
	  cut_yvsRun_data=((Run_data>1&&Run_data<12&&abs(y_data[j]-0.465)<1.93)||(Run_data<=1&&abs(y_data[j]+0.465)<1.93)||(Run_data>=210498&&Run_data<=211256&&abs(y_data[j]+0.465)<1.93)||(Run_data>=211313&&Run_data<=211631&&abs(y_data[j]-0.465)<1.93));
   	  cut_pt_data=((pt_data[j]>10.)&&(pt_data[j]<60.));
	  cut_HLT_PAMu3_v1_data=(HLT_PAMu3_v1_data);
	  cut_mass_data=((mass_data[j]>5.)&&(mass_data[j]<6.));
	  cut_trk1Pt_data=(trk1Pt_data[j]>trkPtCut);
	  cut_trk2Pt_data=(trk2Pt_data[j]>trkPtCut);
	  cut_chi2cl_data=(chi2cl_data[j]>chi2clCut);
	  cut_d0d0err_data=((d0_data[j]/d0Err_data[j])>d0d0ErrCut);
  	  cut_dtheta_data=(cos(dtheta_data[j])>cosdthetaCut);
  	  cut_mumumass_data=abs(mumumass_data[j]-3.096916)<mumumassCut;
  	  cut_tktkmass_data=abs(tktkmass_data[j]-0.89594)<tktkmassCut;
  	  cut_isbestchi2_data=(isbestchi2_data[j]==1);
  	  
  	  hInvMassAll_data->Fill(mass_data[j]);
  	  
      if(cut_yvsRun_data&&cut_pt_data&&cut_HLT_PAMu3_v1_data&&cut_mass_data&&cut_trk1Pt_data&&cut_trk2Pt_data&&cut_chi2cl_data&&cut_d0d0err_data&&cut_dtheta_data&&cut_mumumass_data&&cut_tktkmass_data){
        if(cut_isbestchi2_data) hInvMassSelectedWrongMethod_data->Fill(mass_data[j]);
        if(chi2cl_data[j]>bestchi2_data) {bestchi2_data=chi2cl_data[j]; bestchi2index_data=j;}
          	  
  	  }//candidate seleection
  	}//loop over candidates
  	hInvMassSelected_data->Fill(mass_data[bestchi2index_data]);

  }// loop over events


  for (int i=0; i<entries_mc; i++) {
    nt_mc->GetEntry(i);
        
    bestchi2index_mc=-999;
    bestchi2_mc=-999.;
    
    for(int j=0;j<size_mc;j++){
	  cut_yvsRun_mc=((Run_mc<=1&&abs(y_mc[j]+0.465)<1.93)||(Run_mc>1&&abs(y_mc[j]-0.465)<1.93))&&(gen_mc[j]==23333||gen_mc[j]==41000);
   	  cut_pt_mc=((pt_mc[j]>10.)&&(pt_mc[j]<60.));
	  cut_HLT_PAMu3_v1_mc=(HLT_PAMu3_v1_mc);
	  cut_mass_mc=((mass_mc[j]>5.)&&(mass_mc[j]<6.));
	  cut_trk1Pt_mc=(trk1Pt_mc[j]>trkPtCut);
	  cut_trk2Pt_mc=(trk2Pt_mc[j]>trkPtCut);
	  cut_chi2cl_mc=(chi2cl_mc[j]>chi2clCut);
	  cut_d0d0err_mc=((d0_mc[j]/d0Err_mc[j])>d0d0ErrCut);
  	  cut_dtheta_mc=(cos(dtheta_mc[j])>cosdthetaCut);
  	  cut_mumumass_mc=abs(mumumass_mc[j]-3.096916)<mumumassCut;
  	  cut_tktkmass_mc=abs(tktkmass_mc[j]-0.89594)<tktkmassCut;
  	  cut_isbestchi2_mc=(isbestchi2_mc[j]==1);
  	  
  	  hInvMassAll_mc->Fill(mass_mc[j]);
  	  
      if(cut_yvsRun_mc&&cut_pt_mc&&cut_HLT_PAMu3_v1_mc&&cut_mass_mc&&cut_trk1Pt_mc&&cut_trk2Pt_mc&&cut_chi2cl_mc&&cut_d0d0err_mc&&cut_dtheta_mc&&cut_mumumass_mc&&cut_tktkmass_mc){
        if(cut_isbestchi2_mc) hInvMassSelectedWrongMethod_mc->Fill(mass_mc[j]);
        if(chi2cl_mc[j]>bestchi2_mc) {bestchi2_mc=chi2cl_mc[j]; bestchi2index_mc=j;}
          	  
  	  }//candidate seleection
  	}//loop over candidates
  	hInvMassSelected_mc->Fill(mass_mc[bestchi2index_mc]);

  }// loop over events

  for (int i=0; i<entries_mcNP; i++) {
    nt_mcNP->GetEntry(i);
        
    bestchi2index_mcNP=-999;
    bestchi2_mcNP=-999.;
    
    for(int j=0;j<size_mcNP;j++){
      //continue;
      if(gen_mcNP[j]==23333) continue;
      if(gen_mcNP[j]==41000) continue;
	  cut_yvsRun_mcNP=((Run_mcNP<=1&&abs(y_mcNP[j]+0.465)<1.93)||(Run_mcNP>1&&abs(y_mcNP[j]-0.465)<1.93));
   	  cut_pt_mcNP=((pt_mcNP[j]>10.)&&(pt_mcNP[j]<60.));
	  cut_HLT_PAMu3_v1_mcNP=(HLT_PAMu3_v1_mcNP);
	  cut_mass_mcNP=((mass_mcNP[j]>5.)&&(mass_mcNP[j]<6.));
	  cut_trk1Pt_mcNP=(trk1Pt_mcNP[j]>trkPtCut);
	  cut_trk2Pt_mcNP=(trk2Pt_mcNP[j]>trkPtCut);
	  cut_chi2cl_mcNP=(chi2cl_mcNP[j]>chi2clCut);
	  cut_d0d0err_mcNP=((d0_mcNP[j]/d0Err_mcNP[j])>d0d0ErrCut);
  	  cut_dtheta_mcNP=(cos(dtheta_mcNP[j])>cosdthetaCut);
  	  cut_mumumass_mcNP=abs(mumumass_mcNP[j]-3.096916)<mumumassCut;
  	  cut_tktkmass_mcNP=abs(tktkmass_mcNP[j]-0.89594)<tktkmassCut;
  	  cut_isbestchi2_mcNP=(isbestchi2_mcNP[j]==1);
  	  
  	  hInvMassAll_mcNP->Fill(mass_mcNP[j]);
  	  
      if(cut_yvsRun_mcNP&&cut_pt_mcNP&&cut_HLT_PAMu3_v1_mcNP&&cut_mass_mcNP&&cut_trk1Pt_mcNP&&cut_trk2Pt_mcNP&&cut_chi2cl_mcNP&&cut_d0d0err_mcNP&&cut_dtheta_mcNP&&cut_mumumass_mcNP&&cut_tktkmass_mcNP){
        if(cut_isbestchi2_mcNP) hInvMassSelectedWrongMethod_mcNP->Fill(mass_mcNP[j]);
        if(chi2cl_mcNP[j]>bestchi2_mcNP) {bestchi2_mcNP=chi2cl_mcNP[j]; bestchi2index_mcNP=j;}
          	  
  	  }//candidate seleection
  	}//loop over candidates
  	hInvMassSelected_mcNP->Fill(mass_mcNP[bestchi2index_mcNP]);

  }// loop over events
  

  TCanvas*canvas_goodselection=new TCanvas("canvas_goodselection","canvas_goodselection",1200,500);
  canvas_goodselection->Divide(3,1);
  canvas_goodselection->cd(1);
  hInvMassSelected_data->Draw("e");
  canvas_goodselection->cd(2);
  hInvMassSelected_mc->Draw("e");
  canvas_goodselection->cd(3);
  hInvMassSelected_mcNP->Draw("e");
  canvas_goodselection->SaveAs(Form("Results/canvas_CutId%d_goodselection.eps",icut));
  
  TCanvas*canvas_badselection=new TCanvas("canvas_badselection","canvas_badselection",1200,500);
  canvas_badselection->Divide(3,1);
  canvas_badselection->cd(1);
  hInvMassSelectedWrongMethod_data->Draw("e");
  canvas_badselection->cd(2);
  hInvMassSelectedWrongMethod_mc->Draw("e");
  canvas_badselection->cd(3);
  hInvMassSelectedWrongMethod_mcNP->Draw("e");
  canvas_badselection->SaveAs(Form("Results/canvas_CutId%d_badselection.eps",icut));


  TFile*fileoutput=new TFile(Form("Results/file_CutId%d.root",icut),"recreate");
  fileoutput->cd();
  hInvMassSelected_data->Write();
  hInvMassSelected_mc->Write();
  hInvMassSelected_mcNP->Write();
  hInvMassSelectedWrongMethod_data->Write();
  hInvMassSelectedWrongMethod_mc->Write();
  hInvMassSelectedWrongMethod_mcNP->Write();

  fileoutput->Close();
  
}
