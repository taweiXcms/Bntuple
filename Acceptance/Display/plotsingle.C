void plotsingle(TString suffix="Pt"){

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileoutput=new TFile("../Code/Results/outputBplus.root");
  
  TH1D*hPtAccNum=(TH1D*)fileoutput->Get(Form("hPtAccNumVs%s",suffix.Data()));
  TH1D*hPtAccDen=(TH1D*)fileoutput->Get(Form("hPtAccDenVs%s",suffix.Data()));
  TH1D*hAcc=(TH1D*)fileoutput->Get(Form("hAccVs%s",suffix.Data()));
  
  TCanvas*canvasAcc=new TCanvas("canvasAcc","canvasAcc",1200,450);
  canvasAcc->Divide(3,1);
  
  canvasAcc->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  if(suffix=="Pt") hPtAccNum->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y") hPtAccNum->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccNum->GetYaxis()->SetTitle("Numumerator");
  hPtAccNum->SetMinimum(0.);
  if(suffix=="y") hPtAccNum->SetMaximum(6000.);
  hPtAccNum->GetXaxis()->SetTitleOffset(1.1);
  hPtAccNum->GetYaxis()->SetTitleOffset(1.85);
  hPtAccNum->SetLineWidth(2);
  hPtAccNum->SetLineColor(1);
  hPtAccNum->SetMarkerSize(0.5);
  hPtAccNum->SetMarkerStyle(21);
  hPtAccNum->SetMarkerColor(1);
  hPtAccNum->Draw();

  canvasAcc->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  if(suffix=="Pt") hPtAccDen->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(suffix=="y") hPtAccDen->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccDen->GetYaxis()->SetTitle("Denumerator");
  hPtAccDen->SetMinimum(0.);
  if(suffix=="y") hPtAccDen->SetMaximum(10000.);
  hPtAccDen->GetXaxis()->SetTitleOffset(1.1);
  hPtAccDen->GetYaxis()->SetTitleOffset(1.85);
  hPtAccDen->SetLineWidth(2);
  hPtAccDen->SetLineColor(1);
  hPtAccDen->SetMarkerSize(0.5);
  hPtAccDen->SetMarkerStyle(21);
  hPtAccDen->SetMarkerColor(1);
  hPtAccDen->Draw();

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

  canvasAcc->SaveAs(Form("Plots/canvasAccVs%s_single.eps",suffix.Data()));

}