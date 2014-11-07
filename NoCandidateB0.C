#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

TString inputdata="/afs/cern.ch/work/w/wangj/public/nt_20140727_PAMuon_HIRun2013_Merged_y24_Using03090319Bfinder.root";
TString inputmc="/afs/cern.ch/work/w/wangj/public/nt_20140801_mixed_fromQMBFinder_Kstar.root";

TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>9.94e-02&&(d0/d0Err)>6.08&&cos(dtheta)>7.93e-01&&abs(tktkmass-0.89594)<0.10&&tktkmassKK>1.04&&mu1pt>1.5&&mu2pt>1.5&&abs(mass-5.279)<0.08"; 
TString particle="B^{0}";

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
  TFile *infMC = new TFile(inputmc);
  TTree *ntData = (TTree*) infData->Get("ntKstar");
  TTree *ntMC = (TTree*) infMC->Get("ntKstar");

  TCanvas *c = new TCanvas(Form("c%i",i),"",600,600);
  //if (logy) c->SetLogy();
  
  TH1D* hData = new TH1D("hData","",30,1,31);
  TH1D* hMC = new TH1D("hMC","",30,1,31);

  ntData->Project("hData","size",Form("%s&&(pt>%f&&pt<%f)&&(y>%f&&y<%f)",cut.Data(),ptmin,ptmax,ymin,ymax));
  ntMC->Project("hMC","size",Form("%s&&(pt>%f&&pt<%f)&&(y>%f&&y<%f)",cut.Data(),ptmin,ptmax,ymin,ymax));

  double normData=0,normMC=0;
  normData = hData->GetEntries();
  normMC = hMC->GetEntries();
  cout<<normData<<" "<<normMC<<endl;
  
  hData->Scale(1./normData);
  hMC->Scale(1./normMC); 

  hData->SetXTitle("# of candidate");
  hData->SetYTitle("#Probability");
  hData->SetTitleOffset(1.5,"Y");
  if(hData->GetMaximum()>hMC->GetMaximum()) hData->SetMaximum(hData->GetMaximum()*1.2);
  else hData->SetMaximum(hMC->GetMaximum()*1.2);

  hData->SetLineColor(kBlue+1);
  hData->SetFillStyle(1001);
  hData->SetFillColor(kBlue-9);
  hData->SetLineWidth(3);
  hData->SetStats(0);

  hMC->SetLineColor(kRed);
  hMC->SetFillStyle(3004);
  hMC->SetFillColor(kRed);
  hMC->SetLineWidth(3);
  hMC->SetStats(0);

  hData->Draw();
  hMC->Draw("same");
  
  TLegend *leg = new TLegend(0.50,0.75,0.70,0.87);
  leg->AddEntry(hData,"data","f");
  leg->AddEntry(hMC,"MC","f");
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

  c->SaveAs("CandidateResult/Bzero_candidates_compare_sigreg.pdf");
}

void NoCandidateB0()
{
  const int nBins = 1;
  double ptBins[nBins+1] = {10,60};
  //const int nBins = 5;
  //double ptBins[nBins+1] = {10,15,20,25,30,60};
  //const int nBins=5;
  //double yBins[nBins+1] = {-3,-2,-1,0,1,2};
  int i=0;
  for(i=0;i<nBins;i++)
    {
      dimuonLoop(ptBins[i],ptBins[i+1],-2.4,2.4,i+1);
      //dimuonLoop(10.,60.,yBins[i],yBins[i+1],i+1);
    }
}

/*
.x dataMC.C+("d0/d0Err","d0/#sigma(d0)","d0D0err",40,0,200,1)
.x dataMC.C+("chi2cl","Vertex #chi^{2} Probability","ProbChi2",20,0,1)
.x dataMC.C+("cos(dtheta)","cos(#Delta#theta)","cosdtheta",20,-1,1)
.x dataMC.C+("abs(trk1Dxy/trk1D0Err)","|trk1Dxy/trk1D0Err|","trk1DxyDerr",40,0,200,1)
*/
