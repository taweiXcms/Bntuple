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
//TString inputdata_kp="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kp_TriggerMatchingMuon_EvtBase_skim.root";
//TString inputdata_kstar="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root";
//TString inputdata_phi="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Phi_TriggerMatchingMuon_EvtBase_skim.root";
TString inputdata_kp="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kp_TriggerMatchingMuon.root";
TString inputdata_kstar="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kstar_TriggerMatchingMuon.root";
TString inputdata_phi="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Phi_TriggerMatchingMuon.root";

//Specify eff., Trg=Mu trigger, ID=Mu ID, Trk=Mu tracking
//TString _eff_ = "Trg";
//TString _eff_ = "ID";
TString _eff_ = "Trk";

//Specify channel, 0=B+, 1=B0, 2=Bs
//int _type=0;
//int _type=1;
int _type=2;

//Specify py bin
//const int nBins = 5;
//double ptBins[nBins+1] = {10,15,20,25,30,60};
//const int nBins = 3;
//double ptBins[nBins+1] = {10,15,20,60};
const int nBins = 1;
double ptBins[nBins+1] = {10,60};

TFile *infDataEff = new TFile("TNPHisto_TagMu3_TrgProbeMu3_DATA.root");
TFile *infMCEff = new TFile("TNPHisto_TagMu3_TrgProbeMu3.root");
TH1F* DataEtaBin1 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin1");
TH1F* DataEtaBin2 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin2");
TH1F* DataEtaBin3 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin3");
TH1F* MCEtaBin1 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin1");
TH1F* MCEtaBin2 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin2");
TH1F* MCEtaBin3 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin3");

float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);
void ConvertEff(){
  TFile *inf;
  TTree *nt;
  if(_type==0){
    inf = new TFile(inputdata_kp.Data());
//    nt = (TTree*) inf->Get("ntKp");
    nt = (TTree*) inf->Get("ntGen");
  }
  if(_type==1){
    inf = new TFile(inputdata_kstar.Data());
//    nt = (TTree*) inf->Get("ntKstar");
    nt = (TTree*) inf->Get("ntGen");
  }
  if(_type==2){ 
    inf = new TFile(inputdata_phi.Data());
//    nt = (TTree*) inf->Get("ntphi");
    nt = (TTree*) inf->Get("ntGen");
  }

  Int_t size;                                                                                                                                                                                               
  Float_t y[MAX_GEN];
  Float_t eta[MAX_GEN];
  Float_t pt[MAX_GEN];
  Float_t phi[MAX_GEN];
  Float_t pdgId[MAX_GEN];
  Float_t isSignal[MAX_GEN];
  Float_t mu1pt[MAX_GEN];
  Float_t mu2pt[MAX_GEN];
  Float_t mu1eta[MAX_GEN];
  Float_t mu2eta[MAX_GEN];
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

/*
  int   size; 
  int   HLT_PAMu3_v1;
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
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
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
*/
  int nevents_total = nt->GetEntries();                                               
  int nCand[nBins];
  float effData_tol[nBins];
  float effMC_tol[nBins];
  float _tot_diff[nBins] ;
  for(int i = 0; i < nBins+1; i ++){
    nCand[i] = 0;
    effData_tol[i] = 0;
    effMC_tol[i] = 0;
    _tot_diff[i] = 0;
  }

  TH1D *EffDiff = new TH1D("hPt","",nBins,ptBins);
  if(_type==0)  EffDiff->SetXTitle("B^{+} p_{T} (GeV/c)");
  if(_type==1)  EffDiff->SetXTitle("B0 p_{T} (GeV/c)");
  if(_type==2)  EffDiff->SetXTitle("B_{s} p_{T} (GeV/c)");
  if(_eff_=="Trg")EffDiff->SetYTitle("Trigger eff. diff., data-MC");
  if(_eff_=="ID")EffDiff->SetYTitle("MuID eff. diff., data-MC");
  if(_eff_=="Trk")EffDiff->SetYTitle("Tracking eff. diff., data-MC");
  int tot_=0;
  for(int entry=0; entry<nevents_total; entry++){
    if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    nt->GetEntry(entry);
    for(int c=0; c<size; c++){
//      if(_type==0) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.9&& chi2cl[c]>1.32e-02&&(d0[c]/d0Err[c])>3.41&&cos(dtheta[c])>-3.46e-01 &&gen[c]==23333)) continue;
//      if(_type==1) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7 &&chi2cl[c]>1.65e-01&&(d0[c]/d0Err[c])>4.16&&cos(dtheta[c])>7.50e-01&&abs(tktkmass[c]-0.89594)<2.33e-01 && gen[c]==23333)) continue;
//      if(_type==2) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7&& chi2cl[c]>3.71e-02&&(d0[c]/d0Err[c])>3.37&&cos(dtheta[c])>2.60e-01&&abs(tktkmass[c]-1.019455)<1.55e-02 &&gen[c]==23333)) continue;
      if(isSignal[c]<1) continue;
      if(pt[c]<10 || pt[c]>60 || fabs(y[c]+0.465)>1.93) continue;
      int _etabin = -1;
      int _ptbin = -1;
      float mu1eff_data = GetEff(mu1pt[c], mu1eta[c], true, _eff_, _ptbin, _etabin);
      float mu2eff_data = GetEff(mu2pt[c], mu2eta[c], true, _eff_, _ptbin, _etabin);
      float mu1eff_mc = GetEff(mu1pt[c], mu1eta[c], false,  _eff_, _ptbin, _etabin);
      float mu2eff_mc = GetEff(mu2pt[c], mu2eta[c], false,  _eff_, _ptbin, _etabin);
      tot_++;
      if(mu1eff_data<0 || mu2eff_data<0||mu1eff_mc<0||mu2eff_mc<0) continue;
      if(pt[c]<10 || pt[c]>60) continue;
      float evtEff_data = 0;
      float evtEff_mc = 0;
      if(_eff_=="Trg"){
        evtEff_data = mu1eff_data + mu2eff_data - mu1eff_data*mu2eff_data;
        evtEff_mc = mu1eff_mc + mu2eff_mc - mu1eff_mc*mu2eff_mc;
      }
      else{
        evtEff_data = mu1eff_data*mu2eff_data;
        evtEff_mc = mu1eff_mc*mu2eff_mc;
        //evtEff_data = mu1eff_data;
        //evtEff_mc = mu1eff_mc;
      }
//      cout<<"-----  "<<mu1pt[c]<<"  /  "<<mu1eta[c]<<endl;
//      cout<<mu1eff_data-mu1eff_mc<<"   /   "<<mu1eff_data<<"  /  "<<mu1eff_mc<<endl;
      //cout<<evtEff_data-evtEff_mc<<endl;
      for(int _b=0; _b<nBins; _b++){
        if(pt[c] > ptBins[_b] && pt[c] < ptBins[_b+1]){
          nCand[_b]++;
          effData_tol[_b]+= evtEff_data;
          effMC_tol[_b]+= evtEff_mc;
          //_tot_diff[_b]+=fabs(evtEff_data-evtEff_mc);
          _tot_diff[_b]+=(evtEff_data-evtEff_mc);
        }
      }
    }
  }//Evt loop

  TCanvas *c1=  new TCanvas("c1","",600,600);                                                                                                                                                           
  c1->cd();
  c1->SetLeftMargin(0.15);
  for(int i = 0; i < nBins; i ++){
    cout<<effData_tol[i]<<endl;
    cout<<effMC_tol[i]<<endl;
    //cout<<(effData_tol[i]-effMC_tol[i])/effMC_tol[i]<<endl;
    cout<<(_tot_diff[i])/effMC_tol[i]<<endl;
    //EffDiff->SetBinContent(i+1,(effData_tol[i]-effMC_tol[i])/effMC_tol[i]);
    EffDiff->SetBinContent(i+1,(_tot_diff[i])/effMC_tol[i]);
    EffDiff->SetBinError(i+1,0.000000001);
  }
  //print a line for AN
  for(int i = 0; i < nBins; i ++){
    printf(" %.1f &", ((_tot_diff[i])/effMC_tol[i])*100);
  }
  printf("\n");
  EffDiff->SetMaximum(0.1);
  EffDiff->SetTitleOffset(1.2,"Y");
  EffDiff->SetMarkerColor(2);
  EffDiff->SetMarkerSize(1.2);
  EffDiff->SetLineWidth(1.9);
  EffDiff->Draw("pe");
  cout<<"Total B cand. "<<tot_<<endl;

  //MCEtaBin1->SetMinimum(0);
  //MCEtaBin1->SetMaximum(1);
  //MCEtaBin1->SetMarkerColor(2);
  //MCEtaBin1->Draw("p");
  //DataEtaBin1->Draw("same p");
  //return;

  if(_type==0) {
    if(_eff_=="Trg")c1->SaveAs("bp_trg.pdf");
    if(_eff_=="ID")c1->SaveAs("bp_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("bp_trk.pdf");
  }
  if(_type==1) {
    if(_eff_=="Trg")c1->SaveAs("b0_trg.pdf");
    if(_eff_=="ID")c1->SaveAs("b0_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("b0_trk.pdf");
  }
  if(_type==2) {
    if(_eff_=="Trg")c1->SaveAs("bs_trg.pdf");
    if(_eff_=="ID")c1->SaveAs("bs_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("bs_trk.pdf");
  }
}//Main

float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
  //cout<<pt<<"/"<<eta<<endl;
//special condition
if(_eff_type =="ID"){ 
  if(eta>-0.8 && eta<0.8 && pt>0 && pt<3) return -1;
}
//

  if(-2.4<eta && eta<-0.8){
    _etabin = 1;
    if(isData){
      for(int i = 0; i < DataEtaBin1->GetNbinsX(); i++){
        if(pt>DataEtaBin1->GetBinLowEdge(i+1) && pt<(DataEtaBin1->GetBinLowEdge(i+1)+DataEtaBin1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBin1->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBin1->GetNbinsX(); i++){
        if(pt>MCEtaBin1->GetBinLowEdge(i+1) && pt<(MCEtaBin1->GetBinLowEdge(i+1)+MCEtaBin1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBin1->GetBinContent(i+1);
        }
      }
    }
  }


  else if(-0.8<eta && eta<0.8){
//  if(-0.8<eta && eta<0.8){
    _etabin = 2;
    if(isData){
      for(int i = 0; i < DataEtaBin2->GetNbinsX(); i++){
        if(pt>DataEtaBin2->GetBinLowEdge(i+1) && pt<(DataEtaBin2->GetBinLowEdge(i+1)+DataEtaBin2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBin2->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBin2->GetNbinsX(); i++){
        if(pt>MCEtaBin2->GetBinLowEdge(i+1) && pt<(MCEtaBin2->GetBinLowEdge(i+1)+MCEtaBin2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBin2->GetBinContent(i+1);
        }
      }
    }
  }


  else if(0.8<eta && eta<1.46){
//  if(0.8<eta && eta<1.46){
    _etabin = 3;
    if(isData){
      for(int i = 0; i < DataEtaBin3->GetNbinsX(); i++){
        if(pt>DataEtaBin3->GetBinLowEdge(i+1) && pt<(DataEtaBin3->GetBinLowEdge(i+1)+DataEtaBin3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBin3->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBin3->GetNbinsX(); i++){
        if(pt>MCEtaBin3->GetBinLowEdge(i+1) && pt<(MCEtaBin3->GetBinLowEdge(i+1)+MCEtaBin3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBin3->GetBinContent(i+1);
        }
      }
    }
  }

  return -1;
}
