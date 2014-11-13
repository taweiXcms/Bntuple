#include "../CodeForNtupleProduction/utilities.h"

//Look at me!!!!////////////////////////////////////////////
float Ratio=72.9755/27.9381;
//float Change=0;
float Change=0.041;
//float Change=-0.041;
///////////////////////////////////////////////////////////

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;

//svmithi2
//TString inputdata="/data/bmeson/data/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
//TString inputmc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Kp.root";
//lxplus
TString inputdata="/afs/cern.ch/work/w/wangj/public/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/afs/cern.ch/work/w/wangj/public/nt_20140801_mixed_fromQMBFinder_Kp.root";

//tk pt, chi2
TString cut="abs(y)<2.4&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01&&mu1pt>1.5&&mu2pt>1.5";
//TString cut="abs(y)<2.4&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";

TString seldata_2y=Form("%s",cut.Data());
TString selmc=Form("abs(y)<2.4&&gen==23333&&%s",cut.Data());
TString selmcgen="abs(y)<2.4&&abs(pdgId)==521&&isSignal==1";

TString weight = "(27.493+pt*(-0.218769))";

void clean0(TH1D *h){
  for (int i=1;i<=h->GetNbinsX();i++){
    if (h->GetBinContent(i)==0) h->SetBinError(i,1);
  }
}

TF1 *fit(TTree *nt,TTree *ntMC,double ptmin,double ptmax){   
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;

   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",50,5,6);
   TH1D *hMC = new TH1D(Form("hMC%d",count),"",50,5,6);

   TString iNP="(7.26667e+00*Gaus(x,5.10472e+00,2.63158e-02)/(sqrt(2*3.14159)*2.63158e-02)+4.99089e+01*Gaus(x,4.96473e+00,9.56645e-02)/(sqrt(2*3.14159)*9.56645e-02)+3.94417e-01*(3.74282e+01*Gaus(x,5.34796e+00,3.11510e-02)+1.14713e+01*Gaus(x,5.42190e+00,1.00544e-01)))";
   TF1* fNP = new TF1("fNP",iNP);
   float normNP = fNP->Integral(5,6);
   TString signal = "([5]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[5])*Gaus(x,[1],[6])/(sqrt(2*3.14159)*[6]))";
   TF1 *f = new TF1(Form("f%d",count),Form("[0]*%s+[3]+[4]*x+(%s/%f)*([0]/%f)",signal.Data(),iNP.Data(),Ratio*(1+Change),normNP));

   nt->Project(Form("h%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata_2y.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata_2y.Data(),ptmin,ptmax));   
   clean0(h);
   h->Draw();
   f->SetParLimits(4,-1000,0);
   f->SetParLimits(2,0.01,0.05);
   f->SetParLimits(6,0.01,0.05);
   f->SetParLimits(5,0,1);

   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->SetParameter(6,setparam3);
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
   f->FixParameter(5,f->GetParameter(5));
   f->FixParameter(6,f->GetParameter(6));
   
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
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   //cout<<"======="<<normNP<<"======="<<endl;
   // function for signal shape plotting. take the fit result from f
   TF1 *Bkpi = new TF1(Form("fBkpi",count),Form("([0]/(%f*%f))*%s",Ratio*(1+Change),normNP,iNP.Data()));
   Bkpi->SetParameter(0,f->GetParameter(0));
   Bkpi->SetLineColor(kGreen+1);
   Bkpi->SetFillColor(kGreen+1);
//   Bkpi->SetRange(5.00,5.28);
   Bkpi->SetRange(5.00,6.00);
   Bkpi->SetLineStyle(1);
   Bkpi->SetFillStyle(3004);

   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(5),f->GetParameter(6));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetParError(3,f->GetParError(7));
   mass->SetParError(4,f->GetParError(8));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

   double yield = mass->Integral(5,6)/0.02;
   double yieldErr = mass->Integral(5,6)/0.02*mass->GetParError(0)/mass->GetParameter(0);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");   
   h->SetXTitle("M_{B} (GeV/c^{2})");
   h->SetYTitle("Entries / (20 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.5,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   Bkpi->Draw("same");
   background->Draw("same");   
   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.89);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(h,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h,"B^{+} meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();
   TLegend *leg3 = myLegend(0.02,0.83,0.37,0.92);
   if(Change==0) leg3->AddEntry((TObject*)0,Form("Ratio=%.2f",Ratio),"");
   else leg3->AddEntry((TObject*)0,Form("Ratio=%.2f(%.1f%)",Ratio*(1+Change),Change*100),"");
   leg3->Draw();

   if(Change==0) c->SaveAs("BplusApplyRatio.pdf");
   if(Change>0) c->SaveAs("BplusApplyRatioPlus.pdf");
   if(Change<0) c->SaveAs("BplusApplyRatioMinus.pdf");

   return mass;
}

void fitBarea(TString infname="",bool doweight = 1)
{
  if (doweight==0) weight="1";
  if (infname=="") infname=inputdata.Data();
  TFile *inf = new TFile(infname.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntGen2 = (TTree*)inf->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKp");
    
  ntGen->AddFriend(ntMC);
  ntGen2->AddFriend(ntMC);
    
  const int nBins = 1;
  double ptBins[nBins+1] = {10,60};
//  const int nBins = 1;
//  double ptBins[nBins+1] = {10,60};
  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(5,6)/0.02;
      double yieldErr = f->Integral(5,6)/0.02*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }
  
}
