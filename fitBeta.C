#include "utilities.h"
#include "TH1D.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;

//svmit2
//TString inputdata="/data/bmeson/data/nt_20140403_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
//TString inputmc="/data/bmeson/MC/nt_BoostedMC_20140403_Kp_TriggerMatchingMuon_EvtBase_skim.root;
//TString inputmc="/data/bmeson/MC/nt_BoostedMC_20140408_Kp_TriggerMatchingMuon_EvtBase_skim.root";//have genmu1&genmu2 information

//cgate
//TString inputdata="/mnt/hadoop/cms/store/user/jwang/nt_20140403_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
TString inputdata="/export/d00/scratch/jwang/nt_201403019_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase.root";
//TString inputmc="/mnt/hadoop/cms/store/user/jwang/nt_BoostedMC_20140403_Kp_TriggerMatchingMuon_EvtBase_skim.root";
//TString inputmc="/mnt/hadoop/cms/store/user/jwang/nt_BoostedMC_20140318_Kp_TriggerMatchingMuon_EvtBase.root";
TString inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140408_Kp_TriggerMatchingMuon_EvtBase_skim.root";//have genmu1&genmu2 information


//TString cut="chi2cl>0.01&&(d0)/d0Err>3.4&&dtheta<2.98&&TMath::Abs((trk1Dxy)/trk1D0Err)>2.4";
TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&chi2cl>0.0054&&(d0/d0Err)>3.3&&cos(dtheta)>-0.53&&TMath::Abs((trk1Dxy)/trk1D0Err)>1.9&&mass>5&&mass<6";
TString seldata=Form("abs(y+0.465)<1.93&&pt<60.&&pt>10.&&%s",cut.Data());
TString seldata_2y=Form("((Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&pt<60.&&pt>10.&&%s",cut.Data());
TString selmc=Form("abs(y+0.465)<1.93&&pt>10.&&pt<60.&&%s",cut.Data());
TString selmcgen="abs(y+0.465)<1.93&&pt>10.&&pt<60.&&abs(pdgId)==521&&isSignal>0";

TString weight = "(27.493+pt*(-0.218769))";


void clean0(TH1D *h){
  for (int i=1;i<=h->GetNbinsX();i++){
    if (h->GetBinContent(i)==0) h->SetBinError(i,1);
  }
}

TF1 *fit(TTree *nt,TTree *ntMC,double ptmin,double ptmax, int positive){   
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",50,5,6);
   TH1D *hMC = new TH1D(Form("hMC%d",count),"",50,5,6);
   // Fit function
   TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[5]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   //nt->Project(Form("h%d",count),"mass",Form("%s&&((Run>=210498&&Run<=211256&&(y+0.465)>%f)||(Run>=211313&&Run<=211631&&(y-0.465)>%f))&&((Run>=210498&&Run<=211256&&(y+0.465)<%f)||(Run>=211313&&Run<=211631&&(y-0.465)<%f))",seldata_2y.Data(),ptmin,ptmin,ptmax,ptmax));   
   if(positive) nt->Project(Form("h%d",count),"mass",Form("%s&&Run>=210498&&Run<=211256&&(y+0.465)>%f&&(y+0.465)<%f",seldata_2y.Data(),ptmin,ptmax));
   else nt->Project(Form("h%d",count),"mass",Form("%s&&Run>=211313&&Run<=211631&&(y-0.465)>%f&&(y-0.465)<%f",seldata_2y.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&(y+0.465)>%f&&(y+0.465)<%f",seldata.Data(),ptmin,ptmax));   

   clean0(h);
   h->Draw();
   f->SetParLimits(4,-1000,0);
   f->SetParLimits(2,0.01,0.05);
   f->SetParLimits(8,0.01,0.05);
   f->SetParLimits(7,0,1);
   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->SetParameter(8,setparam3);
   f->FixParameter(1,fixparam1);
   h->GetEntries();

   hMC->Fit(Form("f%d",count),"q","",5,6);
   hMC->Fit(Form("f%d",count),"q","",5,6);
   f->ReleaseParameter(1);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L m","",5,6);

   f->FixParameter(1,f->GetParameter(1));
   f->FixParameter(2,f->GetParameter(2));
   f->FixParameter(7,f->GetParameter(7));
   f->FixParameter(8,f->GetParameter(8));
   
   h->Fit(Form("f%d",count),"q","",5,6);
   h->Fit(Form("f%d",count),"q","",5,6);
   f->ReleaseParameter(1);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L m","",5,6);
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<h->GetEntries()<<endl;

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x");
//   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *Bkpi = new TF1(Form("fBkpi",count),"[0]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   Bkpi->SetParameter(0,f->GetParameter(5));
   Bkpi->SetLineColor(kGreen+1);
   Bkpi->SetFillColor(kGreen+1);
   Bkpi->SetRange(5.00,5.28);
   Bkpi->SetLineStyle(1);
   Bkpi->SetFillStyle(3004);

   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetParError(7,f->GetParError(7));
   mass->SetParError(8,f->GetParError(8));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");
   h->SetXTitle("M_{B} (GeV/c^{2})");
   h->SetYTitle("Entries / (20 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.4,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   Bkpi->Draw("same");
   background->Draw("same");   
   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   double yield = mass->Integral(5,6)/0.02;
   double yieldErr = mass->Integral(5,6)/0.02*mass->GetParError(0)/mass->GetParameter(0);


   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(h,Form("%.1f<|y_{CM}|<%.1f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();

   //c->SaveAs(Form("ResultsBplus/BMass-%d.C",count));
   //c->SaveAs(Form("ResultsBplus/BMass-%d.gif",count));
   //c->SaveAs(Form("ResultsBplus/BMass-%d.eps",count));
   c->SaveAs(Form("ResultsBplus/BMass-%d.pdf",count));

   return mass;
}

void fitBeta(TString infname="",bool doweight = 1)
{
  if (doweight==0) weight="1";
  if (infname=="") infname=inputdata.Data();
  TFile *inf = new TFile(infname.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKp");
    
  const int nBins = 4;
  //double ptBins[nBins+1] = {10,15,20,25,30,60};
  double ptBins[nBins+1] = {-1.93,-1.0,0,1.0,1.93};

  TH1D *hPt1 = new TH1D("hPt1","",nBins,ptBins);
  TH1D *hPt2 = new TH1D("hPt2","",nBins,ptBins);
  TH1D *hPtRecoTruth = new TH1D("hPtRecoTruth","",nBins,ptBins);
  //TH1D *hPtMCtest = new TH1D("hPtMCtest",";y;MC truth",50,-1.93,1.93);
  TH1D *hPtMC = new TH1D("hPtMC",";y_{CM};MC truth",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen",";y_{CM};Gen particle",nBins,ptBins);
  TH1D *hPtGenAcc = new TH1D("hPtGenAcc",";y_{CM};Gen particle",nBins,ptBins);
  //TH1D *hPtGentest = new TH1D("hPtGentest",";y;Gen particle",50,-1.93,1.93);

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1],1);
      double yield = f->Integral(5,6)/0.02;
      double yieldErr = f->Integral(5,6)/0.02*f->GetParError(0)/f->GetParameter(0);
      hPt1->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt1->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }  
  TCanvas *c1=  new TCanvas("c1","",600,600);
  hPt1->SetXTitle("B^{+} p_{T} (GeV/c)");
  hPt1->SetYTitle("Uncorrected B^{+} dN/dy");
  hPt1->Sumw2();
  hPt1->Draw();
  c1->SaveAs("ResultsBplus_1.gif");

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1],0);
      double yield = f->Integral(5,6)/0.02;
      double yieldErr = f->Integral(5,6)/0.02*f->GetParError(0)/f->GetParameter(0);
      hPt2->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt2->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }  
  TCanvas *c2=  new TCanvas("c2","",600,600);
  hPt2->SetXTitle("B^{+} p_{T} (GeV/c)");
  hPt2->SetYTitle("Uncorrected B^{+} dN/dy");
  hPt2->Sumw2();
  hPt2->Draw();
  c2->SaveAs("ResultsBplus_2.gif");

  ntMC->Project("hPtMC","(y+0.465)",TCut(weight)*(TCut(selmc.Data())&&"gen==22233"));
  ntGen->Project("hPtGen","(y+0.465)",TCut(weight)*(TCut(selmcgen.Data())));
  ntGen->Project("hPtGenAcc","(y+0.465)",TCut(weight)*TCut("((abs(mu1eta)<1.3&&mu1pt>3.3)||(abs(mu1eta)>1.3&&abs(mu1eta)<2.2&&mu1p>2.9)||(abs(mu1eta)>2.2&&abs(mu1eta)<2.4&&mu1pt>0.8))&&((abs(mu2eta)<1.3&&mu2pt>3.3)||(abs(mu2eta)>1.3&&abs(mu2eta)<2.2&&mu2p>2.9)||(abs(mu2eta)>2.2&&abs(mu2eta)<2.4&&mu2pt>0.8))&&abs(y+0.465)<1.93&&pt>10.&&pt<60.&&abs(pdgId)==521&&isSignal>0"));

  divideBinWidth(hPtMC);
  divideBinWidth(hPtGen);
  divideBinWidth(hPtGenAcc);

  hPtMC->Sumw2();
  hPtGenAcc->Sumw2();
  hPtGen->Sumw2();

  TH1D *hEfftotal1 = (TH1D*)hPtMC->Clone("hEfftotal1");
  hEfftotal1->Divide(hPtGen);
  hEfftotal1->SetYTitle("total Efficiency");
  TCanvas *cEfftotal1 = new TCanvas("cEfftotal1","",600,600);
  hEfftotal1->Draw();
  cEfftotal1->SaveAs("ResultsBplus/Efftotal_1.gif");
  
  TH1D *hEfftotaltem = (TH1D*)hPtMC->Clone("hEfftotaltem");
  hEfftotaltem->Divide(hPtGen);
  TH1D *hEfftotal2 = new TH1D("hEfftotal2",";y_{CM};total Efficiency",nBins,ptBins);
  for(int i=0;i<nBins;i++)
    {
      hEfftotal2->SetBinContent(i+1,hEfftotaltem->GetBinContent(nBins-i));
      hEfftotal2->SetBinError(i+1,hEfftotaltem->GetBinError(nBins-i));
    }
  TCanvas *cEfftotal2 = new TCanvas("cEfftotal2","",600,600);
  hEfftotal2->Draw();
  cEfftotal2->SaveAs("ResultsBplus/Efftotal_2.gif");

  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hEff->Divide(hPtGenAcc);
  hEff->SetYTitle("cut Efficiency");
  TCanvas *cEff = new TCanvas("cEff","",600,600);
  hEff->Draw();
  cEff->SaveAs("ResultsBplus/Eff.gif");
  
  TH1D *hAcc = (TH1D*)hPtGenAcc->Clone("hAcc");
  hAcc->Divide(hPtGen);
  hAcc->SetYTitle("Acceptance");
  TCanvas *cAcc = new TCanvas("cAcc","",600,600);
  hAcc->Draw();
  cAcc->SaveAs("ResultsBplus/Acc.gif");

  TH1D *hPtCor1 = (TH1D*)hPt1->Clone("hPtCor1");
  hPtCor1->Divide(hEfftotal1);
  TCanvas *cCor1=  new TCanvas("cCorResult1","",600,600);
  hPtCor1->SetYTitle("Corrected B^{+} dN/dy");
  hPtCor1->Draw();
  //hPtGen->Draw("same hist");
  cCor1->SaveAs("ResultsBplus/Cor_1.gif");

  TH1D *hPtCor2 = (TH1D*)hPt2->Clone("hPtCor2");
  hPtCor2->Divide(hEfftotal2);
  TCanvas *cCor2=  new TCanvas("cCorResult2","",600,600);
  hPtCor2->SetYTitle("Corrected B^{+} dN/dy");
  hPtCor2->Draw();
  //hPtGen->Draw("same hist");
  cCor2->SaveAs("ResultsBplus/Cor_2.gif");

  TH1D *hPtCor = (TH1D*)hPtCor1->Clone("hPtCor");
  hPtCor->Add(hPtCor2);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Corrected B^{+} dN/dy");
  hPtCor->Draw();
  cCor->SaveAs("ResultsBplus/Cor.gif");

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  double BRchain=6.09604e-5;
  hPtSigma->Scale(1./(2*luminosity*BRchain));
  hPtSigma->SetYTitle("d#sigma (B^{+})/dy");
  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);
  hPtSigma->Draw();
  cCor->SaveAs("ResultsBplus/Sigma.gif");
  
  TFile *outf = new TFile("ResultsBplus/SigmaBplus.root","recreate");
  outf->cd();
  hPt1->Write();
  hPt2->Write();
  hEff->Write();
  hAcc->Write();
  hEfftotal1->Write();
  hEfftotal2->Write();
  hPtGen->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;

  //back up

  
  

  /*
  TCanvas *cMCfine =  new TCanvas("cMCfine","",600,600);
  //hPtMCtest->Sumw2();
  hPtMCtest->Draw();
  cMCfine->SaveAs("MCfine.gif");
  TCanvas *cMC =  new TCanvas("cMC","",600,600);
  //hPtMC->Sumw2();
  hPtMC->Draw();
  cMC->SaveAs("MC.gif");
  TCanvas *cGen =  new TCanvas("cGen","",600,600);
  //hPtGen->Sumw2();
  hPtGen->Draw();
  cGen->SaveAs("Gen.gif");
  TCanvas *cGenfine =  new TCanvas("cGenfine","",600,600);
  //hPtGentest->Sumw2();
  hPtGentest->Draw();
  cGenfine->SaveAs("Genfine.gif");
  */
  /*  
  hPtMCtest->Divide(hPtGentest);
  hPtMCtest->GetYaxis()->SetTitle("Efficiency");
  TCanvas *cEfffine =  new TCanvas("cEfffine","",600,600);
  //hPtMCtest->Sumw2();
  hPtMCtest->Draw();
  cEfffine->SaveAs("Efffine.gif");
  */

  
}
