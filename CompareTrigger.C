void CompareTrigger(){

  double DoubleRatioError(double,double);


  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileOldTrigger_Bplus=new TFile("../Bntuple/ResultsBplus/SigmaBplus.root");
  TFile*fileNewTrigger_Bplus=new TFile("../BntupleDoubleMuon/ResultsBplus/SigmaBplus.root");
  TFile*fileOldTrigger_Bzero=new TFile("../Bntuple/ResultsBzero/SigmaBzero.root");
  TFile*fileNewTrigger_Bzero=new TFile("../BntupleDoubleMuon/ResultsBzero/SigmaBzero.root");
  TFile*fileOldTrigger_Bs=new TFile("../Bntuple/ResultsBs/SigmaBs.root");
  TFile*fileNewTrigger_Bs=new TFile("../BntupleDoubleMuon/ResultsBs/SigmaBs.root");
 
  TH1F*hOldTrigger_Bplus=(TH1F*)fileOldTrigger_Bplus->Get("hPtCor");
  TH1F*hOldTrigger_Bzero=(TH1F*)fileOldTrigger_Bzero->Get("hPtCor");
  TH1F*hOldTrigger_Bs=(TH1F*)fileOldTrigger_Bs->Get("hPtCor");
  
  TH1F*hNewTrigger_Bplus=(TH1F*)fileNewTrigger_Bplus->Get("hPtCor");
  TH1F*hNewTrigger_Bzero=(TH1F*)fileNewTrigger_Bzero->Get("hPtCor");
  TH1F*hNewTrigger_Bs=(TH1F*)fileNewTrigger_Bs->Get("hPtCor");
   
    
  double relerr_numerator_Bplus=0.;
  double relerr_denumerator_Bplus=0.;
  double ratio_Bplus=0.;
  double errratio_Bplus=0.;
  
  const int nBins_Bplus = 5;
  double ptBins_Bplus[nBins_Bplus+1] = {10,15,20,25,30,60};
  TH1D *hRatioDoubleOverSingle_Bplus = new TH1D("hRatioDoubleOverSingle_Bplus","",nBins_Bplus,ptBins_Bplus);
  
  for (int i=1;i<=5;i++){
  
    relerr_numerator_Bplus=hNewTrigger_Bplus->GetBinError(i)/hNewTrigger_Bplus->GetBinContent(i);
    relerr_denumerator_Bplus=hOldTrigger_Bplus->GetBinError(i)/hOldTrigger_Bplus->GetBinContent(i);

    ratio_Bplus=hNewTrigger_Bplus->GetBinContent(i)/hOldTrigger_Bplus->GetBinContent(i);
    errratio_Bplus=TMath::Sqrt(relerr_numerator_Bplus*relerr_numerator_Bplus+relerr_denumerator_Bplus*relerr_denumerator_Bplus)*ratio_Bplus;
    hRatioDoubleOverSingle_Bplus->SetBinContent(i,ratio_Bplus);
    hRatioDoubleOverSingle_Bplus->SetBinError(i,errratio_Bplus);

  }
  
  double relerr_numerator_Bzero=0.;
  double relerr_denumerator_Bzero=0.;
  double ratio_Bzero=0.;
  double errratio_Bzero=0.;
  
  const int nBins_Bzero = 3;
  double ptBins_Bzero[nBins_Bzero+1] = {10,15,20,60};
  TH1D *hRatioDoubleOverSingle_Bzero = new TH1D("hRatioDoubleOverSingle_Bzero","",nBins_Bzero,ptBins_Bzero);
  
  for (int i=1;i<=5;i++){
  
    relerr_numerator_Bzero=hNewTrigger_Bzero->GetBinError(i)/hNewTrigger_Bzero->GetBinContent(i);
    relerr_denumerator_Bzero=hOldTrigger_Bzero->GetBinError(i)/hOldTrigger_Bzero->GetBinContent(i);

    ratio_Bzero=hNewTrigger_Bzero->GetBinContent(i)/hOldTrigger_Bzero->GetBinContent(i);
    errratio_Bzero=TMath::Sqrt(relerr_numerator_Bzero*relerr_numerator_Bzero+relerr_denumerator_Bzero*relerr_denumerator_Bzero)*ratio_Bzero;
    hRatioDoubleOverSingle_Bzero->SetBinContent(i,ratio_Bzero);
    hRatioDoubleOverSingle_Bzero->SetBinError(i,errratio_Bzero);

  }
  
  double relerr_numerator_Bs=0.;
  double relerr_denumerator_Bs=0.;
  double ratio_Bs=0.;
  double errratio_Bs=0.;

  
  const int nBins_Bs = 1;
  double ptBins_Bs[nBins_Bs+1] = {10,60};
  TH1D *hRatioDoubleOverSingle_Bs = new TH1D("hRatioDoubleOverSingle_Bs","",nBins_Bs,ptBins_Bs);
  
  for (int i=1;i<=5;i++){
  
    relerr_numerator_Bs=hNewTrigger_Bs->GetBinError(i)/hNewTrigger_Bs->GetBinContent(i);
    relerr_denumerator_Bs=hOldTrigger_Bs->GetBinError(i)/hOldTrigger_Bs->GetBinContent(i);

    ratio_Bs=hNewTrigger_Bs->GetBinContent(i)/hOldTrigger_Bs->GetBinContent(i);
    errratio_Bs=TMath::Sqrt(relerr_numerator_Bs*relerr_numerator_Bs+relerr_denumerator_Bs*relerr_denumerator_Bs)*ratio_Bs;
    hRatioDoubleOverSingle_Bs->SetBinContent(i,ratio_Bs);
    hRatioDoubleOverSingle_Bs->SetBinError(i,errratio_Bs);

  }




  TCanvas *canvas=new TCanvas("canvas","canvas",1500,500);
  canvas->Divide(3,1);
  canvas->cd(1);  
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitle("B^{+} p_{t}");
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitle("Ratio Double/Single B^{+}");
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleOffset(1.);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleOffset(1.1);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetLabelSize(0.035);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetLabelSize(0.035);  
  hRatioDoubleOverSingle_Bplus->SetMinimum(0.);
  hRatioDoubleOverSingle_Bplus->SetMaximum(2.);
  hRatioDoubleOverSingle_Bplus->SetLineColor(1);
  hRatioDoubleOverSingle_Bplus->SetLineWidth(2);
  hRatioDoubleOverSingle_Bplus->Draw();

  canvas->cd(2);  
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitle("B^{0} p_{t}");
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitle("Ratio Double/Single B^{0}");
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleOffset(1.);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleOffset(1.1);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetLabelSize(0.035);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetLabelSize(0.035);  
  hRatioDoubleOverSingle_Bzero->SetMinimum(0.);
  hRatioDoubleOverSingle_Bzero->SetMaximum(2.);
  hRatioDoubleOverSingle_Bzero->SetLineColor(1);
  hRatioDoubleOverSingle_Bzero->SetLineWidth(2);
  hRatioDoubleOverSingle_Bzero->Draw();


  canvas->cd(3);  
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitle("B_{s} p_{t}");
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitle("Ratio Double/Single B_{s}");
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleOffset(1.);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleOffset(1.1);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleSize(0.04);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetLabelSize(0.035);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetLabelSize(0.035);  
  hRatioDoubleOverSingle_Bs->SetMinimum(0.);
  hRatioDoubleOverSingle_Bs->SetMaximum(2.);
  hRatioDoubleOverSingle_Bs->SetLineColor(1);
  hRatioDoubleOverSingle_Bs->SetLineWidth(2);
  hRatioDoubleOverSingle_Bs->Draw();


  canvas->SaveAs("Plots/canvasComparisonTriggerCorr.eps");
  
  
}


double DoubleRatioError(double Num=-1,double Den=-1){

  double ratio,errratio;

  ratio=Num/Den;
  errratio=TMath::Sqrt(ratio*(1-ratio)/Den);
  return errratio;
}


