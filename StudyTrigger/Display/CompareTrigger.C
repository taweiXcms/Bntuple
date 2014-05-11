void CompareTrigger(){

  double myrelerrratioyield_Bplus[5]={0.073,0.097,0.144,0.197,0.175};
  double myrelerrratioyield_Bzero[3]={0.127,0.173,0.150};
  double myrelerrratioyield_Bs[1]={0.168};


  double DoubleRatioError(double,double);


  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileOldTrigger_Bplus=new TFile("../InputSingleDouble/SigmaBplusSingle.root");
  TFile*fileNewTrigger_Bplus=new TFile("../InputSingleDouble/SigmaBplusDouble.root");
  TFile*fileOldTrigger_Bzero=new TFile("../InputSingleDouble/SigmaBzeroSingle.root");
  TFile*fileNewTrigger_Bzero=new TFile("../InputSingleDouble/SigmaBzeroDouble.root");
  TFile*fileOldTrigger_Bs=new TFile("../InputSingleDouble/SigmaBsSingle.root");
  TFile*fileNewTrigger_Bs=new TFile("../InputSingleDouble/SigmaBsDouble.root");
 
  TH1F*hOldTrigger_Bplus=(TH1F*)fileOldTrigger_Bplus->Get("hPtCor");
  TH1F*hOldTrigger_Bzero=(TH1F*)fileOldTrigger_Bzero->Get("hPtCor");
  TH1F*hOldTrigger_Bs=(TH1F*)fileOldTrigger_Bs->Get("hPtCor");
  
  TH1F*hNewTrigger_Bplus=(TH1F*)fileNewTrigger_Bplus->Get("hPtCor");
  TH1F*hNewTrigger_Bzero=(TH1F*)fileNewTrigger_Bzero->Get("hPtCor");
  TH1F*hNewTrigger_Bs=(TH1F*)fileNewTrigger_Bs->Get("hPtCor");
   
  TH1F*hYieldOldTrigger_Bplus=(TH1F*)fileOldTrigger_Bplus->Get("hPt");
  TH1F*hYieldOldTrigger_Bzero=(TH1F*)fileOldTrigger_Bzero->Get("hPt");
  TH1F*hYieldOldTrigger_Bs=(TH1F*)fileOldTrigger_Bs->Get("hPt");
  
  TH1F*hYieldNewTrigger_Bplus=(TH1F*)fileNewTrigger_Bplus->Get("hPt");
  TH1F*hYieldNewTrigger_Bzero=(TH1F*)fileNewTrigger_Bzero->Get("hPt");
  TH1F*hYieldNewTrigger_Bs=(TH1F*)fileNewTrigger_Bs->Get("hPt");

  double corryieldnew_Bplus=0.;
  double corryieldold_Bplus=0.;
  double ratiocorryield_Bplus=0.;
  double errratiocorryield_Bplus=0.;
    
  double yieldnew_Bplus=0.;
  double yieldold_Bplus=0.;
  double ratioyield_Bplus=0.;
  double errratioyield_Bplus=0.;
  double relerrratioyield_Bplus=0.;
    
  const int nBins_Bplus = 5;
  double ptBins_Bplus[nBins_Bplus+1] = {10.,15.,20.,25.,30.,60.};
  double ptBinswidth[nBins_Bplus] = {5.,5.,5.,5.,30.};
  
  TH1D *hRatioDoubleOverSingle_Bplus = new TH1D("hRatioDoubleOverSingle_Bplus","",nBins_Bplus,ptBins_Bplus);
  TH1D *hRatioYieldDoubleOverSingle_Bplus = new TH1D("hRatioYieldDoubleOverSingle_Bplus","",nBins_Bplus,ptBins_Bplus);
  
  for (int i=1;i<=5;i++){

    corryieldnew_Bplus=hNewTrigger_Bplus->GetBinContent(i);
    corryieldold_Bplus=hOldTrigger_Bplus->GetBinContent(i);
    
    yieldnew_Bplus=hYieldNewTrigger_Bplus->GetBinContent(i);
    yieldold_Bplus=hYieldOldTrigger_Bplus->GetBinContent(i);
    
    ratiocorryield_Bplus=corryieldnew_Bplus/corryieldold_Bplus;
    ratioyield_Bplus=yieldnew_Bplus/yieldold_Bplus;
        
    hRatioDoubleOverSingle_Bplus->SetBinContent(i,ratiocorryield_Bplus);
    hRatioYieldDoubleOverSingle_Bplus->SetBinContent(i,ratioyield_Bplus);
    
    errratioyield_Bplus=myrelerrratioyield_Bplus[i-1]*ratioyield_Bplus;
    errratiocorryield_Bplus=myrelerrratioyield_Bplus[i-1]*ratiocorryield_Bplus;
    hRatioYieldDoubleOverSingle_Bplus->SetBinError(i,errratioyield_Bplus);    
    hRatioDoubleOverSingle_Bplus->SetBinError(i,errratiocorryield_Bplus);
      
  }

  double corryieldnew_Bzero=0.;
  double corryieldold_Bzero=0.;
  double ratiocorryield_Bzero=0.;
  double errratiocorryield_Bzero=0.;
    
  double yieldnew_Bzero=0.;
  double yieldold_Bzero=0.;
  double ratioyield_Bzero=0.;
  double errratioyield_Bzero=0.;
  double relerrratioyield_Bzero=0.;
    
  const int nBins_Bzero = 3;
  double ptBins_Bzero[nBins_Bzero+1] = {10.,15.,20.,60.};
  double ptBinswidth[nBins_Bzero] = {5.,5.,40.};
  
  TH1D *hRatioDoubleOverSingle_Bzero = new TH1D("hRatioDoubleOverSingle_Bzero","",nBins_Bzero,ptBins_Bzero);
  TH1D *hRatioYieldDoubleOverSingle_Bzero = new TH1D("hRatioYieldDoubleOverSingle_zero","",nBins_Bzero,ptBins_Bzero);

    
  
  for (int i=1;i<=3;i++){

    corryieldnew_Bzero=hNewTrigger_Bzero->GetBinContent(i);
    corryieldold_Bzero=hOldTrigger_Bzero->GetBinContent(i);
    
    yieldnew_Bzero=hYieldNewTrigger_Bzero->GetBinContent(i);
    yieldold_Bzero=hYieldOldTrigger_Bzero->GetBinContent(i);
    
    ratiocorryield_Bzero=corryieldnew_Bzero/corryieldold_Bzero;
    ratioyield_Bzero=yieldnew_Bzero/yieldold_Bzero;
        
    hRatioDoubleOverSingle_Bzero->SetBinContent(i,ratiocorryield_Bzero);
    hRatioYieldDoubleOverSingle_Bzero->SetBinContent(i,ratioyield_Bzero);
    
    errratioyield_Bzero=myrelerrratioyield_Bzero[i-1]*ratioyield_Bzero;
    errratiocorryield_Bzero=myrelerrratioyield_Bzero[i-1]*ratiocorryield_Bzero;
    hRatioYieldDoubleOverSingle_Bzero->SetBinError(i,errratioyield_Bzero);    
    hRatioDoubleOverSingle_Bzero->SetBinError(i,errratiocorryield_Bzero);
      
  }
  
  double corryieldnew_Bs=0.;
  double corryieldold_Bs=0.;
  double ratiocorryield_Bs=0.;
  double errratiocorryield_Bs=0.;
    
  double yieldnew_Bs=0.;
  double yieldold_Bs=0.;
  double ratioyield_Bs=0.;
  double errratioyield_Bs=0.;
  double relerrratioyield_Bs=0.;
    
  const int nBins_Bs = 1;
  double ptBins_Bs[nBins_Bs+1] = {10.,60.};
  double ptBinswidth[nBins_Bs] = {50.};
  TH1D *hRatioDoubleOverSingle_Bs = new TH1D("hRatioDoubleOverSingle_Bs","",nBins_Bs,ptBins_Bs);
  TH1D *hRatioYieldDoubleOverSingle_Bs = new TH1D("hRatioYieldDoubleOverSingle_Bs","",nBins_Bs,ptBins_Bs);

    
  for (int i=1;i<=1;i++){

    corryieldnew_Bs=hNewTrigger_Bs->GetBinContent(i);
    corryieldold_Bs=hOldTrigger_Bs->GetBinContent(i);
    
    yieldnew_Bs=hYieldNewTrigger_Bs->GetBinContent(i);
    yieldold_Bs=hYieldOldTrigger_Bs->GetBinContent(i);
    
    ratiocorryield_Bs=corryieldnew_Bs/corryieldold_Bs;
    ratioyield_Bs=yieldnew_Bs/yieldold_Bs;
        
    hRatioDoubleOverSingle_Bs->SetBinContent(i,ratiocorryield_Bs);
    hRatioYieldDoubleOverSingle_Bs->SetBinContent(i,ratioyield_Bs);
    
    errratioyield_Bs=myrelerrratioyield_Bs[i-1]*ratioyield_Bs;
    errratiocorryield_Bs=myrelerrratioyield_Bs[i-1]*ratiocorryield_Bs;
    hRatioYieldDoubleOverSingle_Bs->SetBinError(i,errratioyield_Bs);    
    hRatioDoubleOverSingle_Bs->SetBinError(i,errratiocorryield_Bs);
      
  }

  


  TCanvas *canvasCorrected=new TCanvas("canvasCorrected","canvasCorrected",1200,400);
  canvasCorrected->Divide(3,1);
  canvasCorrected->cd(1);  
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitle("B^{+} p_{T}");
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitle("DoubleMuOpen / SingleMu3 B^{+}");
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleOffset(1.0);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleOffset(1.05);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bplus->GetXaxis()->SetLabelSize(0.037);
  hRatioDoubleOverSingle_Bplus->GetYaxis()->SetLabelSize(0.037);  
  hRatioDoubleOverSingle_Bplus->SetMinimum(0.);
  hRatioDoubleOverSingle_Bplus->SetMaximum(2.);
  hRatioDoubleOverSingle_Bplus->SetMarkerSize(1.2);
  hRatioDoubleOverSingle_Bplus->SetLineColor(1);
  hRatioDoubleOverSingle_Bplus->SetLineWidth(2);
  hRatioDoubleOverSingle_Bplus->SetMarkerStyle(21);
  hRatioDoubleOverSingle_Bplus->SetMarkerSize(1);
  hRatioDoubleOverSingle_Bplus->Draw("pe");
  hRatioYieldDoubleOverSingle_Bplus->SetMarkerSize(1.2);
  hRatioYieldDoubleOverSingle_Bplus->SetMinimum(0.);
  hRatioYieldDoubleOverSingle_Bplus->SetMaximum(2.);
  hRatioYieldDoubleOverSingle_Bplus->SetLineColor(2);
  hRatioYieldDoubleOverSingle_Bplus->SetLineWidth(2);  
  hRatioYieldDoubleOverSingle_Bplus->SetMarkerStyle(20);
  hRatioYieldDoubleOverSingle_Bplus->SetMarkerColor(2);
  hRatioYieldDoubleOverSingle_Bplus->SetMarkerSize(1);
  hRatioYieldDoubleOverSingle_Bplus->Draw("pesame");
  
  TLegend *leg_Bplus = new TLegend(0.2295951,0.7284292,0.7899737,0.8570061,NULL,"brNDC");
  leg_Bplus->AddEntry(hRatioYieldDoubleOverSingle_Bplus,"Yields uncorrected","pl");
  leg_Bplus->AddEntry(hRatioDoubleOverSingle_Bplus,"dN/dp_{T} fully corrected","pl");
  leg_Bplus->SetBorderSize(0);
  leg_Bplus->SetFillStyle(0);
  leg_Bplus->SetTextSize(0.05);
  leg_Bplus->SetTextFont(42);
  leg_Bplus->Draw();



  canvasCorrected->cd(2);  
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitle("B^{0} p_{T}");
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitle("DoubleMuOpen / SingleMu3 B^{0}");
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleOffset(1.0);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleOffset(1.05);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bzero->GetXaxis()->SetLabelSize(0.037);
  hRatioDoubleOverSingle_Bzero->GetYaxis()->SetLabelSize(0.037);  
  hRatioDoubleOverSingle_Bzero->SetMinimum(0.);
  hRatioDoubleOverSingle_Bzero->SetMaximum(2.);
  hRatioDoubleOverSingle_Bzero->SetMarkerSize(1.2);
  hRatioDoubleOverSingle_Bzero->SetLineColor(1);
  hRatioDoubleOverSingle_Bzero->SetLineWidth(2);
  hRatioDoubleOverSingle_Bzero->SetMarkerStyle(21);
  hRatioDoubleOverSingle_Bzero->SetMarkerSize(1);
  hRatioDoubleOverSingle_Bzero->Draw("pe");
  hRatioYieldDoubleOverSingle_Bzero->SetMarkerSize(1.2);
  hRatioYieldDoubleOverSingle_Bzero->SetMinimum(0.);
  hRatioYieldDoubleOverSingle_Bzero->SetMaximum(2.);
  hRatioYieldDoubleOverSingle_Bzero->SetLineColor(2);
  hRatioYieldDoubleOverSingle_Bzero->SetLineWidth(2);  
  hRatioYieldDoubleOverSingle_Bzero->SetMarkerStyle(20);
  hRatioYieldDoubleOverSingle_Bzero->SetMarkerColor(2);
  hRatioYieldDoubleOverSingle_Bzero->SetMarkerSize(1);
  hRatioYieldDoubleOverSingle_Bzero->Draw("pesame");
  
  TLegend *leg_Bzero = new TLegend(0.2295951,0.7284292,0.7899737,0.8570061,NULL,"brNDC");
  leg_Bzero->AddEntry(hRatioYieldDoubleOverSingle_Bzero,"Yields uncorrected","pl");
  leg_Bzero->AddEntry(hRatioDoubleOverSingle_Bzero,"dN/dp_{T} fully corrected","pl");
  leg_Bzero->SetBorderSize(0);
  leg_Bzero->SetFillStyle(0);
  leg_Bzero->SetTextSize(0.05);
  leg_Bzero->SetTextFont(42);
  leg_Bzero->Draw();


  

  canvasCorrected->cd(3);  
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitle("B_{s} p_{T}");
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitle("DoubleMuOpen / SingleMu3 B_{s}");
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleOffset(1.0);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleOffset(0.9);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleSize(0.045);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetTitleFont(42);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetLabelFont(42);
  hRatioDoubleOverSingle_Bs->GetXaxis()->SetLabelSize(0.037);
  hRatioDoubleOverSingle_Bs->GetYaxis()->SetLabelSize(0.037);  
  hRatioDoubleOverSingle_Bs->SetMinimum(0.);
  hRatioDoubleOverSingle_Bs->SetMaximum(2.);
  hRatioDoubleOverSingle_Bs->SetMarkerSize(1.2);
  hRatioDoubleOverSingle_Bs->SetLineColor(1);
  hRatioDoubleOverSingle_Bs->SetLineWidth(2);
  hRatioDoubleOverSingle_Bs->SetMarkerStyle(21);
  hRatioDoubleOverSingle_Bs->SetMarkerSize(1);
  hRatioDoubleOverSingle_Bs->Draw("pe");
  hRatioYieldDoubleOverSingle_Bs->SetMarkerSize(1.2);
  hRatioYieldDoubleOverSingle_Bs->SetMinimum(0.);
  hRatioYieldDoubleOverSingle_Bs->SetMaximum(2.);
  hRatioYieldDoubleOverSingle_Bs->SetLineColor(2);
  hRatioYieldDoubleOverSingle_Bs->SetLineWidth(2);  
  hRatioYieldDoubleOverSingle_Bs->SetMarkerStyle(20);
  hRatioYieldDoubleOverSingle_Bs->SetMarkerColor(2);
  hRatioYieldDoubleOverSingle_Bs->SetMarkerSize(1);
  hRatioYieldDoubleOverSingle_Bs->Draw("pesame");
  
  TLegend *leg_Bs = new TLegend(0.2295951,0.7284292,0.7899737,0.8570061,NULL,"brNDC");
  leg_Bs->AddEntry(hRatioYieldDoubleOverSingle_Bs,"Yields uncorrected","pl");
  leg_Bs->AddEntry(hRatioDoubleOverSingle_Bs,"dN/dp_{T} fully corrected","pl");
  leg_Bs->SetBorderSize(0);
  leg_Bs->SetFillStyle(0);
  leg_Bs->SetTextSize(0.05);
  leg_Bs->SetTextFont(42);
  leg_Bs->Draw();



  canvasCorrected->SaveAs("Plots/canvasComparisonTriggerCorr.eps");
}


double DoubleRatioError(double Num=-1,double Den=-1){

  double ratio,errratio;

  ratio=Num/Den;
  errratio=TMath::Sqrt(ratio*(1-ratio)/Den);
  return errratio;
}


