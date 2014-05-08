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
  
  for (int i=1;i<=5;i++){

    corryieldnew_Bplus=hNewTrigger_Bplus->GetBinContent(i);
    corryieldold_Bplus=hOldTrigger_Bplus->GetBinContent(i);
    yieldnew_Bplus=hYieldNewTrigger_Bplus->GetBinContent(i);
    yieldold_Bplus=hYieldOldTrigger_Bplus->GetBinContent(i);
    ratiocorryield_Bplus=corryieldnew_Bplus/corryieldold_Bplus;
    ratioyield_Bplus=yieldnew_Bplus/yieldold_Bplus;
    
    //cout<<"yieldnew_Bplus"<<yieldnew_Bplus*ptBinswidth[i-1]<<"yieldold_Bplus"<<yieldold_Bplus*ptBinswidth[i-1]<<endl;
    
    hRatioDoubleOverSingle_Bplus->SetBinContent(i,ratiocorryield_Bplus);
    errratioyield_Bplus=DoubleRatioError(yieldnew_Bplus*ptBinswidth[i-1],yieldold_Bplus*ptBinswidth[i-1]);
    if(i==4) errratioyield_Bplus=ratioyield_Bplus*0.05;
    relerrratioyield_Bplus=errratioyield_Bplus/ratioyield_Bplus;
    errratiocorryield_Bplus=relerrratioyield_Bplus*ratiocorryield_Bplus;
    hRatioDoubleOverSingle_Bplus->SetBinContent(i,ratiocorryield_Bplus);
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
  
  for (int i=1;i<=3;i++){

    corryieldnew_Bzero=hNewTrigger_Bzero->GetBinContent(i);
    corryieldold_Bzero=hOldTrigger_Bzero->GetBinContent(i);
    yieldnew_Bzero=hYieldNewTrigger_Bzero->GetBinContent(i);
    yieldold_Bzero=hYieldOldTrigger_Bzero->GetBinContent(i);
    ratiocorryield_Bzero=corryieldnew_Bzero/corryieldold_Bzero;
    ratioyield_Bzero=yieldnew_Bzero/yieldold_Bzero;
    
    //cout<<"yieldnew_Bzero"<<yieldnew_Bzero*ptBinswidth[i-1]<<"yieldold_Bzero"<<yieldold_Bzero*ptBinswidth[i-1]<<endl;
    
    hRatioDoubleOverSingle_Bzero->SetBinContent(i,ratiocorryield_Bzero);
    errratioyield_Bzero=DoubleRatioError(yieldnew_Bzero*ptBinswidth[i-1],yieldold_Bzero*ptBinswidth[i-1]);
    relerrratioyield_Bzero=errratioyield_Bzero/ratioyield_Bzero;
    errratiocorryield_Bzero=relerrratioyield_Bzero*ratiocorryield_Bzero;
    hRatioDoubleOverSingle_Bzero->SetBinContent(i,ratiocorryield_Bzero);
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
  
  for (int i=1;i<=5;i++){

    corryieldnew_Bs=hNewTrigger_Bs->GetBinContent(i);
    corryieldold_Bs=hOldTrigger_Bs->GetBinContent(i);
    yieldnew_Bs=hYieldNewTrigger_Bs->GetBinContent(i);
    yieldold_Bs=hYieldOldTrigger_Bs->GetBinContent(i);
    ratiocorryield_Bs=corryieldnew_Bs/corryieldold_Bs;
    ratioyield_Bs=yieldnew_Bs/yieldold_Bs;
    
    //cout<<"yieldnew_Bs"<<yieldnew_Bs*ptBinswidth[i-1]<<"yieldold_Bs"<<yieldold_Bs*ptBinswidth[i-1]<<endl;
    
    hRatioDoubleOverSingle_Bs->SetBinContent(i,ratiocorryield_Bs);
    errratioyield_Bs=DoubleRatioError(yieldnew_Bs*ptBinswidth[i-1],yieldold_Bs*ptBinswidth[i-1]);
    relerrratioyield_Bs=errratioyield_Bs/ratioyield_Bs;
    errratiocorryield_Bs=relerrratioyield_Bs*ratiocorryield_Bs;
    hRatioDoubleOverSingle_Bs->SetBinContent(i,ratiocorryield_Bs);
    hRatioDoubleOverSingle_Bs->SetBinError(i,errratiocorryield_Bs);
    
      
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


