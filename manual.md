Manuel d'utilisation – Console Escape Game
Description générale
Cette console interactive fait partie d’une escape game. Elle est équipée :
•	d’un écran LCD
•	de 4 boutons poussoirs : Haut, Bas, Gauche, OK/Droite
•	de 2 LEDs (verte et rouge)
Le jeu se compose de deux énigmes à résoudre. À chaque étape, les indices s’affichent à l’écran.

 Version Tinkercade :
Les boutons sont positionnés de la façon suivante :
        Haut
Gauche / Bas / Droite

Version Arduino :
Les boutons sont positionnés de la façon suivante :
Gauche / Haut / Bas / Droite

L’utilisation des boutons est à découvrir durant la partie

Solution :
Lancement du jeu
Dès que l'écran affiche :
Appuyez sur OK
Appuyez sur le bouton OK/Droite pour démarrer le jeu.
 
Énigme 1 : Le code à 4 chiffres
Un code composé de 4 chiffres doit être trouvé.
Contrôles :
•	Bouton Haut (↑) : Incrémente le chiffre sélectionné.
•	Bouton Gauche (←) : Déplace le curseur vers la gauche.
•	Bouton OK/Droite (→) : Valide le code une fois modifié.
Le code correct est : 1234

En cas d'erreur :
•	La LED rouge s’allume, et l’écran affiche "Faux !"
•	L’énigme est à refaire.
En cas de réussite :
•	La LED verte s’allume, l’écran affiche "Correct !"
•	L’écran indique : "Tirer carte 8"
•	Puis, il propose de passer à l’énigme suivante.
 
Énigme 2 : La séquence de flèches
Un jeu de mémorisation de 4 flèches vous est proposé.
Mémorisez :
Les flèches s’affichent une par une à l’écran. Les flèches possibles sont :
•	^ (haut)
•	V (bas)
•	<- (gauche)
•	-> (droite)
Entrez la séquence :
Utilisez les boutons directionnels pour entrer la séquence dans le bon ordre. Par exemple :
•	↑ : Haut
•	↓ : Bas
•	← : Gauche
•	→ (OK) : Droite
En cas d'erreur :
•	La LED rouge s’allume, l’écran affiche "Faux"
•	Une nouvelle séquence est générée.

En cas de réussite :
•	La LED verte s’allume.
•	L’écran affiche : "Gagné" puis "Tirer carte 4"
•	La partie se termine avec l’écran : "Fin de partie"
________________________________________
Conseils d'utilisation
•	Patientez entre chaque appui (~0,5s) pour être sûr que la pression sur le bouton soient prise en compte
•	Ne restez pas appuyé sur les boutons. (Sauf dans le cas de l’énigme 1 pour l’incrémentation)

