#include "TFile.h"
#include "TTree.h"
#include <iostream>


void checkB0(){
 
  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");
     
  TString cut_kpi="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01"; 
  TString seldata=Form("abs(y+0.465)<1.93&&%s&&mass>5.&&mass<6.&&gen==22233",cut_kpi.Data());
   
  TH1D *hproject = new TH1D("hproject","",50,5,6);
  nt->Project("hproject","mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),10.,60.));   
  
  TH1F*h=new TH1F("h","h",50,5,6);
  TH1F*hBstoJPsiPhi=new TH1F("hBstoJPsiPhi","hBstoJPsiPhi",50,5,6);
  TH1F*hBplustoJPsiK1plus=new TH1F("hBplustoJPsiK1plus","hBplustoJPsiK1plus",50,5,6);
  TH1F*hBzerotoJPsiK10=new TH1F("hBzerotoJPsiK10","hBzerotoJPsiK10",50,5,6);

   
  Float_t mumumass[4096];
  Float_t y[4096];
  Float_t mass[4096];
  Float_t trk1Pt[4096];
  Float_t trk2Pt[4096];
  Float_t chi2cl[4096];
  Float_t d0[4096];
  Float_t d0Err[4096];
  Float_t dtheta[4096];
  Float_t tktkmass[4096];
  Int_t isbestchi2[4096];
  Int_t HLT_PAMu3_v1[4096];
  Float_t gen[4096];
  
  
  Int_t trk1geninfo[4096];
  Int_t pdgtrk1[4096];
  Int_t mothertrk1geninfo[4096];
  Int_t pdgmothertrk1[4096];
  Int_t grandmothertrk1geninfo[4096];
  Int_t pdggrandmothertrk1[4096];

  Int_t trk2geninfo[4096];
  Int_t pdgtrk2[4096];
  Int_t mothertrk2geninfo[4096];
  Int_t pdgmothertrk2[4096];
  Int_t grandmothertrk2geninfo[4096];
  Int_t pdggrandmothertrk2[4096];

  Int_t muon1geninfo[4096];
  Int_t pdgmuon1[4096];
  Int_t mothermuon1geninfo[4096];
  Int_t pdgmothermuon1[4096];
  Int_t grandmothermuon1geninfo[4096];
  Int_t pdggrandmothermuon1[4096];

  Int_t muon2geninfo[4096];
  Int_t pdgmuon2[4096];
  Int_t mothermuon2geninfo[4096];
  Int_t pdgmothermuon2[4096];
  Int_t grandmothermuon2geninfo[4096];
  Int_t pdggrandmothermuon2[4096];
  
  Int_t trk1geninfo[4096];
  Int_t trk2geninfo[4096];
  Int_t muon1geninfo[4096];
  Int_t muon2geninfo[4096];


  Int_t grandmothertrk1geninfo[4096];
  Int_t grandmothertrk2geninfo[4096];
  Int_t grandmothermuon1geninfo[4096];
  Int_t grandmothermuon2geninfo[4096];
  
  Int_t Event;

  
  

  nt->SetBranchAddress("y",&y);
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  nt->SetBranchAddress("mumumass",&mumumass);
  nt->SetBranchAddress("mass",&mass);
  nt->SetBranchAddress("isbestchi2",&isbestchi2);
  nt->SetBranchAddress("trk1Pt",&trk1Pt);
  nt->SetBranchAddress("trk2Pt",&trk2Pt);
  nt->SetBranchAddress("chi2cl",&chi2cl);
  nt->SetBranchAddress("d0Err",&d0Err);
  nt->SetBranchAddress("d0",&d0);
  nt->SetBranchAddress("dtheta",&dtheta);
  nt->SetBranchAddress("tktkmass",&tktkmass);
  nt->SetBranchAddress("gen",&gen);
  nt->SetBranchAddress("Event",&Event);
  
  
  nt->SetBranchAddress("pdgtrk1",&pdgtrk1);
  nt->SetBranchAddress("pdgtrk2",&pdgtrk2);
  nt->SetBranchAddress("pdgmuon1",&pdgmuon1);
  nt->SetBranchAddress("pdgmuon2",&pdgmuon2);
  
  nt->SetBranchAddress("pdgmothertrk1",&pdgmothertrk1);
  nt->SetBranchAddress("pdgmothertrk2",&pdgmothertrk2);
  nt->SetBranchAddress("pdgmothermuon1",&pdgmothermuon1);
  nt->SetBranchAddress("pdgmothermuon2",&pdgmothermuon2);

  nt->SetBranchAddress("pdggrandmothertrk1",&pdggrandmothertrk1);
  nt->SetBranchAddress("pdggrandmothertrk2",&pdggrandmothertrk2);
  nt->SetBranchAddress("pdggrandmothermuon1",&pdggrandmothermuon1);
  nt->SetBranchAddress("pdggrandmothermuon2",&pdggrandmothermuon2);
  
  nt->SetBranchAddress("trk1geninfo",&trk1geninfo);
  nt->SetBranchAddress("trk2geninfo",&trk2geninfo);
  nt->SetBranchAddress("muon1geninfo",&muon1geninfo);
  nt->SetBranchAddress("muon2geninfo",&muon2geninfo);
  
  nt->SetBranchAddress("grandmothertrk1geninfo",&grandmothertrk1geninfo);
  nt->SetBranchAddress("grandmothertrk2geninfo",&grandmothertrk2geninfo);
  nt->SetBranchAddress("grandmothermuon1geninfo",&grandmothermuon1geninfo);
  nt->SetBranchAddress("grandmothermuon2geninfo",&grandmothermuon2geninfo);



  Int_t nentries = (Int_t)nt->GetEntries();

  for (Int_t i=0; i<nentries; i++) {
    nt->GetEntry(i);
    
    cout<<"event number="<<Event<<endl;
    for (int j=0;j<3;j++){
    cout<<isbestchi2[j]<<endl;
    bool cut1=(TMath::Abs(y[0]+0.465)<1.93);
    bool cut2=(HLT_PAMu3_v1[0]==1);
    bool cut3=(TMath::Abs(mumumass[0]-3.096916));
    bool cut4=(mass[0]>5.);
    bool cut5=(mass[0]<6.);
    bool cut6=(isbestchi2[0]==1);
    bool cut7=(trk1Pt[0]>0.7);
    bool cut8=(trk2Pt[0]>0.7);
    bool cut9=(chi2cl[0]>1.65e-01);
    bool cut10=((d0[0]/d0Err[0])>4.16);
    bool cut11=(TMath::Cos(dtheta[0])>7.50e-01);
    bool cut12=(TMath::Abs(tktkmass[0]-0.89594)<2.33e-01);
    bool cut13=(!(gen[0]==22233||gen[0]==41000));
    bool cut14=((mass[0]>5.)&&(mass[0]<6));
    
    bool cut15=(trk1geninfo[0]>-1);
    bool cut16=(trk2geninfo[0]>-1);
    bool cut17=(muon1geninfo[0]>-1);
    bool cut18=(muon2geninfo[0]>-1);
    
    if(cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11&&cut12&&cut13&&cut14&&cut14&&cut15&&cut16&&cut17&&cut18){
    h->Fill(mass[0]);
    
    
    if((pdggrandmothertrk1[0]==531)&&(pdggrandmothertrk2[0]==531)&&(pdggrandmothermuon1[0]==531)&&(pdggrandmothermuon2[0]==531)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){
    hBstoJPsiPhi->Fill(mass[0]);
    }
    }
    
    if((pdggrandmothertrk1[0]==521)&&(pdggrandmothertrk2[0]==521)&&(pdggrandmothermuon1[0]==521)&&(pdggrandmothermuon2[0]==521)){
    if((pdgmothertrk1[0]==10323)&&(pdgmothertrk2[0]==10323)&&(pdgmothermuon1[0]==443)&&(pdgmothermuon2[0]==443)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){

    hBplustoJPsiK1plus->Fill(mass[0]);
    }
    }
    }
    
    if((pdggrandmothertrk1[0]==511)&&(pdggrandmothertrk2[0]==511)&&(pdggrandmothermuon1[0]==511)&&(pdggrandmothermuon2[0]==511)){
    if((pdgmothertrk1[0]==10313)&&(pdgmothertrk2[0]==10313)&&(pdgmothermuon1[0]==443)&&(pdgmothermuon2[0]==443)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){

    hBzerotoJPsiK10->Fill(mass[0]);
    }
    }
    }
    
    if((pdggrandmothertrk1[0]==pdggrandmothertrk2[0])&&(pdggrandmothermuon1[0]==pdggrandmothermuon2[0])&&(pdggrandmothermuon1[0]==pdggrandmothertrk1[0])){
   
    cout<<"--------------------------"<<endl;
    cout<<"pdgtrk1="<<pdgtrk1[0]<<", pdgmothertrk1="<<pdgmothertrk1[0]<<", pdggrandmothertrk1="<<pdggrandmothertrk1[0]<<endl;
    cout<<"pdgtrk2="<<pdgtrk2[0]<<", pdgmothertrk2="<<pdgmothertrk2[0]<<", pdggrandmothertrk2="<<pdggrandmothertrk2[0]<<endl;
    cout<<"pdgmuon1="<<pdgmuon1[0]<<", pdgmothermuon1="<<pdgmothermuon1[0]<<", pdggrandmothermuon1="<<pdggrandmothermuon1[0]<<endl;
    cout<<"pdgmuon2="<<pdgmuon2[0]<<", pdgmothermuon2="<<pdgmothermuon2[0]<<", pdggrandmothermuon2="<<pdggrandmothermuon2[0]<<endl;

   }
}
  }//end for
  }
  h->Draw();
  TCanvas*canvas=new TCanvas("canvas","canvas",800,400);
  canvas->Divide(3,2);
  canvas->cd(1);
  h->Draw();
  canvas->cd(2);
  hBstoJPsiPhi->Draw();
  canvas->cd(3);
  hBplustoJPsiK1plus->Draw();
  canvas->cd(4);
  hBzerotoJPsiK10->Draw();
  canvas->cd(5);
  h->Draw();
  
  canvas->SaveAs("canvas.png");

}//end macro
