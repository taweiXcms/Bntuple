void DisplayDoubleRatio(){

  TFile*file_Data_D0err_NoCut=new TFile("Results/CutId1/SigmaBplusCutId1_isData1.root"));
  TFile*file_Data_D0err_Cut=new TFile("Results/CutId1/SigmaBplusCutId2_isData1.root"));
  
  TFile*file_Data_Trkpt_NoCut=new TFile("Results/CutId1/SigmaBplusCutId3_isData1.root"));
  TFile*file_Data_Trkpt_Cut=new TFile("Results/CutId1/SigmaBplusCutId4_isData1.root"));

  
  
  TFile*file0_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData0.root",variationoption,variationoption));
  TH1F*hPtYieldBis_Data1=(TH1F*)file0_Data->Get("hPt");
  TH1F*hPtYieldBis_MC1=(TH1F*)file0_MC->Get("hPt");
  hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
  hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
  
}
