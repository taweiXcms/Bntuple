/*
const int nbins=5;
Double_t acceptance[nbins]={0.4,0.2,1.0,0.7,0.9};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9,3.9};
Double_t best[nbins]={3.2,3.2,3.2,3.2,3.2};
Double_t Bselection[nbins]={4.0,4.0,4.0,4.0,4.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6,0.6};
Double_t PDF[nbins]={11.7,11.7,11.7,11.7,11.7};
Double_t total[nbins]={0.,0.,0.,0.,0.};
Double_t tandprobe[nbins]={6.9,5.0,5.0,4.5,6.5};
*/
/*
const int nbins=3;
Double_t acceptance[nbins]={0.3,0.3,1.7};
Double_t hadron[nbins]={7.8,7.8,7.8};
Double_t best[nbins]={3.1,3.1,3.1};
Double_t Bselection[nbins]={11,11,11};
Double_t ptres[nbins]={0.6,0.6,0.6};
Double_t PDF[nbins]={10.0,10.0,10.0};
Double_t total[nbins]={0.,0.,0.};
Double_t tandprobe[nbins]={7.3,6.0,5.4};
*/
/*
const int nbins=1;
Double_t acceptance[nbins]={5.6};
Double_t hadron[nbins]={7.8};
Double_t best[nbins]={2.4};
Double_t Bselection[nbins]={11.0};
Double_t ptres[nbins]={0.6};
Double_t PDF[nbins]={14.6};
Double_t total[nbins]={0.};
Double_t tandprobe[nbins]={6.5};
*/

const int nbins=5;
Double_t acceptance[nbins]={2.5,2.8,3.4,2.9,2.5};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9,3.9};
Double_t best[nbins]={3.2,3.2,3.2,3.2,3.2};
Double_t Bselection[nbins]={4.0,4.0,4.0,4.0,4.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6,0.6};
Double_t PDF[nbins]={11.7,11.7,11.7,11.7,11.7};
Double_t total[nbins]={0.,0.,0.,0.,0.};
Double_t tandprobe[nbins]={5.9,6.3,5.6,7.0,5.8};

void CalculateSystForNuclear(){



  for (int i=0;i<nbins;i++){

    total[i]=total[i]+acceptance[i]*acceptance[i];
    total[i]=total[i]+hadron[i]*hadron[i];
    total[i]=total[i]+best[i]*best[i];
    total[i]=total[i]+Bselection[i]*Bselection[i];
    total[i]=total[i]+ptres[i]*ptres[i];
//    total[i]=total[i]+trgeff[i]*trgeff[i];
//    total[i]=total[i]+muonid[i]*muonid[i];
//    total[i]=total[i]+innertrk[i]*innertrk[i];
    total[i]=total[i]+PDF[i]*PDF[i];
    total[i]=total[i]+tandprobe[i]*tandprobe[i];
    total[i]=TMath::Sqrt(total[i]);
//    tandprobe[i]=(1+trgeff[i]*0.01)*(1+muonid[i]*0.01)*(1+innertrk[i]*0.01);

  }
  cout<<"Total Systematics"<<endl;
  cout<<"{";
  for (int i=0;i<nbins;i++) {
    printf("%.3f",0.01*total[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;
  cout<<"T&P coefficient corrections"<<endl;
  cout<<"{";
  for (int i=0;i<nbins;i++) {
    printf("%.7f",tandprobe[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;


}
