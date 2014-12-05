#include "utilities.h"

double luminosity=34*1e-3;
double setparam0=100.;
double setparam1=5.367;
double setparam2=0.02;
double setparam3=0.03;
double fixparam1=5.367;

//svmit02
//TString inputdata="/data/bmeson/data/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
//TString inputmc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Phi.root";

//lxplus
TString inputdata="/afs/cern.ch/work/w/wangj/public/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/afs/cern.ch/work/w/wangj/public/nt_20140801_mixed_fromQMBFinder_Phi.root";

//Bs tkpt chi2
TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";

TString seldata_2y=Form("%s",cut.Data());
TString selmc=Form("abs(y)<2.4&&gen==23333&&%s",cut.Data());
TString selmcgen="abs(y)<2.4&&abs(pdgId)==531&&isSignal>0";

TString weight = "27.493+pt*(-0.218769)";
TString particle="B^{0}_{s}";

void clean0(TH1D *h)
{
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      if (h->GetBinContent(i)==0) h->SetBinError(i,1);
   }
}


TF1 *fit(TTree *nt,TTree *ntMC,double ptmin,double ptmax,float mupt,bool ifmc)
{
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",24,5.03,5.99);
   TH1D *hMC = new TH1D(Form("hMC%d",count),"",24,5.03,5.99);
   // Fit function
   TString iNP="Gaus(x,5.36800e+00,5.77122e-02)/(sqrt(2*3.14159)*abs(5.77122e-02))";
   TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+ [3]+[4]*x+[5]*x*x + [11]*("+iNP+")");
   nt->Project(Form("h%d",count),"mass",Form("%s&&pt>%f&&pt<%f&&mu1pt>%f&&mu2pt>%f",seldata_2y.Data(),ptmin,ptmax,mupt,mupt));   
   ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f&&mu1pt>%f&&mu2pt>%f",seldata_2y.Data(),ptmin,ptmax,mupt,mupt));   
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
   f->SetParLimits(11,0,1000);
   f->SetParameter(11,10);
   f->FixParameter(11,0);
   f->FixParameter(9,0);
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
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *Bkpi = new TF1(Form("fBkpi",count),"[0]*("+iNP+")");
   Bkpi->SetParameter(0,f->GetParameter(11));
   Bkpi->SetLineColor(kGreen+1);
   Bkpi->SetFillColor(kGreen+1);
//   Bkpi->SetRange(5.00,5.28);
   Bkpi->SetRange(5.00,6.00);
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
   h->SetYTitle("Entries / (40 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   Bkpi->Draw("same");
   background->Draw("same");   
   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   double yield = mass->Integral(5,6)/0.040;
   double yieldErr = mass->Integral(5,6)/0.04*mass->GetParError(0)/mass->GetParameter(0);


   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.89);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(h,Form("#mu p_{T} > %.1f GeV/c",mupt),"");
   //leg->AddEntry(h,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
//   leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();

   if(ifmc) c->SaveAs(Form("MuonPt/Bs/BMassMC-%d.pdf",count));
   else c->SaveAs(Form("MuonPt/Bs/BMass-%d.pdf",count));

   return mass;
}

void ncDmBsFit(TString infname="",bool doweight = 1)
{
   if (doweight==0) weight="1";
   if (infname=="") infname=inputdata.Data();
   TFile *inf = new TFile(infname.Data());
   TTree *nt = (TTree*) inf->Get("ntphi");

   TFile *infMC = new TFile(inputmc.Data());
   TTree *ntGen = (TTree*)infMC->Get("ntGen");
   TTree *ntMC = (TTree*)infMC->Get("ntphi");

   ntGen->AddFriend(ntMC);

   const int nBins = 6;
   double ptBins[nBins+1] = {0.5,1.0,1.5,2.0,2.5,3.0,3.5};

   TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
   TH1D *hPtBase = new TH1D("hPtBase","",nBins,ptBins);
   TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
   TH1D *hPtMCBase = new TH1D("hPtMCBase","",nBins,ptBins);

   TCanvas *cfinal = new TCanvas("cfinal","",600,600);

   TF1 *fbase = fit(nt,ntMC,10,60,0,false);
   double yieldBase = fbase->Integral(5,6)/0.02;
   double yieldErrBase = fbase->Integral(5,6)/0.02*fbase->GetParError(0)/fbase->GetParameter(0);

   TF1 *fmcbase = fit(ntMC,ntMC,10,60,0,true);
   double yieldMCBase = fmcbase->Integral(5,6)/0.02;

   for (int i=0;i<nBins;i++)
     {
       TF1 *f = fit(nt,ntMC,10,60,ptBins[i],false);
       double yield = f->Integral(5,6)/0.02;
       double yieldErr = f->Integral(5,6)/0.02*f->GetParError(0)/f->GetParameter(0);
       hPt->SetBinContent(i+1,yield);
       hPt->SetBinError(i+1,yieldErr);
       hPtBase->SetBinContent(i+1,yieldBase);
       hPtBase->SetBinError(i+1,yieldErrBase);

       TF1 *fMC = fit(ntMC,ntMC,10,60,ptBins[i],true);
       double yieldMC = fMC->Integral(5,6)/0.02;
       hPtMC->SetBinContent(i+1,yieldMC);
       hPtMCBase->SetBinContent(i+1,yieldMCBase);
     }  

   //hPt->Sumw2();
   //hPtBase->Sumw2();
   hPt->Divide(hPtBase);
   //hPt->Sumw2();
   hPtMC->Divide(hPtMCBase);

   for(int i=0;i<nBins;i++)
     {
       double tem=0;
       tem = hPt->GetBinContent(i+1);
       hPt->SetBinContent(i+1,1-tem);
       tem = hPtMC->GetBinContent(i+1);
       hPtMC->SetBinContent(i+1,1-tem);
     }

   hPtMC->SetXTitle("#mu p_{T} larger than (GeV)");
   hPtMC->SetYTitle("Probability of losing candidate");
   hPtMC->SetTitleOffset(1.5,"Y");
   hPtMC->SetMaximum(0.35);
   //  if(hPt->GetMaximum()>hPtMC->GetMaximum()) hPtMC->SetMaximum(hPt->GetMaximum()*1.03);
   //  else hPtMC->SetMaximum(hPtMC->GetMaximum()*1.03);

   hPt->SetMarkerStyle(8);
   hPt->SetStats(0);
   hPtMC->SetLineColor(kRed);
   hPtMC->SetFillStyle(3004);
   hPtMC->SetFillColor(kRed);
   hPtMC->SetLineWidth(3);
   hPtMC->SetStats(0);
  
   hPtMC->Draw();
   hPt->Draw("same lep");

   TLegend *legi = new TLegend(0.13,0.72,0.33,0.84);
   legi->AddEntry(hPt,"data","pl");
   legi->AddEntry(hPtMC,"MC","f");
   legi->SetBorderSize(0);
   legi->SetFillStyle(0);
   legi->Draw("same");
   TLegend *leg1i = new TLegend(0.20,0.7,0.50,0.9);
   leg1i->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
   leg1i->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",10.0,60.0),"");
   leg1i->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",-2.4,2.4),"");
   leg1i->SetBorderSize(0);
   leg1i->SetFillStyle(0);
   leg1i->Draw("same");

   cfinal->SaveAs("MuonPt/Bs/muonpt.pdf");


   /*
   divideBinWidth(hPtMC);
   divideBinWidth(hPtGen);

   TCanvas *c=  new TCanvas("cResult","",600,600);
   hPt->SetXTitle("B_{s} p_{T} (GeV/c)");
   hPt->SetYTitle("Uncorrected B_{s} dN/dp_{T}");
   hPt->Draw();
   hRecoTruth->Draw("same hist");
   
   hPtMC->Sumw2();
   TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
   hPtMC->Sumw2();
   hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Correctd B_{s} dN/dp_{T}");
  hPtCor->Draw();
  hPtGen->Draw("same");

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  double BRchain=2.89977e-5;
  hPtSigma->Scale(1./(2*luminosity*BRchain));
  hPtSigma->SetYTitle("d#sigma/dp_{T} (B_{s})");

  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);

  hPtSigma->Draw();
  
  TFile *outf = new TFile("../ResultsBs/SigmaBs.root","recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;
  */
}
