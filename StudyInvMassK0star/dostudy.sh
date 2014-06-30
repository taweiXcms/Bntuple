rm Results/file_CutId*.eps
rm Results/canvas_CutId*.eps

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(1)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(2)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(3)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(4)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(5)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(6)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(7)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(8)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(9)
.q
EOI

time root -b <<EOI
.L StudyB0bkg_MCdata.C+
StudyB0bkg_MCdata(10)
.q
EOI
