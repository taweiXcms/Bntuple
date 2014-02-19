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
////Include Bfinder interface/format.h here
#include "~/HeavyFlavor_20131030/Bfinder/CMSSW_5_3_8_patch3/src/Bfinder/Bfinder/interface/format.h"
   
void effXacc(){

//Setting the corresponding channel
	int MCflag = 1;//K+
//	MCflag = 2;//K*
//	MCflag = 3;//Phi
	TFile* fout;
	if(MCflag == 1)
		fout = new TFile("fout_kp.root","recreate");
	if(MCflag == 2)
		fout = new TFile("fout_kstar.root","recreate");
	if(MCflag == 3)
		fout = new TFile("fout_phi.root","recreate");
	TCanvas*c1 = new TCanvas("c1", "", 200, 10, 1000, 800);

	TChain *root = new TChain("demo/root");
	if(MCflag == 1)
		root->Add("../../Bfinder_all_full_20140215/Bfinder_all_MC_Kp.root");
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
		if(bsig_genidx.size() > 1) printf("Got %i B signal in one event\n", bsig_genidx.size());

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
			printf("Got %i B gen signal in one event\n", geninfo_bidx.size());
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
