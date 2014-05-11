#include <iostream>                                                                                                                                                                                         
#include <utility>
#include <TRandom.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TCut.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TNtuple.h>
#include <TLorentzVector.h>
#define MAX_XB 8192
#define MAX_GEN 4096 
#define MAX_GEN 4096 //default 2048
#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916
#define PSI2S_MASS  3.686109

//TString inputmc="/data/bmeson/MC/nt_BoostedMC_20140510_Kp_TriggerMatchingMuon.root";
TString inputdata="/data/bmeson/data/nt_20140510_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";


//const int nBins=5;
//double ptBins[nBins+1]={10,15,20,25,30,60};

int NCandidate_All=0;
int NCandidateSingle_All=0;
int NCandidateDouble_All=0;
int NCandidateSingleAndDouble_All=0;
int NCandidateSingleAndNotDouble_All=0;
int NCandidateNotSingleAndDouble_All=0;

void StudyTriggerOverlap(){

  TFile *inf = new TFile(inputdata.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");

  int size;                                                                                                                                                                                               
  float y[MAX_GEN];
  float eta[MAX_GEN];
  float pt[MAX_GEN];
  float phi[MAX_GEN];
  float pdgId[MAX_GEN];
  float isSignal[MAX_GEN];
  float mu1pt[MAX_GEN];
  float mu2pt[MAX_GEN];
  float mu1eta[MAX_GEN];
  float mu2eta[MAX_GEN];
  
  int   HLT_PAMu3_v1;
  int HLT_PAL1DoubleMuOpen_v1;
  float y[MAX_XB];
  float pt[MAX_XB];
  float mass[MAX_XB];
  int isbestchi2[MAX_XB];
  float trk1Pt[MAX_XB];
  float trk2Pt[MAX_XB];
  float chi2cl[MAX_XB];
  float d0[MAX_XB];
  float d0Err[MAX_XB];
  float dtheta[MAX_XB];
  float tktkmass[MAX_XB];
  float mumumass[MAX_XB];
  float gen[MAX_XB];
  float mu1pt[MAX_XB];
  float mu2pt[MAX_XB];
  float mu1eta[MAX_XB];
  float mu2eta[MAX_XB];

  nt->SetBranchAddress("size",&size);
  nt->SetBranchAddress("y",&y);
  nt->SetBranchAddress("eta",eta);
  nt->SetBranchAddress("phi",phi);
  nt->SetBranchAddress("pt",pt);
  nt->SetBranchAddress("pdgId",pdgId);
  nt->SetBranchAddress("isSignal",isSignal);
  nt->SetBranchAddress("mu1pt",mu1pt);
  nt->SetBranchAddress("mu2pt",mu2pt);
  nt->SetBranchAddress("mu1eta",mu1eta);
  nt->SetBranchAddress("mu2eta",mu2eta);
  nt->SetBranchAddress("size",&size);
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  nt->SetBranchAddress("HLT_PAL1DoubleMuOpen_v1",&HLT_PAL1DoubleMuOpen_v1);
  nt->SetBranchAddress("pt",pt);
  nt->SetBranchAddress("y",y);
  nt->SetBranchAddress("mass",mass);
  nt->SetBranchAddress("isbestchi2",isbestchi2);
  nt->SetBranchAddress("trk1Pt",trk1Pt);
  nt->SetBranchAddress("trk2Pt",trk2Pt);
  nt->SetBranchAddress("chi2cl",chi2cl);
  nt->SetBranchAddress("d0",d0);
  nt->SetBranchAddress("d0Err",d0Err);
  nt->SetBranchAddress("dtheta",dtheta);
  nt->SetBranchAddress("tktkmass",tktkmass);
  nt->SetBranchAddress("mumumass",mumumass);
  nt->SetBranchAddress("gen",gen);
  nt->SetBranchAddress("mu1pt",mu1pt);
  nt->SetBranchAddress("mu2pt",mu2pt);
  nt->SetBranchAddress("mu1eta",mu1eta);
  nt->SetBranchAddress("mu2eta",mu2eta);
  
  int nevents_total = nt->GetEntries();    
  nevents_total=1000000; 
  for(int entry=0; entry<nevents_total; entry++){
    if((entry%10000)==0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    nt->GetEntry(entry);

    for(int c=0; c<size; c++){
                 
      if(pt[c]>10. && pt[c]<15.){
          
        if((abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.9&& chi2cl[c]>1.32e-02&&(d0[c]/d0Err[c])>3.41&&cos(dtheta[c])>-3.46e-01)){
          NCandidate_All++;
          
          if(HLT_PAMu3_v1[c]) NCandidateSingle_All++;
          if(HLT_PAL1DoubleMuOpen_v1[c]) NCandidateDouble_All++;
          if(HLT_PAMu3_v1[c] && HLT_PAL1DoubleMuOpen_v1[c]) NCandidateSingleAndDouble_All++;
          if(HLT_PAMu3_v1[c] && !HLT_PAL1DoubleMuOpen_v1[c]) NCandidateSingleAndNotDouble_All++;
          if(!HLT_PAMu3_v1[c] && HLT_PAL1DoubleMuOpen_v1[c]) NCandidateNotSingleAndDouble_All++;

        }
      }
    }
  }
  cout<<"Invariant mass range 5<mass<6"<<endl;
  cout<<"% of candidate selected by single ="<<(double)(NCandidateSingle_All)/(double)(NCandidate_All)<<endl;
  cout<<"% of candidate selected by double ="<<(double)(NCandidateDouble_All)/(double)(NCandidate_All)<<endl;
  cout<<"% of candidate selected by single and double ="<<(double)(NCandidateSingleAndDouble_All)/(double)(NCandidate_All)<<endl;
  cout<<"% of candidate selected by single and not by double ="<<(double)(NCandidateSingleAndNotDouble_All)/(double)(NCandidate_All)<<endl;
  cout<<"% of candidate selected by double and not by single ="<<(double)(NCandidateNotSingleAndDouble_All)/(double)(NCandidate_All)<<endl;
  
}