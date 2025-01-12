

#ifndef GAME_H
#define GAME_H

/*!
 * \file game.h
 * \brief Set of usefull functions for the game
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include "type.h"
#include "mingl/mingl.h"
#include <chrono>


/*!
 * \brief Move the current token according to the character in the 2nd parameter
 * \param[in, out] Mat the matrix before and after the move
 * \param[in] Move the key pressed by the user
 * \param[in, out] Pos the player's position before and after the move
 * \param[in] The Parameter extract from the .yaml file
 * \param[out] Tp1 position of the first Teleporter in Mat
 * \param[out] Tp2 position of the second Teleporter in Mat
 */

void MoveToken (CMat & Mat, const char & Move, CPosition & Pos, const CMyParamV2 & Param, CPosition & Tp1, CPosition & Tp2 );


/*!
 * \brief Test if the Move made by the player is legal, this mean if there is no wall and no out of bound
 * \param[in] Mat the matrix
 * \param[in] Move the key pressed by the user
 * \param[in] Pos the player's position
 * \param[in] The Parameter extract from the .yaml file
 * @return true if the Move can be made
 */

bool IsMoveLegal(const CMat & Mat, const char & Move, const CPosition & Pos, const CMyParamV2 & Param);

/*!
 * \brief returns the contents of the next cell and its position in the matrix (even with teleporter)
 * \param[in] Mat the matrix
 * \param[in] Move the key pressed by the user
 * \param[in] Pos the player's position
 * \param[in] The Parameter extract from the .yaml file
 * \param[in] The position of teleporter number 1
 * \param[in] The position of teleporter number 2
 * @return <content of the cell <pos x, pos y>>
 */

std::pair<char, CPosition> nextMove(const CMat &Mat, const char &Move, const CPosition &Pos,
                                    const CMyParamV2 &Param, CPosition &Tp1, CPosition &Tp2);

/*!
 * \brief Test whether the content of the next move's cell is an element
 * \param[in] Mat the matrix
 * \param[in] Move the key pressed by the user
 * \param[in] Pos the player's position
 * \param[in] The Parameter extract from the .yaml file
 * @return true if the next move's cell is an element
 */

bool IsCollectible(const CMat & Mat, const char & Move, const CPosition & Pos, const CMyParamV2 & Param);


/*!
 * \brief Increments the score for each item in the list
 * \param[in] The list of items the player has collected
 * \param[in] The score increases with each element
 */

void CalculateScore(std::vector<char> &objets, int &score);



/**
 * @brief cette fonction affiche un sprite dans la fenetre
 * @param window La fenêtre dans laquelle le sprite sera affiché
 * @param grid_x La position X dans la grille
 * @param grid_y La position Y dans la grille
 * @param pos_x La position X dans la fenêtre
 * @param pos_y La position Y dans la fenêtre
 * @param mat_x La largeur du sprite dans la grille
 * @param mat_y La hauteur du sprite dans la grille
 * @param sprite Le nom du fichier du sprite à afficher
 */
void Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y, int mat_x, int mat_y, std::string sprite);

/**
 * @brief cette fonction affiche la grille sur MinGl
 * @param window La fenêtre dans laquelle la grille sera affichée
 * @param mat La matrice représentant la grille à afficher
 * @param Screen_size La taille de l'écran sous forme de tuple (largeur, hauteur)
 */
void DisplayGrid (MinGL &window, const CMat & mat, std::tuple <int, int> Screen_size);

/**
 * @brief cette affiche le menu principal sur MinGl
 * @param window La fenêtre où il sera affiché
 * @param clickablepool Un vecteur d'éléments cliquables, où chaque élément est un tuple
 *                      contenant des informations sur les zones cliquables
 * @param Screen_size La taille de l'écran sous forme de tuple (largeur, hauteur)
 * @param menuid L'identifiant du menu actuel
 * @param start Le moment où l'affichage du menu a commencé
 */
void MenuP(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
           std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);


/**
 * @brief cette fonction affiche les options du jeux
 * @param window La fenêtre dans laquelle le menu sera affiché
 * @param clickablepool Un vecteur d'éléments cliquables
 * @param Screen_size La taille de l'écran
 * @param menuid L'identifiant du menu actuel
 * @param start Le moment où l'affichage du menu a commencé
 */
void Options(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool, std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

/**
 * @brief cette affiche les credits
 * @param window La fenêtre dans laquelle le menu sera affiché
 * @param clickablepool Un vecteur d'éléments cliquables
 * @param Screen_size La taille de l'écran sous forme de tuple (largeur, hauteur)
 * @param menuid L'identifiant du menu actuel
 * @param start Le moment où l'affichage du menu a commencé
 */
void Credits(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
             std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

/**
 * @brief cette fonction affiche le menu pause
 * @param window La fenêtre dans laquelle le menu sera affiché
 * @param clickablepool Un vecteur d'éléments cliquables
 * @param menuid L'identifiant du menu actuel
 * @param start Le moment où l'affichage du menu a commencé
 */
void Pause(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
           std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

/**
 * @brief cette fonction gere la boucle principale du jeu
 * @param window La fenêtre dans laquelle le jeu sera affiché
 * @param clickablepool Un vecteur d'éléments cliquables
 * @param Mat La matrice représentant la carte du jeu
 * @param menuid L'identifiant du menu actuel
 * @param PartyNum Le nombre de partie
 * @param Key_UP L'état de la touche UP
 * @param Key_DOWN L'état de la touche DOWN
 * @param Key_RIGHT L'état de la touche RIGHT
 * @param Key_LEFT L'état de la touche LEFT
 * @param Screen_size La taille de l'écran sous forme de tuple (largeur, hauteur)
 * @param param Paramètres de configuration
 * @param Victory Indicateur de victoire
 * @param KMaxPartyNum Nombre maximum de tours dans une partie
 * @param PosPlayer1 La position du joueur 1
 * @param PosPlayer2 La position du joueur 2
 * @param PosTP1 La position du premier téléporteur
 * @param PosTP2 La position du deuxième téléporteur
 * @param Player1Turn Indicateur permettant de savoir le tour de quel joueur
 * @param N_move Le prochain mouvement du joueur sous forme de tuple (direction, position)
 * @param objetJ1 Liste des objets ramassé par joueur 1
 * @param objetJ2 Liste des objets ramassé par joueur 2
 * @param scoreJ1 Le score du joueur 1
 * @param scoreJ2 Le score du joueur 2
 * @param PosMonster Liste des positions des monstres
 */
void GameLoop(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>>clickablepool,CMat Mat, int menuid, unsigned PartyNum,
              bool Key_UP, bool Key_DOWN, bool Key_RIGHT, bool Key_LEFT, std::tuple <int, int> Screen_size, CMyParamV2 param,
              bool Victory, unsigned KMaxPartyNum, CPosition PosPlayer1, CPosition PosPlayer2, CPosition PosTP1,
              CPosition PosTP2, bool Player1Turn, std::pair<char,CPosition> N_move, std::vector<char> objetJ1, std::vector<char> objetJ2,
              int scoreJ1, int scoreJ2, std::vector <CPosition> PosMonster);



/**
 * @brief new main
 * @return 0 if everything is OK
 * @fn int ppal ();
 */
int ppal ();
#endif // GAME_H
