#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000

Float_t trkPtCut=0.7;
Float_t chi2clCut=9.94e-02;
Float_t d0d0ErrCut=6.08;
Float_t cosdthetaCut=7.93e-01;
Float_t mumumassCut=0.15;
Float_t tktkmassCut=0.10;
Float_t mintktkmassCut=0.85;

const int nBins = 3;
double ptBins[nBins+1] = {10,15,20,60};


double funcweight(double mypt){

  double myweight=27.493+mypt*(-0.218769);
  return myweight;
}

void LoopB0(TString cutconfig="newcutopt8"){

  TH1D* Loop(TTree*,double,double,int);
  TH1D* LoopGen(TTree*,double,double);
  
  TString infname_data="/data/bmeson/data/nt_20140607_PAMuon_HIRun2013_Merged.root";
  TString infname_mc="/data/bmeson/MC/nt_MixMC_20140503_Kstar__TriggerMatchingMuon_EvtBase_skim.root";

  TFile *inf_data = new TFile(infname_data.Data());
  TFile *inf_mc = new TFile(infname_mc.Data());
  
  TTree *nt_data = (TTree*) inf_data->Get("ntKstar");
  TTree *nt_mc = (TTree*) inf_mc->Get("ntKstar");
  
  TTree *nt_mcgen = (TTree*)inf_mc->Get("ntGen");
  nt_mcgen->AddFriend(nt_mc);
  
  
  TH1D *hMass1=Loop(nt_data,10.,15.,1);
  TH1D *hMass2=Loop(nt_data,15.,20.,1);
  TH1D *hMass3=Loop(nt_data,20.,60.,1);
  
  TH1D *hMassMC1=Loop(nt_mc,10.,15.,2);
  TH1D *hMassMC2=Loop(nt_mc,15.,20.,2);
  TH1D *hMassMC3=Loop(nt_mc,20.,60.,2);
  
  TH1D *hPtMC=Loop(nt_mc,10.,60.,3);
  TH1D *hPtGen=LoopGen(nt_mcgen,10.,60.);
  
  TFile*fB0output=new TFile(Form("ResultsLoopBzero/B0output_%s.root",cutconfig.Data()),"recreate");
  fB0output->cd();
  hMass1->SetName("hMass1");
  hMass2->SetName("hMass2");
  hMass3->SetName("hMass3");
  hMassMC1->SetName("hMassMC1");
  hMassMC2->SetName("hMassMC2");
  hMassMC3->SetName("hMassMC3");
  hPtMC->SetName("hPtMC");
  hPtGen->SetName("hPtGen");

  hMass1->Write();
  hMass2->Write();
  hMass3->Write();
  hMassMC1->Write();
  hMassMC2->Write();
  hMassMC3->Write(); 
  hPtMC->Write();
  hPtGen->Write();
  
  fB0output->Close();

}


void TestNPBackground(){

  TH1D* Loop(TTree*,double,double,int);

  TString infname_mcNP="/data/ginnocen/InclusiveNonPromptMC/nt_BoostedMC_20140506_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root";
  TFile *inf_mcNP = new TFile(infname_mcNP.Data());
  TTree *nt_mcNP = (TTree*) inf_mcNP->Get("ntKstar");

  
  TH1D *hMassBkg=Loop(nt_mcNP,10.,60.,4);
  
  TFile*fB0output=new TFile("ResultsLoopBzero/B0outputBkgCutInv10.root","recreate");
  fB0output->cd();
  hMassBkg->SetName("hMassBkg");
  hMassBkg->Write();
  fB0output->Close();

}

TH1D* Loop(TTree* ntuple,double ptmin,double ptmax,int option=1){

  double funcweight(double);

  bool cut_yvsRun,cut_pt,cut_mumumass,cut_HLT_PAMu3_v1,cut_mass;
  bool cut_trk1Pt,cut_trk2Pt,cut_chi2cl,cut_d0d0err;
  bool cut_dtheta,cut_tktkmass;

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
  Float_t gen[NUM_BX];

  int bestchi2index;
  Float_t bestchi2;

  ntuple->SetBranchAddress("Run",&Run);
  ntuple->SetBranchAddress("y",y);
  ntuple->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  ntuple->SetBranchAddress("size",&size);
  ntuple->SetBranchAddress("mumumass",mumumass);
  ntuple->SetBranchAddress("mass",mass);
  ntuple->SetBranchAddress("isbestchi2",isbestchi2);
  ntuple->SetBranchAddress("trk1Pt",trk1Pt);
  ntuple->SetBranchAddress("trk2Pt",trk2Pt);
  ntuple->SetBranchAddress("chi2cl",chi2cl);
  ntuple->SetBranchAddress("d0Err",d0Err);
  ntuple->SetBranchAddress("d0",d0);
  ntuple->SetBranchAddress("dtheta",dtheta);
  ntuple->SetBranchAddress("tktkmass",tktkmass);
  ntuple->SetBranchAddress("Event",&Event);
  ntuple->SetBranchAddress("pt",pt);
  if(option==2 || option==3 || option==4) ntuple->SetBranchAddress("gen",gen);


  TH1D *h = new TH1D("h","h",30,5.03,5.93);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);

  Int_t entries = (Int_t)ntuple->GetEntries();
  
  for (int i=0; i<entries; i++) {
    ntuple->GetEntry(i);
        
    bestchi2index=-999;
    bestchi2=-999.;
    
    for(int j=0;j<size;j++){
    
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      cut_d0d0err=((d0[j]/d0Err[j])>d0d0ErrCut);
      if(!cut_pt) continue;
      if(!cut_d0d0err) continue;
      
      cut_yvsRun=false;
	  if(option==1 || option==2) cut_yvsRun=((Run>1&&Run<12&&abs(y[j]-0.465)<1.93)||(Run<=1&&abs(y[j]+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93));
   	  if(option==3) cut_yvsRun=((Run>1&&Run<12&&abs(y[j]-0.465)<1.93)||(Run<=1&&abs(y[j]+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(gen[j]==23333||gen[j]==41000);
   	  if(option==4) cut_yvsRun=((Run>1&&Run<12&&abs(y[j]-0.465)<1.93)||(Run<=1&&abs(y[j]+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y[j]+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y[j]-0.465)<1.93))&&(!(gen[j]==23333||gen[j]==41000));

	  cut_HLT_PAMu3_v1=(HLT_PAMu3_v1);
	  cut_mass=((mass[j]>5.)&&(mass[j]<6.));
	  cut_trk1Pt=(trk1Pt[j]>trkPtCut);
	  cut_trk2Pt=(trk2Pt[j]>trkPtCut);
	  cut_chi2cl=(chi2cl[j]>chi2clCut);
	  
  	  cut_dtheta=(cos(dtheta[j])>cosdthetaCut);
  	  cut_mumumass=abs(mumumass[j]-3.096916)<mumumassCut;
  	  cut_tktkmass=abs(tktkmass[j]-0.89594)<tktkmassCut&&(tktkmass[j]>mintktkmassCut);
  	    	  
      if(cut_yvsRun&&cut_HLT_PAMu3_v1&&cut_mass&&cut_trk1Pt&&cut_trk2Pt&&cut_chi2cl&&cut_dtheta&&cut_mumumass&&cut_tktkmass){
        if(chi2cl[j]>bestchi2) {bestchi2=chi2cl[j]; bestchi2index=j;}
        //h->Fill(mass[j]);  	  
  	  }//candidate seleection
  	}//loop over candidates
  	
  	if(bestchi2index>-1 ){
  	  h->Fill(mass[bestchi2index]);
  	  hPtMC->Fill(pt[bestchi2index],funcweight(pt[bestchi2index]));
  	}
  
  }// loop over events
  if(option==1 || option==2 || option==4) return h;
  else return hPtMC; 
}


TH1D* LoopGen(TTree* ntuple,double ptmin,double ptmax){

  double funcweight(double);

  int Run,size;
  bool cut_yvsRun,cut_pt;
  Float_t gen[NUM_BX];
  Float_t pdgId[NUM_BX];
  Float_t isSignal[NUM_BX];
  Float_t y[NUM_BX];
  Float_t pt[NUM_BX];
  

  ntuple->SetBranchAddress("size",&size);
  ntuple->SetBranchAddress("Run",&Run);
  ntuple->SetBranchAddress("gen",gen);
  ntuple->SetBranchAddress("pdgId",pdgId);
  ntuple->SetBranchAddress("isSignal",isSignal);
  ntuple->SetBranchAddress("y",y);
  ntuple->SetBranchAddress("pt",pt);

  TH1D *hPtMCGen = new TH1D("hPtMCGen","",nBins,ptBins);

  Int_t entries = (Int_t)ntuple->GetEntries();
  
  for (int i=0; i<entries; i++) {
    ntuple->GetEntry(i);
        
    for(int j=0;j<size;j++){
    
      cut_yvsRun=((Run<=1&&abs(y[j]+0.465)<1.93)||(Run>1&&abs(y[j]-0.465)<1.93))&&abs(pdgId[j])==511&&isSignal[j]!=0;
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      if(cut_yvsRun&&cut_pt) hPtMCGen->Fill(pt[j],funcweight(pt[j]));
          	  
  	}//loop over candidates
  }// loop over events

  return hPtMCGen; 
}

