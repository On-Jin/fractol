#FRACTOL
===

![Julia](https://github.com/Jino42/fractol/blob/master/fractol_pres.png)

Énnoncé :
<<Ce nouveau projet sera pour vous l’occasion de vous perfectionner dans l’utilisation
de la miniLibX, de vous faire découvrir/utiliser la notion mathémathique des nombres
complexes ainsi que de vous faire aborder la problématique de l’optimisation en programmation
graphique.>>
<br />
Fractol, Opencl pour l'utilisation de la carte graphique.<br />
Grace a l'Opencl, j'ai pu "animer" mes fractals, vue qu'elles étaient presque toujours a 40-60 FPS :)<br />

Equation : https://youtu.be/fQM8M3edG8o<br />
Mandelbrot ✅<br />
Julia ✅<br />
Burningship ✅<br />
<br />
Geométrique : lien()<br />
Triangle de Sierpinski ✅<br />
Tree ✅<br />
<br />
Buddhabrot :

![Julia](https://github.com/Jino42/fractol/blob/master/Buddhablanc.png)

Malencontresement, buddhabrot semble avoir quelques difficultés lorsque le nombre d'itération est trop grands.
Les cartes graphiques sont très caprieuse, si un seul problème est rencontré, c'est le crash
Pourtant l'utilisation des fonctions atomic pour incrémenter les variable a bien été utilisé, afin de créer un mutex et se proteger des conflits<br />
<br />
Anyway, OpenCl, j'en est loins d'en fini avec lui :D <3

Les rendus sont au final un peut sombre, mais je n'ai plus eu le courage a la fin de chercher des parametres sexy :3

![Julia](https://github.com/Jino42/fractol/blob/master/Buddhamult.png)
![Julia](https://github.com/Jino42/fractol/blob/master/Buddhabase.png)
