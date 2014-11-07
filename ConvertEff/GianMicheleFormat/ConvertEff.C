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
#include <TGraphAsymmErrors.h>
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
//TString _eff_ = "Trk";
TString _eff_ = "All";

//int _type=0;
//int _type=1;
//int _type=2;

//Specify B meson pt bin
const int Bp_nBins = 5;
double Bp_ptBins[Bp_nBins+1] = {10,15,20,25,30,60};
const int B0_nBins = 3;
double B0_ptBins[B0_nBins+1] = {10,15,20,60};
const int Bs_nBins = 1;
double Bs_ptBins[Bs_nBins+1] = {10,60};
const int Eta_nBins = 5;
double Eta_ptBins[Eta_nBins+1] = {-2.865,-1.935,-1.0,0,1.0,1.935};
/////=======

TString inputdata_kp="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kp.root";
TString inputdata_kstar="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kstar.root";
TString inputdata_phi="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Phi.root";

TFile *TrginfMCEff = new TFile("Results/foutputTrigger.root");
TFile *TrginfDataEff = new TFile("Results/foutputTrigger.root");
TFile *IDinfMCEff = new TFile("Results/foutputMuonID.root");
TFile *IDinfDataEff = new TFile("Results/foutputMuonID.root");
TFile *TrkinfMCEff = new TFile("Results/foutputTracking.root");
TFile *TrkinfDataEff = new TFile("Results/foutputTracking.root");
TGraphAsymmErrors* TrgDataEtaBin1 = (TGraphAsymmErrors*)TrginfDataEff->Get("fEff_pt_etabin0_Data");
TGraphAsymmErrors* TrgDataEtaBin2 = (TGraphAsymmErrors*)TrginfDataEff->Get("fEff_pt_etabin1_Data");
TGraphAsymmErrors* TrgDataEtaBin3 = (TGraphAsymmErrors*)TrginfDataEff->Get("fEff_pt_etabin2_Data");
TGraphAsymmErrors* TrgMCEtaBin1 = (TGraphAsymmErrors*)TrginfMCEff->Get("fEff_pt_etabin0_MC");
TGraphAsymmErrors* TrgMCEtaBin2 = (TGraphAsymmErrors*)TrginfMCEff->Get("fEff_pt_etabin1_MC");
TGraphAsymmErrors* TrgMCEtaBin3 = (TGraphAsymmErrors*)TrginfMCEff->Get("fEff_pt_etabin2_MC");
TGraphAsymmErrors* IDDataEtaBin1 = (TGraphAsymmErrors*)IDinfDataEff->Get("fEff_pt_etabin0_Data");
TGraphAsymmErrors* IDDataEtaBin2 = (TGraphAsymmErrors*)IDinfDataEff->Get("fEff_pt_etabin1_Data");
TGraphAsymmErrors* IDDataEtaBin3 = (TGraphAsymmErrors*)IDinfDataEff->Get("fEff_pt_etabin2_Data");
TGraphAsymmErrors* IDMCEtaBin1 = (TGraphAsymmErrors*)IDinfMCEff->Get("fEff_pt_etabin0_MC");
TGraphAsymmErrors* IDMCEtaBin2 = (TGraphAsymmErrors*)IDinfMCEff->Get("fEff_pt_etabin1_MC");
TGraphAsymmErrors* IDMCEtaBin3 = (TGraphAsymmErrors*)IDinfMCEff->Get("fEff_pt_etabin2_MC");
TGraphAsymmErrors* TrkDataEtaBin1 = (TGraphAsymmErrors*)TrkinfDataEff->Get("fEff_pt_etabin0_Data");
TGraphAsymmErrors* TrkDataEtaBin2 = (TGraphAsymmErrors*)TrkinfDataEff->Get("fEff_pt_etabin1_Data");
TGraphAsymmErrors* TrkDataEtaBin3 = (TGraphAsymmErrors*)TrkinfDataEff->Get("fEff_pt_etabin2_Data");
TGraphAsymmErrors* TrkMCEtaBin1 = (TGraphAsymmErrors*)TrkinfMCEff->Get("fEff_pt_etabin0_MC");
TGraphAsymmErrors* TrkMCEtaBin2 = (TGraphAsymmErrors*)TrkinfMCEff->Get("fEff_pt_etabin1_MC");
TGraphAsymmErrors* TrkMCEtaBin3 = (TGraphAsymmErrors*)TrkinfMCEff->Get("fEff_pt_etabin2_MC");

void _ConvertEff(int _type, int nBins, double ptBins[], bool InEtaBin);
void Saving(TCanvas* c1, TString name);
float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);
float GetPOGTrgEff(float pt, float eta, float eta2,  bool isData);
float GetPOGIDEff(float pt, float eta, bool isData);
void ConvertEff(){
//Specify channel, 0=B+, 1=B0, 2=Bs
  _ConvertEff(0, Bp_nBins, Bp_ptBins, false);
  _ConvertEff(1, B0_nBins, B0_ptBins, false);
  _ConvertEff(2, Bs_nBins, Bs_ptBins, false);
  _ConvertEff(0, Eta_nBins, Eta_ptBins, true);
  _ConvertEff(1, Eta_nBins, Eta_ptBins, true);
  _ConvertEff(2, Eta_nBins, Eta_ptBins, true);
}
void _ConvertEff(int _type, int nBins, double ptBins[], bool InEtaBin){
  TFile *inf;
  TTree *_nt;
  TTree *nt;
  if(_type==0){
    inf = new TFile(inputdata_kp.Data());
    _nt = (TTree*) inf->Get("ntKp");
    nt = (TTree*) inf->Get("ntGen");
  }
  if(_type==1){
    inf = new TFile(inputdata_kstar.Data());
    _nt = (TTree*) inf->Get("ntKstar");
    nt = (TTree*) inf->Get("ntGen");
  }
  if(_type==2){ 
    inf = new TFile(inputdata_phi.Data());
    _nt = (TTree*) inf->Get("ntphi");
    nt = (TTree*) inf->Get("ntGen");
  }
  nt->AddFriend(_nt);

  Int_t size;                                                                                                                                                                                               
  Int_t Run;
  Float_t y[MAX_GEN];
  Float_t eta[MAX_GEN];
  Float_t pt[MAX_GEN];
  Float_t phi[MAX_GEN];
  Float_t pdgId[MAX_GEN];
  Float_t isSignal[MAX_GEN];
  Float_t mu1pt[MAX_GEN];
  Float_t mu2pt[MAX_GEN];
  Float_t mu1p[MAX_GEN];
  Float_t mu2p[MAX_GEN];
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
  nt->SetBranchAddress("Run",&Run);
  nt->SetBranchAddress("size",&size);
  nt->SetBranchAddress("y",&y);
  nt->SetBranchAddress("eta",eta);
  nt->SetBranchAddress("phi",phi);
  nt->SetBranchAddress("pt",pt);
  nt->SetBranchAddress("pdgId",pdgId);
  nt->SetBranchAddress("isSignal",isSignal);
  nt->SetBranchAddress("mu1pt",mu1pt);
  nt->SetBranchAddress("mu2pt",mu2pt);
  nt->SetBranchAddress("mu1p",mu1p);
  nt->SetBranchAddress("mu2p",mu2p);
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
  if(_type==0)  EffDiff->SetXTitle("B^{+} p_{T} (GeV/c)");
  if(_type==1)  EffDiff->SetXTitle("B0 p_{T} (GeV/c)");
  if(_type==2)  EffDiff->SetXTitle("B_{s} p_{T} (GeV/c)");
  //if(_eff_=="Trg")EffDiff->SetYTitle("Trigger eff. diff., data-MC");
  //if(_eff_=="ID")EffDiff->SetYTitle("MuID eff. diff., data-MC");
  //if(_eff_=="Trk")EffDiff->SetYTitle("Tracking eff. diff., data-MC");
  //if(_eff_=="All")EffDiff->SetYTitle("All eff. diff., data-MC");
  if(_eff_=="Trg")EffDiff->SetYTitle("Trigger eff., data/MC");
  if(_eff_=="ID")EffDiff->SetYTitle("MuID eff., data/MC");
  if(_eff_=="Trk")EffDiff->SetYTitle("Tracking eff., data/MC");
  if(_eff_=="All")EffDiff->SetYTitle("All eff., data/MC");
  int tot_=0;
  TLorentzVector mu1;
  TLorentzVector mu2;
  TLorentzVector tk1;
  TLorentzVector tk2;
  TLorentzVector B;
  for(int entry=1; entry<10000; entry++){
//  for(int entry=0; entry<nevents_total; entry++){
    if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    nt->GetEntry(entry);
    for(int c=0; c<size; c++){
      //if(_type==0) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.9&& chi2cl[c]>1.32e-02&&(d0[c]/d0Err[c])>3.41&&cos(dtheta[c])>-3.46e-01 &&gen[c]==23333)) continue;
      //if(_type==1) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7 &&chi2cl[c]>1.65e-01&&(d0[c]/d0Err[c])>4.16&&cos(dtheta[c])>7.50e-01&&abs(tktkmass[c]-0.89594)<2.33e-01 && gen[c]==23333)) continue;
      //if(_type==2) if(!((HLT_PAMu3_v1)&&abs(mumumass[c]-3.096916)<0.15&&mass[c]>5&&mass[c]<6&& isbestchi2[c]&&trk1Pt[c]>0.7&&trk2Pt[c]>0.7&& chi2cl[c]>3.71e-02&&(d0[c]/d0Err[c])>3.37&&cos(dtheta[c])>2.60e-01&&abs(tktkmass[c]-1.019455)<1.55e-02 &&gen[c]==23333)) continue;
      if(isSignal[c]<1) continue;
      //if(pt[c]<10 || pt[c]>60 || fabs(y[c]+0.465)>1.93) continue;
      if(pt[c]<10 || pt[c]>60 || fabs(y[c]>2.4)) continue;
      //Acc
      if(fabs(mu1eta[c]) < 1.3) {if(mu1pt[c] < 3.3) continue;}
      else if(fabs(mu1eta[c]) > 1.3 && fabs(mu1eta[c]) < 2.2) {if(mu1p[c] < 2.9) continue;}
      else if(fabs(mu1eta[c]) > 2.2 && fabs(mu1eta[c]) < 2.4) {if(mu1pt[c] < 0.8) continue;}
      else {continue;}
      if(fabs(mu2eta[c]) < 1.3) {if(mu2pt[c] < 3.3) continue;}
      else if(fabs(mu2eta[c]) > 1.3 && fabs(mu2eta[c]) < 2.2) {if(mu2p[c] < 2.9) continue;}
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
      float Trgmu1eff_data = GetEff(mu1pt[c], mu1eta[c], true, "Trg", _ptbin, _etabin);
      float Trgmu2eff_data = GetEff(mu2pt[c], mu2eta[c], true, "Trg", _ptbin, _etabin);
      float Trgmu1eff_mc = GetEff(mu1pt[c], mu1eta[c], false,  "Trg", _ptbin, _etabin);
      float Trgmu2eff_mc = GetEff(mu2pt[c], mu2eta[c], false,  "Trg", _ptbin, _etabin);
      float IDmu1eff_data = GetEff(mu1pt[c], mu1eta[c], true, "ID", _ptbin, _etabin);
      float IDmu2eff_data = GetEff(mu2pt[c], mu2eta[c], true, "ID", _ptbin, _etabin);
      float IDmu1eff_mc = GetEff(mu1pt[c], mu1eta[c], false,  "ID", _ptbin, _etabin);
      float IDmu2eff_mc = GetEff(mu2pt[c], mu2eta[c], false,  "ID", _ptbin, _etabin);
      float Trkmu1eff_data = GetEff(mu1pt[c], mu1eta[c], true, "Trk", _ptbin, _etabin);
      float Trkmu2eff_data = GetEff(mu2pt[c], mu2eta[c], true, "Trk", _ptbin, _etabin);
      float Trkmu1eff_mc = GetEff(mu1pt[c], mu1eta[c], false,  "Trk", _ptbin, _etabin);
      float Trkmu2eff_mc = GetEff(mu2pt[c], mu2eta[c], false,  "Trk", _ptbin, _etabin);
      if(UsePOGIDEff){
        IDmu1eff_data = GetPOGIDEff(mu1pt[c], mu1eta[c], true);
        IDmu2eff_data = GetPOGIDEff(mu2pt[c], mu2eta[c], true);
        IDmu1eff_mc = GetPOGIDEff(mu1pt[c], mu1eta[c], false);
        IDmu2eff_mc = GetPOGIDEff(mu2pt[c], mu2eta[c], false);
      }
      tot_++;
      if(Trgmu1eff_data<0 || Trgmu2eff_data<0|| Trgmu1eff_mc<0 || Trgmu2eff_mc<0) continue;
      if(IDmu1eff_data<0 || IDmu2eff_data<0 || IDmu1eff_mc<0 || IDmu2eff_mc<0) continue;
      if(Trkmu1eff_data<0 || Trkmu2eff_data<0 || Trkmu1eff_mc<0 || Trkmu2eff_mc<0) continue;
      float evtEff_data = 0;
      float evtEff_mc = 0;
      float TrgevtEff_data = 0;
      float TrgevtEff_mc = 0;
      float IDevtEff_data = 0;
      float IDevtEff_mc = 0;
      float TrkevtEff_data = 0;
      float TrkevtEff_mc = 0;
      TrgevtEff_data = Trgmu1eff_data + Trgmu2eff_data - Trgmu1eff_data*Trgmu2eff_data;
      TrgevtEff_mc = Trgmu1eff_mc + Trgmu2eff_mc - Trgmu1eff_mc*Trgmu2eff_mc;
      if(UsePOGTrgEff) {
        if(mu1pt[c]>mu2pt[c]) {
          TrgevtEff_data = GetPOGTrgEff(mu1pt[c], mu1eta[c], mu2eta[c], true);
          TrgevtEff_mc = GetPOGTrgEff(mu1pt[c], mu1eta[c], mu2eta[c], false);
        }
        if(mu2pt[c]>mu1pt[c]) {
          TrgevtEff_data = GetPOGTrgEff(mu2pt[c], mu2eta[c], mu1eta[c], true);
          TrgevtEff_mc = GetPOGTrgEff(mu2pt[c], mu2eta[c], mu1eta[c], false);
        }
        if(TrgevtEff_data==-1 || TrgevtEff_mc==-1) continue;
	  	//cout<<evtEff_mc<<" //  "<<evtEff_mc-evtEff_data<<endl;
      }
      IDevtEff_data = IDmu1eff_data*IDmu2eff_data;
      IDevtEff_mc = IDmu1eff_mc*IDmu2eff_mc;
      TrkevtEff_data = Trkmu1eff_data*Trkmu2eff_data;
      TrkevtEff_mc = Trkmu1eff_mc*Trkmu2eff_mc;
      if(_eff_=="Trg") {
        evtEff_data = TrgevtEff_data;
        evtEff_mc = TrgevtEff_mc;
      }
      if(_eff_=="ID") {
        evtEff_data = IDevtEff_data;
        evtEff_mc = IDevtEff_mc;
      }
      if(_eff_=="Trk") {
        evtEff_data = TrkevtEff_data;
        evtEff_mc = TrkevtEff_mc;
      }
      if(_eff_=="All") {
        evtEff_data = TrgevtEff_data*IDevtEff_data*TrkevtEff_data;
        evtEff_mc = TrgevtEff_mc*IDevtEff_mc*TrkevtEff_mc;
      }
      //evtEff_data = mu1eff_data;
      //evtEff_mc = mu1eff_mc;
      //cout<<"-----  "<<mu1pt[c]<<"  /  "<<mu1eta[c]<<endl;
      //cout<<mu1eff_data-mu1eff_mc<<"   /   "<<mu1eff_data<<"  /  "<<mu1eff_mc<<endl;
      //cout<<evtEff_data-evtEff_mc<<endl;
      for(int _b=0; _b<nBins; _b++){
        if((!InEtaBin && pt[c] > ptBins[_b] && pt[c] < ptBins[_b+1]) ||
           (InEtaBin && ((Run<=1) && (-y[c]-0.465)>ptBins[_b] && (-y[c]-0.465) < ptBins[_b+1]) || ((Run>1) && (y[c]-0.465)>ptBins[_b] && (y[c]-0.465) < ptBins[_b+1]))
          ){
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
    //EffDiff->SetBinContent(i+1,(_tot_diff[i])/effMC_tol[i]);
    EffDiff->SetBinContent(i+1,(effData_tol[i])/effMC_tol[i]);
    EffDiff->SetBinError(i+1,0.000000001);
  }
  //print a line for AN
  for(int i = 0; i < nBins; i ++){
//    printf(" %.1f &", ((_tot_diff[i])/effMC_tol[i])*100);
    printf(" %.3f &", ((effData_tol[i])/effMC_tol[i]));
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
      if(!InEtaBin) Saving(c1, "PtBinning_bp");
      if(InEtaBin) Saving(c1, "EtaBinning_bp");
  }
  if(_type==1) {
      if(!InEtaBin) Saving(c1, "PtBinning_b0");
      if(InEtaBin) Saving(c1, "EtaBinning_b0");
  }
  if(_type==2) {
      if(!InEtaBin) Saving(c1, "PtBinning_bs");
      if(InEtaBin) Saving(c1, "EtaBinning_bs");
  }
}//Main
void Saving(TCanvas* c1, TString name){
    if(_eff_=="Trg" && !UsePOGTrgEff) c1->SaveAs(Form("%s_trg.pdf"    , name.Data()));
    if(_eff_=="Trg" && UsePOGTrgEff)  c1->SaveAs(Form("%s_POG_trg.pdf", name.Data()));
    if(_eff_=="ID" && !UsePOGIDEff)   c1->SaveAs(Form("%s_id.pdf"     , name.Data()));
    if(_eff_=="ID" && UsePOGIDEff)    c1->SaveAs(Form("%s_POG_id.pdf" , name.Data()));
    if(_eff_=="Trk")                  c1->SaveAs(Form("%s_trk.pdf"    , name.Data()));
    if(_eff_=="All")                  c1->SaveAs(Form("%s_all.pdf"    , name.Data()));

    if(_eff_=="Trg" && !UsePOGTrgEff) c1->SaveAs(Form("%s_trg.root"    , name.Data()));
    if(_eff_=="Trg" && UsePOGTrgEff)  c1->SaveAs(Form("%s_POG_trg.root", name.Data()));
    if(_eff_=="ID" && !UsePOGIDEff)   c1->SaveAs(Form("%s_id.root"     , name.Data()));
    if(_eff_=="ID" && UsePOGIDEff)    c1->SaveAs(Form("%s_POG_id.root" , name.Data()));
    if(_eff_=="Trk")                  c1->SaveAs(Form("%s_trk.root"    , name.Data()));
    if(_eff_=="All")                  c1->SaveAs(Form("%s_all.root"    , name.Data()));
}

float GetEff(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
  double x=0;
  double y=0;
  TGraphAsymmErrors* DataEtaBin1; 
  TGraphAsymmErrors* DataEtaBin2;
  TGraphAsymmErrors* DataEtaBin3;
  TGraphAsymmErrors* MCEtaBin1; 
  TGraphAsymmErrors* MCEtaBin2; 
  TGraphAsymmErrors* MCEtaBin3;
  if(_eff_type=="Trg"){
    DataEtaBin1 = TrgDataEtaBin1;
    DataEtaBin2 = TrgDataEtaBin2;
    DataEtaBin3 = TrgDataEtaBin3;
    MCEtaBin1 = TrgMCEtaBin1;
    MCEtaBin2 = TrgMCEtaBin2;
    MCEtaBin3 = TrgMCEtaBin3;
  }
  if(_eff_type=="ID"){
    DataEtaBin1 = IDDataEtaBin1;
    DataEtaBin2 = IDDataEtaBin2;
    DataEtaBin3 = IDDataEtaBin3;
    MCEtaBin1 = IDMCEtaBin1;
    MCEtaBin2 = IDMCEtaBin2;
    MCEtaBin3 = IDMCEtaBin3;
  }
  if(_eff_type=="Trk"){
    DataEtaBin1 = TrkDataEtaBin1;
    DataEtaBin2 = TrkDataEtaBin2;
    DataEtaBin3 = TrkDataEtaBin3;
    MCEtaBin1 = TrkMCEtaBin1;
    MCEtaBin2 = TrkMCEtaBin2;
    MCEtaBin3 = TrkMCEtaBin3;
  }

  DataEtaBin1->GetPoint(0, x, y);
  if(-2.4<eta && eta<-0.8){
    _etabin = 1;
    if(isData){
      for(int i = 0; i < 5; i++){
        DataEtaBin1->GetPoint(i, x, y);
        if(pt>(x-DataEtaBin1->GetErrorXlow(i)) && pt<(x+DataEtaBin1->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
        }
      }
    }
    if(!isData){
      for(int i = 0; i < 5; i++){
        MCEtaBin1->GetPoint(i, x, y);
        if(pt>(x-MCEtaBin1->GetErrorXlow(i)) && pt<(x+MCEtaBin1->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
        }
      }
    }
  }


  else if(-0.8<eta && eta<0.8){
    _etabin = 2;
    if(isData){
      for(int i = 0; i < 5; i++){
        DataEtaBin2->GetPoint(i, x, y);
        if(pt>(x-DataEtaBin2->GetErrorXlow(i)) && pt<(x+DataEtaBin2->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
        }
      }
    }
    if(!isData){
      for(int i = 0; i < 5; i++){
        MCEtaBin2->GetPoint(i, x, y);
        if(pt>(x-MCEtaBin2->GetErrorXlow(i)) && pt<(x+MCEtaBin2->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
        }
      }
    }
  }


  else if(0.8<eta && eta<2.4){
    _etabin = 3;
    if(isData){
      for(int i = 0; i < 5; i++){
        DataEtaBin3->GetPoint(i, x, y);
        if(pt>(x-DataEtaBin3->GetErrorXlow(i)) && pt<(x+DataEtaBin3->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
        }
      }
    }
    if(!isData){
      for(int i = 0; i < 5; i++){
        MCEtaBin3->GetPoint(i, x, y);
        if(pt>(x-MCEtaBin3->GetErrorXlow(i)) && pt<(x+MCEtaBin3->GetErrorXhigh(i))){
          _ptbin = i+1;
          return y;
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
