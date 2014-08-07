#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000


const int nBins = 5;
double ptBins[nBins+1] = {10,15,20,25,30,60};

const int nBinsy = 5;
double yBins[nBinsy+1] = {-2.4,-1.46,-0.46,0.46,1.46,2.4};

double trkPtCut=0.9;
double ptmax=60.;
double ptmin=10.;

void Acceptance(){
  
  TString infnamemc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Kp.root";
  TFile *filemc = new TFile(infnamemc.Data());
  TTree *nt_mcgen = (TTree*)filemc->Get("ntGen");
  TTree *nt = (TTree*)filemc->Get("ntKp");
  
  TFile*fileinputreweight=new TFile("../InputFile/FunctionsReweighting.root");
  TF1*fPt=(TF1*)fileinputreweight->Get("fPt");
  TF1*fy=(TF1*)fileinputreweight->Get("fy");

/*
  TH1D *hPtAccNumVsPt = new TH1D("hPtAccNumVsPt","",nBins,ptBins);
  TH1D *hPtAccNumVsPtReweight = new TH1D("hPtAccNumVsPtReweight","",nBins,ptBins);
  TH1D *hPtAccNumVsPtLow = new TH1D("hPtAccNumVsPtLow","",nBins,ptBins);
  TH1D *hPtAccNumVsPtHigh = new TH1D("hPtAccNumVsPtHigh","",nBins,ptBins);

  TH1D *hPtAccDenVsPt = new TH1D("hPtAccDenVsPt","",nBins,ptBins);
  TH1D *hPtAccDenVsPtReweight = new TH1D("hPtAccDenVsPtReweight","",nBins,ptBins);
  TH1D *hPtAccDenVsPtLow = new TH1D("hPtAccDenVsPtLow","",nBins,ptBins);
  TH1D *hPtAccDenVsPtHigh = new TH1D("hPtAccDenVsPtHigh","",nBins,ptBins);
  
  TH1D *hPtAccNumVsy = new TH1D("hPtAccNumVsy","",nBinsy,yBins);
  TH1D *hPtAccNumVsyReweight = new TH1D("hPtAccNumVsyReweight","",nBinsy,yBins);
  TH1D *hPtAccNumVsyLow = new TH1D("hPtAccNumVsyLow","",nBinsy,yBins);
  TH1D *hPtAccNumVsyHigh = new TH1D("hPtAccNumVsyHigh","",nBinsy,yBins);

  TH1D *hPtAccDenVsy = new TH1D("hPtAccDenVsy","",nBinsy,yBins);
  TH1D *hPtAccDenVsyReweight = new TH1D("hPtAccDenVsyReweight","",nBinsy,yBins);
  TH1D *hPtAccDenVsyLow = new TH1D("hPtAccDenVsyLow","",nBinsy,yBins);
  TH1D *hPtAccDenVsyHigh = new TH1D("hPtAccDenVsyHigh","",nBinsy,yBins);
*/
  TH1D *hPtAccNumVsPt = new TH1D("hPtAccNumVsPt","",40,10.,60.);
  TH1D *hPtAccNumVsPtReweight = new TH1D("hPtAccNumVsPtReweight","",40,10.,60.);
  TH1D *hPtAccNumVsPtLow = new TH1D("hPtAccNumVsPtLow","",40,10.,60.);
  TH1D *hPtAccNumVsPtHigh = new TH1D("hPtAccNumVsPtHigh","",40,10.,60.);

  TH1D *hPtAccDenVsPt = new TH1D("hPtAccDenVsPt","",40,10.,60.);
  TH1D *hPtAccDenVsPtReweight = new TH1D("hPtAccDenVsPtReweight","",40,10.,60.);
  TH1D *hPtAccDenVsPtLow = new TH1D("hPtAccDenVsPtLow","",40,10.,60.);
  TH1D *hPtAccDenVsPtHigh = new TH1D("hPtAccDenVsPtHigh","",40,10.,60.);
  
  TH1D *hPtAccNumVsy = new TH1D("hPtAccNumVsy","",40,-2.4,2.4);
  TH1D *hPtAccNumVsyReweight = new TH1D("hPtAccNumVsyReweight","",40,-2.4,2.4);
  TH1D *hPtAccNumVsyLow = new TH1D("hPtAccNumVsyLow","",40,-2.4,2.4);
  TH1D *hPtAccNumVsyHigh = new TH1D("hPtAccNumVsyHigh","",40,-2.4,2.4);

  TH1D *hPtAccDenVsy = new TH1D("hPtAccDenVsy","",40,-2.4,2.4);
  TH1D *hPtAccDenVsyReweight = new TH1D("hPtAccDenVsyReweight","",40,-2.4,2.4);
  TH1D *hPtAccDenVsyLow = new TH1D("hPtAccDenVsyLow","",40,-2.4,2.4);
  TH1D *hPtAccDenVsyHigh = new TH1D("hPtAccDenVsyHigh","",40,-2.4,2.4);

  
  hPtAccNumVsPt->Sumw2();
  hPtAccNumVsPtReweight->Sumw2();
  hPtAccNumVsPtLow->Sumw2();
  hPtAccNumVsPtHigh->Sumw2();

  hPtAccDenVsPt->Sumw2();
  hPtAccDenVsPtReweight->Sumw2();
  hPtAccDenVsPtLow->Sumw2();
  hPtAccDenVsPtHigh->Sumw2();
  
  hPtAccNumVsy->Sumw2();
  hPtAccNumVsyReweight->Sumw2();
  hPtAccNumVsyLow->Sumw2();
  hPtAccNumVsyHigh->Sumw2();

  hPtAccDenVsy->Sumw2();
  hPtAccDenVsyReweight->Sumw2();
  hPtAccDenVsyLow->Sumw2();
  hPtAccDenVsyHigh->Sumw2();

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
  
  double weightPtHigh;
  double weightPtLow;
  double weightyHigh;
  double weightyLow;

  for (int i=0; i<entries; i++) {
    nt_mcgen->GetEntry(i);        
    nt->GetEntry(i);        
    for(int j=0;j<size;j++){
    
     cut_yvsRun=Run<=1&&abs(y[j])<2.4&&abs(pdgId[j])==521&&isSignal[j]==1;
      cut_pt=((pt[j]>ptmin)&&(pt[j]<ptmax));
      if(cut_pt&&cut_yvsRun) {
      
        weightPtLow=0.016*pt[j]+0.44;
        weightPtHigh=-0.016*pt[j]+1.56;
        weightyHigh=-(0.8/4.8)*y[j]+1;
        weightyLow=+(0.8/4.8)*y[j]+1;
            
        hPtAccDenVsPt->Fill(pt[j]);  
        hPtAccDenVsPtReweight->Fill(pt[j],fy->Eval(-y[j]-0.465)); 
        hPtAccDenVsPtLow->Fill(pt[j],weightyLow);  
        hPtAccDenVsPtHigh->Fill(pt[j],weightyHigh);  

        hPtAccDenVsy->Fill(y[j]); 
        hPtAccDenVsyReweight->Fill(y[j],fPt->Eval(pt[j]));
        hPtAccDenVsyLow->Fill(y[j],weightPtLow);  
        hPtAccDenVsyHigh->Fill(y[j],weightPtHigh);  

        cut_mu1acc=(abs(mu1eta[j])<1.3&&mu1pt[j]>3.3)||(abs(mu1eta[j])>1.3&&abs(mu1eta[j])<2.2&&mu1p[j]>2.9)||(abs(mu1eta[j])>2.2&&abs(mu1eta[j])<2.4&&mu1pt[j]>0.8);
	    cut_mu2acc=(abs(mu2eta[j])<1.3&&mu2pt[j]>3.3)||(abs(mu2eta[j])>1.3&&abs(mu2eta[j])<2.2&&mu2p[j]>2.9)||(abs(mu2eta[j])>2.2&&abs(mu2eta[j])<2.4&&mu2pt[j]>0.8);
	    cut_trk1Pt=(trk1Pt[j]>trkPtCut);
	    cut_trk1eta=(abs(trk1eta[j])<2.4);
        if(cut_mu1acc&&cut_mu2acc&&cut_trk1Pt&&cut_trk1eta){
          hPtAccNumVsPt->Fill(pt[j]);  
          hPtAccNumVsPtReweight->Fill(pt[j],fy->Eval(-y[j]-0.465)); 
          hPtAccNumVsPtLow->Fill(pt[j],weightyLow);  
          hPtAccNumVsPtHigh->Fill(pt[j],weightyHigh);  

          hPtAccNumVsy->Fill(y[j]); 
          hPtAccNumVsyReweight->Fill(y[j],fPt->Eval(pt[j]));
          hPtAccNumVsyLow->Fill(y[j],weightPtLow);  
          hPtAccNumVsyHigh->Fill(y[j],weightPtHigh);  

        }
      }  	  
    }//loop over candidates
  }// loop over events

  
  TH1D *hAccVsPt = (TH1D*)hPtAccNumVsPt->Clone("hAccVsPt");  
  hAccVsPt->Sumw2();
  hAccVsPt->Divide(hAccVsPt, hPtAccDenVsPt, 1.0, 1.0, "B");
  
  TH1D *hAccVsPtReweight = (TH1D*)hPtAccNumVsPtReweight->Clone("hAccVsPtReweight");  
  hAccVsPtReweight->Sumw2();
  hAccVsPtReweight->Divide(hAccVsPtReweight, hPtAccDenVsPtReweight, 1.0, 1.0, "B");
  
  TH1D *hAccVsPtLow = (TH1D*)hPtAccNumVsPtLow->Clone("hAccVsPtLow");  
  hAccVsPtLow->Sumw2();
  hAccVsPtLow->Divide(hAccVsPtLow, hPtAccDenVsPtLow, 1.0, 1.0, "B");

  TH1D *hAccVsPtHigh = (TH1D*)hPtAccNumVsPtHigh->Clone("hAccVsPtHigh");  
  hAccVsPtHigh->Sumw2();
  hAccVsPtHigh->Divide(hAccVsPtHigh, hPtAccDenVsPtHigh, 1.0, 1.0, "B");
  
  TH1D *hAccVsy = (TH1D*)hPtAccNumVsy->Clone("hAccVsy");  
  hAccVsy->Sumw2();
  hAccVsy->Divide(hAccVsy, hPtAccDenVsy, 1.0, 1.0, "B");
  
  TH1D *hAccVsyReweight = (TH1D*)hPtAccNumVsyReweight->Clone("hAccVsyReweight");  
  hAccVsyReweight->Sumw2();
  hAccVsyReweight->Divide(hAccVsyReweight, hPtAccDenVsyReweight, 1.0, 1.0, "B");

  TH1D *hAccVsyLow = (TH1D*)hPtAccNumVsyLow->Clone("hAccVsyLow");  
  hAccVsyLow->Sumw2();
  hAccVsyLow->Divide(hAccVsyLow, hPtAccDenVsyLow, 1.0, 1.0, "B");

  TH1D *hAccVsyHigh = (TH1D*)hPtAccNumVsyHigh->Clone("hAccVsyHigh");  
  hAccVsyHigh->Sumw2();
  hAccVsyHigh->Divide(hAccVsyHigh, hPtAccDenVsyHigh, 1.0, 1.0, "B");

  
  TFile*fileoutput=new TFile("Results/outputBplus.root","recreate");
  fileoutput->cd();

  hPtAccNumVsPt->Write();
  hPtAccNumVsPtReweight->Write();  
  hPtAccNumVsPtLow->Write();
  hPtAccNumVsPtHigh->Write();
  hPtAccDenVsPt->Write(); 
  hPtAccDenVsPtReweight->Write(); 
  hPtAccDenVsPtLow->Write();
  hPtAccDenVsPtHigh->Write();
  hAccVsPt->Write();
  hAccVsPtReweight->Write();
  hAccVsPtLow->Write(); 
  hAccVsPtHigh->Write(); 

  hPtAccNumVsy->Write();
  hPtAccNumVsyReweight->Write();  
  hPtAccNumVsyLow->Write();
  hPtAccNumVsyHigh->Write();
  hPtAccDenVsy->Write(); 
  hPtAccDenVsyReweight->Write(); 
  hPtAccDenVsyLow->Write();
  hPtAccDenVsyHigh->Write();
  hAccVsy->Write();
  hAccVsyReweight->Write();
  hAccVsyLow->Write(); 
  hAccVsyHigh->Write(); 
 
}
