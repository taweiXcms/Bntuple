void plotAcceptance(TString suffix="Pt",int optionplot=1){

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileoutput=new TFile("../Code/Results/outputBplus.root");
  
  TH1D*hPtAccNum=(TH1D*)fileoutput->Get(Form("hPtAccNumVs%s",suffix.Data()));
  TH1D*hPtAccNumReweight=(TH1D*)fileoutput->Get(Form("hPtAccNumVs%sReweight",suffix.Data()));
  TH1D*hPtAccNumLow=(TH1D*)fileoutput->Get(Form("hPtAccNumVs%sLow",suffix.Data()));
  TH1D*hPtAccNumHigh=(TH1D*)fileoutput->Get(Form("hPtAccNumVs%sHigh",suffix.Data()));
  
  TH1D*hPtAccDen=(TH1D*)fileoutput->Get(Form("hPtAccDenVs%s",suffix.Data()));
  TH1D*hPtAccDenReweight=(TH1D*)fileoutput->Get(Form("hPtAccDenVs%sReweight",suffix.Data()));
  TH1D*hPtAccDenLow=(TH1D*)fileoutput->Get(Form("hPtAccDenVs%sLow",suffix.Data()));
  TH1D*hPtAccDenHigh=(TH1D*)fileoutput->Get(Form("hPtAccDenVs%sHigh",suffix.Data()));
  
  TH1D*hAcc=(TH1D*)fileoutput->Get(Form("hAccVs%s",suffix.Data()));
  TH1D*hAccReweight=(TH1D*)fileoutput->Get(Form("hAccVs%sReweight",suffix.Data()));
  TH1D*hAccLow=(TH1D*)fileoutput->Get(Form("hAccVs%sLow",suffix.Data()));
  TH1D*hAccHigh=(TH1D*)fileoutput->Get(Form("hAccVs%sHigh",suffix.Data()));
  
  TCanvas*canvasAcc=new TCanvas("canvasAcc","canvasAcc",1000,1200);
  canvasAcc->Divide(2,2);
  
  canvasAcc->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  if(suffix=="Pt") hPtAccNum->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y") hPtAccNum->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccNum->GetYaxis()->SetTitle("Numumerator");
  hPtAccNum->SetMinimum(0.);
  if(suffix=="y") hPtAccNum->SetMaximum(5000.);
  hPtAccNum->GetXaxis()->SetTitleOffset(1.1);
  hPtAccNum->GetYaxis()->SetTitleOffset(1.85);
  hPtAccNum->SetLineWidth(2);
  hPtAccNum->SetLineColor(1);
  hPtAccNum->SetMarkerSize(0.5);
  hPtAccNum->SetMarkerStyle(21);
  hPtAccNum->SetMarkerColor(1);
  hPtAccNum->Draw();
  if(optionplot){
  hPtAccNumReweight->SetLineWidth(2);
  hPtAccNumReweight->SetLineColor(2);
  hPtAccNumReweight->SetMarkerSize(0.5);
  hPtAccNumReweight->SetMarkerStyle(21);
  hPtAccNumReweight->SetMarkerColor(2);
  hPtAccNumReweight->Draw("SAMES");
  }
  hPtAccNumLow->SetLineWidth(2);
  hPtAccNumLow->SetLineColor(3);
  hPtAccNumLow->SetMarkerSize(0.5);
  hPtAccNumLow->SetMarkerStyle(21);
  hPtAccNumLow->SetMarkerColor(3);
  hPtAccNumLow->Draw("SAMES");
  hPtAccNumHigh->SetLineWidth(2);
  hPtAccNumHigh->SetLineColor(4);
  hPtAccNumHigh->SetMarkerSize(0.5);
  hPtAccNumHigh->SetMarkerStyle(21);
  hPtAccNumHigh->SetMarkerColor(4);
  hPtAccNumHigh->Draw("SAMES");


  TLegend *legAcc=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legAcc->SetBorderSize(0);
  legAcc->SetFillStyle(0);
  legAcc->SetTextSize(0.045);

  TLegendEntry *entAcc=legAcc->AddEntry(hPtAccNum," central","P");
  entAcc->SetTextColor(1);
  if(optionplot){
  TLegendEntry *entAccReweight=legAcc->AddEntry(hPtAccNumReweight," reweight according to Data-MC diff","P");
  entAccReweight->SetTextColor(2);
  }
  TLegendEntry *entAccLow=legAcc->AddEntry(hPtAccNumLow," reweight low 40%","P");
  entAccLow->SetTextColor(3);
  TLegendEntry *entAccHigh=legAcc->AddEntry(hPtAccNumHigh," reweight up 40%","P");
  entAccHigh->SetTextColor(4);

  legAcc->Draw();
  
  canvasAcc->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  if(suffix=="Pt") hPtAccDen->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y") hPtAccDen->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccDen->GetYaxis()->SetTitle("Denumerator");
  hPtAccDen->SetMinimum(0.);
  if(suffix=="y") hPtAccDen->SetMaximum(5000.);
  hPtAccDen->GetXaxis()->SetTitleOffset(1.1);
  hPtAccDen->GetYaxis()->SetTitleOffset(1.85);
  hPtAccDen->SetLineWidth(2);
  hPtAccDen->SetLineColor(1);
  hPtAccDen->SetMarkerSize(0.5);
  hPtAccDen->SetMarkerStyle(21);
  hPtAccDen->SetMarkerColor(1);
  hPtAccDen->Draw();
  if(optionplot){
  hPtAccDenReweight->SetLineWidth(2);
  hPtAccDenReweight->SetLineColor(2);
  hPtAccDenReweight->SetMarkerSize(0.5);
  hPtAccDenReweight->SetMarkerStyle(21);
  hPtAccDenReweight->SetMarkerColor(2);
  hPtAccDenReweight->Draw("SAMES");
  }
  hPtAccDenLow->SetLineWidth(2);
  hPtAccDenLow->SetLineColor(3);
  hPtAccDenLow->SetMarkerSize(0.5);
  hPtAccDenLow->SetMarkerStyle(21);
  hPtAccDenLow->SetMarkerColor(3);
  hPtAccDenLow->Draw("SAMES");
  hPtAccDenHigh->SetLineWidth(2);
  hPtAccDenHigh->SetLineColor(4);
  hPtAccDenHigh->SetMarkerSize(0.5);
  hPtAccDenHigh->SetMarkerStyle(21);
  hPtAccDenHigh->SetMarkerColor(4);
  hPtAccDenHigh->Draw("SAMES");

  legAcc->Draw();

  canvasAcc->cd(3);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  if(suffix=="Pt") hAcc->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y") hAcc->GetXaxis()->SetTitle("y_{LAB}");
  hAcc->GetYaxis()->SetTitle("Acceptance");
  hAcc->SetMinimum(0.);
  hAcc->SetMaximum(1.5);
  hAcc->GetXaxis()->SetTitleOffset(1.1);
  hAcc->GetYaxis()->SetTitleOffset(1.85);
  hAcc->SetLineWidth(2);
  hAcc->SetLineColor(1);
  hAcc->SetMarkerSize(0.5);
  hAcc->SetMarkerStyle(21);
  hAcc->SetMarkerColor(1);
  hAcc->Draw();
  if(optionplot){
  hAccReweight->SetLineWidth(2);
  hAccReweight->SetLineColor(2);
  hAccReweight->SetMarkerSize(0.5);
  hAccReweight->SetMarkerStyle(21);
  hAccReweight->SetMarkerColor(2);
  hAccReweight->Draw("SAMES");
  }
  hAccLow->SetLineWidth(2);
  hAccLow->SetLineColor(3);
  hAccLow->SetMarkerSize(0.5);
  hAccLow->SetMarkerStyle(21);
  hAccLow->SetMarkerColor(3);
  hAccLow->Draw("SAMES");
  hAccHigh->SetLineWidth(2);
  hAccHigh->SetLineColor(4);
  hAccHigh->SetMarkerSize(0.5);
  hAccHigh->SetMarkerStyle(21);
  hAccHigh->SetMarkerColor(4);
  hAccHigh->Draw("SAMES");

  legAcc->Draw();

  canvasAcc->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  TH1D*hAccRatioReweightOverNoWeight=(TH1D*)hAccReweight->Clone("hAccRatioReweightOverNoWeight");
  hAccRatioReweightOverNoWeight->Divide(hAcc);
  TH1D*hAccRatioLowOverNoWeight=(TH1D*)hAccLow->Clone("hAccRatioLowOverNoWeight");
  hAccRatioLowOverNoWeight->Divide(hAcc);
  TH1D*hAccRatioHighOverNoWeight=(TH1D*)hAccHigh->Clone("hAccRatioHighOverNoWeight");
  hAccRatioHighOverNoWeight->Divide(hAcc);

  
  if(suffix=="Pt")hAccRatioReweightOverNoWeight->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y")hAccRatioReweightOverNoWeight->GetXaxis()->SetTitle("y_{LAB}");
  hAccRatioReweightOverNoWeight->GetYaxis()->SetTitle("Ratio Acceptance Reweight/NoWeight");
  hAccRatioLowOverNoWeight->SetMinimum(0.9);
  hAccRatioLowOverNoWeight->SetMaximum(1.1);
  hAccRatioReweightOverNoWeight->GetXaxis()->SetTitleOffset(1.1);
  hAccRatioReweightOverNoWeight->GetYaxis()->SetTitleOffset(1.85);
  
  hAccRatioLowOverNoWeight->SetLineWidth(2);
  hAccRatioLowOverNoWeight->SetLineColor(3);
  hAccRatioLowOverNoWeight->SetMarkerSize(0.5);
  hAccRatioLowOverNoWeight->SetMarkerStyle(21);
  hAccRatioLowOverNoWeight->SetMarkerColor(3);
  hAccRatioLowOverNoWeight->Draw("same");

  hAccRatioHighOverNoWeight->SetLineWidth(2);
  hAccRatioHighOverNoWeight->SetLineColor(4);
  hAccRatioHighOverNoWeight->SetMarkerSize(0.5);
  hAccRatioHighOverNoWeight->SetMarkerStyle(21);
  hAccRatioHighOverNoWeight->SetMarkerColor(4);
  hAccRatioHighOverNoWeight->Draw("same");
  
  if(optionplot){
  hAccRatioReweightOverNoWeight->SetLineWidth(2);
  hAccRatioReweightOverNoWeight->SetLineColor(2);
  hAccRatioReweightOverNoWeight->SetMarkerSize(0.5);
  hAccRatioReweightOverNoWeight->SetMarkerStyle(21);
  hAccRatioReweightOverNoWeight->SetMarkerColor(2);
  hAccRatioReweightOverNoWeight->Draw("same");
  }


  for (int i=1;i<=40;i++){
    hAccRatioReweightOverNoWeight->SetBinError(i,0.);
    hAccRatioLowOverNoWeight->SetBinError(i,0.);
    hAccRatioHighOverNoWeight->SetBinError(i,0.);
  
  }
  
  TLegend *legRatioAcc=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legRatioAcc->SetBorderSize(0);
  legRatioAcc->SetFillStyle(0);
  legRatioAcc->SetTextSize(0.045);
  if(optionplot){
  TLegendEntry *entRatioReweightAcc=legRatioAcc->AddEntry(hAccRatioReweightOverNoWeight," reweight according to Data-MC diff","P");
  entRatioReweightAcc->SetTextColor(2);
  }
  TLegendEntry *entRatioLowAcc=legRatioAcc->AddEntry(hAccRatioLowOverNoWeight," reweight up 40%","P");
  entRatioLowAcc->SetTextColor(3);
  TLegendEntry *entRatioHighAcc=legRatioAcc->AddEntry(hAccRatioHighOverNoWeight," reweight down 40%","P");
  entRatioHighAcc->SetTextColor(4);

  legRatioAcc->Draw();
  canvasAcc->SaveAs(Form("Plots/canvasAccVs%s.eps",suffix.Data()));

}