time root -b > an.log 2>&1 <<EOI
.x dataMC.C+("d0/d0Err","d0/#sigma(d0)","d0D0loose",40,0,200,1)
.q
EOI

time root -b > an.log 2>&1 <<EOI
.x dataMC.C+("chi2cl","Vertex #chi^{2} Probability","ProbChi2loose",20,0,1,0)
.q
EOI

time root -b > an.log 2>&1 <<EOI
.x dataMC.C+("cos(dtheta)","cos(#Delta#theta)","cosdthetaloose",20,0.9,1,0)
.q
EOI

time root -b > an.log 2>&1 <<EOI
.x dataMC.C+("abs(trk1Dxy/trk1D0Err)","|trk1Dxy/trk1D0Err|","trk1DxyDloose",40,0,200,1)
.q
EOI
