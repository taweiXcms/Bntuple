void CompareSystPtInt(int idcut=4){

  const int nBins=10;

  //int idcut=1; double ptBins[nBins+1]={0.,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1};
  //int idcut=2; double ptBins[nBins+1]={2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4};
  //int idcut=3; double ptBins[nBins+1]={-0.5,-0.4,-0.3,-0.2,-0.1,0.,0.1,0.2,0.3,0.4,0.5};
  //int idcut=4; double ptBins[nBins+1]={0.6,0.64,0.68,0.72,0.76,0.8,0.84,0.88,0.92,0.96,1.0};
  

  
  double ptBins[nBins+1];
  
  if(idcut==1){ ptBins[0]=0.; ptBins[1]=0.01; ptBins[2]=0.02; ptBins[3]=0.03; ptBins[4]=0.04; ptBins[5]=0.05; ptBins[6]=0.06; ptBins[7]=0.07; ptBins[8]=0.08; ptBins[9]=0.09; ptBins[10]=0.1;}
  if(idcut==2){ ptBins[0]=2.4; ptBins[1]=2.6; ptBins[2]=2.8; ptBins[3]=3.0; ptBins[4]=3.2; ptBins[5]=3.4; ptBins[6]=3.6; ptBins[7]=3.8; ptBins[8]=4.0; ptBins[9]=4.2; ptBins[10]=4.4;}
  if(idcut==3){ ptBins[0]=-0.5; ptBins[1]=-0.4; ptBins[2]=-0.3; ptBins[3]=-0.2; ptBins[4]=-0.1; ptBins[5]=0.; ptBins[6]=0.1; ptBins[7]=0.2; ptBins[8]=0.3; ptBins[9]=0.4; ptBins[10]=0.5;}
  if(idcut==4){ ptBins[0]=0.6; ptBins[1]=0.64; ptBins[2]=0.68; ptBins[3]=0.72; ptBins[4]=0.76; ptBins[5]=0.80; ptBins[6]=0.84; ptBins[7]=0.88; ptBins[8]=0.92; ptBins[9]=0.96; ptBins[10]=1.0;}
  

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*file0=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step0_isData1.root",idcut));
  TFile*file1=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step1_isData1.root",idcut));
  TFile*file2=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step2_isData1.root",idcut));
  TFile*file3=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step3_isData1.root",idcut));
  TFile*file4=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step4_isData1.root",idcut));
  TFile*file5=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step5_isData1.root",idcut));
  TFile*file6=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step6_isData1.root",idcut));
  TFile*file7=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step7_isData1.root",idcut));
  TFile*file8=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step8_isData1.root",idcut));
  TFile*file9=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step9_isData1.root",idcut));
  
  
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
  canvasVscut->SaveAs(Form("Plots/canvasVscutId%d.pdf",idcut));
  
  
}
