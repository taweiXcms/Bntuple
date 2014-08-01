#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000

const int nBins = 10;
double trkPtCut=0.9;
double ptmax=60.;
double ptmin=10.;

void Acceptance(){

  TH1D* LoopGen(TTree*,double,double);
  TH1D* LoopAccNum(TTree*,double,double);
  TH1D* LoopAccNum(TTree*,double,double);
  
  TString infnamemc="/data/bmeson/MC/nt_MixMC_20140503_Kp__TriggerMatchingMuon_EvtBase_skim.root";
  TFile *filemc = new TFile(infnamemc.Data());
  TTree *nt_mcgen = (TTree*)filemc->Get("ntGen");
  TTree *nt = (TTree*)filemc->Get("ntKp");
  
  TFile*fileinputreweight=new TFile("../InputFile/InputFilesMCData.root");

  TH1D *hPtData = (TH1D*)fileinputreweight->Get("hPtData");
  TH1D *hPtMC = (TH1D*)fileinputreweight->Get("hPtData");
  TH1D *hyData = (TH1D*)fileinputreweight->Get("hPtData");
  TH1D *hyMC = (TH1D*)fileinputreweight->Get("hPtData");
  
  TH1D*hReweightDataOverMC_Pt=(TH1D*)hPtData->Clone("hReweightDataOverMC_Pt");
  TH1D*hReweightDataOverMC_y=(TH1D*)hyData->Clone("hReweightDataOverMC_y");
  
  hReweightDataOverMC_Pt->Divide(hPtMC);
  hReweightDataOverMC_y->Divide(hyMC);
  
  TH1D *hPtAccNumVsPt = new TH1D("hPtAccNumVsPt","",nBins,10.,60.);
  TH1D *hPtAccDenVsPt = new TH1D("hPtAccDenVsPt","",nBins,10.,60.);
  
  hPtAccNumVsPt->Sumw2();
  hPtAccDenVsPt->Sumw2();
  
  
  
  bool cut_yvsRun,cut_pt,cut_trk1Pt,cut_trk1eta,cut_mu1acc,cut_mu2acc;
  
  int Run,size;
  Float_t pdgId[NUM_BX];
  Float_t isSignal[NUM_BX];
  Float_t y[NUM_BX];
  Float_t pt[NUM_BX];
  Float_t mu1eta[NUM_BX];
  Float_t mu2eta[NUM_BX];
  Float_t mu1pt[NUM_BX];
  Float_t mu2pt[NUM_BX];
  Float_t mu1p[NUM_BX];
  Float_t mu2p[NUM_BX];
  Float_t trk1Pt[NUM_BX];
  Float_t trk1eta[NUM_BX];
  
  nt_mcgen->SetBranchAddress("size",&size);
  nt_mcgen->SetBranchAddress("pdgId",pdgId);
  nt_mcgen->SetBranchAddress("isSignal",isSignal);
  nt_mcgen->SetBranchAddress("y",y);
  nt_mcgen->SetBranchAddress("pt",pt);
  nt_mcgen->SetBranchAddress("mu1eta",mu1eta);
  nt_mcgen->SetBranchAddress("mu2eta",mu2eta);
  nt_mcgen->SetBranchAddress("mu1pt",mu1pt);
  nt_mcgen->SetBranchAddress("mu2pt",mu2pt);
  nt_mcgen->SetBranchAddress("mu1p",mu1p);
  nt_mcgen->SetBranchAddress("mu2p",mu2p);
  nt_mcgen->SetBranchAddress("tk1pt",trk1Pt);
  nt_mcgen->SetBranchAddress("tk1eta",trk1eta);
  nt->SetBranchAddress("Run",&Run);

  Int_t entries = (Int_t)nt_mcgen->GetEntries();
  
  for (int i=0; i<entries; i++) {
    nt_mcgen->GetEntry(i);        
    nt->GetEntry(i);        
    for(int j=0;j<size;j++){
      cut_yvsRun=((Run<=1&&abs(y[j]+0.465)<1.93)||(Run>1&&abs(y[j]-0.465)<1.93))&&abs(pdgId[j])==521&&isSignal[j]==1;
      //cut_yvsRun=abs(y[j])<2.4&&abs(pdgId[j])==521&&isSignal[j]==1;
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      if(cut_pt&&cut_yvsRun) {
        hPtAccDenVsPt->Fill(pt[j]);  
        cut_mu1acc=(abs(mu1eta[j])<1.3&&mu1pt[j]>3.3)||(abs(mu1eta[j])>1.3&&abs(mu1eta[j])<2.2&&mu1p[j]>2.9)||(abs(mu1eta[j])>2.2&&abs(mu1eta[j])<2.4&&mu1pt[j]>0.8);
	    cut_mu2acc=(abs(mu2eta[j])<1.3&&mu2pt[j]>3.3)||(abs(mu2eta[j])>1.3&&abs(mu2eta[j])<2.2&&mu2p[j]>2.9)||(abs(mu2eta[j])>2.2&&abs(mu2eta[j])<2.4&&mu2pt[j]>0.8);
	    cut_trk1Pt=(trk1Pt[j]>trkPtCut);
	    cut_trk1eta=(abs(trk1eta[j])<2.4);
        if(cut_mu1acc&&cut_mu2acc&&cut_trk1Pt&&cut_trk1eta){
          hPtAccNumVsPt->Fill(pt[j]);  
        }
      }    	  
  	}//loop over candidates
  }// loop over events

  
  TH1D *hAccVsPt = (TH1D*)hPtAccNumVsPt->Clone("hAccVsPt");  
  hAccVsPt->Sumw2();
  hAccVsPt->Divide(hAccVsPt, hPtAccDenVsPt, 1.0, 1.0, "B");

  TFile*fileoutput=new TFile("Results/outputBplus.root","recreate");
  fileoutput->cd();
  hAccVsPt->Write();
  hPtAccNumVsPt->Write();
  hPtAccDenVsPt->Write();  
  
  TCanvas*canvasreweight=new TCanvas("canvasreweight","canvasreweight",1000,500);
  canvasreweight->Divide(2,1);
  canvasreweight->cd(1);
  hReweightDataOverMC_Pt->Draw();
  canvasreweight->cd(2);
  hReweightDataOverMC_y->Draw();
  
}
