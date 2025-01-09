# Projet SAE 1.01 - Lethal

## Contexte du Projet

Dans le cadre de cette **SAE**, notre équipe a été chargée d'améliorer un jeu d'aventure initialement développé lors des TPs 10. Le but était d'ajouter de nouvelles fonctionnalités, et de coder tout en ayant en esprit de fournir une documentation complète du projet avec Doxygen. Nous avons également mis en place des améliorations graphique avec MinGL2.

## Objectifs

Les objectifs que nous souhaitons pour ce projet les suivants :

1. **Blinder le code existant** : 
   - Sécurisation des indices (pas de débordements de tableaux) et gestion des erreurs.
   - Ajout de vérification qui permet d'éviter au 1er joueur qu'il joue à la place du deuxième joueur.
   
2. **Ajout de nouvelles fonctionnalités** :
   - Lecture de fichiers de configuration ```config.yaml.```
   - Générer des murs de manière procédurale
   - Ajout d'un monstre qui a pour but de suivre un joueur proche et de le manger.
   - Ajout de safe zones où le monstre n'aura pas le droit d'attaquer le joueur
   - Ajout d'un système de score dans le jeu.
   - Ajout de téléporteur dans le jeu qui permettra au joueur de se déplacer plus rapidement.
   - (Ajout de skin pour les personages)
   - (Ajout de power up dans le jeu)  
   - (Implémentation d'un système de high scores.)
   - Réalisation d'un Lore
   - Utilisation de **MinGL** pour une meuilleure expérience de jeu

3. **Documentation avec Doxygen** : Génération d'une documentation à l'aide de Doxygen grâce aau commentaires dans le code

---
## Comment jouer au jeu
Ce jeu se joue exclusivement sur **Linux**. Pour y jouer, vous devez impérativement être **deux joueurs**. Vous jouez tous les 2 en temps réel dans la fenêtre MinGL2 à l'aide des touches du clavier. L’objectif du jeu est d'avoir le maximum de points en ramassant les objets, tout en évitant de se faire attraper par le monstre. Les touches utilisées peuvent être personnalisées, tout comme la taille de la carte.

### Règles du jeu :
1. **Multijoueur** : Le jeu se joue exclusivement à **deux joueurs**.
2. **Objectifs** : 
   - Ramasser des objets dispersés sur la carte pour accumuler des points.
   - Éviter d’être tué par le monstre qui rôde dans la zone.
   - Obtenir plus de points que l'autre joueur.
3. **Gagner** : Pour gagner, vous devez ramasser un total de points supérieur à **(longueur de la carte + largeur de la carte)** * **15**, ou bien avoir plus de point que l'adversaire si le temps imparti est dépassé.
   - Une fois ce total atteint, vous devez ramener ces objets à votre maison pour valider vos points.

### Mécanismes du jeu :
- **Tour de jeu** : Les deux joueurs jouent tous les 2 en temps réel dans la fenêtre MinGL2.
- **Personnalisation des touches** : Les touches qui permettant de se déplacer peuvent être modifié.
- **Taille de la carte** : Vous pouvez modifier la taille de la carte sur le fichier config, ce qui peut augmenter ou diminuer la difficulté du jeu. Une carte plus grande augmente le nombre d’objets à ramasser, mais tout de même à faire attention, la portée du monstre augmente avec le monstre.

### Stratégies :
- **Ramasser les objets** : Explorez la carte pour ramasser les objets tout en évitant le monstre.
- **Calculer votre score** : Assurez-vous de ramasser suffisamment d’objets pour atteindre le score requis avant que l’autre joueur gagne ou le monstre ne vous élimine.
- **Coopérez** : Effectuez des aliances pour éviter de vous faire manger par le monstre.
