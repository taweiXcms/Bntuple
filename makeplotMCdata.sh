

time aliroot -b > an.log 2>&1 <<EOI
.x dataMC.C+("d0/d0Err","d0/#sigma(d0)","d0D0err",40,0,200,1)
.x dataMC.C+("chi2cl","Vertex #chi^{2} Probability","ProbChi2",20,0,1)
.x dataMC.C+("cos(dtheta)","cos(#Delta#theta)","cosdtheta",20,-1,1)
.x dataMC.C+("abs(trk1Dxy/trk1D0Err)","|trk1Dxy/trk1D0Err|","trk1DxyDerr",40,0,200,1)
.q
EOI
