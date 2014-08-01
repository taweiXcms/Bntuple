void FakeInput(){

  const int nBins = 5;
  double ptBins[nBins+1] = {10,15,20,25,30,60};
  
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtData = new TH1D("hPtData","",nBins,ptBins);
  
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


  TCanvas*c=new TCanvas("c","c",800,500);
  c->Divide(2,1);
  c->cd(1);
  hPtData->Draw();
  c->cd(2);
  hPtMC->Draw();
  c->SaveAs("prova.pdf");
  
  TFile*fout=new TFile("InputFilesMCData.root","recreate");
  fout->cd();
  hPtData->Write();
  hPtMC->Write();

}