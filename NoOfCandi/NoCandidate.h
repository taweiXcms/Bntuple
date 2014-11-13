#include <TTree.h>

#define MAX_XB 8192
#define MAX_MUON 64
#define MAX_TRACK 4096 //default 2048
#define MAX_GEN 4096 //default 2048
#define MAX_BX 128
#define N_TRIGGER_BOOKINGS 5842


Int_t   Run;
Int_t   Event;
Int_t   size;

float mass[MAX_XB];
float pt[MAX_XB];
float y[MAX_XB];
float d0[MAX_XB];
float d0Err[MAX_XB];
float chi2cl[MAX_XB];
float dtheta[MAX_XB];

float gen[MAX_XB];
int isbestchi2[MAX_XB]; 

float mu1pt[MAX_XB];
float mu2pt[MAX_XB];
float mumumass[MAX_XB];

float trk1Pt[MAX_XB];
float trk2Pt[MAX_XB];
float tktkmass[MAX_XB];


Int_t HLT_PAMu3_v1;


void setBranch(TTree *root)
{
  root->SetBranchAddress("Run",&Run);
  root->SetBranchAddress("Event",&Event);
  root->SetBranchAddress("size",&size);

  root->SetBranchAddress("mass",mass);
  root->SetBranchAddress("pt",pt);
  root->SetBranchAddress("y",y);
  root->SetBranchAddress("d0",d0);
  root->SetBranchAddress("d0Err",d0Err);
  root->SetBranchAddress("chi2cl",chi2cl);
  root->SetBranchAddress("dtheta",dtheta);

  root->SetBranchAddress("gen",gen);
  root->SetBranchAddress("isbestchi2",isbestchi2);

  root->SetBranchAddress("mu1pt",mu1pt);
  root->SetBranchAddress("mu2pt",mu2pt);
  root->SetBranchAddress("mumumass",mumumass);

  root->SetBranchAddress("trk1Pt",trk1Pt);
  root->SetBranchAddress("trk2Pt",trk2Pt);
  root->SetBranchAddress("tktkmass",tktkmass);

  root->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);

}
