void FakeInput(){

  const int nBins = 5;
  double ptBins[nBins+1] = {10,15,20,25,30,60};
  
  const int nBinsy = 4;
  double yBins[nBinsy+1] = {-1.465,-0.5,0.0,0.5,1.465};
  
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtData = new TH1D("hPtData","",nBins,ptBins);
  
  TH1D *hyMC = new TH1D("hyMC","",nBinsy,yBins);
  TH1D *hyData = new TH1D("hyData","",nBinsy,yBins);
  
  hPtMC->SetBinContent(1,0.15);
  hPtMC->SetBinContent(2,0.052);
  hPtMC->SetBinContent(3,0.02);
  hPtMC->SetBinContent(4,0.008);
  hPtMC->SetBinContent(5,0.002);

  hPtData->SetBinContent(1,0.15);
  hPtData->SetBinContent(2,0.055);
  hPtData->SetBinContent(3,0.022);
  hPtData->SetBinContent(4,0.01);
  hPtData->SetBinContent(5,0.0017);  
  
  hPtMC->SetBinError(1,hPtMC->GetBinContent(1)*0.1);
  hPtMC->SetBinError(2,hPtMC->GetBinContent(2)*0.1);
  hPtMC->SetBinError(3,hPtMC->GetBinContent(3)*0.1);
  hPtMC->SetBinError(4,hPtMC->GetBinContent(4)*0.1);
  hPtMC->SetBinError(5,hPtMC->GetBinContent(5)*0.1);
  
  hPtData->SetBinError(1,hPtData->GetBinContent(1)*0.1);
  hPtData->SetBinError(2,hPtData->GetBinContent(2)*0.1);
  hPtData->SetBinError(3,hPtData->GetBinContent(3)*0.1);
  hPtData->SetBinError(4,hPtData->GetBinContent(4)*0.1);
  hPtData->SetBinError(5,hPtData->GetBinContent(5)*0.1);
  
  
  hyMC->SetBinContent(1,0.15);
  hyMC->SetBinContent(2,0.14);
  hyMC->SetBinContent(3,0.16);
  hyMC->SetBinContent(4,0.17);

  hyData->SetBinContent(1,0.15);
  hyData->SetBinContent(2,0.13);
  hyData->SetBinContent(3,0.18);
  hyData->SetBinContent(4,0.15);
  
  hyMC->SetBinError(1,hyMC->GetBinContent(1)*0.1);
  hyMC->SetBinError(2,hyMC->GetBinContent(2)*0.1);
  hyMC->SetBinError(3,hyMC->GetBinContent(3)*0.1);
  hyMC->SetBinError(4,hyMC->GetBinContent(4)*0.1);
  
  hyData->SetBinError(1,hyData->GetBinContent(1)*0.1);
  hyData->SetBinError(2,hyData->GetBinContent(2)*0.1);
  hyData->SetBinError(3,hyData->GetBinContent(3)*0.1);
  hyData->SetBinError(4,hyData->GetBinContent(4)*0.1);


  TCanvas*c=new TCanvas("c","c",800,500);
  c->Divide(2,2);
  c->cd(1);
  hPtData->Draw();
  c->cd(2);
  hPtMC->Draw();
  c->cd(3);
  hyData->Draw();
  c->cd(4);
  hyMC->Draw();

  c->SaveAs("prova.pdf");
  
  TFile*fout=new TFile("InputFilesMCData.root","recreate");
  fout->cd();
  hPtData->Write();
  hPtMC->Write();
  hyData->Write();
  hyMC->Write();


}