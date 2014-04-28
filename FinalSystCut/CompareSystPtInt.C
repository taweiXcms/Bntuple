void CompareSystPtInt(){

  const int nBins=10;

  //int idcut=1; double ptBins[nBins+1]={0.,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1};
  //int idcut=2; double ptBins[nBins+1]={2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4};
  int idcut=3; double ptBins[nBins+1]={-0.3,-0.24,-0.18,-0.12,-0.06,0.,0.06,0.12,0.18,0.24,0.3};
  //int idcut=4; double ptBins[nBins+1]={0.8,0.82,0.84,0.86,0.88,0.9,0.92,0.94,0.96,0.98,1.0};
   
  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*file0=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step0.root",idcut));
  TFile*file1=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step1.root",idcut));
  TFile*file2=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step2.root",idcut));
  TFile*file3=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step3.root",idcut));
  TFile*file4=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step4.root",idcut));
  TFile*file5=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step5.root",idcut));
  TFile*file6=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step6.root",idcut));
  TFile*file7=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step7.root",idcut));
  TFile*file8=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step8.root",idcut));
  TFile*file9=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step9.root",idcut));
  
  
 TH1F*hSigmaBis0=(TH1F*)file0->Get("hPtSigma");
 TH1F*hSigmaBis1=(TH1F*)file1->Get("hPtSigma");
 TH1F*hSigmaBis2=(TH1F*)file2->Get("hPtSigma");
 TH1F*hSigmaBis3=(TH1F*)file3->Get("hPtSigma");
 TH1F*hSigmaBis4=(TH1F*)file4->Get("hPtSigma");
 TH1F*hSigmaBis5=(TH1F*)file5->Get("hPtSigma");
 TH1F*hSigmaBis6=(TH1F*)file6->Get("hPtSigma");
 TH1F*hSigmaBis7=(TH1F*)file7->Get("hPtSigma");
 TH1F*hSigmaBis8=(TH1F*)file8->Get("hPtSigma");
 TH1F*hSigmaBis9=(TH1F*)file9->Get("hPtSigma");
 
 hSigmaBis0->SetName("hSigmaBis0");
 hSigmaBis1->SetName("hSigmaBis1");
 hSigmaBis2->SetName("hSigmaBis2");
 hSigmaBis3->SetName("hSigmaBis3");
 hSigmaBis4->SetName("hSigmaBis4");
 hSigmaBis5->SetName("hSigmaBis5");
 hSigmaBis6->SetName("hSigmaBis6");
 hSigmaBis7->SetName("hSigmaBis7");
 hSigmaBis8->SetName("hSigmaBis8");
 hSigmaBis9->SetName("hSigmaBis9");

  TH1D *hPtAll = new TH1D("hPtAll","",nBins,ptBins);
  
  hPtAll->SetBinContent(1,hSigmaBis0->GetBinContent(1));
  hPtAll->SetBinContent(2,hSigmaBis1->GetBinContent(1));
  hPtAll->SetBinContent(3,hSigmaBis2->GetBinContent(1));
  hPtAll->SetBinContent(4,hSigmaBis3->GetBinContent(1));
  hPtAll->SetBinContent(5,hSigmaBis4->GetBinContent(1));
  hPtAll->SetBinContent(6,hSigmaBis5->GetBinContent(1));
  hPtAll->SetBinContent(7,hSigmaBis6->GetBinContent(1));
  hPtAll->SetBinContent(8,hSigmaBis7->GetBinContent(1));
  hPtAll->SetBinContent(9,hSigmaBis8->GetBinContent(1));
  hPtAll->SetBinContent(10,hSigmaBis9->GetBinContent(1));
  
  hPtAll->SetBinError(1,hSigmaBis0->GetBinError(1));
  hPtAll->SetBinError(2,hSigmaBis1->GetBinError(1));
  hPtAll->SetBinError(3,hSigmaBis2->GetBinError(1));
  hPtAll->SetBinError(4,hSigmaBis3->GetBinError(1));
  hPtAll->SetBinError(5,hSigmaBis4->GetBinError(1));
  hPtAll->SetBinError(6,hSigmaBis5->GetBinError(1));
  hPtAll->SetBinError(7,hSigmaBis6->GetBinError(1));
  hPtAll->SetBinError(8,hSigmaBis7->GetBinError(1));
  hPtAll->SetBinError(9,hSigmaBis8->GetBinError(1));
  hPtAll->SetBinError(10,hSigmaBis9->GetBinError(1));

  if (idcut==1 || idcut==3) hPtAll->Scale(1/hPtAll->GetBinContent(1)); 
  
 
  if (idcut==2 || idcut==4) {
  hPtAll->Scale(1/hPtAll->GetBinContent(5)); 
  }

  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",500,500);
  canvasVscut->cd();  
  canvasVscut->cd(1);
  if(idcut==1) hPtAll->GetXaxis()->SetTitle("chi2cl cut value");
  if(idcut==2) hPtAll->GetXaxis()->SetTitle("d0/d0err cut value");
  if(idcut==3) hPtAll->GetXaxis()->SetTitle("cosTheta cut value");
  if(idcut==4) hPtAll->GetXaxis()->SetTitle("trk pt cut value");
  hPtAll->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hPtAll->GetXaxis()->SetTitleOffset(1.);
  hPtAll->GetYaxis()->SetTitleOffset(1.);
  hPtAll->GetXaxis()->SetTitleSize(0.04);
  hPtAll->GetYaxis()->SetTitleSize(0.04);
  hPtAll->GetXaxis()->SetTitleFont(42);
  hPtAll->GetYaxis()->SetTitleFont(42);
  hPtAll->GetXaxis()->SetLabelFont(42);
  hPtAll->GetYaxis()->SetLabelFont(42);
  hPtAll->GetXaxis()->SetLabelSize(0.035);
  hPtAll->GetYaxis()->SetLabelSize(0.035);  
  hPtAll->SetMinimum(0.);
  hPtAll->Draw();
  TF1 *fPt0 = new TF1("fPt0","[0]*x+[1]");
  hPtAll->Fit("fPt0","L q","",ptBins[0],ptBins[10]);
  TLatex * tlatexPt0=new TLatex(0.15,0.35,Form("Intersection y axis= %.2f",fPt0->GetParameter(1)));
  tlatexPt0->SetNDC();
  tlatexPt0->SetTextColor(1);
  tlatexPt0->SetTextFont(42);
  tlatexPt0->SetTextSize(0.06);
  tlatexPt0->Draw();  
  canvasVscut->SaveAs(Form("canvasVscutId%d.pdf",idcut));
  
  
}
