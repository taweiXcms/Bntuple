#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

TString inputdata="/afs/cern.ch/work/w/wangj/public/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";

TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02&&mu1pt>1.5&&mu2pt>1.5";
TString particle="B^{0}_{s}";

/*
double norm(TH1D* h,double low,double high)
{
    TF1 *f = new TF1("f","[0]+[1]*x");
    h->Fit("f","L","",5.4,6);
    double val = f->Integral(low,high);
    delete f;
    return val;
}
*/

void dimuonLoop(float ptmin, float ptmax, float ymin, float ymax, int i)
{
  TFile *infData = new TFile(inputdata);
  TTree *ntData = (TTree*) infData->Get("ntphi");

  TCanvas *c = new TCanvas(Form("c%i",i),"",600,600);
  
  TH1D* hJpsi = new TH1D("hJpsi","",50,2.8,3.3);
  TH1D* hDimuon = new TH1D("hDimuon","",50,2.8,3.3);

  ntData->Project("hDimuon","mumumass",Form("%s&&(pt>%f&&pt<%f)&&(y>%f&&y<%f)",cut.Data(),ptmin,ptmax,ymin,ymax));
  ntData->Project("hJpsi","ujmass",Form("%s&&(pt>%f&&pt<%f)&&(y>%f&&y<%f)",cut.Data(),ptmin,ptmax,ymin,ymax));

  double normDimuon=0,normJpsi=0;
  normDimuon = hDimuon->GetEntries();
  normJpsi = hJpsi->GetEntries();
  cout<<normDimuon<<" "<<normJpsi<<endl;
  
  hDimuon->Scale(1./normDimuon);
  hJpsi->Scale(1./normJpsi); 

  hDimuon->SetXTitle("#mu#mu mass");
  hDimuon->SetYTitle("#Probability");
  hDimuon->SetTitleOffset(1.5,"Y");
  if(hDimuon->GetMaximum()>hJpsi->GetMaximum()) hDimuon->SetMaximum(hDimuon->GetMaximum()*1.2);
  else hDimuon->SetMaximum(hJpsi->GetMaximum()*1.2);

  hDimuon->SetLineColor(kBlue+1);
  hDimuon->SetFillStyle(1001);
  hDimuon->SetFillColor(kBlue-9);
  hDimuon->SetLineWidth(3);
  hDimuon->SetStats(0);

  hJpsi->SetLineColor(kRed);
  hJpsi->SetFillStyle(3004);
  hJpsi->SetFillColor(kRed);
  hJpsi->SetLineWidth(3);
  hJpsi->SetStats(0);

  hDimuon->Draw();
  hJpsi->Draw("same");
  
  TLegend *leg = new TLegend(0.11,0.75,0.50,0.9);
  leg->AddEntry(hDimuon,"#mu#mu invariant mass","f");
  leg->AddEntry(hJpsi,"J/#psi mass after fit","f");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");
  TLegend *leg1 = new TLegend(0.60,0.7,0.90,0.9);
  leg1->AddEntry((TObject*)0,Form("%s",particle.Data()),"");
  leg1->AddEntry((TObject*)0,Form("%.0f<p_{T}<%.0f GeV",ptmin,ptmax),"");
  leg1->AddEntry((TObject*)0,Form("%.1f<y_{CM}<%.1f",ymin,ymax),"");
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->Draw("same");

  c->SaveAs(Form("MuonResult/Bsubs/dimuony_%i.pdf",i));
  //c->SaveAs(Form("MuonResult/Bsubs/Bs_dimuon.pdf",i));
}

void dimuonBs()
{
  //const int nBins = 1;
  //double ptBins[nBins+1] = {10,60};
  //const int nBins = 3;
  //double ptBins[nBins+1] = {10,15,20,60};
  const int nBins=5;
  double yBins[nBins+1] = {-3,-2,-1,0,1,2};
  int i=0;
  for(i=0;i<nBins;i++)
    {
      //dimuonLoop(ptBins[i],ptBins[i+1],-2.4,2.4,i+1);
      dimuonLoop(10.,60.,yBins[i],yBins[i+1],i+1);
    }
}

/*
.x dataMC.C+("d0/d0Err","d0/#sigma(d0)","d0D0err",40,0,200,1)
.x dataMC.C+("chi2cl","Vertex #chi^{2} Probability","ProbChi2",20,0,1)
.x dataMC.C+("cos(dtheta)","cos(#Delta#theta)","cosdtheta",20,-1,1)
.x dataMC.C+("abs(trk1Dxy/trk1D0Err)","|trk1Dxy/trk1D0Err|","trk1DxyDerr",40,0,200,1)
*/
