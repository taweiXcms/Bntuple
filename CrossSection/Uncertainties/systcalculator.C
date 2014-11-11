void systcalculator(){

double defaultBplus=604.;
double defaultBzero=164.;
double defaultBsubs=40.;

double singlegausBplus=588.;
double singlegausBzero=152.;
double singlegausBsubs=39.;

double combiBplus=593.;
double combiBzero=186.;
double combiBsubs=40.;

double nonpromptBplus=575.;
double nonpromptBzero=173.;
double nonpromptBsubs=40.;

double floatingBplus=654.;
double floatingBzero=160.;
double floatingBsubs=37.;

double increasedBplus=658.;
double increasedBzero=179.;
double increasedBsubs=43.;



double absdiffperc_singlegausBplus=TMath::Abs(1-singlegausBplus/defaultBplus);
double absdiffperc_combiBplus=TMath::Abs(1-combiBplus/defaultBplus);
double absdiffperc_nonpromptBplus=TMath::Abs(1-nonpromptBplus/defaultBplus);
double absdiffperc_floatingBplus=TMath::Abs(1-floatingBplus/defaultBplus);
double absdiffperc_increasedBplus=TMath::Abs(1-increasedBplus/defaultBplus);


double absdiffperc_singlegausBzero=TMath::Abs(1-singlegausBzero/defaultBzero);
double absdiffperc_combiBzero=TMath::Abs(1-combiBzero/defaultBzero);
double absdiffperc_nonpromptBzero=TMath::Abs(1-nonpromptBzero/defaultBzero);
double absdiffperc_floatingBzero=TMath::Abs(1-floatingBzero/defaultBzero);
double absdiffperc_increasedBzero=TMath::Abs(1-increasedBzero/defaultBzero);



double absdiffperc_singlegausBsubs=TMath::Abs(1-singlegausBsubs/defaultBsubs);
double absdiffperc_combiBsubs=TMath::Abs(1-combiBsubs/defaultBsubs);
double absdiffperc_nonpromptBsubs=TMath::Abs(1-nonpromptBsubs/defaultBsubs);
double absdiffperc_floatingBsubs=TMath::Abs(1-floatingBsubs/defaultBsubs);
double absdiffperc_increasedBsubs=TMath::Abs(1-increasedBsubs/defaultBsubs);



cout<<absdiffperc_singlegausBplus<<"-"<<absdiffperc_combiBplus<<"-"<<absdiffperc_nonpromptBplus<<"-"<<absdiffperc_floatingBplus<<"-"<<absdiffperc_increasedBplus<<endl;
cout<<absdiffperc_singlegausBzero<<"-"<<absdiffperc_combiBzero<<"-"<<absdiffperc_nonpromptBzero<<"-"<<absdiffperc_floatingBzero<<"-"<<absdiffperc_increasedBzero<<endl;
cout<<absdiffperc_singlegausBsubs<<"-"<<absdiffperc_combiBsubs<<"-"<<absdiffperc_nonpromptBsubs<<"-"<<absdiffperc_floatingBsubs<<"-"<<absdiffperc_increasedBsubs<<endl;


}