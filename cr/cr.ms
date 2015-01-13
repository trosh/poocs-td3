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

Le processus précis est décrit dans l'énoncé et consiste à vider
une cavité de triangles autour de $P$ et reconstruire de nouveaux
triangles plus petits.

Cet algorithme de maillage privilegiera souvent trop certaines
régions de l'image, mais en limitant la granularité à celle du pixel,
on répartit l'importance donnée aux zones de l'image.

.ne 6
.SH
\s+2Mise en place\s-2
.LP
On a implémenté les différentes parties de notre outil avec
pour chacune une classe décrite entièrement dans un fichier
\fC.hh\fP et un fichier \fC.cc\fP si ce n'est pas une classe
\fCtemplate\fP (dans quel cas on construit un objet \fC.o\fP
pour cette classe).

Voici un graphe d'inclusion qui représente ces classes
selon l'inclusion de leur \fIheader\fP.

.PS
box "N2"
box "Pixel"    at 1st box + (1.2, 0)
box "Image"    at 2nd box + (1.5, 0)
box "Maillage" at 3rd box - (0,   1)
box "Triangle" at 4th box - (1.5, 0)
box "Cavite"   at 5th box - (0,   1)
box "Tableau"  at 6th box + (1.5, 0)
arrow from 1st box .e  to 2nd box .w thickness 1.7
arrow from 2nd box .e  to 3rd box .w
arrow from 2nd box .s  to 5th box .n
arrow from 3rd box .s  to 4th box .n
arrow from 5th box .e  to 4th box .w dashed
arrow from 5th box .s  to 6th box .n
arrow from 6th box .ne to 4th box .sw
arrow from 7th box .n  to 4th box .s
arrow from 7th box .w  to 6th box .e
.PE

.SH
Tableau (\fCTableau<T>\fP)
.LP
Cette classe \fCtemplate\fP nous a fait un exercice sur les classes
génériques: on peut accéder à ou modifier une liste d'élèments
générique. On réduit le nombre d'allocations nécessaires au passage
à l'échelle en séparant les concepts de \fItaille\fP et de \fIcapacité\fP.

La méthode \fCretaille\fP peut faire appel à \fCreserve\fP si on demande
une taille qui excède la capacité (on choisit de ne pas \fIréallouer vers
le bas\fP). Comme les objets stockés sont génériques, on ne fait pas
de réallocation à la \fCrealloc\fP, mais on fait un appel à \fCnew\fP
et on boucle avec des appels à \fCoperator=\fP. De même lorsqu'on
supprime un élèment on ne fait que le remplacer par le dernier;
on fait encore un appel à \fCoperator=\fP et on appelle le constructeur
générique pour le dernier élèment déplacé. C'est relativement lent
par rapport à des fonctions type \fCmemcpy\fP mais on préfère
préserver l'usage \fIPOO\fP.

.SH
N2
.LP
On implémente ici une classe très simple reprèsentant des coordonnées
entières à deux dimensions, et quelques opérations de base.

Par exemple, \fCoperator==\fP rendait aisé de tester si un point
était présent dans un maillage sans avoir à implémenter
\fCbool\ *_pixels_presents\fP. C'est par contre une méthode plus
lente qu'avec ce tableau.

.ne 5
.SH
Pixel
.LP
Cette classe hérite de \fCN2\fP et lui ajoute une valeur de couleur
\fItypedef'd\fP à un \fCint\fP. Sachant qu'on travaille avec le
format \fC.pgm\fP, on aurait pû stocker la couleur dans un \fCchar\fP,
comme ce sera le cas dans une \fCImage\fP, mais pour pouvoir
manipuler les \fCPixel\fPs avec aise on a fait ce choix.

On a ainsi prévu que pour le calcul d'un barycentre on voudra pouvoir
écrire :

.DS L
.fam C
Pixel p = (p1 + p2 + p3) / 3;
.fam P
.DE

Sans se soucier d'\fIoverflow\fP sur les \fCPixel\fPs intermédiaires.

.SH
Triangle
.LP
Cette classe représente un rassemblement de trois \fCPixel\fPs
et c'est à ce niveau qu'on implémente en particulier la méthode
\fCbool\ cercleCirconscritContient(N2)\fP, au coeur de notre
algorithme de maillage.
