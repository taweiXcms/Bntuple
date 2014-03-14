void CompareSyst(){

   gROOT->SetStyle("Plain");	
   gStyle->SetOptStat(0);
   gStyle->SetOptStat(0000);
   gStyle->SetPalette(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetFrameFillColor(0);
   gStyle->SetOptTitle(0);



 TFile*file0=new TFile("Results/SigmaBplus0.root");
 TFile*file1=new TFile("Results/SigmaBplus1.root");
 TFile*file2=new TFile("Results/SigmaBplus2.root");
 TFile*file3=new TFile("Results/SigmaBplus3.root");
 TFile*file4=new TFile("Results/SigmaBplus4.root");
 TFile*file5=new TFile("Results/SigmaBplus5.root");
 TFile*file6=new TFile("Results/SigmaBplus6.root");
 TFile*file7=new TFile("Results/SigmaBplus7.root");
 TFile*file8=new TFile("Results/SigmaBplus8.root");
 TFile*file9=new TFile("Results/SigmaBplus9.root");
 
 
 TH1F*hSigma0=(TH1F*)file0->Get("hPtSigma");
 TH1F*hSigma1=(TH1F*)file1->Get("hPtSigma");
 TH1F*hSigma2=(TH1F*)file2->Get("hPtSigma");
 TH1F*hSigma3=(TH1F*)file3->Get("hPtSigma");
 TH1F*hSigma4=(TH1F*)file4->Get("hPtSigma");
 TH1F*hSigma5=(TH1F*)file5->Get("hPtSigma");
 TH1F*hSigma6=(TH1F*)file6->Get("hPtSigma");
 TH1F*hSigma7=(TH1F*)file7->Get("hPtSigma");
 TH1F*hSigma8=(TH1F*)file8->Get("hPtSigma");
 TH1F*hSigma9=(TH1F*)file9->Get("hPtSigma");
 
 hSigma0->SetName("hSigma0");
 hSigma1->SetName("hSigma1");
 hSigma2->SetName("hSigma2");
 hSigma3->SetName("hSigma3");
 hSigma4->SetName("hSigma4");
 hSigma5->SetName("hSigma5");
 hSigma6->SetName("hSigma6");
 hSigma7->SetName("hSigma7");
 hSigma8->SetName("hSigma8");
 hSigma9->SetName("hSigma9");
 
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
 
 TH1F*hSigmaDen=(TH1F*)file5->Get("hPtSigma");
 
 
 hSigma0->Sumw2();
 hSigma1->Sumw2();
 hSigma2->Sumw2();
 hSigma3->Sumw2();
 hSigma4->Sumw2();
 hSigma5->Sumw2();
 hSigma6->Sumw2();
 hSigma7->Sumw2();
 hSigma8->Sumw2();
 hSigma9->Sumw2();
 hSigmaBis0->Sumw2();
 hSigmaBis1->Sumw2();
 hSigmaBis2->Sumw2();
 hSigmaBis3->Sumw2();
 hSigmaBis4->Sumw2();
 hSigmaBis5->Sumw2();
 hSigmaBis6->Sumw2();
 hSigmaBis7->Sumw2();
 hSigmaBis8->Sumw2();
 hSigmaBis9->Sumw2();
 hSigmaDen->Sumw2();
 
 hSigma0->Divide(hSigmaDen);
 hSigma1->Divide(hSigmaDen);
 hSigma2->Divide(hSigmaDen);
 hSigma3->Divide(hSigmaDen);
 hSigma4->Divide(hSigmaDen);
 hSigma5->Divide(hSigmaDen);
 hSigma6->Divide(hSigmaDen);
 hSigma7->Divide(hSigmaDen);
 hSigma8->Divide(hSigmaDen);
 hSigma9->Divide(hSigmaDen);

  TCanvas *canvas=new TCanvas("canvas","canvas",600,500);
  canvas->cd();
  hSigma0->GetXaxis()->SetTitle("p_{t} (GeV/c)");
  hSigma0->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hSigma0->GetXaxis()->SetTitleOffset(1.);
  hSigma0->GetYaxis()->SetTitleOffset(1.1);
  hSigma0->GetXaxis()->SetTitleSize(0.04);
  hSigma0->GetYaxis()->SetTitleSize(0.04);
  hSigma0->GetXaxis()->SetTitleFont(42);
  hSigma0->GetYaxis()->SetTitleFont(42);
  hSigma0->GetXaxis()->SetLabelFont(42);
  hSigma0->GetYaxis()->SetLabelFont(42);
  hSigma0->GetXaxis()->SetLabelSize(0.035);
  hSigma0->GetYaxis()->SetLabelSize(0.035);  
  hSigma0->SetMinimum(0.);
  hSigma0->SetMaximum(2.);
    

hSigma0->Draw();
hSigma1->Draw("same");
hSigma2->Draw("same");
hSigma3->Draw("same");
hSigma4->Draw("same");
hSigma5->Draw("same");
hSigma6->Draw("same");
hSigma7->Draw("same");
hSigma8->Draw("same");
hSigma9->Draw("same");


  TLatex * tlatexBplus=new TLatex(0.1,0.85,"All cuts as default, varying |trk1Dxy/Err| within 1.4-2.4");
  tlatexBplus->SetNDC();
  tlatexBplus->SetTextColor(1);
  tlatexBplus->SetTextFont(42);
  tlatexBplus->SetTextSize(0.04);
  tlatexBplus->Draw();
  
  TLatex * tlatexBplus=new TLatex(0.2,0.75,"Default 1.9");
  tlatexBplus->SetNDC();
  tlatexBplus->SetTextColor(1);
  tlatexBplus->SetTextFont(42);
  tlatexBplus->SetTextSize(0.04);
  tlatexBplus->Draw();

canvas->SaveAs("SystCheckOnEff.eps");

  
  const int nBins = 10;
  double ptBins[nBins+1] = {1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4};
  TH1D *hPt0 = new TH1D("hPt0","",nBins,ptBins);
  TH1D *hPt1 = new TH1D("hPt1","",nBins,ptBins);
  TH1D *hPt2 = new TH1D("hPt2","",nBins,ptBins);
  TH1D *hPt3 = new TH1D("hPt3","",nBins,ptBins);
  TH1D *hPt4 = new TH1D("hPt4","",nBins,ptBins);
  TH1D *hPt5 = new TH1D("hPt5","",nBins,ptBins);
  
  hPt0->SetBinContent(1,hSigmaBis0->GetBinContent(1));
  hPt0->SetBinContent(2,hSigmaBis1->GetBinContent(1));
  hPt0->SetBinContent(3,hSigmaBis2->GetBinContent(1));
  hPt0->SetBinContent(4,hSigmaBis3->GetBinContent(1));
  hPt0->SetBinContent(5,hSigmaBis4->GetBinContent(1));
  hPt0->SetBinContent(6,hSigmaBis5->GetBinContent(1));
  hPt0->SetBinContent(7,hSigmaBis6->GetBinContent(1));
  hPt0->SetBinContent(8,hSigmaBis7->GetBinContent(1));
  hPt0->SetBinContent(9,hSigmaBis8->GetBinContent(1));
  hPt0->SetBinContent(10,hSigmaBis9->GetBinContent(1));
  
  hPt1->SetBinContent(1,hSigmaBis0->GetBinContent(2));
  hPt1->SetBinContent(2,hSigmaBis1->GetBinContent(2));
  hPt1->SetBinContent(3,hSigmaBis2->GetBinContent(2));
  hPt1->SetBinContent(4,hSigmaBis3->GetBinContent(2));
  hPt1->SetBinContent(5,hSigmaBis4->GetBinContent(2));
  hPt1->SetBinContent(6,hSigmaBis5->GetBinContent(2));
  hPt1->SetBinContent(7,hSigmaBis6->GetBinContent(2));
  hPt1->SetBinContent(8,hSigmaBis7->GetBinContent(2));
  hPt1->SetBinContent(9,hSigmaBis8->GetBinContent(2));
  hPt1->SetBinContent(10,hSigmaBis9->GetBinContent(2));
  
  hPt2->SetBinContent(1,hSigmaBis0->GetBinContent(3));
  hPt2->SetBinContent(2,hSigmaBis1->GetBinContent(3));
  hPt2->SetBinContent(3,hSigmaBis2->GetBinContent(3));
  hPt2->SetBinContent(4,hSigmaBis3->GetBinContent(3));
  hPt2->SetBinContent(5,hSigmaBis4->GetBinContent(3));
  hPt2->SetBinContent(6,hSigmaBis5->GetBinContent(3));
  hPt2->SetBinContent(7,hSigmaBis6->GetBinContent(3));
  hPt2->SetBinContent(8,hSigmaBis7->GetBinContent(3));
  hPt2->SetBinContent(9,hSigmaBis8->GetBinContent(3));
  hPt2->SetBinContent(10,hSigmaBis9->GetBinContent(3));
  
  hPt3->SetBinContent(1,hSigmaBis0->GetBinContent(4));
  hPt3->SetBinContent(2,hSigmaBis1->GetBinContent(4));
  hPt3->SetBinContent(3,hSigmaBis2->GetBinContent(4));
  hPt3->SetBinContent(4,hSigmaBis3->GetBinContent(4));
  hPt3->SetBinContent(5,hSigmaBis4->GetBinContent(4));
  hPt3->SetBinContent(6,hSigmaBis5->GetBinContent(4));
  hPt3->SetBinContent(7,hSigmaBis6->GetBinContent(4));
  hPt3->SetBinContent(8,hSigmaBis7->GetBinContent(4));
  hPt3->SetBinContent(9,hSigmaBis8->GetBinContent(4));
  hPt3->SetBinContent(10,hSigmaBis9->GetBinContent(4));
  
  hPt4->SetBinContent(1,hSigmaBis0->GetBinContent(5));
  hPt4->SetBinContent(2,hSigmaBis1->GetBinContent(5));
  hPt4->SetBinContent(3,hSigmaBis2->GetBinContent(5));
  hPt4->SetBinContent(4,hSigmaBis3->GetBinContent(5));
  hPt4->SetBinContent(5,hSigmaBis4->GetBinContent(5));
  hPt4->SetBinContent(6,hSigmaBis5->GetBinContent(5));
  hPt4->SetBinContent(7,hSigmaBis6->GetBinContent(5));
  hPt4->SetBinContent(8,hSigmaBis7->GetBinContent(5));
  hPt4->SetBinContent(9,hSigmaBis8->GetBinContent(5));
  hPt4->SetBinContent(10,hSigmaBis9->GetBinContent(5));
  
  hPt5->SetBinContent(1,hSigmaBis0->GetBinContent(6));
  hPt5->SetBinContent(2,hSigmaBis1->GetBinContent(6));
  hPt5->SetBinContent(3,hSigmaBis2->GetBinContent(6));
  hPt5->SetBinContent(4,hSigmaBis3->GetBinContent(6));
  hPt5->SetBinContent(5,hSigmaBis4->GetBinContent(6));
  hPt5->SetBinContent(6,hSigmaBis5->GetBinContent(6));
  hPt5->SetBinContent(7,hSigmaBis6->GetBinContent(6));
  hPt5->SetBinContent(8,hSigmaBis7->GetBinContent(6));
  hPt5->SetBinContent(9,hSigmaBis8->GetBinContent(6));
  hPt5->SetBinContent(10,hSigmaBis9->GetBinContent(6));
  
  
  hPt0->SetBinError(1,hSigmaBis0->GetBinError(1));
  hPt0->SetBinError(2,hSigmaBis1->GetBinError(1));
  hPt0->SetBinError(3,hSigmaBis2->GetBinError(1));
  hPt0->SetBinError(4,hSigmaBis3->GetBinError(1));
  hPt0->SetBinError(5,hSigmaBis4->GetBinError(1));
  hPt0->SetBinError(6,hSigmaBis5->GetBinError(1));
  hPt0->SetBinError(7,hSigmaBis6->GetBinError(1));
  hPt0->SetBinError(8,hSigmaBis7->GetBinError(1));
  hPt0->SetBinError(9,hSigmaBis8->GetBinError(1));
  hPt0->SetBinError(10,hSigmaBis9->GetBinError(1));
  
  hPt1->SetBinError(1,hSigmaBis0->GetBinError(2));
  hPt1->SetBinError(2,hSigmaBis1->GetBinError(2));
  hPt1->SetBinError(3,hSigmaBis2->GetBinError(2));
  hPt1->SetBinError(4,hSigmaBis3->GetBinError(2));
  hPt1->SetBinError(5,hSigmaBis4->GetBinError(2));
  hPt1->SetBinError(6,hSigmaBis5->GetBinError(2));
  hPt1->SetBinError(7,hSigmaBis6->GetBinError(2));
  hPt1->SetBinError(8,hSigmaBis7->GetBinError(2));
  hPt1->SetBinError(9,hSigmaBis8->GetBinError(2));
  hPt1->SetBinError(10,hSigmaBis9->GetBinError(2));
  
  hPt2->SetBinError(1,hSigmaBis0->GetBinError(3));
  hPt2->SetBinError(2,hSigmaBis1->GetBinError(3));
  hPt2->SetBinError(3,hSigmaBis2->GetBinError(3));
  hPt2->SetBinError(4,hSigmaBis3->GetBinError(3));
  hPt2->SetBinError(5,hSigmaBis4->GetBinError(3));
  hPt2->SetBinError(6,hSigmaBis5->GetBinError(3));
  hPt2->SetBinError(7,hSigmaBis6->GetBinError(3));
  hPt2->SetBinError(8,hSigmaBis7->GetBinError(3));
  hPt2->SetBinError(9,hSigmaBis8->GetBinError(3));
  hPt2->SetBinError(10,hSigmaBis9->GetBinError(3));
  
  hPt3->SetBinError(1,hSigmaBis0->GetBinError(4));
  hPt3->SetBinError(2,hSigmaBis1->GetBinError(4));
  hPt3->SetBinError(3,hSigmaBis2->GetBinError(4));
  hPt3->SetBinError(4,hSigmaBis3->GetBinError(4));
  hPt3->SetBinError(5,hSigmaBis4->GetBinError(4));
  hPt3->SetBinError(6,hSigmaBis5->GetBinError(4));
  hPt3->SetBinError(7,hSigmaBis6->GetBinError(4));
  hPt3->SetBinError(8,hSigmaBis7->GetBinError(4));
  hPt3->SetBinError(9,hSigmaBis8->GetBinError(4));
  hPt3->SetBinError(10,hSigmaBis9->GetBinError(4));
  
  hPt4->SetBinError(1,hSigmaBis0->GetBinError(5));
  hPt4->SetBinError(2,hSigmaBis1->GetBinError(5));
  hPt4->SetBinError(3,hSigmaBis2->GetBinError(5));
  hPt4->SetBinError(4,hSigmaBis3->GetBinError(5));
  hPt4->SetBinError(5,hSigmaBis4->GetBinError(5));
  hPt4->SetBinError(6,hSigmaBis5->GetBinError(5));
  hPt4->SetBinError(7,hSigmaBis6->GetBinError(5));
  hPt4->SetBinError(8,hSigmaBis7->GetBinError(5));
  hPt4->SetBinError(9,hSigmaBis8->GetBinError(5));
  hPt4->SetBinError(10,hSigmaBis9->GetBinError(5));
  
  hPt5->SetBinError(1,hSigmaBis0->GetBinError(6));
  hPt5->SetBinError(2,hSigmaBis1->GetBinError(6));
  hPt5->SetBinError(3,hSigmaBis2->GetBinError(6));
  hPt5->SetBinError(4,hSigmaBis3->GetBinError(6));
  hPt5->SetBinError(5,hSigmaBis4->GetBinError(6));
  hPt5->SetBinError(6,hSigmaBis5->GetBinError(6));
  hPt5->SetBinError(7,hSigmaBis6->GetBinError(6));
  hPt5->SetBinError(8,hSigmaBis7->GetBinError(6));
  hPt5->SetBinError(9,hSigmaBis8->GetBinError(6));
  hPt5->SetBinError(10,hSigmaBis9->GetBinError(6));
  
  
  hPt0->Scale(1/hSigmaBis5->GetBinContent(1));
  hPt3->Scale(1/hSigmaBis5->GetBinContent(4));

  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",1000,500);
  canvasVscut->cd();
  canvasVscut->Divide(2,1);
  canvasVscut->cd(1);
  hPt0->GetXaxis()->SetTitle("|trk1Dxy/Err| cut value");
  hPt0->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hPt0->GetXaxis()->SetTitleOffset(1.);
  hPt0->GetYaxis()->SetTitleOffset(1.);
  hPt0->GetXaxis()->SetTitleSize(0.04);
  hPt0->GetYaxis()->SetTitleSize(0.04);
  hPt0->GetXaxis()->SetTitleFont(42);
  hPt0->GetYaxis()->SetTitleFont(42);
  hPt0->GetXaxis()->SetLabelFont(42);
  hPt0->GetYaxis()->SetLabelFont(42);
  hPt0->GetXaxis()->SetLabelSize(0.035);
  hPt0->GetYaxis()->SetLabelSize(0.035);  
  hPt0->SetMinimum(0.);
  TLatex * tlatexPt0=new TLatex(0.2,0.85,"5 <p_{t}<10 GeV/c");
  tlatexPt0->SetNDC();
  tlatexPt0->SetTextColor(1);
  tlatexPt0->SetTextFont(42);
  tlatexPt0->SetTextSize(0.04);
  tlatexPt0->Draw();
  hPt0->Draw();
  tlatexPt0->Draw();
  canvasVscut->cd(2);
  hPt3->GetXaxis()->SetTitle("|trk1Dxy/Err| cut value");
  hPt3->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hPt3->GetXaxis()->SetTitleOffset(1.);
  hPt3->GetYaxis()->SetTitleOffset(1.1);
  hPt3->GetXaxis()->SetTitleSize(0.04);
  hPt3->GetYaxis()->SetTitleSize(0.04);
  hPt3->GetXaxis()->SetTitleFont(42);
  hPt3->GetYaxis()->SetTitleFont(42);
  hPt3->GetXaxis()->SetLabelFont(42);
  hPt3->GetYaxis()->SetLabelFont(42);
  hPt3->GetXaxis()->SetLabelSize(0.035);
  hPt3->GetYaxis()->SetLabelSize(0.035);  
  hPt3->SetMinimum(0.);
  TLatex * tlatexPt6=new TLatex(0.2,0.85,"20 <p_{t}<25 GeV/c");
  tlatexPt6->SetNDC();
  tlatexPt6->SetTextColor(1);
  tlatexPt6->SetTextFont(42);
  tlatexPt6->SetTextSize(0.04);
  tlatexPt6->Draw();
  hPt3->Draw();
  tlatexPt6->Draw();
  canvasVscut->SaveAs("canvasVscut.eps");
  
  
}
