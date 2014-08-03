void plotreweighting(){

//        weightPtLow=0.016*pt[j]+0.44;
//        weightPtHigh=-0.016*pt[j]+1.56;
//        weightyHigh=-(0.8/4.8)*y[j]+1;
//        weightyLow=+(0.8/4.8)*y[j]+1;


  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);
  
  TH2D *hemptyPt = new TH2D("hemptyPt","",40,10.,60.,10,0.,2.);
  hemptyPt->GetXaxis()->SetTitle("p_{t} (GeV/c)");
  hemptyPt->GetYaxis()->SetTitle("function");
  hemptyPt->GetXaxis()->SetTitleOffset(1.);
  hemptyPt->GetYaxis()->SetTitleOffset(.9);
  hemptyPt->GetXaxis()->SetTitleSize(0.045);
  hemptyPt->GetYaxis()->SetTitleSize(0.045);
  hemptyPt->GetXaxis()->SetTitleFont(42);
  hemptyPt->GetYaxis()->SetTitleFont(42);
  hemptyPt->GetXaxis()->SetLabelFont(42);
  hemptyPt->GetYaxis()->SetLabelFont(42);
  hemptyPt->GetXaxis()->SetLabelSize(0.035);
  hemptyPt->GetYaxis()->SetLabelSize(0.035);  
  hemptyPt->SetMinimum(0.);
  hemptyPt->SetMaximum(2.);

  TH2D *hemptyy = new TH2D("hemptyy","",40,-2.4,2.4.,10,0,2);
  hemptyy->GetXaxis()->SetTitle("y_{LAB} (GeV/c)");
  hemptyy->GetYaxis()->SetTitle("function");
  hemptyy->GetXaxis()->SetTitleOffset(1.);
  hemptyy->GetYaxis()->SetTitleOffset(.9);
  hemptyy->GetXaxis()->SetTitleSize(0.045);
  hemptyy->GetYaxis()->SetTitleSize(0.045);
  hemptyy->GetXaxis()->SetTitleFont(42);
  hemptyy->GetYaxis()->SetTitleFont(42);
  hemptyy->GetXaxis()->SetLabelFont(42);
  hemptyy->GetYaxis()->SetLabelFont(42);
  hemptyy->GetXaxis()->SetLabelSize(0.035);
  hemptyy->GetYaxis()->SetLabelSize(0.035);  
  hemptyy->SetMinimum(0.);
  hemptyy->SetMaximum(2.);





  TF1 *fptlow = new TF1("fptlow","0.016*x+0.44",10,60);
  TF1 *fptup = new TF1("fptup","-0.016*x+1.56",10,60);
  TF1 *fpt = new TF1("fpt","1",10,60);
  
  TF1 *fylow = new TF1("fylow","(0.8/4.8)*x+1",-2.4,2.4);
  TF1 *fyup = new TF1("fyup","-(0.8/4.8)*x+1",-2.4,2.4);
  TF1 *fy = new TF1("fy","1",-2.4,2.4);

  
  fptlow->SetLineColor(4);
  fpt->SetLineColor(1);
  fptup->SetLineColor(2);

  fylow->SetLineColor(4);
  fy->SetLineColor(1);
  fyup->SetLineColor(2);


  TCanvas*canvas=new TCanvas("canvas","canvas",1200,450);
  canvas->Divide(2,1);
  canvas->cd(1);
  hemptyPt->Draw();
  fptlow->Draw("same");
  fptup->Draw("same");
  fpt->Draw("same");
  
  canvas->cd(2);
  hemptyy->Draw();
  fylow->Draw("same");
  fyup->Draw("same");
  fy->Draw("same");
  canvas->SaveAs("Plotreweighting.pdf");
  




}