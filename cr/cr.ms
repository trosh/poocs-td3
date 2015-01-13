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
privilégiera dans les zones avec des grandes differences de couleur.

On n'alignera \fIpas\fP les côtés des triangles avec les lignes
qu'on pourra distinguer dans l'image mais on construira toujours de
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
au plus grand \fIécart\fP dans notre maillage. On travaille maintenant
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
\fCtemplate\fP (et on construit un objet \fC.o\fP
pour cette classe).

Voici un graphe d'inclusion qui représente ces classes
selon l'inclusion de leur \fIheader\fP.

.PS
box "\fCN2\fP"
box "\fCPixel\fP"    at 1st box + (1.2, 0)
box "\fCImage\fP"    at 2nd box + (1.5, 0)
box "\fCMaillage\fP" at 3rd box - (0,   1)
box "\fCTriangle\fP" at 4th box - (1.5, 0)
box "\fCCavite\fP"   at 5th box - (0,   1)
box "\fCTableau\fP"  at 6th box + (1.5, 0)
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
génériques. On réduit le nombre d'allocations nécessaires au passage
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
On implémente ici une classe très simple représentant des coordonnées
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
format \fC.pgm\fP, on aurait pû stocker la couleur dans un
\fCunsigned char\fP, comme ce sera le cas dans une \fCImage\fP,
mais pour pouvoir manipuler les \fCPixel\fPs avec aisance on a fait
ce choix.

On a ainsi prévu que pour le calcul d'un barycentre on voudra pouvoir
écrire :

.DS L
.fam C
Pixel p = (p1 + p2 + p3) / 3;
.fam P
.DE

Sans se soucier d'\fIoverflow\fP sur les \fCPixel\fPs intermédiaires.

La couleur de ce \fCPixel\fP est $C$ telle que définie plus haut.

.SH
Triangle
.LP
Cette classe représente un rassemblement de trois \fCPixel\fPs
et c'est à ce niveau qu'on implémente en particulier la méthode
\fCbool\ cercleCirconscritContient(N2)\fP, au coeur de notre
algorithme de maillage. Pour cette méthode on calcule le déterminant
d'une matrice en stockant certaines valeurs uniquement par soucis
d'écriture, on laisse le compilateur éviter les répétitions
inutiles en général.

.SH
Cavité
.LP
On construit la région à mettre à jour dans notre modèle
comme à la fois un tableau des triangles à supprimer
(ceux dont le cercle circonscrit contient le point à ajouter)
et un tableau des pixels à partir desquels on va insérer les
nouveaux triangles.

C'est le constructeur
\fCCavite::Cavite(const\ Tableau<Triangle>&,\ const\ Pixel&)\fP
qui détermine ces tableaux à partir des triangles de notre maillage
et du point qu'on veut ajouter.

.SH
Image
.LP
Cette classe est quasiment une copie de la classe \fCPGMImage\fP
fournie dans les documents de l'énoncé. On a décidé de ne pas
séparer les concepts d'image et de lecteur de fichier image car
notre but n'était pas d'implémenter un outil pour un panel varié
d'images dans le sens abstrait, mais de tester si la méthode de
compression était intéressante pour des images exemples.

Il n'était ainsi pas nécessaire de donner plus de sens à une image
que le format qu'on comptait tester, représenté principalement par
l'attribut \fCunsigned char\ *_data\fP.

Pour revenir au stockage \fCint\fP des couleurs dans la classe
\fCPixel\fP, on stocke ici la couleur comme \fCunsigned char\fP
mais on la distribue comme \fCint\fP soit \fIvia\fP les accesseurs
\fCpixel(...)\fP soit \fIvia\fP l'accesseur \fCoperator()(int, int)\fP.

Le lecteur de fichier \fC.pgm\fP se fait \fIvia\fP le constructeur
\fCImage::Image(const char*)\fP. Celui-ci fait peu de vérifications
quant au contenu, mais encore une fois cet outil n'est pas fait
pour un usage très varié.

.ne 3
.SH
Maillage
.LP
Voici la classe qui représente l'objet qu'on veut construire
\fIin fine\fP. C'est un tableau de triangles avec l'image sur
laquelle on travaille comme attribut intrinséquement lié au maillage
qui va le représenter.

On initialise le maillage avec le constructeur
\fCMaillage::Maillage(Image&)\fP qui pointe \fCImage* _img\fP
vers l'image étudiée et initialise le maillage par défaut à ses
dimensions. Voici le type de maillage initial qu'on construit
(deux triangles) :

.PS
box wid 1.2 ht .7
line from 1st box .sw to 1st box .ne
.PE

La méthode \fCajoute(const int itermax, const int precision)\fP
itère sur le maillage tant que \fIl'écart\fP en chaque triangle est
trop important (et que \fCiter < itermax\fP). À chaque itération
on détermine (parmis les triangles dont le barycentre n'est
pas un point d'un triangle du maillage) quel triangle $T$ vérifie
le plus grand \fIécart\fP. On détermine la cavité à partir de son
barycentre, on supprime les triangles mis en relief et on ajoute
tous les nouveaux triangles.

La méthode \fCsupprime\fP réordonne le tableau en sa fin, et on
sait quoi supprimer uniquement par son index qu'on veut garder
cohérent pendant la suppression. Avec la garantie qu'on a une liste
croissante des index des triangles à supprimer, on itère en arrière
sur ce tableau et on garantit qu'on a supprimé uniquement les bons
triangles.

La couleur $C$ du barycentre ne nous intéresse plus, on voudra
insérer la couleur de l'image en son point avec les coordonnées
du barycentre.
(\fC p = Pixel(p, (*_image)(p)); \fP)

On construit les nouveaux triangles à partir d'un tableau de pixels.
On fait bien attention à les construire dans le sens trigonométrique
et à ne pas oublier le triangle qui contient les dernier et premier
points du tableau.

Une fois qu'on a suffisement itéré, on peut \fCsauvegarder\fP le
maillage dans un fichier \fC.vtk\fP qu'on peut visualiser avec
\fIParaview\fP. Plusieurs captures d'écran en \fC.png\fP des résultats
sont à la racine du projet.

.SH
\s+2Conclusion\s-2
.LP
On arrive dans ce projet à construire l'outil demandé.
La construction des maillages n'est pourtant pas vraiment
satisfaisante:

\(bu L'image telle qu'on peut l'afficher après compression a perdu
beaucoup de qualité

\(bu Pour une précision suffisamment correcte ($<10$) et dans les
limites de notre implémentation, le temps de calcul est beaucoup trop
long ($approx 1$ minute).

\(bu On n'a pas particulièrement gagné en taille de fichier.
Si on avait un format plus spécifique à notre maillage que le
format \fC.vtk\fP (en binaire, etc...), on pourrait par contre
réduire assez clairement la taille du fichier.
