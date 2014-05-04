void DisplayDoubleRatioBzero(){

  TFile*file_Data_resmass_NoCut=new TFile("ResultsBzero/CutId2/SigmaBzeroCutId2_isData1.root");
  TFile*file_Data_resmass_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");
  TFile*file_Data_chi2cl_NoCut=new TFile("ResultsBzero/CutId3/SigmaBzeroCutId3_isData1.root");
  TFile*file_Data_chi2cl_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");
  TFile*file_Data_costheta_NoCut=new TFile("ResultsBzero/CutId4/SigmaBzeroCutId4_isData1.root");
  TFile*file_Data_costheta_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");

  TFile*file_MC_resmass_NoCut=new TFile("ResultsBzero/CutId2/SigmaBzeroCutId2_isData0.root");
  TFile*file_MC_resmass_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");
  TFile*file_MC_chi2cl_NoCut=new TFile("ResultsBzero/CutId3/SigmaBzeroCutId3_isData0.root");
  TFile*file_MC_chi2cl_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");
  TFile*file_MC_costheta_NoCut=new TFile("ResultsBzero/CutId4/SigmaBzeroCutId4_isData0.root");
  TFile*file_MC_costheta_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");

  TH1F*hPtYield_Data_resmass_Cut=(TH1F*)file_Data_resmass_Cut->Get("hPt");
  TH1F*hPtYield_Data_resmass_NoCut=(TH1F*)file_Data_resmass_NoCut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_Cut=(TH1F*)file_Data_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_NoCut=(TH1F*)file_Data_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_Data_costheta_Cut=(TH1F*)file_Data_costheta_Cut->Get("hPt");
  TH1F*hPtYield_Data_costheta_NoCut=(TH1F*)file_Data_costheta_NoCut->Get("hPt");  

  TH1F*hPtYield_MC_resmass_Cut=(TH1F*)file_MC_resmass_Cut->Get("hPt");
  TH1F*hPtYield_MC_resmass_NoCut=(TH1F*)file_MC_resmass_NoCut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_NoCut=(TH1F*)file_MC_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_Cut=(TH1F*)file_MC_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_MC_costheta_NoCut=(TH1F*)file_MC_costheta_NoCut->Get("hPt");
  TH1F*hPtYield_MC_costheta_Cut=(TH1F*)file_MC_costheta_Cut->Get("hPt");  

  double yield_Data_resmass_Cut=hPtYield_Data_resmass_Cut->GetBinContent(1);
  double yield_Data_resmass_NoCut=hPtYield_Data_resmass_NoCut->GetBinContent(1);
  double yield_MC_resmass_Cut=hPtYield_MC_resmass_Cut->GetBinContent(1);
  double yield_MC_resmass_NoCut=hPtYield_MC_resmass_NoCut->GetBinContent(1);
  double relerryield_Data_resmass_Cut=hPtYield_Data_resmass_Cut->GetBinError(1)/hPtYield_Data_resmass_Cut->GetBinContent(1);
  double relerryield_Data_resmass_NoCut=hPtYield_Data_resmass_NoCut->GetBinError(1)/hPtYield_Data_resmass_NoCut->GetBinContent(1);
  double relerryield_MC_resmass_Cut=hPtYield_MC_resmass_Cut->GetBinError(1)/hPtYield_MC_resmass_Cut->GetBinContent(1);
  double relerryield_MC_resmass_NoCut=hPtYield_MC_resmass_NoCut->GetBinError(1)/hPtYield_MC_resmass_NoCut->GetBinContent(1);
  double dratioresmass=(yield_Data_resmass_Cut/yield_Data_resmass_NoCut)/(yield_MC_resmass_Cut/yield_MC_resmass_NoCut);
  double errdratioresmass=(relerryield_Data_resmass_Cut+relerryield_Data_resmass_NoCut+relerryield_MC_resmass_Cut+relerryield_MC_resmass_NoCut)*dratioresmass;

 
  double yield_Data_chi2cl_Cut=hPtYield_Data_chi2cl_Cut->GetBinContent(1);
  double yield_Data_chi2cl_NoCut=hPtYield_Data_chi2cl_NoCut->GetBinContent(1);
  double yield_MC_chi2cl_Cut=hPtYield_MC_chi2cl_Cut->GetBinContent(1);
  double yield_MC_chi2cl_NoCut=hPtYield_MC_chi2cl_NoCut->GetBinContent(1);
  double relerryield_Data_chi2cl_Cut=hPtYield_Data_chi2cl_Cut->GetBinError(1)/hPtYield_Data_chi2cl_Cut->GetBinContent(1);
  double relerryield_Data_chi2cl_NoCut=hPtYield_Data_chi2cl_NoCut->GetBinError(1)/hPtYield_Data_chi2cl_NoCut->GetBinContent(1);
  double relerryield_MC_chi2cl_Cut=hPtYield_MC_chi2cl_Cut->GetBinError(1)/hPtYield_MC_chi2cl_Cut->GetBinContent(1);
  double relerryield_MC_chi2cl_NoCut=hPtYield_MC_chi2cl_NoCut->GetBinError(1)/hPtYield_MC_chi2cl_NoCut->GetBinContent(1);
  double dratiochi2cl=(yield_Data_chi2cl_Cut/yield_Data_chi2cl_NoCut)/(yield_MC_chi2cl_Cut/yield_MC_chi2cl_NoCut);
  double errdratiochi2cl=(relerryield_Data_chi2cl_Cut+relerryield_Data_chi2cl_NoCut+relerryield_MC_chi2cl_Cut+relerryield_MC_chi2cl_NoCut)*dratiochi2cl;

  double yield_Data_costheta_Cut=hPtYield_Data_costheta_Cut->GetBinContent(1);
  double yield_Data_costheta_NoCut=hPtYield_Data_costheta_NoCut->GetBinContent(1);
  double yield_MC_costheta_Cut=hPtYield_MC_costheta_Cut->GetBinContent(1);
  double yield_MC_costheta_NoCut=hPtYield_MC_costheta_NoCut->GetBinContent(1);
  double relerryield_Data_costheta_Cut=hPtYield_Data_costheta_Cut->GetBinError(1)/hPtYield_Data_costheta_Cut->GetBinContent(1);
  double relerryield_Data_costheta_NoCut=hPtYield_Data_costheta_NoCut->GetBinError(1)/hPtYield_Data_costheta_NoCut->GetBinContent(1);
  double relerryield_MC_costheta_Cut=hPtYield_MC_costheta_Cut->GetBinError(1)/hPtYield_MC_costheta_Cut->GetBinContent(1);
  double relerryield_MC_costheta_NoCut=hPtYield_MC_costheta_NoCut->GetBinError(1)/hPtYield_MC_costheta_NoCut->GetBinContent(1);
  double dratiocostheta=(yield_Data_costheta_Cut/yield_Data_costheta_NoCut)/(yield_MC_costheta_Cut/yield_MC_costheta_NoCut);
  double errdratiocostheta=(relerryield_Data_costheta_Cut+relerryield_Data_costheta_NoCut+relerryield_MC_costheta_Cut+relerryield_MC_costheta_NoCut)*dratiocostheta;
  
  /*
  cout<<"yield_Data_costheta_NoCut"<<yield_Data_costheta_NoCut*50.<<endl;
  cout<<"yield_Data_chi2cl_NoCut"<<yield_Data_chi2cl_NoCut*50.<<endl;
  cout<<"yield_Data_resmass_NoCut"<<yield_Data_resmass_NoCut*50.<<endl;
  cout<<"yield_Data_Cut"<<yield_Data_resmass_Cut*50.<<endl;

  cout<<"yield_MC_costheta_NoCut"<<yield_MC_costheta_NoCut*50.<<endl;
  cout<<"yield_MC_chi2cl_NoCut"<<yield_MC_chi2cl_NoCut*50.<<endl;
  cout<<"yield_MC_resmass_NoCut"<<yield_MC_resmass_NoCut*50.<<endl;
  cout<<"yield_MC_Cut"<<yield_MC_resmass_Cut*50.<<endl;

*/


  cout<<"double ratio resmass"<<dratioresmass<<" with stat error +- "<<errdratioresmass<<endl;
  cout<<"double ratio chi2cl"<<dratiochi2cl<<" with stat error +- "<<errdratiochi2cl<<endl;
  cout<<"double ratio costheta"<<dratiocostheta<<" with stat error +- "<<errdratiocostheta<<endl;

  
}
