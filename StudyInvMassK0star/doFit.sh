rm Results/file_CutId*.eps
rm Results/canvas_CutId*.eps

time root -b <<EOI
.x testfit.C(1)
.q
EOI

time root -b <<EOI
.x testfit.C(2)
.q
EOI

time root -b <<EOI
.x testfit.C(3)
.q
EOI

time root -b <<EOI
.x testfit.C(4)
.q
EOI

time root -b <<EOI
.x testfit.C(5)
.q
EOI

time root -b <<EOI
.x testfit.C(6)
.q
EOI

time root -b <<EOI
.x testfit.C(7)
.q
EOI

time root -b <<EOI
.x testfit.C(8)
.q
EOI

