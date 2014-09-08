#include <iostream>                                                                                                                                                                                         
#include <utility>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TLegend.h>
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
/////=======Customize options
//Use POG Trg
bool UsePOGTrgEff = 0;

//Use POG ID
bool UsePOGIDEff = 0;

//Specify eff., Trg=Mu trigger, ID=Mu ID, Trk=Mu tracking
//TString _eff_ = "Trg";
//TString _eff_ = "ID";
TString _eff_ = "Trk";

//Specify channel, 0=B+, 1=B0, 2=Bs
int _type=0;
//int _type=1;
//int _type=2;

//Specify B meson pt bin
//const int nBins = 5;
//double ptBins[nBins+1] = {10,15,20,25,30,60};
//const int nBins = 3;
//double ptBins[nBins+1] = {10,15,20,60};
//const int nBins = 1;
//double ptBins[nBins+1] = {10,60};
const int nBins = 4;
double ptBins[nBins+1] = {-1.93,-1.0,0,1.0,1.93};

/////=======

//TString inputdata_kp="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kp_TriggerMatchingMuon_EvtBase_skim.root";
//TString inputdata_kstar="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root";
//TString inputdata_phi="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Phi_TriggerMatchingMuon_EvtBase_skim.root";
TString inputdata_kp="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kp_TriggerMatchingMuon.root";
TString inputdata_kstar="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Kstar_TriggerMatchingMuon.root";
TString inputdata_phi="/export/d00/scratch/jwang/nt_BoostedMC_20140506_Phi_TriggerMatchingMuon.root";

TFile *infDataEff = new TFile("../TNPHisto_TagMu3_TrgProbeMu3_DATA_new3.root");
TFile *infMCEff = new TFile("../TNPHisto_TagMu3_TrgProbeMu3_MC_new3.root");
TH1F* DataEtaBin1 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin1");
TH1F* DataEtaBin2 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin2");
TH1F* DataEtaBin3 = (TH1F*)infDataEff->Get("hMu"+_eff_+"etabin3");
TH1F* MCEtaBin1 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin1");
TH1F* MCEtaBin2 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin2");
TH1F* MCEtaBin3 = (TH1F*)infMCEff->Get("hMu"+_eff_+"etabin3");

float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);
float GetPOGTrgEff(float pt, float eta, float eta2,  bool isData);
float GetPOGIDEff(float pt, float eta, bool isData);
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
  Float_t mu1phi[MAX_GEN];
  Float_t mu2phi[MAX_GEN];
  Float_t tk1pt[MAX_GEN];
  Float_t tk2pt[MAX_GEN];
  Float_t tk1eta[MAX_GEN];
  Float_t tk2eta[MAX_GEN];
  Float_t tk1phi[MAX_GEN];
  Float_t tk2phi[MAX_GEN];
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
  nt->SetBranchAddress("mu1phi",mu1phi);
  nt->SetBranchAddress("mu2phi",mu2phi);
  nt->SetBranchAddress("tk1pt",tk1pt);
  nt->SetBranchAddress("tk2pt",tk2pt);
  nt->SetBranchAddress("tk1eta",tk1eta);
  nt->SetBranchAddress("tk2eta",tk2eta);
  nt->SetBranchAddress("tk1phi",tk1phi);
  nt->SetBranchAddress("tk2phi",tk2phi);

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
  if(_type==0)  EffDiff->SetXTitle("B^{+} y_{CM} (GeV/c)");
  if(_type==1)  EffDiff->SetXTitle("B0 y_{CM} (GeV/c)");
  if(_type==2)  EffDiff->SetXTitle("B_{s} y_{CM} (GeV/c)");
  if(_eff_=="Trg")EffDiff->SetYTitle("Trigger eff. diff., data-MC");
  if(_eff_=="ID")EffDiff->SetYTitle("MuID eff. diff., data-MC");
  if(_eff_=="Trk")EffDiff->SetYTitle("Tracking eff. diff., data-MC");
  int tot_=0;
  TLorentzVector mu1;
  TLorentzVector mu2;
  TLorentzVector tk1;
  TLorentzVector tk2;
  TLorentzVector B;
  for(int entry=0; entry<nevents_total; entry++){
    if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    nt->GetEntry(entry);
    for(int c=0; c<size; c++){
//      if(_type==0) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.9&& chi2cl[c]>1.32e-02&&(d0[c]/d0Err[c])>3.41&&cos(dtheta[c])>-3.46e-01 &&gen[c]==23333)) continue;
//      if(_type==1) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7 &&chi2cl[c]>1.65e-01&&(d0[c]/d0Err[c])>4.16&&cos(dtheta[c])>7.50e-01&&abs(tktkmass[c]-0.89594)<2.33e-01 && gen[c]==23333)) continue;
//      if(_type==2) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7&& chi2cl[c]>3.71e-02&&(d0[c]/d0Err[c])>3.37&&cos(dtheta[c])>2.60e-01&&abs(tktkmass[c]-1.019455)<1.55e-02 &&gen[c]==23333)) continue;
      if(isSignal[c]<1) continue;
      if(pt[c]<10 || pt[c]>60 || fabs(y[c]+0.465)>1.93) continue;
      //Acc
      if(fabs(mu1eta[c]) < 1.3) {if(mu1pt[c] < 3.3) continue;}
      else if(fabs(mu1eta[c]) > 1.3 && fabs(mu1eta[c]) < 2.2) {if(mu1pt[c] < 2.9) continue;}
      else if(fabs(mu1eta[c]) > 2.2 && fabs(mu1eta[c]) < 2.4) {if(mu1pt[c] < 0.8) continue;}
      else {continue;}
      if(fabs(mu2eta[c]) < 1.3) {if(mu2pt[c] < 3.3) continue;}
      else if(fabs(mu2eta[c]) > 1.3 && fabs(mu2eta[c]) < 2.2) {if(mu2pt[c] < 2.9) continue;}
      else if(fabs(mu2eta[c]) > 2.2 && fabs(mu2eta[c]) < 2.4) {if(mu2pt[c] < 0.8) continue;}
      else {continue;}
/*
      mu1.SetPtEtaPhiM(mu1pt[c], mu1eta[c], mu1phi[c], MUON_MASS);
      mu2.SetPtEtaPhiM(mu2pt[c], mu2eta[c], mu2phi[c], MUON_MASS);
      if(_type==0){
        if(tk1pt[c] < 0.9) continue;
        tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
        B = mu1+mu2+tk1;
      }
      if(_type==1){
        if(tk1pt[c] < 0.7) continue;
        if(tk2pt[c] < 0.7) continue;
        tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
        tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], PION_MASS);
        B = mu1+mu2+tk1+tk2;
      }
      if(_type==2){
        if(tk1pt[c] < 0.7) continue;
        if(tk2pt[c] < 0.7) continue;
        tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
        tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], KAON_MASS);
        B = mu1+mu2+tk1+tk2;
      }
      //cout<<B.Mag()<<endl;
      if(B.Mag() < 4.95 || B.Mag() > 5.55) continue;
*/
      int _etabin = -1;
      int _ptbin = -1;
      float mu1eff_data = GetEff(mu1pt[c], mu1eta[c], true, _eff_, _ptbin, _etabin);
      float mu2eff_data = GetEff(mu2pt[c], mu2eta[c], true, _eff_, _ptbin, _etabin);
      float mu1eff_mc = GetEff(mu1pt[c], mu1eta[c], false,  _eff_, _ptbin, _etabin);
      float mu2eff_mc = GetEff(mu2pt[c], mu2eta[c], false,  _eff_, _ptbin, _etabin);
      if(_eff_=="ID" && UsePOGIDEff){
        mu1eff_data = GetPOGIDEff(mu1pt[c], mu1eta[c], true);
        mu2eff_data = GetPOGIDEff(mu2pt[c], mu2eta[c], true);
        mu1eff_mc = GetPOGIDEff(mu1pt[c], mu1eta[c], false);
        mu2eff_mc = GetPOGIDEff(mu2pt[c], mu2eta[c], false);
      }
      tot_++;
      if(mu1eff_data<0 || mu2eff_data<0||mu1eff_mc<0||mu2eff_mc<0) continue;
      if(pt[c]<10 || pt[c]>60) continue;
      float evtEff_data = 0;
      float evtEff_mc = 0;
      if(_eff_=="Trg"){
        evtEff_data = mu1eff_data + mu2eff_data - mu1eff_data*mu2eff_data;
        evtEff_mc = mu1eff_mc + mu2eff_mc - mu1eff_mc*mu2eff_mc;
        if(UsePOGTrgEff) {
          if(mu1pt[c]>mu2pt[c]) {
            evtEff_data = GetPOGTrgEff(mu1pt[c], mu1eta[c], mu2eta[c], true);
            evtEff_mc = GetPOGTrgEff(mu1pt[c], mu1eta[c], mu2eta[c], false);
          }
          if(mu2pt[c]>mu1pt[c]) {
            evtEff_data = GetPOGTrgEff(mu2pt[c], mu2eta[c], mu1eta[c], true);
            evtEff_mc = GetPOGTrgEff(mu2pt[c], mu2eta[c], mu1eta[c], false);
          }
          if(evtEff_data==-1 || evtEff_mc==-1) continue;
			//cout<<evtEff_mc<<" //  "<<evtEff_mc-evtEff_data<<endl;
        }
      }
      else{
        evtEff_data = mu1eff_data*mu2eff_data;
        evtEff_mc = mu1eff_mc*mu2eff_mc;
        //evtEff_data = mu1eff_data;
        //evtEff_mc = mu1eff_mc;
      }
      //cout<<"-----  "<<mu1pt[c]<<"  /  "<<mu1eta[c]<<endl;
      //cout<<mu1eff_data-mu1eff_mc<<"   /   "<<mu1eff_data<<"  /  "<<mu1eff_mc<<endl;
      //cout<<evtEff_data-evtEff_mc<<endl;
      for(int _b=0; _b<nBins; _b++){
//        if(pt[c] > ptBins[_b] && pt[c] < ptBins[_b+1]){
        if(y[c]+0.465 > ptBins[_b] && y[c]+0.465 < ptBins[_b+1]){
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
    if(_eff_=="Trg" && !UsePOGTrgEff)c1->SaveAs("bp_trg.pdf");
    if(_eff_=="Trg" && UsePOGTrgEff)c1->SaveAs("bp_POG_trg.pdf");
    if(_eff_=="ID" && !UsePOGIDEff)c1->SaveAs("bp_id.pdf");
    if(_eff_=="ID" && UsePOGIDEff)c1->SaveAs("bp_POG_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("bp_trk.pdf");
  }
  if(_type==1) {
    if(_eff_=="Trg" && !UsePOGTrgEff)c1->SaveAs("b0_trg.pdf");
    if(_eff_=="Trg" && UsePOGTrgEff)c1->SaveAs("b0_POG_trg.pdf");
    if(_eff_=="ID" && !UsePOGIDEff)c1->SaveAs("b0_id.pdf");
    if(_eff_=="ID" && UsePOGIDEff)c1->SaveAs("b0_POG_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("b0_trk.pdf");
  }
  if(_type==2) {
    if(_eff_=="Trg" && !UsePOGTrgEff)c1->SaveAs("bs_trg.pdf");
    if(_eff_=="Trg" && UsePOGTrgEff)c1->SaveAs("bs_POG_trg.pdf");
    if(_eff_=="ID" && !UsePOGIDEff)c1->SaveAs("bs_id.pdf");
    if(_eff_=="ID" && UsePOGIDEff)c1->SaveAs("bs_POG_id.pdf");
    if(_eff_=="Trk")c1->SaveAs("bs_trk.pdf");
  }
}//Main

float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
  //cout<<pt<<"/"<<eta<<endl;
//special condition
//if(_eff_type =="ID"){ 
//  if(eta>-0.8 && eta<0.8 && pt>0 && pt<3) return -1;
//}
if(_eff_type =="Trk"){ 
  if(eta>-2.4 && eta<-0.8 && pt>0 && pt<1.5) return -1;
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
//Mu17Mu8 dR<0.3
float GetPOGTrgEff(float pt, float eta, float eta2,  bool isData){
//page18
  if(isData){
    if(pt>0 && pt<10){
      if(fabs(eta)>1.2 && fabs(eta)<2.4) if(fabs(eta2)>1.2 && fabs(eta2)<2.4) return 0.736;
      if(fabs(eta)>1.2 && fabs(eta)<2.4) if(fabs(eta2)>0 && fabs(eta2)<1.2) return 0.830;
      if(fabs(eta)>0 && fabs(eta)<1.2) if(fabs(eta2)>1.2 && fabs(eta2)<2.4) return 0.833;
      if(fabs(eta)>0 && fabs(eta)<1.2) if(fabs(eta2)>0 && fabs(eta2)<1.2) return 0.840;
    }
    if(pt>10 && pt<20){
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>2.1 && fabs(eta2)<2.4) return 0.780;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>1.2 && fabs(eta2)<2.1) return 0.790;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.807;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.862;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>1.2 && fabs(eta2)<2.1) return 0.776;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.805;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.846;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.833;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.863;
      if(fabs(eta)>0 && fabs(eta)<0.9) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.914;
    }
  }
//page24
  if(!isData){
    if(pt>0 && pt<10){
      if(fabs(eta)>1.2 && fabs(eta)<2.4) if(fabs(eta2)>1.2 && fabs(eta2)<2.4) return 0.835;
      if(fabs(eta)>1.2 && fabs(eta)<2.4) if(fabs(eta2)>0 && fabs(eta2)<1.2) return 0.875;
      if(fabs(eta)>0 && fabs(eta)<1.2) if(fabs(eta2)>1.2 && fabs(eta2)<2.4) return 0.884;
      if(fabs(eta)>0 && fabs(eta)<1.2) if(fabs(eta2)>0 && fabs(eta2)<1.2) return 0.923;
    }
    if(pt>10 && pt<20){
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>2.1 && fabs(eta2)<2.4) return 0.828;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>1.2 && fabs(eta2)<2.1) return 0.844;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.864;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.886;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>1.2 && fabs(eta2)<2.1) return 0.858;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.878;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.900;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) if(fabs(eta2)>0.9 && fabs(eta2)<1.2) return 0.898;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.921;
      if(fabs(eta)>0 && fabs(eta)<0.9) if(fabs(eta2)>0 && fabs(eta2)<0.9) return 0.944;
    }
  }
  return -1;
}
float GetPOGIDEff(float pt, float eta, bool isData){
  if(pt>20){
    if(isData){
      if(fabs(eta)>0 && fabs(eta)<0.9) return 0.9436;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) return 0.9472;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) return 0.9683;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) return 0.9036;
    }
    if(!isData){
      if(fabs(eta)>0 && fabs(eta)<0.9) return 0.9579;
      if(fabs(eta)>0.9 && fabs(eta)<1.2) return 0.9541;
      if(fabs(eta)>1.2 && fabs(eta)<2.1) return 0.9703;
      if(fabs(eta)>2.1 && fabs(eta)<2.4) return 0.8717;
    }
  }
  return -1;
}
