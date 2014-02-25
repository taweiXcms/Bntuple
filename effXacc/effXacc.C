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
//#include "~/HeavyFlavor_20131030/Bfinder/CMSSW_5_3_8_patch3/src/Bfinder/Bfinder/interface/format.h"
#include "/net/hisrv0001/home/tawei/HeavyFlavor_20131030/Bfinder/CMSSW_5_3_8_patch3/src/Bfinder/Bfinder/interface/format.h"

#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916
#define PSI2S_MASS  3.686109
   
void effXacc(){

//Setting the corresponding channel
	int MCflag = 1;//K+
//	MCflag = 2;//K*
//	MCflag = 3;//Phi
	TFile* fout;
	if(MCflag == 1){
//		fout = new TFile("fout_kp.root","recreate");
//		fout = new TFile("fout_kp_temp.root","recreate");
		fout = new TFile("fout_kp_cutted.root","recreate");
//		fout = new TFile("fout_kp_temp_cutted.root","recreate");
	}
	if(MCflag == 2){
		fout = new TFile("fout_kstar.root","recreate");
	}
	if(MCflag == 3){
		fout = new TFile("fout_phi.root","recreate");
	}
	TCanvas*c1 = new TCanvas("c1", "", 200, 10, 1000, 800);

	TChain *root = new TChain("demo/root");
	if(MCflag == 1)
		root->Add("../../Bfinder_all_full_20140215/Bfinder_all_MC_Kp.root");
//		root->Add("~/HeavyFlavor_20131030/Bfinder/CMSSW_5_3_8_patch3/src/Bfinder/PyquenMix_STARTHI53_V27_embedHIJING_boostedMC_GEN_SIM_DIGI_RECO_Bp2JpsiKp_Bpt5_5TeV_v1/Bfinder_all.root");
	if(MCflag == 2)
		root->Add("../../Bfinder_all_full_20140215/Bfinder_all_MC_Kstar.root");
	if(MCflag == 3)
		root->Add("../../Bfinder_all_full_20140215/Bfinder_all_MC_Phi.root");
	
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
	
	const int nBins = 6;
    double ptBins[nBins+1] = {5,10,15,20,25,30,60};
	TH1F* reco_bsig_pt = new TH1F("reco bsig pt", "", nBins,ptBins);
	TH1F* gen_bsig_pt = new TH1F("gen bsig pt", "", nBins,ptBins);
	TH1F* CutLevel = new TH1F("cutlevel", "cutlevel", 20, 0, 20);
		
	int total_reco_true_bsig = 0;
	int total_gen_bsig = 0;

    int nevents_total = root->GetEntries();
	for(int entry=0; entry<nevents_total; entry++){
//	for(int entry=0; entry<9979; entry++){
    	if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
        root->GetEntry(entry);
		
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

		int Ngenbsig = 0;
		for(int i = 0; i < BInfo.size; i++){
			
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

			bool pass = 1;
			int clevel = 0;
            CutLevel->Fill(clevel);clevel++;//0

			//Selections
			//Muon
			if(MuonInfo.i_striphit[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] <= 5 ||
			   MuonInfo.i_striphit[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] <= 5) pass = 0;
            else CutLevel->Fill(clevel);clevel++;//1

			if(MuonInfo.i_pixelhit[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] <= 1 ||
			   MuonInfo.i_pixelhit[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] <= 1) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//2

			if(MuonInfo.i_chi2[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]]/MuonInfo.i_ndf[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 1.8 ||
			   MuonInfo.i_chi2[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]]/MuonInfo.i_ndf[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 1.8) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//3

			if(MuonInfo.dxyPV[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 3.0 ||
			   MuonInfo.dxyPV[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 3.0) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//4

			if(MuonInfo.dzPV[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] >= 30. ||
			   MuonInfo.dzPV[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] >= 30.) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//5

			if(!(MuonInfo.muqual[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] & 4096) ||
			   !(MuonInfo.muqual[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] & 4096)) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//6

			if(!(MuonInfo.muqual[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]] & 16) ||
			   !(MuonInfo.muqual[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]] & 16)) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//7

			//Jpsi
			if(TMath::Prob(BInfo.uj_vtxchi2[BInfo.rfuj_index[i]],BInfo.uj_vtxdof[BInfo.rfuj_index[i]]) <= 0.01) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//8

			JpsiVtx.SetXYZ(BInfo.uj_vtxX[BInfo.rfuj_index[i]], BInfo.uj_vtxY[BInfo.rfuj_index[i]], BInfo.uj_vtxZ[BInfo.rfuj_index[i]]);
			JpsiVtx =PV-JpsiVtx;
			float JpsiCt = JpsiVtx.Mag()*JPSI_MASS/BInfo.uj_pt[BInfo.rfuj_index[i]];
			if(JpsiCt <= 0.15 ) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//9

			//Track
			if(TrackInfo.striphit[BInfo.rftk1_index[i]] <= 3) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//10

			if(TrackInfo.pixelhit[BInfo.rftk1_index[i]] <= 0) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//11

			if(TrackInfo.chi2[BInfo.rftk1_index[i]]/TrackInfo.ndf[BInfo.rftk1_index[i]] >= 5) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//12

			if(TMath::Prob(TrackInfo.chi2[BInfo.rftk1_index[i]],TrackInfo.ndf[BInfo.rftk1_index[i]]) <= 0.001) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//13

			if(TrackInfo.pt[BInfo.rftk1_index[i]] <= 2.) pass = 0;
            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//14

			if(MCflag != 1){
				if(TrackInfo.striphit[BInfo.rftk2_index[i]] <= 3) pass = 0;
				if(TrackInfo.pixelhit[BInfo.rftk2_index[i]] <= 0) pass = 0;
				if(TrackInfo.chi2[BInfo.rftk2_index[i]]/TrackInfo.ndf[BInfo.rftk2_index[i]] >= 5) pass = 0;
				if(TMath::Prob(TrackInfo.chi2[BInfo.rftk2_index[i]],TrackInfo.ndf[BInfo.rftk2_index[i]]) <= 0.001) pass = 0;
				if(TrackInfo.pt[BInfo.rftk2_index[i]] <= 2.) pass = 0;
			}

			//Triplet mass 4.95~5.5
			TLorentzVector mu1, mu2, tk1, tk2, theB;
			mu1.SetPtEtaPhiM(MuonInfo.pt[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], MuonInfo.eta[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], MuonInfo.phi[BInfo.uj_rfmu1_index[BInfo.rfuj_index[i]]], 0.10565837);
			mu2.SetPtEtaPhiM(MuonInfo.pt[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], MuonInfo.eta[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], MuonInfo.phi[BInfo.uj_rfmu2_index[BInfo.rfuj_index[i]]], 0.10565837);

			double tk1_mass = 0;
			double tk2_mass = 0;
			if(MCflag == 1) tk1_mass = 0.493677;
			if(MCflag == 2 && BInfo.type[i] == 4) tk1_mass = 0.493677;
			if(MCflag == 2 && BInfo.type[i] == 4) tk2_mass = 0.13957018;
			if(MCflag == 2 && BInfo.type[i] == 5) tk1_mass = 0.13957018;
			if(MCflag == 2 && BInfo.type[i] == 5) tk2_mass = 0.493677;
			if(MCflag == 3) tk1_mass = 0.493677;
			if(MCflag == 3) tk2_mass = 0.493677;

			tk1.SetPtEtaPhiM(TrackInfo.pt[BInfo.rftk1_index[i]], TrackInfo.eta[BInfo.rftk1_index[i]], TrackInfo.phi[BInfo.rftk1_index[i]], tk1_mass);
			tk2.SetPtEtaPhiM(TrackInfo.pt[BInfo.rftk2_index[i]], TrackInfo.eta[BInfo.rftk2_index[i]], TrackInfo.phi[BInfo.rftk2_index[i]], tk2_mass);

			if(MCflag == 1) {
				theB = mu1+mu2+tk1;
				if(theB.M() < 4.6 || theB.M() > 6.0) pass = 0;
	            else if (pass == 1) CutLevel->Fill(clevel);clevel++;//15
			}
			
			if(MCflag == 2 || MCflag == 3) {
				theB = mu1+mu2+tk1+tk2;
				if(theB.M() < 4.6 || theB.M() > 6.0) pass = 0;
            	else if (pass == 1) CutLevel->Fill(clevel);clevel++;//15
			}

			//Selections
			if(!pass) continue;

			if(abs(GenInfo.pdgId[mu1genidx]) == 13 && abs(GenInfo.pdgId[mu2genidx]) == 13) {//both reco mu are gen mu
				if(GenInfo.nMo[mu1genidx] > 0 && GenInfo.nMo[mu2genidx] > 0){//both gen mu has at least 1 mother
					if(GenInfo.mo1[mu1genidx] == GenInfo.mo1[mu2genidx] && GenInfo.pdgId[jpgenidx] == 443){//gem mom are the same and being jpsi
						jp_sig = 1;
					}
				}
			}
			//printf("a jp sig %i, %i, %i, %i, %i\n", mu1genidx, mu2genidx, GenInfo.mo1[mu1genidx], GenInfo.mo1[mu2genidx], GenInfo.pdgId[jpgenidx]);
			//Kp
			if(BInfo.type[i] == 1 && jp_sig && MCflag == 1){
				if(abs(GenInfo.pdgId[tk1genidx]) == 321){//reco tk is gen K+
					if(abs(GenInfo.pdgId[GenInfo.mo1[jpgenidx]]) == 521)//gen jpsi from B+
					if(abs(GenInfo.pdgId[GenInfo.mo1[tk1genidx]]) == 521)//gen K+ from B+
					if(GenInfo.mo1[jpgenidx] == GenInfo.mo1[tk1genidx]){//gen jpsi and gen K+ have same mom
						bsig_genidx.push_back(GenInfo.mo1[jpgenidx]);
						total_reco_true_bsig++;
						if(fabs(BInfo.eta[i]) < 1.93 && BInfo.pt[i] > 5) 
							reco_bsig_pt->Fill(BInfo.pt[i]);
					}
				}
			}
			//Kp
			//K*
			if((BInfo.type[i] == 4 || BInfo.type[i] == 5) && jp_sig && MCflag == 2){
			//printf("%i, %i, %i, %i, %i, %i\n", entry, BInfo.type[i], GenInfo.pdgId[tk1genidx], GenInfo.pdgId[tk2genidx], tk1genidx, tk2genidx);
				if( ( BInfo.type[i] == 4 && GenInfo.pdgId[tk1genidx] == 321 && GenInfo.pdgId[tk2genidx] == -211) || 
					( BInfo.type[i] == 5 && GenInfo.pdgId[tk1genidx] == 211 && GenInfo.pdgId[tk2genidx] == -321)
					//if( ( BInfo.type[i] == 5 && GenInfo.pdgId[tk1genidx] == 321 && GenInfo.pdgId[tk2genidx] == -211) || 
					//	( BInfo.type[i] == 4 && GenInfo.pdgId[tk1genidx] == 211 && GenInfo.pdgId[tk2genidx] == -321)//this is K/pi miss reconstruction
					//if( ( abs(GenInfo.pdgId[tk1genidx]) == 321 && abs(GenInfo.pdgId[tk2genidx]) == 211) || 
					//	( abs(GenInfo.pdgId[tk1genidx]) == 211 && abs(GenInfo.pdgId[tk2genidx]) == 321)
					){//a pi and a K, note that channel 4: -K and +pi / channel 5: +K and -pi
					if(GenInfo.nMo[tk1genidx] > 0 && GenInfo.nMo[tk2genidx] > 0)//both has mom >1
					if(abs(GenInfo.pdgId[GenInfo.mo1[tk1genidx]]) == 313)//gen from K*
					if(GenInfo.mo1[tk1genidx] == GenInfo.mo1[tk2genidx])//pi, K have same mother
					if(GenInfo.nMo[GenInfo.mo1[tk1genidx]] > 0)//K* has mom >1
					if(abs(GenInfo.pdgId[GenInfo.mo1[GenInfo.mo1[tk1genidx]]]) == 511)//K* from Bd
					if(abs(GenInfo.pdgId[GenInfo.mo1[jpgenidx]]) == 511)//gen jpsi from Bd
					if(GenInfo.mo1[jpgenidx] == GenInfo.mo1[GenInfo.mo1[tk1genidx]]){//gen jpsi and gen K* have same mom
						bsig_genidx.push_back(GenInfo.mo1[jpgenidx]);
						total_reco_true_bsig++;
						if(fabs(BInfo.eta[i]) < 1.93 && BInfo.pt[i] > 5) 
							reco_bsig_pt->Fill(BInfo.pt[i]);
					}
				}
			}
			//K*
			//Phi
			if((BInfo.type[i] == 6) && jp_sig && MCflag == 3){
				if( ( abs(GenInfo.pdgId[tk1genidx]) == 321 && abs(GenInfo.pdgId[tk2genidx]) == 321) ){//two K
					if(GenInfo.nMo[tk1genidx] > 0 && GenInfo.nMo[tk2genidx] > 0)//both has mom >1
					if(abs(GenInfo.pdgId[GenInfo.mo1[tk1genidx]]) == 333)//gen from Phi
					if(GenInfo.mo1[tk1genidx] == GenInfo.mo1[tk2genidx])//two K have same mother
					if(GenInfo.nMo[GenInfo.mo1[tk1genidx]] > 0)//Phi has mom >1
					if(abs(GenInfo.pdgId[GenInfo.mo1[GenInfo.mo1[tk1genidx]]]) == 531)//Phi from Bs
					if(abs(GenInfo.pdgId[GenInfo.mo1[jpgenidx]]) == 531)//gen jpsi from Bs
					if(GenInfo.mo1[jpgenidx] == GenInfo.mo1[GenInfo.mo1[tk1genidx]]){//gen jpsi and gen Phi have same mom
						bsig_genidx.push_back(GenInfo.mo1[jpgenidx]);
						total_reco_true_bsig++;
						if(fabs(BInfo.eta[i]) < 1.93 && BInfo.pt[i] > 5) 
							reco_bsig_pt->Fill(BInfo.pt[i]);
					}
				}
			}
			//Phi
		}
		if(bsig_genidx.size() > 1) printf("Got %lu B signal in one event\n", bsig_genidx.size());

		vector<int> geninfo_bidx;
		for(int i = 0; i < GenInfo.size; i++){
			bool geninfo_jp = 0;
			if(abs(GenInfo.pdgId[i]) == 521 || abs(GenInfo.pdgId[i]) == 511 || abs(GenInfo.pdgId[i]) == 531){
				//printf("B+ da1 is %i\n", GenInfo.pdgId[GenInfo.da1[i]]);
				//printf("B+ da2 is %i\n", GenInfo.pdgId[GenInfo.da2[i]]);
				if(GenInfo.nDa[i] > 1)
				if(GenInfo.pdgId[GenInfo.da1[i]] == 443)//if has jpsi as ga, it must be da1
				if(abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da1[i]]]) == 13 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da1[i]]]) == 13)
				geninfo_jp = 1;

				//Kp
				if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 321 && abs(GenInfo.pdgId[i]) == 521 && MCflag == 1) {
					geninfo_bidx.push_back(i);
					total_gen_bsig++;
					if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5) 
						gen_bsig_pt->Fill(GenInfo.pt[i]);
			
				}
				//Kp
				//K*
				if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 313 && abs(GenInfo.pdgId[i]) == 511 && MCflag == 2) {
					if( (abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 321 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 211) ||
						(abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 211 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 321) 
					){
						geninfo_bidx.push_back(i);
						total_gen_bsig++;
						if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5) 
							gen_bsig_pt->Fill(GenInfo.pt[i]);
					}
			
				}
				//K*
				//Phi
				if(geninfo_jp == 1 && abs(GenInfo.pdgId[GenInfo.da2[i]]) == 333 && abs(GenInfo.pdgId[i]) == 531 && MCflag == 3) {
					if( (abs(GenInfo.pdgId[GenInfo.da1[GenInfo.da2[i]]]) == 321 && abs(GenInfo.pdgId[GenInfo.da2[GenInfo.da2[i]]]) == 321)){
						geninfo_bidx.push_back(i);
						total_gen_bsig++;
						if(fabs(GenInfo.eta[i]) < 1.93 && GenInfo.pt[i] > 5) 
							gen_bsig_pt->Fill(GenInfo.pt[i]);
					}
			
				}
				//Phi
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

	
	}//looping events
	printf("%i, %i\n", total_reco_true_bsig, total_gen_bsig);
//	TH1F *reco_gen_eff_pt = (TH1F*)reco_bsig_pt->Clone("reco/gen eff pt kp");
//	reco_gen_eff_pt->Divide(gen_bsig_pt);
	c1->cd();
	TEfficiency *reco_gen_eff_pt = new TEfficiency(*reco_bsig_pt, *gen_bsig_pt);
	if(MCflag == 1)
		reco_gen_eff_pt->SetTitle("acc*eff, K+ channel");
	if(MCflag == 2)
		reco_gen_eff_pt->SetTitle("acc*eff, K* channel");
	if(MCflag == 3)
		reco_gen_eff_pt->SetTitle("acc*eff, #phi channel");

	reco_gen_eff_pt->SetFillColor(2);
	reco_gen_eff_pt->SetFillStyle(3001);
	reco_gen_eff_pt->Draw("");
	c1->Update();
	reco_gen_eff_pt->GetPaintedGraph()->GetXaxis()->SetTitle("pt[GeV]");
	reco_gen_eff_pt->Draw("a2");
	reco_gen_eff_pt->Draw("same");
	reco_gen_eff_pt->Write();

	c1->Write();
    fout->Write();
    fout->Close();
}//main
