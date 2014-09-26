#include "utilities.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;
double setparam3=0.03;
double fixparam2=0.04;

//svmit02
TString inputdata="/data/bmeson/data/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/data/bmeson/MC/nt_20140801_mixed_fromQMBFinder_Kstar.root";


TString cut_kpi="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>9.94e-02&&(d0/d0Err)>6.08&&cos(dtheta)>7.93e-01&&abs(tktkmass-0.89594)<0.10&&tktkmassKK>1.04"; 

/*
TString seldata_2y_kpi=Form("((Run>1&&Run<12&&abs(y-0.465)<1.93)||(Run<=1&&abs(y+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&%s",cut_kpi.Data());
TString selmc_kpi=Form("((Run<=1&&abs(y+0.465)<1.93)||(Run>1&&abs(y-0.465)<1.93))&&(gen==23333||gen==41000)&&%s",cut_kpi.Data());
TString selmcgen="((Run<=1&&abs(y+0.465)<1.93)||(Run>1&&abs(y-0.465)<1.93))&&abs(pdgId)==511&&isSignal!=0";
*/

TString seldata_2y_kpi=Form("%s",cut_kpi.Data());
TString selmc_kpi=Form("abs(y)<2.4&&%s",cut_kpi.Data());
TString selmcgen="abs(y)<2.4&&abs(pdgId)==511&&isSignal!=0";

TString weight = "27.493+pt*(-0.218769)";

void clean0(TH1D *h)
{
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      if (h->GetBinContent(i)==0) h->SetBinError(i,1);
   }
}

TF1 *fit(TTree *nt, TTree *ntMC, double ptmin,double ptmax)
{   
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",30,5.03,5.93);
   TH1D *hMCright = new TH1D(Form("hMCright%d",count),"",30,5.03,5.93);
   TH1D *hMCwrong = new TH1D(Form("hMCwrong%d",count),"",30,5.03,5.93);
   TH1D *hMC = new TH1D(Form("hMC%d",count),"",30,5.03,5.93);

   TF1* frightSignal = new TF1("frightSignal","[0]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])");
   TF1* fwrongSignal = new TF1("fwrongSignal","[0]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])");
   // Fit function
   TString iNP="2.28629e1*Gaus(x,5.02606,6.84e-2)/(sqrt(2*3.14159)*(6.84e-2))+3.85695*Gaus(x,5.27701,0.04305)/(sqrt(2*3.14159)*(0.04305))";


   TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[7])*Gaus(x,[5],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[6]*("+iNP+")");

   nt->Project(Form("h%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata_2y_kpi.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMCright%d",count),"mass",Form("gen==23333&&%s&&pt>%f&&pt<%f",seldata_2y_kpi.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMCwrong%d",count),"mass",Form("gen==41000&&%s&&pt>%f&&pt<%f",seldata_2y_kpi.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMC%d",count),"mass",Form("(gen==41000||gen==23333)&&%s&&pt>%f&&pt<%f",seldata_2y_kpi.Data(),ptmin,ptmax));   

   //hMCwrong->Draw();
   //hMCright->Draw();

   clean0(h);
   h->Draw();

   frightSignal->SetParLimits(2,0.01,0.08);
   frightSignal->SetParameter(2,setparam2);
   frightSignal->SetParameter(1,setparam1);
   frightSignal->FixParameter(1,fixparam1);
   hMCright->Fit("frightSignal","q","",5,6);
   hMCright->Fit("frightSignal","q","",5,6);
   hMCright->Fit("frightSignal","q","",5,6);
   frightSignal->ReleaseParameter(1);
   hMCright->Fit("frightSignal","q","",5,6);
   hMCright->Fit("frightSignal","q","",5,6);
   hMCright->Fit("frightSignal","q","",5,6);

   fwrongSignal->SetParLimits(2,0.01,0.1);
   fwrongSignal->SetParameter(2,setparam3);
   fwrongSignal->FixParameter(1,fixparam1);
   hMCwrong->Fit("fwrongSignal","q","",5,6);
   hMCwrong->Fit("fwrongSignal","q","",5,6);
   hMCwrong->Fit("fwrongSignal","q","",5,6);
   fwrongSignal->ReleaseParameter(1);
   hMCwrong->Fit("fwrongSignal","q","",5,6);
   hMCwrong->Fit("fwrongSignal","q","",5,6);
   hMCwrong->Fit("fwrongSignal","q","",5,6);

   f->FixParameter(1,frightSignal->GetParameter(1));
   f->FixParameter(2,frightSignal->GetParameter(2));
   f->FixParameter(5,fwrongSignal->GetParameter(1));
   f->FixParameter(8,fwrongSignal->GetParameter(2));

   f->SetParLimits(7,0,1);
   f->FixParameter(6,0);
   hMC->Fit(Form("f%d",count),"q","",5,6);
   hMC->Fit(Form("f%d",count),"q","",5,6);
   hMC->Fit(Form("f%d",count),"q","",5,6);

   cout<<f->GetParameter(1)<<endl;
   cout<<f->GetParameter(2)<<endl;
   cout<<f->GetParameter(5)<<endl;
   cout<<f->GetParameter(8)<<endl;
   cout<<f->GetParameter(7)<<endl;
   
   f->FixParameter(7,f->GetParameter(7));
   f->ReleaseParameter(6);
   f->SetParLimits(4,-1000,0);
   f->SetParLimits(6,0,1000);
   f->SetParameter(0,setparam0);
   h->Fit(Form("f%d",count),"q","",5,6);
   h->Fit(Form("f%d",count),"q","",5,6);
   /*
   f->ReleaseParameter(1);
   f->ReleaseParameter(5);
   h->Fit(Form("f%d",count),"q","",5,6);
   h->Fit(Form("f%d",count),"q","",5,6);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L m","",5,6);
   */
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<h->GetEntries()<<endl;

   cout<<"################################# "<<endl;
   cout<<f->GetParameter(0)<<endl;
   cout<<f->GetParameter(1)<<endl;
   cout<<f->GetParameter(2)<<endl;
   cout<<f->GetParameter(5)<<endl;
   cout<<f->GetParameter(8)<<endl;
   cout<<f->GetParameter(7)<<endl;
   cout<<f->GetParameter(3)<<endl;
   cout<<f->GetParameter(4)<<endl;
   cout<<f->GetParameter(6)<<endl;
   cout<<"################################# "<<endl;

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);

   // function for signal shape plotting. take the fit result from f
   TF1 *Bkpi = new TF1(Form("fBkpi%d",count),"[0]*("+iNP+")");
   Bkpi->SetParameter(0,f->GetParameter(6));
   Bkpi->SetLineColor(kGreen+1);
   Bkpi->SetFillColor(kGreen+1);
   Bkpi->SetRange(5.00,6.00);
   Bkpi->SetLineStyle(1);
   Bkpi->SetFillStyle(3005);

   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass%d",count),"[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[5],[4])/(sqrt(2*3.14159)*[4]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8),f->GetParameter(5));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetParError(7,f->GetParError(7));
   mass->SetParError(8,f->GetParError(8));
   mass->SetParError(5,f->GetParError(5));
   mass->SetLineColor(kRed);
   mass->SetLineStyle(2);
   
   TF1 *massRight = new TF1(Form("fmassRight%d",count),"[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2]))");
   massRight->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7));
   massRight->SetParError(0,f->GetParError(0));
   massRight->SetParError(1,f->GetParError(1));
   massRight->SetParError(2,f->GetParError(2));
   massRight->SetParError(3,f->GetParError(7));
   massRight->SetLineColor(kOrange-4);
   massRight->SetLineStyle(1);

   TF1 *massWrong = new TF1(Form("fmassWrong%d",count),"[0]*((1-[3])*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2]))");
   massWrong->SetParameters(f->GetParameter(0),f->GetParameter(5),f->GetParameter(8),f->GetParameter(7));
   massWrong->SetParError(0,f->GetParError(0));
   massWrong->SetParError(1,f->GetParError(5));
   massWrong->SetParError(2,f->GetParError(8));
   massWrong->SetParError(3,f->GetParError(7));
   massWrong->SetLineColor(kMagenta+2);
   massWrong->SetLineStyle(1);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");
   h->SetXTitle("M_{B} (GeV/c^{2})");
   h->SetYTitle("Entries / (30 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.5,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");

 //  hBck->Draw("hist same");

   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   cout<<"test1 ";
   massRight->SetRange(5,6);
   massRight->Draw("same");
   massRight->SetLineStyle(1);
   massRight->SetFillStyle(3001);
   massRight->SetFillColor(kOrange-4);
   cout<<"test2 ";
   massWrong->SetRange(5,6);
   massWrong->Draw("same");
   massWrong->SetLineStyle(1);
   massWrong->SetFillStyle(3004);
   massWrong->SetFillColor(kMagenta+2);
   Bkpi->Draw("same");
   background->Draw("same");   

   //f->Draw("same");

   //cout <<"fit result:"<<f->GetParameter(0)*2.5<<" "<<f->Integral(5,6)/h->GetBinWidth(1)<<endl;

   double yield = mass->Integral(5,6)/0.03;
   double yieldErr = mass->Integral(5,6)/0.03*mass->GetParError(0)/mass->GetParameter(0);
   
   // Draw the legend:)   
   TLegend *leg = myLegend(0.45,0.45,0.86,0.89);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(h,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(massRight,"Correct K#pi Combination","f");
   leg->AddEntry(massWrong,"Wrong K#pi Combination","f");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.30,0.89,0.45);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",f->GetParameter(1)*1000.,f->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f",yield,yieldErr),"");
   leg2->Draw();


   //c->SaveAs(Form("ResultsBzero/BMass-%d.C",count));
   //c->SaveAs(Form("ResultsBzero/BMass-%d.gif",count));
   //c->SaveAs(Form("ResultsBzero/BMass-%d.eps",count));
   c->SaveAs(Form("ResultsBzero/BMass-%d.pdf",count));

   return mass;
   /*
   TF1 *test = new TF1("test","x");
   return test;
   */
}

void fitB2signal(TString infname="",bool doweight = 1)
{
  if (doweight==0) weight="1";
  if (infname=="") infname=inputdata.Data();
  TFile *inf = new TFile(infname.Data());
  TTree *nt = (TTree*) inf->Get("ntKstar");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKstar");

  ntGen->AddFriend(ntMC);
  //nt->SetAlias("LD",LDalias.Data());
  //nt2->SetAlias("LD",LDalias.Data());

  //ntMC->SetAlias("LD",LDalias.Data());
  //ntMC2->SetAlias("LD",LDalias.Data());
  
  const int nBins = 1;
  double ptBins[nBins+1] = {10,60};

  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D *hRecoTruth = new TH1D("hRecoTruth","",nBins,ptBins);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen","",nBins,ptBins);
  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(5,6)/0.03;
      double yieldErr = f->Integral(5,6)/0.03*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i])); 
    }  

  /*  
  TCanvas *c=  new TCanvas("cResult","",600,600);
  hPt->SetXTitle("B^{0} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected B^{0} dN/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  

  ntMC->Project("hPtMC","pt",TCut(weight)*(TCut(seldata_2y_kpi.Data())&&"(gen==23333||gen==41000)"));

  nt->Project("hRecoTruth","pt",TCut(seldata_2y_kpi.Data())&&"(gen==23333||gen==41000)");
  ntGen->Project("hPtGen","pt",TCut(weight)*(selmcgen.Data()));
  divideBinWidth(hRecoTruth);
  
  hRecoTruth->Draw("same hist");
  divideBinWidth(hPtMC);
  divideBinWidth(hPtGen);
  
  hPtMC->Sumw2();
  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hPtMC->Sumw2();
  hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Correctd B^{0} dN/dp_{T}");
  hPtCor->Draw();
  hPtGen->Draw("same hist");

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");

  // B0->J/psi K*0(892) = 1.34 +- 0.06 x 10^-3
  // J/psi -> mumu = 5.93 +- 0.06 x 10^-2
  // K*0(892) -> K+ pi- = 66%
  double BRchain=5.244e-5;

  hPtSigma->Scale(1./(2*luminosity*BRchain));
  hPtSigma->SetYTitle("d#sigma/dp_{T} (B^{0}) ");

  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);

  hPtSigma->Draw();
  
  TFile *outf = new TFile("ResultsBzero/SigmaBzero.root","recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;
  */
}
