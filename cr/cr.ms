.fam N
.AM
.EQ
delim $$
.EN
.TL
Compte Rendu TP3 POOCS

\s+2Compression d'une Image par Maillage\s-2
.AU
J\s-2OHN\s+2 GLIKSBERG
.AI
M1 IHPS @ UVSQ
.SH
\s+2Introduction\s-2
.LP
Le but de ce TD/TP est de fournir un outil qui génère une maille
de triangles à partir d'une image pour réduire la quantité
d'information stockée d'une image.

Le maillage consistera en un ensemble de triangles dont les points
sont des pixels de l'image.
Chaque pixel retiendra la couleur de l'image en ce point.
On pourra retrouver un affichage de l'image d'origine en dessinant
les triangles remplis de la couleur moyenne de celles de ses points.

La "compression" se fait sur la formation de triangles qu'on
privilégiera dans les zone avec des grandes differences de couleur.

On n'alignera \fIpas\fP les côtés des triangles avec les lignes
qu'on peut distinguer dans l'image mais on construira toujours de
nouveaux triangles dans la zone qui diffère le plus de l'image
(sauf lorsque l'on a atteint une résolution trop fine).

C'est ainsi un processus itératif car on ne prévoit pas où sera
le prochain découpage.

On décide d'avance qu'on ne travaillera que sur des images en
niveaux de gris. Pour la modélisation de notre outil on décide de
se limiter à des fichiers en entrée au format \fC.pgm\fP et un
enregistrement du maillage au format \fC.vtk\fP.

\fBDéfinitions:\fP Dans un maillage $M$
donné, pour un triangle $T$ dans $M$ donné, si $C sub 1$,
$C sub 2$ et $C sub 3$ sont les couleurs des points de $T$,
on définit $C$ la couleur moyenne du triangle, et
l'\fIécart\fP en $T$ correspond à la différence absolue entre
$C$ et la couleur de l'image au barycentre des points du triangle.

Ceci nous permet d'une itération à l'autre de choisir le triangle
au plus grand écart dans notre maillage. On travaille maintenant
sur le barycentre $P$ de ce triangle, c'est le point à partir
duquel on va rendre notre maillage plus précis.

.SH
\s+2Mise en place\s-2
.LP

.PS
box "N2"
box "Pixel"    at 1st box + (1,   0)
box "Image"    at 2nd box + (1,   0)
box "Maillage" at 3rd box - (.5,  1)
box "Triangle" at 4th box - (1.5, 0)
box "Cavite"   at 5th box - (0,   1)
box "Tableau"  at 6th box + (1.5, 0)
arrow from 1st box .e to 2nd box .w
arrow from 2nd box .e to 3rd box .w
arrow from 2nd box .sw to 5th box .n
arrow from 3rd box .s to 4th box .n
arrow from 5th box .e to 4th box .w
arrow from 5th box .s to 6th box .n
arrow from 6th box .ne to 4th box .sw
arrow from 7th box .n to 4th box .s
arrow from 7th box .w to 6th box .e
.PE

.DS L
.fam C
POOCS.hh
Vect.hh Vect.cc
Mat.hh  Mat.cc
MatG.hh MatG.cc
MatC.hh MatC.cc
main.cc
Makefile
.fam N
.DE

.SH
\s+2Accesseurs\s-2
.LP

.SH
\s+2Mutateurs\s-2
.LP

.SH
\s+2Opérations d'algèbre linéaire\s-2
.LP

.DS L
\(bu\fC  Vect   Vect::operator+(Vect)    \fP addition vectorielle
\(bu\fC  Vect   Vect::operator-(Vect)    \fP soustraction vectorielle
\(bu\fC  double Vect::operator*(Vect)    \fP produit scalaire
\(bu\fC  Vect   Vect::operator*(double)  \fP produit vecteur par un scalaire
\(bu\fC  Vect Mat::operator*(Vect)       \fP produit matrice vecteur
.DE
