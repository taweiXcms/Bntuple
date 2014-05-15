#include <iostream>                                                                                                                                                                                         
#include <utility>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLegendEntry.h>

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

TString _eff_ = "All";
//TString _eff_ = "ID";
//TString _eff_ = "Trk";

//Specify channel, 0=B+, 1=B0, 2=Bs
int _type=0;
//int _type=1;
//int _type=2;

//Specify B meson pt bin
const int nBins = 5;
double ptBins[nBins+1] = {10,15,20,25,30,60};
//const int nBins = 3;
//double ptBins[nBins+1] = {10,15,20,60};
//const int nBins = 1;
//double ptBins[nBins+1] = {10,60};
/////=======

TString inputdata_kp="/Users/ginnocen/InputsFiles/nt_BoostedMC_20140506_Kp_TriggerMatchingMuon.root";
TString inputdata_kstar="/Users/ginnocen/InputsFiles/nt_BoostedMC_20140506_Kstar_TriggerMatchingMuon.root";
TString inputdata_phi="/Users/ginnocen/InputsFiles/nt_BoostedMC_20140506_Phi_TriggerMatchingMuon.root";

TFile *infDataEff = new TFile("TNPHisto_TagMu3_TrgProbeMu3_DATA_new3.root");
TFile *infMCEff = new TFile("TNPHisto_TagMu3_TrgProbeMu3_MC_new3.root");


TH1F* DataEtaBinTrg1 = (TH1F*)infDataEff->Get("hMuTrgetabin1");
TH1F* DataEtaBinTrg2 = (TH1F*)infDataEff->Get("hMuTrgetabin2");
TH1F* DataEtaBinTrg3 = (TH1F*)infDataEff->Get("hMuTrgetabin3");
TH1F* MCEtaBinTrg1 = (TH1F*)infMCEff->Get("hMuTrgetabin1");
TH1F* MCEtaBinTrg2 = (TH1F*)infMCEff->Get("hMuTrgetabin2");
TH1F* MCEtaBinTrg3 = (TH1F*)infMCEff->Get("hMuTrgetabin3");

TH1F* DataEtaBinTrk1 = (TH1F*)infDataEff->Get("hMuTrketabin1");
TH1F* DataEtaBinTrk2 = (TH1F*)infDataEff->Get("hMuTrketabin2");
TH1F* DataEtaBinTrk3 = (TH1F*)infDataEff->Get("hMuTrketabin3");
TH1F* MCEtaBinTrk1 = (TH1F*)infMCEff->Get("hMuTrketabin1");
TH1F* MCEtaBinTrk2 = (TH1F*)infMCEff->Get("hMuTrketabin2");
TH1F* MCEtaBinTrk3 = (TH1F*)infMCEff->Get("hMuTrketabin3");

TH1F* DataEtaBinID1 = (TH1F*)infDataEff->Get("hMuIDetabin1");
TH1F* DataEtaBinID2 = (TH1F*)infDataEff->Get("hMuIDetabin2");
TH1F* DataEtaBinID3 = (TH1F*)infDataEff->Get("hMuIDetabin3");
TH1F* MCEtaBinID1 = (TH1F*)infMCEff->Get("hMuIDetabin1");
TH1F* MCEtaBinID2 = (TH1F*)infMCEff->Get("hMuIDetabin2");
TH1F* MCEtaBinID3 = (TH1F*)infMCEff->Get("hMuIDetabin3");



float GetEffTrg(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);
float GetEffTrk(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);
float GetEffID(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin);


float GetPOGTrgEff(float pt, float eta, float eta2,  bool isData);
float GetPOGIDEff(float pt, float eta, bool isData);


void ConvertEffNewMethod(){

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

  int nevents_total = nt->GetEntries();                                               
  int nCand[nBins];
  float effDataTrg_tol[nBins];
  float effMCTrg_tol[nBins];
  float effDataTrk_tol[nBins];
  float effMCTrk_tol[nBins];
  float effDataID_tol[nBins];
  float effMCID_tol[nBins];
  float effDataAll_tol[nBins];
  float effMCAll_tol[nBins];
  
  float _tot_diff[nBins] ;
  for(int i = 0; i < nBins+1; i ++){
    nCand[i] = 0;
    effDataTrg_tol[i] = 0;
    effMCTrg_tol[i] = 0;
    effDataTrk_tol[i] = 0;
    effMCTrk_tol[i] = 0;
    effDataID_tol[i] = 0;
    effMCID_tol[i] = 0;
    effDataAll_tol[i] = 0;
    effMCAll_tol[i] = 0;
    _tot_diff[i] = 0;
  }

  TH1D *EffDataOverMCTrg = new TH1D("EffDataOverMCTrg","",nBins,ptBins);
  TH1D *EffDataOverMCTrk = new TH1D("EffDataOverMCTrk","",nBins,ptBins);
  TH1D *EffDataOverMCID = new TH1D("EffDataOverMCID","",nBins,ptBins);
  TH1D *EffDataOverMCAll = new TH1D("EffDataOverMCAll","",nBins,ptBins);
  TH1D *EffDataOverMCAllOldApproach = new TH1D("EffDataOverMCAllOldApproach","",nBins,ptBins);

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

      int _etabin = -1;
      int _ptbin = -1;
          
      float evtEffTrg_data,evtEffTrk_data,evtEffID_data;
      float evtEffTrg_mc,evtEffTrk_mc,evtEffID_mc;
          
          
      float mu1effTrg_data = GetEffTrg(mu1pt[c], mu1eta[c], true, "Trg", _ptbin, _etabin);
      float mu2effTrg_data = GetEffTrg(mu2pt[c], mu2eta[c], true, "Trg", _ptbin, _etabin);
      float mu1effTrg_mc = GetEffTrg(mu1pt[c], mu1eta[c], false, "Trg", _ptbin, _etabin);
      float mu2effTrg_mc = GetEffTrg(mu2pt[c], mu2eta[c], false, "Trg", _ptbin, _etabin);

      float mu1effTrk_data = GetEffTrk(mu1pt[c], mu1eta[c], true, "Trk", _ptbin, _etabin);
      float mu2effTrk_data = GetEffTrk(mu2pt[c], mu2eta[c], true, "Trk", _ptbin, _etabin);
      float mu1effTrk_mc = GetEffTrk(mu1pt[c], mu1eta[c], false, "Trk", _ptbin, _etabin);
      float mu2effTrk_mc = GetEffTrk(mu2pt[c], mu2eta[c], false, "Trk", _ptbin, _etabin);

      float mu1effID_data = GetEffID(mu1pt[c], mu1eta[c], true, "ID", _ptbin, _etabin);
      float mu2effID_data = GetEffID(mu2pt[c], mu2eta[c], true, "ID", _ptbin, _etabin);
      float mu1effID_mc = GetEffID(mu1pt[c], mu1eta[c], false, "ID", _ptbin, _etabin);
      float mu2effID_mc = GetEffID(mu2pt[c], mu2eta[c], false, "ID", _ptbin, _etabin);


      tot_++;
      if(mu1effTrg_data<0 || mu2effTrg_data<0||mu1effTrg_mc<0||mu1effTrg_mc<0) continue;
      if(mu1effTrk_data<0 || mu2effTrk_data<0||mu1effTrk_mc<0||mu1effTrk_mc<0) continue;
      if(mu1effID_data<0 || mu2effID_data<0||mu1effID_mc<0||mu1effID_mc<0) continue;
      
      
      if(pt[c]<10 || pt[c]>60) continue;
      float evtEffAll_data = 0;
      float evtEffAll_mc = 0;
    

      if(_eff_=="All"){
      
        evtEffTrg_data = mu1effTrg_data + mu2effTrg_data - mu1effTrg_data*mu2effTrg_data;
        evtEffTrg_mc = mu1effTrg_mc + mu2effTrg_mc - mu1effTrg_mc*mu2effTrg_mc;
        evtEffTrk_data = mu1effTrk_data*mu2effTrk_data;
        evtEffTrk_mc = mu1effTrk_mc*mu2effTrk_mc;
        evtEffID_data = mu1effID_data*mu2effID_data;
        evtEffID_mc = mu1effID_mc*mu2effID_mc;
        
        
        evtEffAll_data=evtEffTrg_data*evtEffTrk_data*evtEffID_data;
        evtEffAll_mc=evtEffTrg_mc*evtEffTrk_mc*evtEffID_mc;        
                
      }
    
      for(int _b=0; _b<nBins; _b++){
        if(pt[c] > ptBins[_b] && pt[c] < ptBins[_b+1]){
          nCand[_b]++;
          
          effDataTrg_tol[_b]+= evtEffTrg_data;
          effMCTrg_tol[_b]+= evtEffTrg_mc;
          effDataTrk_tol[_b]+= evtEffTrk_data;
          effMCTrk_tol[_b]+= evtEffTrk_mc;
          effDataID_tol[_b]+= evtEffID_data;
          effMCID_tol[_b]+= evtEffID_mc;
          
          effDataAll_tol[_b]+= evtEffAll_data;
          effMCAll_tol[_b]+= evtEffAll_mc;
        
        }
      }
  

    }
  }//Evt loop

  TCanvas *c1=  new TCanvas("c1","",850,600);      
  c1->Divide(2,2);                                                                                                                                                     
  c1->SetLeftMargin(0.15);
  for(int i = 0; i < nBins; i ++){
    cout<<effDataTrg_tol[i]<<endl;
    cout<<effMCTrg_tol[i]<<endl;
    cout<<(effDataTrg_tol[i])/effMCTrg_tol[i]<<endl;
    EffDataOverMCTrg->SetBinContent(i+1,(effDataTrg_tol[i])/effMCTrg_tol[i]);
    EffDataOverMCTrg->SetBinError(i+1,0.000000001);
    EffDataOverMCTrk->SetBinContent(i+1,(effDataTrk_tol[i])/effMCTrk_tol[i]);
    EffDataOverMCTrk->SetBinError(i+1,0.000000001);
    EffDataOverMCID->SetBinContent(i+1,(effDataID_tol[i])/effMCID_tol[i]);
    EffDataOverMCID->SetBinError(i+1,0.000000001);
    EffDataOverMCAll->SetBinContent(i+1,(effDataAll_tol[i])/effMCAll_tol[i]);
    EffDataOverMCAll->SetBinError(i+1,0.000000001);
    
    EffDataOverMCAllOldApproach->SetBinContent(i+1,EffDataOverMCTrg->GetBinContent(i+1)*EffDataOverMCTrk->GetBinContent(i+1)*EffDataOverMCID->GetBinContent(i+1));
    EffDataOverMCAllOldApproach->SetBinError(i+1,0.000000001);
  }
  //print a line for AN
  printf("\n");
  c1->cd(1);
  EffDataOverMCTrg->SetMaximum(0.9);
  EffDataOverMCTrg->SetMaximum(1.1);
  EffDataOverMCTrg->SetTitleOffset(1.2,"Y");
  EffDataOverMCTrg->SetMarkerColor(2);
  EffDataOverMCTrg->SetMarkerSize(1.2);
  EffDataOverMCTrg->SetLineWidth(1.9);
  EffDataOverMCTrg->Draw("pe");  
  EffDataOverMCTrg->SetXTitle("B^{+} p_{T} (GeV/c)");
  EffDataOverMCTrg->SetYTitle("B^{+} p_{T} Data/MC trigger (GeV/c)");
  
  EffDataOverMCTrg->GetXaxis()->SetTitleOffset(.85);
  EffDataOverMCTrg->GetYaxis()->SetTitleOffset(.9);
  EffDataOverMCTrg->GetXaxis()->SetTitleSize(0.045);
  EffDataOverMCTrg->GetYaxis()->SetTitleSize(0.045);
  EffDataOverMCTrg->GetXaxis()->SetTitleFont(42);
  EffDataOverMCTrg->GetYaxis()->SetTitleFont(42);
  EffDataOverMCTrg->GetXaxis()->SetLabelFont(42);
  EffDataOverMCTrg->GetYaxis()->SetLabelFont(42);
  EffDataOverMCTrg->GetXaxis()->SetLabelSize(0.04);
  EffDataOverMCTrg->GetYaxis()->SetLabelSize(0.04);  


  
  c1->cd(2);
  EffDataOverMCTrk->SetMaximum(0.9);
  EffDataOverMCTrk->SetMaximum(1.1);
  EffDataOverMCTrk->SetTitleOffset(1.2,"Y");
  EffDataOverMCTrk->SetMarkerColor(2);
  EffDataOverMCTrk->SetMarkerSize(1.2);
  EffDataOverMCTrk->SetLineWidth(1.9);
  EffDataOverMCTrk->Draw("pe");
  EffDataOverMCTrk->SetXTitle("B^{+} p_{T} (GeV/c)");
  EffDataOverMCTrk->SetYTitle("B^{+} p_{T} Data/MC tracking (GeV/c)");
  
  EffDataOverMCTrk->GetXaxis()->SetTitleOffset(.85);
  EffDataOverMCTrk->GetYaxis()->SetTitleOffset(.9);
  EffDataOverMCTrk->GetXaxis()->SetTitleSize(0.045);
  EffDataOverMCTrk->GetYaxis()->SetTitleSize(0.045);
  EffDataOverMCTrk->GetXaxis()->SetTitleFont(42);
  EffDataOverMCTrk->GetYaxis()->SetTitleFont(42);
  EffDataOverMCTrk->GetXaxis()->SetLabelFont(42);
  EffDataOverMCTrk->GetYaxis()->SetLabelFont(42);
  EffDataOverMCTrk->GetXaxis()->SetLabelSize(0.04);
  EffDataOverMCTrk->GetYaxis()->SetLabelSize(0.04);  


  c1->cd(3);
  EffDataOverMCID->SetMaximum(0.9);
  EffDataOverMCID->SetMaximum(1.1);
  EffDataOverMCID->SetTitleOffset(1.2,"Y");
  EffDataOverMCID->SetMarkerColor(2);
  EffDataOverMCID->SetMarkerSize(1.2);
  EffDataOverMCID->SetLineWidth(1.9);
  EffDataOverMCID->Draw("pe");
  EffDataOverMCID->SetXTitle("B^{+} p_{T} (GeV/c)");
  EffDataOverMCID->SetYTitle("B^{+} p_{T} Data/MC ID (GeV/c)");
  
  EffDataOverMCID->GetXaxis()->SetTitleOffset(.85);
  EffDataOverMCID->GetYaxis()->SetTitleOffset(.9);
  EffDataOverMCID->GetXaxis()->SetTitleSize(0.045);
  EffDataOverMCID->GetYaxis()->SetTitleSize(0.045);
  EffDataOverMCID->GetXaxis()->SetTitleFont(42);
  EffDataOverMCID->GetYaxis()->SetTitleFont(42);
  EffDataOverMCID->GetXaxis()->SetLabelFont(42);
  EffDataOverMCID->GetYaxis()->SetLabelFont(42);
  EffDataOverMCID->GetXaxis()->SetLabelSize(0.04);
  EffDataOverMCID->GetYaxis()->SetLabelSize(0.04);  

  c1->cd(4);
  EffDataOverMCAll->SetMaximum(0.9);
  EffDataOverMCAll->SetMaximum(1.2);
  EffDataOverMCAll->SetTitleOffset(1.2,"Y");
  EffDataOverMCAll->SetMarkerColor(2);
  EffDataOverMCAll->SetMarkerSize(1.2);
  EffDataOverMCAll->SetLineWidth(1.9);
  EffDataOverMCAll->Draw("pe");
  EffDataOverMCAll->SetXTitle("B^{+} p_{T} (GeV/c)");
  EffDataOverMCAll->SetYTitle("B^{+} p_{T} All convoluted ID (GeV/c)");
  
  EffDataOverMCAll->GetXaxis()->SetTitleOffset(.85);
  EffDataOverMCAll->GetYaxis()->SetTitleOffset(.9);
  EffDataOverMCAll->GetXaxis()->SetTitleSize(0.045);
  EffDataOverMCAll->GetYaxis()->SetTitleSize(0.045);
  EffDataOverMCAll->GetXaxis()->SetTitleFont(42);
  EffDataOverMCAll->GetYaxis()->SetTitleFont(42);
  EffDataOverMCAll->GetXaxis()->SetLabelFont(42);
  EffDataOverMCAll->GetYaxis()->SetLabelFont(42);
  EffDataOverMCAll->GetXaxis()->SetLabelSize(0.04);
  EffDataOverMCAll->GetYaxis()->SetLabelSize(0.04);  

  
  EffDataOverMCAllOldApproach->Draw("pesame");
  

  
  
  TLegend *myleg=new TLegend(0.3,0.564271,0.5145161,0.7167019,"");
  myleg->SetBorderSize(0);
  myleg->SetLineColor(0);
  myleg->SetFillColor(0);
  myleg->SetFillStyle(1001);
  myleg->SetTextFont(42);
  myleg->SetTextSize(0.05);

  TLegendEntry *ent_EffDataOverMCAll=myleg->AddEntry(EffDataOverMCAll,"<Data/MC(trg)><Data/MC(trk)><Data/MC(ID)>","PL");
  ent_EffDataOverMCAll->SetTextFont(42);
  ent_EffDataOverMCAll->SetLineColor(1);
  ent_EffDataOverMCAll->SetMarkerColor(1);
  
  TLegendEntry *ent_EffDataOverMCAllOldApproach=myleg->AddEntry(EffsDataOverMCAllOldApproach,"<Data/MC(trg)*Data/MC(trk)*Data/MC(ID)>","PL");
  ent_EffDataOverMCAllOldApproach->SetTextFont(42);
  ent_EffDataOverMCAllOldApproach->SetLineColor(1);
  ent_EffDataOverMCAllOldApproach->SetMarkerColor(1);

  myleg->Draw();
  
  c1->SaveAs("checkTPcorrection.pdf");
  
  

  //cout<<"Total B cand. "<<tot_<<endl;

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

float GetEffTrg(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
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
      for(int i = 0; i < DataEtaBinTrg1->GetNbinsX(); i++){
        if(pt>DataEtaBinTrg1->GetBinLowEdge(i+1) && pt<(DataEtaBinTrg1->GetBinLowEdge(i+1)+DataEtaBinTrg1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrg1->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrg1->GetNbinsX(); i++){
        if(pt>MCEtaBinTrg1->GetBinLowEdge(i+1) && pt<(MCEtaBinTrg1->GetBinLowEdge(i+1)+MCEtaBinTrg1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrg1->GetBinContent(i+1);
        }
      }
    }
  }


  else if(-0.8<eta && eta<0.8){
//  if(-0.8<eta && eta<0.8){
    _etabin = 2;
    if(isData){
      for(int i = 0; i < DataEtaBinTrg2->GetNbinsX(); i++){
        if(pt>DataEtaBinTrg2->GetBinLowEdge(i+1) && pt<(DataEtaBinTrg2->GetBinLowEdge(i+1)+DataEtaBinTrg2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrg2->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrg2->GetNbinsX(); i++){
        if(pt>MCEtaBinTrg2->GetBinLowEdge(i+1) && pt<(MCEtaBinTrg2->GetBinLowEdge(i+1)+MCEtaBinTrg2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrg2->GetBinContent(i+1);
        }
      }
    }
  }


  else if(0.8<eta && eta<1.46){
//  if(0.8<eta && eta<1.46){
    _etabin = 3;
    if(isData){
      for(int i = 0; i < DataEtaBinTrg3->GetNbinsX(); i++){
        if(pt>DataEtaBinTrg3->GetBinLowEdge(i+1) && pt<(DataEtaBinTrg3->GetBinLowEdge(i+1)+DataEtaBinTrg3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrg3->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrg3->GetNbinsX(); i++){
        if(pt>MCEtaBinTrg3->GetBinLowEdge(i+1) && pt<(MCEtaBinTrg3->GetBinLowEdge(i+1)+MCEtaBinTrg3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrg3->GetBinContent(i+1);
        }
      }
    }
  }
  return -1;
}


float GetEffTrk(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
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
      for(int i = 0; i < DataEtaBinTrk1->GetNbinsX(); i++){
        if(pt>DataEtaBinTrk1->GetBinLowEdge(i+1) && pt<(DataEtaBinTrk1->GetBinLowEdge(i+1)+DataEtaBinTrk1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrk1->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrk1->GetNbinsX(); i++){
        if(pt>MCEtaBinTrk1->GetBinLowEdge(i+1) && pt<(MCEtaBinTrk1->GetBinLowEdge(i+1)+MCEtaBinTrk1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrk1->GetBinContent(i+1);
        }
      }
    }
  }


  else if(-0.8<eta && eta<0.8){
//  if(-0.8<eta && eta<0.8){
    _etabin = 2;
    if(isData){
      for(int i = 0; i < DataEtaBinTrk2->GetNbinsX(); i++){
        if(pt>DataEtaBinTrk2->GetBinLowEdge(i+1) && pt<(DataEtaBinTrk2->GetBinLowEdge(i+1)+DataEtaBinTrk2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrk2->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrk2->GetNbinsX(); i++){
        if(pt>MCEtaBinTrk2->GetBinLowEdge(i+1) && pt<(MCEtaBinTrk2->GetBinLowEdge(i+1)+MCEtaBinTrk2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrk2->GetBinContent(i+1);
        }
      }
    }
  }


  else if(0.8<eta && eta<1.46){
//  if(0.8<eta && eta<1.46){
    _etabin = 3;
    if(isData){
      for(int i = 0; i < DataEtaBinTrk3->GetNbinsX(); i++){
        if(pt>DataEtaBinTrk3->GetBinLowEdge(i+1) && pt<(DataEtaBinTrk3->GetBinLowEdge(i+1)+DataEtaBinTrk3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinTrk3->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinTrk3->GetNbinsX(); i++){
        if(pt>MCEtaBinTrk3->GetBinLowEdge(i+1) && pt<(MCEtaBinTrk3->GetBinLowEdge(i+1)+MCEtaBinTrk3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinTrk3->GetBinContent(i+1);
        }
      }
    }
  }
  return -1;
}



float GetEffID(float pt, float eta, bool isData, TString _eff_type, int &_ptbin, int &_etabin){
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
      for(int i = 0; i < DataEtaBinID1->GetNbinsX(); i++){
        if(pt>DataEtaBinID1->GetBinLowEdge(i+1) && pt<(DataEtaBinID1->GetBinLowEdge(i+1)+DataEtaBinID1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinID1->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinID1->GetNbinsX(); i++){
        if(pt>MCEtaBinID1->GetBinLowEdge(i+1) && pt<(MCEtaBinID1->GetBinLowEdge(i+1)+MCEtaBinID1->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinID1->GetBinContent(i+1);
        }
      }
    }
  }


  else if(-0.8<eta && eta<0.8){
//  if(-0.8<eta && eta<0.8){
    _etabin = 2;
    if(isData){
      for(int i = 0; i < DataEtaBinID2->GetNbinsX(); i++){
        if(pt>DataEtaBinID2->GetBinLowEdge(i+1) && pt<(DataEtaBinID2->GetBinLowEdge(i+1)+DataEtaBinID2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinID2->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinID2->GetNbinsX(); i++){
        if(pt>MCEtaBinID2->GetBinLowEdge(i+1) && pt<(MCEtaBinID2->GetBinLowEdge(i+1)+MCEtaBinID2->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinID2->GetBinContent(i+1);
        }
      }
    }
  }


  else if(0.8<eta && eta<1.46){
//  if(0.8<eta && eta<1.46){
    _etabin = 3;
    if(isData){
      for(int i = 0; i < DataEtaBinID3->GetNbinsX(); i++){
        if(pt>DataEtaBinID3->GetBinLowEdge(i+1) && pt<(DataEtaBinID3->GetBinLowEdge(i+1)+DataEtaBinID3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return DataEtaBinID3->GetBinContent(i+1);
        }
      }
    }
    if(!isData){
      for(int i = 0; i < MCEtaBinID3->GetNbinsX(); i++){
        if(pt>MCEtaBinID3->GetBinLowEdge(i+1) && pt<(MCEtaBinID3->GetBinLowEdge(i+1)+MCEtaBinID3->GetBinWidth(i+1))){
          _ptbin = i+1;
          return MCEtaBinID3->GetBinContent(i+1);
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
