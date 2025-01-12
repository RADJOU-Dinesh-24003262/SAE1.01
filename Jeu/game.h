

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




void Sprite(MinGL &window, int grid_x, int grid_y, int pos_x, int pos_y, int mat_x, int mat_y, std::string sprite);


void DisplayGrid (MinGL &window, const CMat & mat, std::tuple <int, int> Screen_size);

void MenuP(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
           std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

void Options(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool, std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

void Credits(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
             std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);
void Pause(MinGL &window, std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> clickablepool,
           std::tuple <int, int> Screen_size, int & menuid, std::chrono::time_point<std::chrono::steady_clock> start);

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
