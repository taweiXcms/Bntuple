#include <iostream>
#include <math.h>
#include <TTree.h>                  
#include <TFile.h>
#include <TNtuple.h> 
#include <TVector3.h>
#include <TChain.h>
#include <TH1.h>
#include <TEfficiency.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TLorentzVector.h>
////Include Bfinder interface/format.h here
//#include "/net/hisrv0001/home/tawei/HeavyFlavor_20131030/Bfinder/CMSSW_5_3_8_patch3/src/Bfinder/Bfinder/interface/format.h"
#include "format.h"
#include "loop.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916
#define PSI2S_MASS  3.686109

// T&P efficiency re-weight factor
TFile* fEffWeight1 = new TFile("TNPeffciiencyWeight/WeightFactor_etabin1CS_1st_20140318.root");
TH1D* hEffCorr1 = (TH1D*)fEffWeight1->Get("hRD");
TFile* fEffWeight2 = new TFile("TNPeffciiencyWeight/WeightFactor_etabin2CS_1st_20140318.root");
TH1D* hEffCorr2 = (TH1D*)fEffWeight2->Get("hRD");
TFile*fEffWeight3 = new TFile("TNPeffciiencyWeight/WeightFactor_etabin3CS_1st_20140318.root");
TH1D* hEffCorr3 = (TH1D*)fEffWeight3->Get("hRD");

   
bool kineCut(bool, double muPt, double muEta, double muP);
float getEffWeight(bool isBoosted=0,  float mupt1=0, float mueta1=0, float mupt2=0, float mueta2=0);
void Bfinder_eff(bool useDataDrivenEff=1){

//Setting the corresponding channel
	int MCflag = 1;//K+
	MCflag = 2;//K*
	MCflag = 3;//Phi
	TFile* fout;
	if(MCflag == 1){
		fout = new TFile("fout_kp.root","recreate");
//		fout = new TFile("fout_kp_temp.root","recreate");
//		fout = new TFile("fout_kp_cutted.root","recreate");
//		fout = new TFile("fout_kp_temp_cutted.root","recreate");
	}
	if(MCflag == 2){
		fout = new TFile("fout_kstar.root","recreate");
	}
	if(MCflag == 3){
		fout = new TFile("fout_phi.root","recreate");
	}
	TCanvas*c1 = new TCanvas("c1", "", 200, 10, 1000, 800);
	TCanvas*c2 = new TCanvas("c2", "", 200, 10, 1000, 800);
	TCanvas*c3 = new TCanvas("c3", "", 200, 10, 1000, 800);
	TCanvas*c4 = new TCanvas("c4", "", 200, 10, 1000, 800);

	TChain *root = new TChain("demo/root");
	TChain *hlt = new TChain("hltanalysis/HltTree");
	string infname;
	if(MCflag == 1){
//		infname = "/mnt/hadoop/cms/store/user/jwang/BfinderBoostedMC_20140303_kp/*";
//		infname = "HIJINGemb_BuJpsiK_TuneZ2star_5TeV_cff_step4_RAW2DIGI_L1Reco_RECO.root";
//		infname = "/mnt/hadoop/cms/store/user/jwang/BfinderBoostedMC_20140305_Kp/*";
//		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_kp_matchingMuon/*";
		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_kp_selectedMuon/*";
	}
	if(MCflag == 2){
//		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_kstar_matchingMuon/*";
		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_kstar_selectedMuon/*";
	}
	if(MCflag == 3){
//		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_phi_matchingMuon/*";
		infname = "/mnt/hadoop/cms/store/user/jwang/Bfinder_BoostedMC_20140313_phi_selectedMuon/*";
	}
	root->Add(infname.c_str());
	hlt->Add(infname.c_str());
	
    EvtInfoBranches EvtInfo;
    MuonInfoBranches MuonInfo;
    TrackInfoBranches TrackInfo;
    BInfoBranches BInfo;
    GenInfoBranches GenInfo;
    EvtInfo.setbranchadd(root);
    MuonInfo.setbranchadd(root);
    TrackInfo.setbranchadd(root);
    BInfo.setbranchadd(root);
    GenInfo.setbranchadd(root); 
//    setHltBranch(hlt);
    hlt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
    
    const int nBins = 6;
    double ptBins[nBins+1] = {5,10,15,20,25,30,60};
    const int nEtaBins = 4;
    double etaBins[nEtaBins+1] = {-2.395, -1.47, -0.47, 0.53, 1.465};
	TH1F* reco_bsig_pt = new TH1F("reco_bsig_pt", "", nBins,ptBins);
	TH1F* reco_bsig_pt_stage2 = new TH1F("reco_bsig_pt_stage2", "", nBins,ptBins);
	TH1F* gen_bsig_pt = new TH1F("gen_bsig_pt", "", nBins,ptBins);
	TH1F* reco_bsig_eta_stage2 = new TH1F("reco_bsig_eta_stage2", "", nEtaBins,etaBins);
	TH1F* reco_bsig_eta = new TH1F("reco_bsig_eta", "", nEtaBins,etaBins);
	TH1F* gen_bsig_eta = new TH1F("gen_bsig_eta", "", nEtaBins,etaBins);
	reco_bsig_pt->SetMinimum(0);
	gen_bsig_pt->SetMinimum(0);
	reco_bsig_eta->SetMinimum(0);
	gen_bsig_eta->SetMinimum(0);

////For test
TH1F* gen_sig_eta = new TH1F("gen_sig_eta", "", 100, -3.5, 3.5);
TH1F* gen_dauSum_eta = new TH1F("gen_dauSum_eta", "", 100, -3.5, 3.5);
TH1F* gen_sig_y = new TH1F("gen_sig_y", "", 100, -3.5, 3.5);
TH1F* gen_dauSum_y = new TH1F("gen_dauSum_y", "", 100, -3.5, 3.5);
		
	TH1F* CutLevel = new TH1F("cutlevel", "cutlevel", 20, 0, 20);
	double  total_reco_true_bsig_stage2 = 0;
	double  total_reco_true_bsig = 0;
	double  total_gen_bsig = 0;
	double  eta_total_reco_true_bsig_stage2 = 0;
	double  eta_total_reco_true_bsig = 0;
	double  eta_total_gen_bsig = 0;
	double  optc1 = 0;
	double  optc2 = 0;
	double  optc3 = 0;
	double  optc4 = 0;
	double  optc5 = 0;
	double  optc6 = 0;

    int offsetHltTree=0; 
    int nevents_total = root->GetEntries();
//	for(int entry=400000; entry<nevents_total; entry++){
	for(int entry=0; entry<nevents_total; entry++){
//	for(int entry=0; entry<150000; entry++){
//	for(int entry=0; entry<10000; entry++){
    	if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
        root->GetEntry(entry);
		hlt->GetEntry(entry+offsetHltTree);
		//cout<<HLT_PAMu3_v1<<endl;

//////GEN
		vector<int> geninfo_bidx;
		vector<int> geninfo_mu1idx;
		vector<int> geninfo_mu2idx;
		vector<int> geninfo_tk1idx;
		vector<int> geninfo_tk2idx;
		int gmu1idx = -1;	int gmu2idx = -1;	int gtk1idx = -1;	int gtk2idx = -1;
		TLorentzVector mu1;
		TLorentzVector mu2;
		TLorentzVector tk1;
		TLorentzVector tk2;
		TLorentzVector B;
		TLorentzVector trueB;
		for(int i = 0; i < GenInfo.size; i++){
			bool geninfo_jp = 0;
			if(abs(GenInfo.pdgId[i]) == 521 || abs(GenInfo.pdgId[i]) == 511 || abs(GenInfo.pdgId[i]) == 531){
				//printf("B+ da1 is %i\n", GenInfo.pdgId[GenInfo.da1[i]]);
				//printf("B+ da2 is %i\n", GenInfo.pdgId[GenInfo.da2[i]]);
				if(GenInfo.nDa[i] > 1){
					if(GenInfo.pdgId[GenInfo.da1[i]] == 443){//if has jpsi as ga, it must be da1
						if(abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da1[i]]]) == 13 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da1[i]]]) == 13){
//if(1){if(1){if(1){
							geninfo_jp = 1;
							gmu1idx = GenInfo.da1[GenInfo.da1[i]];
							gmu2idx = GenInfo.da2[GenInfo.da1[i]];
							//Mu acc def


							if(fabs(GenInfo.eta[gmu1idx]) < 1.3) {if(GenInfo.pt[gmu1idx] < 3.3) continue;}
							else if(fabs(GenInfo.eta[gmu1idx]) > 1.3 && fabs(GenInfo.eta[gmu1idx]) < 2.2) {if(GenInfo.pt[gmu1idx] < 2.9) continue;}
							else if(fabs(GenInfo.eta[gmu1idx]) > 2.2 && fabs(GenInfo.eta[gmu1idx]) < 2.4) {if(GenInfo.pt[gmu1idx] < 0.8) continue;}
							else {continue;}
							if(fabs(GenInfo.eta[gmu2idx]) < 1.3) {if(GenInfo.pt[gmu2idx] < 3.3) continue;}
							else if(fabs(GenInfo.eta[gmu2idx]) > 1.3 && fabs(GenInfo.eta[gmu2idx]) < 2.2) {if(GenInfo.pt[gmu2idx] < 2.9) continue;}
							else if(fabs(GenInfo.eta[gmu2idx]) > 2.2 && fabs(GenInfo.eta[gmu2idx]) < 2.4) {if(GenInfo.pt[gmu2idx] < 0.8) continue;}
							else {continue;}


							mu1.SetPtEtaPhiM(GenInfo.pt[gmu1idx], GenInfo.eta[gmu1idx], GenInfo.phi[gmu1idx], MUON_MASS);
							mu2.SetPtEtaPhiM(GenInfo.pt[gmu2idx], GenInfo.eta[gmu2idx], GenInfo.phi[gmu2idx], MUON_MASS);
							//Kp
//							if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 321 && abs(GenInfo.pdgId[i]) == 521 && MCflag == 1) {
							if(abs(GenInfo.pdgId[i]) == 521 && MCflag == 1) {
								gtk1idx = GenInfo.da2[i];
//								if(GenInfo.pt[gtk1idx] < 0.4) continue;								
								tk1.SetPtEtaPhiM(GenInfo.pt[gtk1idx], GenInfo.eta[gtk1idx], GenInfo.phi[gtk1idx], KAON_MASS);
								B = mu1+mu2+tk1;
								trueB.SetPtEtaPhiM(GenInfo.pt[i], GenInfo.eta[i], GenInfo.phi[i], GenInfo.mass[i]);
//								if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5)
								if(B.Eta() > -2.395 && B.Eta() < 1.465 && B.Mag() > 4.95 && B.Mag() < 5.55 && B.Pt() < 60 && B.Pt() > 5) {
//								if(1){
									geninfo_bidx.push_back(i);
									geninfo_mu1idx.push_back(gmu1idx);
									geninfo_mu2idx.push_back(gmu2idx);
									geninfo_tk1idx.push_back(gtk1idx);
									total_gen_bsig++;
									eta_total_gen_bsig++;
//									gen_bsig_pt->Fill(GenInfo.pt[i]);
									gen_bsig_pt->Fill(B.Pt());
//									gen_bsig_eta->Fill(GenInfo.eta[i]);
									gen_bsig_eta->Fill(B.Eta());

									if(fabs(GenInfo.eta[i]+0.465) < 1.93)gen_sig_eta->Fill(GenInfo.eta[i]);
									if(fabs(GenInfo.eta[i]+0.465) < 1.93)gen_dauSum_eta->Fill(B.Eta());
									if(fabs(B.Rapidity()+0.465) < 1.93)gen_sig_y->Fill(B.Rapidity());
									if(fabs(trueB.Rapidity()+0.465) < 1.93)gen_dauSum_y->Fill(trueB.Rapidity());
								}
							}
							//Kp
							//K*
							if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 313 && abs(GenInfo.pdgId[i]) == 511 && MCflag == 2) {
								if( (abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 321 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 211) ||
									(abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 211 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 321) 
								){
									gtk1idx = GenInfo.da1[GenInfo.da2[i]];
									gtk2idx = GenInfo.da2[GenInfo.da2[i]];
//									if(GenInfo.pt[gtk1idx] < 0.4) continue;								
//									if(GenInfo.pt[gtk2idx] < 0.4) continue;								
									if((abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 321)){
										tk1.SetPtEtaPhiM(GenInfo.pt[gtk1idx], GenInfo.eta[gtk1idx], GenInfo.phi[gtk1idx], KAON_MASS);
										tk2.SetPtEtaPhiM(GenInfo.pt[gtk2idx], GenInfo.eta[gtk2idx], GenInfo.phi[gtk2idx], PION_MASS);
									}
									else {
										tk1.SetPtEtaPhiM(GenInfo.pt[gtk1idx], GenInfo.eta[gtk1idx], GenInfo.phi[gtk1idx], PION_MASS);
										tk2.SetPtEtaPhiM(GenInfo.pt[gtk2idx], GenInfo.eta[gtk2idx], GenInfo.phi[gtk2idx], KAON_MASS);
									}
									B = mu1+mu2+tk1+tk2;
//									if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5) 
									if(B.Eta() > -2.395 && B.Eta() < 1.465 && B.Mag() > 4.95 && B.Mag() < 5.55 && B.Pt() < 60 && B.Pt() > 5) {
										geninfo_bidx.push_back(i);
										geninfo_mu1idx.push_back(gmu1idx);
										geninfo_mu2idx.push_back(gmu2idx);
										geninfo_tk1idx.push_back(gtk1idx);
										geninfo_tk2idx.push_back(gtk2idx);
										total_gen_bsig++;
										eta_total_gen_bsig++;
										gen_bsig_pt->Fill(B.Pt());
										gen_bsig_eta->Fill(B.Eta());
									}
								}
							}
							//K*
							//Phi
							if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 333 && abs(GenInfo.pdgId[i]) == 531 && MCflag == 3) {
								if( (abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 321 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 321)){
									gtk1idx = GenInfo.da1[GenInfo.da2[i]];
									gtk2idx = GenInfo.da2[GenInfo.da2[i]];
//									if(GenInfo.pt[gtk1idx] < 0.4) continue;								
//									if(GenInfo.pt[gtk2idx] < 0.4) continue;								
									tk1.SetPtEtaPhiM(GenInfo.pt[gtk1idx], GenInfo.eta[gtk1idx], GenInfo.phi[gtk1idx], KAON_MASS);
									tk2.SetPtEtaPhiM(GenInfo.pt[gtk2idx], GenInfo.eta[gtk2idx], GenInfo.phi[gtk2idx], KAON_MASS);
									B = mu1+mu2+tk1+tk2;
//									if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5) 
									if(B.Eta() > -2.395 && B.Eta() < 1.465 && B.Mag() > 4.95 && B.Mag() < 5.55 && B.Pt() < 60 && B.Pt() > 5) {
										geninfo_bidx.push_back(i);
										geninfo_mu1idx.push_back(gmu1idx);
										geninfo_mu2idx.push_back(gmu2idx);
										geninfo_tk1idx.push_back(gtk1idx);
										geninfo_tk2idx.push_back(gtk2idx);
										total_gen_bsig++;
										eta_total_gen_bsig++;
										gen_bsig_pt->Fill(B.Pt());
										gen_bsig_eta->Fill(B.Eta());
									}
								}
							}
							//Phi
						}
					}
				}
			}	
		}
		if(geninfo_bidx.size() > 1) {
			printf("Got %lu B gen signal in one event\n", geninfo_bidx.size());
			printf("%i, %i, %i, %i, %i, %i\n", geninfo_bidx[0], GenInfo.pdgId[geninfo_bidx[0]], GenInfo.pdgId[GenInfo.da1[geninfo_bidx[0]]], GenInfo.pdgId[GenInfo.da2[geninfo_bidx[0]]], 
			GenInfo.pdgId[GenInfo.da1[GenInfo.da1[geninfo_bidx[0]]]], GenInfo.pdgId[GenInfo.da2[GenInfo.da1[geninfo_bidx[0]]]]);
			printf("%i, %i, %i, %i, %i, %i\n", geninfo_bidx[1], GenInfo.pdgId[geninfo_bidx[1]], GenInfo.pdgId[GenInfo.da1[geninfo_bidx[1]]], GenInfo.pdgId[GenInfo.da2[geninfo_bidx[1]]],
			GenInfo.pdgId[GenInfo.da1[GenInfo.da1[geninfo_bidx[1]]]], GenInfo.pdgId[GenInfo.da2[GenInfo.da1[geninfo_bidx[1]]]]);	
		}
		//if(bsig_genidx.size() > 0) printf("reco true bsig: %i, gen bsig : %i\n", bsig_genidx.size(), geninfo_bidx.size());
//////GEN
/////RECO		
		int mu1idx = -1;
		int mu2idx = -1;
		int tk1idx = -1;
		int tk2idx = -1;
		int jpidx = -1;
		int mu1genidx = -1;
		int mu2genidx = -1;
		int tk1genidx = -1;
		int tk2genidx = -1;
		int jpgenidx = -1;
		vector<int> bsig_genidx;

		TVector3 PV;
		PV.SetXYZ(EvtInfo.PVx, EvtInfo.PVy, EvtInfo.PVz);
		TVector3 JpsiVtx;
		TVector3 deltaJpsiPV;

		if(!HLT_PAMu3_v1) continue;
		int Ngenbsig = 0;
		for(int i = 0; i < BInfo.size; i++){
			if(MCflag == 1) if(BInfo.type[i] != 1) continue;
			if(MCflag == 2) if(BInfo.type[i] != 4 && BInfo.type[i] != 5) continue;
			if(MCflag == 3) if(BInfo.type[i] != 6) continue;
			
			bool jp_sig = 0; 
			bool bsig = 0;		
			jpidx = BInfo.rfuj_index[i];
			tk1idx = BInfo.rftk1_index[i];
			tk2idx = BInfo.rftk2_index[i];
			mu1idx = BInfo.uj_rfmu1_index[jpidx];
			mu2idx = BInfo.uj_rfmu2_index[jpidx];
			mu1genidx = MuonInfo.geninfo_index[mu1idx];
			mu2genidx = MuonInfo.geninfo_index[mu2idx];
			tk1genidx = TrackInfo.geninfo_index[tk1idx];
			tk2genidx = TrackInfo.geninfo_index[tk2idx];
			jpgenidx = GenInfo.mo1[mu1genidx];

			//match to gen level
			bool match2gen = false;
			for(unsigned int gi = 0; gi < geninfo_mu1idx.size(); gi++){
				if(
				   mu1genidx == geninfo_mu1idx[gi] &&
				   mu2genidx == geninfo_mu2idx[gi] &&
				   tk1genidx == geninfo_tk1idx[gi]
				) {
					if(MCflag == 1) match2gen = true;
				    if(MCflag == 2) {
						if(tk2genidx == geninfo_tk2idx[gi]) {
							if(BInfo.type[i] == 4 && abs(GenInfo.pdgId[tk1genidx]) == 321) match2gen = true;
							if(BInfo.type[i] == 5 && abs(GenInfo.pdgId[tk1genidx]) == 211) match2gen = true;
						}
					}
				    if(MCflag == 3) if(tk2genidx == geninfo_tk2idx[gi]) match2gen = true;
				}
//				printf("-----%i, %i, %i\n", geninfo_mu1idx[gi], geninfo_mu2idx[gi], geninfo_tk1idx[gi]);
			}
//				printf("%i, %i, %i\n", mu1genidx, mu2genidx, tk1genidx);
			if(!match2gen) continue;

			bool pass = 1;
            CutLevel->Fill(0);

			//Selections
			//Muon
			if(MuonInfo.i_striphit[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] <= 5 ||
			   MuonInfo.i_striphit[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] <= 5) pass = 0;
            if (pass == 1)CutLevel->Fill(1);;

			if(MuonInfo.i_pixelhit[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] <= 1 ||
			   MuonInfo.i_pixelhit[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] <= 1) pass = 0;
            if (pass == 1) CutLevel->Fill(2);

			if(MuonInfo.i_chi2[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]]/MuonInfo.i_ndf[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 1.8 ||
			   MuonInfo.i_chi2[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]]/MuonInfo.i_ndf[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 1.8) pass = 0;
            if (pass == 1) CutLevel->Fill(3);

			if(MuonInfo.dxyPV[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 3.0 ||
			   MuonInfo.dxyPV[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 3.0) pass = 0;
            if (pass == 1) CutLevel->Fill(4);

			if(MuonInfo.dzPV[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 30. ||
			   MuonInfo.dzPV[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 30.) pass = 0;
            if (pass == 1) CutLevel->Fill(5);

			if(!(MuonInfo.muqual[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] & 4096) ||
			   !(MuonInfo.muqual[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] & 4096)) pass = 0;
            if (pass == 1) CutLevel->Fill(6);

			if(!(MuonInfo.muqual[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] & 16) ||
			   !(MuonInfo.muqual[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] & 16)) pass = 0;
            if (pass == 1) CutLevel->Fill(7);

			//Jpsi
			if(TMath::Prob(BInfo.uj_vtxchi2[BInfo.rfuj_index[i]],BInfo.uj_vtxdof[BInfo.rfuj_index[i]]) <= 0.01) pass = 0;
            if (pass == 1) CutLevel->Fill(8);

			JpsiVtx.SetXYZ(BInfo.uj_vtxX[BInfo.rfuj_index[i]], BInfo.uj_vtxY[BInfo.rfuj_index[i]], BInfo.uj_vtxZ[BInfo.rfuj_index[i]]);
			JpsiVtx =PV-JpsiVtx;
			float JpsiCt = JpsiVtx.Mag()*JPSI_MASS/BInfo.uj_pt[BInfo.rfuj_index[i]];
			if(JpsiCt <= 0.15 ) pass = 0;
            if (pass == 1) CutLevel->Fill(9);

			//Track
			if(TrackInfo.striphit[BInfo.rftk1_index[i]] <= 3) pass = 0;
            if (pass == 1) CutLevel->Fill(10);

			if(TrackInfo.pixelhit[BInfo.rftk1_index[i]] <= 0) pass = 0;
            if (pass == 1) CutLevel->Fill(11);

			if(TrackInfo.chi2[BInfo.rftk1_index[i]]/TrackInfo.ndf[BInfo.rftk1_index[i]] >= 5) pass = 0;
            if (pass == 1) CutLevel->Fill(12);

			if(TMath::Prob(TrackInfo.chi2[BInfo.rftk1_index[i]],TrackInfo.ndf[BInfo.rftk1_index[i]]) <= 0.001) pass = 0;
            if (pass == 1) CutLevel->Fill(13);

			if(TrackInfo.pt[BInfo.rftk1_index[i]] <= 2.) pass = 0;
            if (pass == 1) CutLevel->Fill(14);

			if(MCflag != 1){
				if(TrackInfo.striphit[BInfo.rftk2_index[i]] <= 3) pass = 0;
				if(TrackInfo.pixelhit[BInfo.rftk2_index[i]] <= 0) pass = 0;
				if(TrackInfo.chi2[BInfo.rftk2_index[i]]/TrackInfo.ndf[BInfo.rftk2_index[i]] >= 5) pass = 0;
				if(TMath::Prob(TrackInfo.chi2[BInfo.rftk2_index[i]],TrackInfo.ndf[BInfo.rftk2_index[i]]) <= 0.001) pass = 0;
				if(TrackInfo.pt[BInfo.rftk2_index[i]] <= 2.) pass = 0;
			}

			//Triplet mass 4.95~5.5
			TLorentzVector LVmu1, LVmu2, LVtk1, LVtk2, LVtheB;
			LVmu1.SetPtEtaPhiM(MuonInfo.pt[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], MuonInfo.eta[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], MuonInfo.phi[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], 0.10565837);
			LVmu2.SetPtEtaPhiM(MuonInfo.pt[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], MuonInfo.eta[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], MuonInfo.phi[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], 0.10565837);

			double tk1_mass = 0;
			double tk2_mass = 0;
			if(MCflag == 1) tk1_mass = 0.493677;
			if(MCflag == 2 && BInfo.type[i] == 4) tk1_mass = 0.493677;
			if(MCflag == 2 && BInfo.type[i] == 4) tk2_mass = 0.13957018;
			if(MCflag == 2 && BInfo.type[i] == 5) tk1_mass = 0.13957018;
			if(MCflag == 2 && BInfo.type[i] == 5) tk2_mass = 0.493677;
			if(MCflag == 3) tk1_mass = 0.493677;
			if(MCflag == 3) tk2_mass = 0.493677;

			LVtk1.SetPtEtaPhiM(TrackInfo.pt[BInfo.rftk1_index[i]], TrackInfo.eta[BInfo.rftk1_index[i]], TrackInfo.phi[BInfo.rftk1_index[i]], tk1_mass);
			LVtk2.SetPtEtaPhiM(TrackInfo.pt[BInfo.rftk2_index[i]], TrackInfo.eta[BInfo.rftk2_index[i]], TrackInfo.phi[BInfo.rftk2_index[i]], tk2_mass);

			if(MCflag == 1) {
				LVtheB = mu1+mu2+tk1;
				if(LVtheB.M() < 4.6 || LVtheB.M() > 6.0) pass = 0;
	            if (pass == 1) CutLevel->Fill(15);
			}
			
			if(MCflag == 2 || MCflag == 3) {
				LVtheB = mu1+mu2+tk1+tk2;
				if(LVtheB.M() < 4.6 || LVtheB.M() > 6.0) pass = 0;
            	if (pass == 1) CutLevel->Fill(15);
			}

			//Selections
//			if(!pass) continue;
//			pif(BInfo.pt[i] < 10) continue;
			if(BInfo.pt[i] > 60 || BInfo.pt[i] < 5)	continue;
			if(BInfo.eta[i] < etaBins[0] || BInfo.eta[i] > etaBins[nEtaBins]) continue;

//			reco_bsig_eta->Fill(GenInfo.eta[GenInfo.mo1[jpgenidx]]);
			
			float effWeight = 1;
			if (useDataDrivenEff) {
			  effWeight = getEffWeight( true,
						    MuonInfo.pt[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], 
						    MuonInfo.eta[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]],
						    MuonInfo.pt[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], 
						    MuonInfo.eta[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]]		    );
			}
			
			
			reco_bsig_eta->Fill(BInfo.eta[i],effWeight);
			eta_total_reco_true_bsig++;
			reco_bsig_pt->Fill(BInfo.pt[i],effWeight);
			bsig_genidx.push_back(GenInfo.mo1[jpgenidx]);
			total_reco_true_bsig++;

			//printf("a jp sig %i, %i, %i, %i, %i\n", mu1genidx, mu2genidx, GenInfo.mo1[mu1genidx], GenInfo.mo1[mu2genidx], GenInfo.pdgId[jpgenidx]);
			//Stage2 selections
			double chi2cl = TMath::Prob(BInfo.vtxchi2[i],BInfo.vtxdof[i]); 
			double d0 = sqrt((BInfo.vtxX[i]-EvtInfo.PVx)*(BInfo.vtxX[i]-EvtInfo.PVx)+(BInfo.vtxY[i]-EvtInfo.PVy)*(BInfo.vtxY[i]-EvtInfo.PVy));
			double d0Err = sqrt(BInfo.vtxXE[i]*BInfo.vtxXE[i]+BInfo.vtxYE[i]*BInfo.vtxYE[i]);
			TVector3 bP;
			TVector3 bVtx;
			bP.SetXYZ(BInfo.px[i],BInfo.py[i],BInfo.pz[i]*0);
			bVtx.SetXYZ(BInfo.vtxX[i]-EvtInfo.PVx, BInfo.vtxY[i]-EvtInfo.PVy, BInfo.vtxZ[i]*0-EvtInfo.PVz*0); 
			double dtheta = bP.Angle(bVtx);
			double trk1Dxy = TrackInfo.dxyPV[BInfo.rftk1_index[i]];
			double trk1D0Err = TrackInfo.d0error[BInfo.rftk1_index[i]]; 
			double tktkmass = BInfo.tktk_mass[i]; 
			int stage2 = 0;
			
			if(MCflag == 1) {
				if(chi2cl>5.5e-03) { optc1++; stage2++;}
				if((d0)/d0Err>3.3e00) { optc2++; stage2++;}
 				if(cos(dtheta)>-0.53) { optc3++; stage2++;}
 				if(TMath::Abs((trk1Dxy)/trk1D0Err)>1.9) { optc4++;stage2++;}
				if(1) { optc5++; stage2++;}
			}
			if(MCflag == 2) {
				if(chi2cl>0.15) { optc1++; stage2++;}
				if((d0)/d0Err>8.1) { optc2++; stage2++;}
 				if(cos(dtheta)>-0.44) { optc3++; stage2++;}
 				if(TMath::Abs((trk1Dxy)/trk1D0Err)>0.81) { optc4++;stage2++;}
				if(TMath::Abs(tktkmass-0.89591)<0.140) { optc5++; stage2++;}
			}
			if(MCflag == 3) {
				if(chi2cl>3.8e-02) { optc1++; stage2++;}
				if((d0)/d0Err>3.2e+00) { optc2++; stage2++;}
 				if(cos(dtheta)>7.4e-01) { optc3++; stage2++;}
 				if(TMath::Abs((trk1Dxy)/trk1D0Err)>1.3e+00) { optc4++;stage2++;}
				if(TMath::Abs(tktkmass-1.01944)<1.5e-02) { optc5++; stage2++;}
			}
			if(stage2==5){
			  reco_bsig_eta_stage2->Fill(BInfo.eta[i],effWeight);
				eta_total_reco_true_bsig_stage2++;
				reco_bsig_pt_stage2->Fill(BInfo.pt[i],effWeight);
				total_reco_true_bsig_stage2++;
			}

		}
		if(bsig_genidx.size() > 1) printf("Got %lu B signal in one event\n", bsig_genidx.size());
//////RECO
	}//looping events

	printf("eta: %.0f, %.0f, %.0f\n", eta_total_reco_true_bsig_stage2, eta_total_reco_true_bsig, eta_total_gen_bsig);
	printf("pt : %.0f, %.0f, %.0f\n", total_reco_true_bsig_stage2, total_reco_true_bsig, total_gen_bsig);
	printf("base: %.4f\n", total_reco_true_bsig/total_gen_bsig);
	printf("opt1: %.4f\n", optc1/eta_total_reco_true_bsig);
	printf("opt2: %.4f\n", optc2/eta_total_reco_true_bsig);
	printf("opt3: %.4f\n", optc3/eta_total_reco_true_bsig);
	printf("opt4: %.4f\n", optc4/eta_total_reco_true_bsig);
	printf("opt5: %.4f\n", optc5/eta_total_reco_true_bsig);
//	TH1F *reco_gen_eff_pt = (TH1F*)reco_bsig_pt->Clone("reco/gen eff pt kp");
//	reco_gen_eff_pt->Divide(gen_bsig_pt);

	TEfficiency *reco_gen_eff_pt = new TEfficiency(*reco_bsig_pt, *gen_bsig_pt);
	TEfficiency *reco_gen_eff_eta = new TEfficiency(*reco_bsig_eta, *gen_bsig_eta);

	TEfficiency *reco_gen_eff_pt_stage2 = new TEfficiency(*reco_bsig_pt_stage2, *reco_bsig_pt);
	TEfficiency *reco_gen_eff_eta_stage2 = new TEfficiency(*reco_bsig_eta_stage2, *reco_bsig_eta);

	if(MCflag == 1){
		reco_gen_eff_pt->SetTitle("eff base, K+ channel");
		reco_gen_eff_eta->SetTitle("eff base, K+ channel");
		reco_gen_eff_pt_stage2->SetTitle("eff opt, K+ channel");
		reco_gen_eff_eta_stage2->SetTitle("eff opt, K+ channel");
	}
	if(MCflag == 2){
		reco_gen_eff_pt->SetTitle("eff base, K* channel");
		reco_gen_eff_eta->SetTitle("eff base, K* channel");
		reco_gen_eff_pt_stage2->SetTitle("eff opt, K* channel");
		reco_gen_eff_eta_stage2->SetTitle("eff opt, K* channel");
	}
	if(MCflag == 3){
		reco_gen_eff_pt->SetTitle("eff base, #phi channel");
		reco_gen_eff_eta->SetTitle("eff base, #phi channel");
		reco_gen_eff_pt_stage2->SetTitle("eff opt, #phi channel");
		reco_gen_eff_eta_stage2->SetTitle("eff opt, #phi channel");
	}

	for(int i = 0; i < reco_bsig_pt->GetNbinsX(); i ++){
		printf("bin content pt: %.0f, %.0f\n", reco_bsig_pt->GetBinContent(i+1), gen_bsig_pt->GetBinContent(i+1));
	}

	c1->cd();
	reco_gen_eff_pt->SetFillColor(2);
	reco_gen_eff_pt->SetFillStyle(3001);
	reco_gen_eff_pt->Draw("");
	c1->Update();
	reco_gen_eff_pt->GetPaintedGraph()->GetXaxis()->SetTitle("pt[GeV]");
	reco_gen_eff_pt->Draw("a2");
	reco_gen_eff_pt->Draw("same");
	reco_gen_eff_pt->Write();
	c1->Write();

	c3->cd();
	reco_gen_eff_pt_stage2->SetFillColor(2);
	reco_gen_eff_pt_stage2->SetFillStyle(3001);
	reco_gen_eff_pt_stage2->Draw("");
	c3->Update();
	reco_gen_eff_pt_stage2->GetPaintedGraph()->GetXaxis()->SetTitle("pt[GeV]");
	reco_gen_eff_pt_stage2->Draw("a2");
	reco_gen_eff_pt_stage2->Draw("same");
	reco_gen_eff_pt_stage2->Write();
	c3->Write();

	for(int i = 0; i < reco_bsig_eta->GetNbinsX(); i ++){
		printf("bincontent eta: %.0f, %.0f\n", reco_bsig_eta->GetBinContent(i+1), gen_bsig_eta->GetBinContent(i+1));
	}	

	c2->cd();
	reco_gen_eff_eta->SetFillColor(2);
	reco_gen_eff_eta->SetFillStyle(3001);
	reco_gen_eff_eta->Draw("");
	c2->Update();
	reco_gen_eff_eta->GetPaintedGraph()->GetXaxis()->SetTitle("eta");
	reco_gen_eff_eta->Draw("a2");
	reco_gen_eff_eta->Draw("same");
	reco_gen_eff_eta->Write();
	c2->Write();

	c4->cd();
	reco_gen_eff_eta_stage2->SetFillColor(2);
	reco_gen_eff_eta_stage2->SetFillStyle(3001);
	reco_gen_eff_eta_stage2->Draw("");
	c4->Update();
	reco_gen_eff_eta_stage2->GetPaintedGraph()->GetXaxis()->SetTitle("eta");
	reco_gen_eff_eta_stage2->Draw("a2");
	reco_gen_eff_eta_stage2->Draw("same");
	reco_gen_eff_eta_stage2->Write();
	c4->Write();

	CutLevel->Scale(1./CutLevel->GetBinContent(1));
    fout->Write();
    fout->Close();
	if(MCflag == 1){
		c1->SaveAs("fig_effstage1/kp_pt_eff.pdf");
		c2->SaveAs("fig_effstage1/kp_eta_eff.pdf");
		c3->SaveAs("fig_effstage2/kp_pt_eff.pdf");
		c4->SaveAs("fig_effstage2/kp_eta_eff.pdf");
	}
	if(MCflag == 2){
		c1->SaveAs("fig_effstage1/kstar_pt_eff.pdf");
		c2->SaveAs("fig_effstage1/kstar_eta_eff.pdf");
		c3->SaveAs("fig_effstage2/kstar_pt_eff.pdf");
		c4->SaveAs("fig_effstage2/kstar_eta_eff.pdf");
	}
	if(MCflag == 3){
		c1->SaveAs("fig_effstage1/phi_pt_eff.pdf");
		c2->SaveAs("fig_effstage1/phi_eta_eff.pdf");
		c3->SaveAs("fig_effstage2/phi_pt_eff.pdf");
		c4->SaveAs("fig_effstage2/phi_eta_eff.pdf");
	}
}//main


float getEffWeight(bool isBoosted,  float mupt1, float mueta1, float mupt2, float mueta2) {
  float mup1 = mupt1* cosh(mueta1);
  float mup2 = mupt2* cosh(mueta2);

  if ( kineCut( isBoosted, mupt1, mueta1, mup1)==false)
    return 0;
  if ( kineCut( isBoosted, mupt2, mueta2, mup2)==false)
    return 0;

  TH1D* hw1;
  TH1D* hw2;
  if ( mueta1 < -1.47 )   hw1 = hEffCorr1;
  else if ( mueta1 < 0.28 )   hw1 = hEffCorr2;
  else    hw1 = hEffCorr3;
  if ( mueta2 < -1.47 )   hw2 = hEffCorr1;
  else if ( mueta2 < 0.28 )   hw2 = hEffCorr2;
  else    hw2 = hEffCorr3;

  int bin1 = hw1->FindBin(mupt1);
  int bin2 = hw1->FindBin(mupt2);

  float effWeight1 = hw1->GetBinContent(bin1);
  float effWeight2 = hw1->GetBinContent(bin2);
  return effWeight1 * effWeight2;
}



bool kineCut(bool isBoosted, double muPt, double muEta, double muP) {

  if(muEta<-2.4 || muEta>=1.93)
    //      if(muEta<-2.4 || muEta>=2.4) //single muon eta cut
    {return false;}
  else if(TMath::Abs(muEta)>=2.2 && TMath::Abs(muEta)<2.4 && muPt<=0.8)
    {return false;}
  else if(TMath::Abs(muEta)>=1.3 && TMath::Abs(muEta)<2.2 && muP<=2.9)
    {return false;}
  else if(TMath::Abs(muEta)<1.3 && muPt<=3.3)
    {return false;}

  else {return true;}

}
