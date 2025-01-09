#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

/*!
 * \file gridmanagement.h
 * \brief Set of usefull functions for the grid management
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include <string>

#include "type.h" //nos types

/**
 * @brief Clear the current terminal
 * @fn void ClearScreen ();
 */
void ClearScreen ();

/**
 * @brief Set the color of the future input in the terminal
 * @param[in] Col : Next color to be used
 * @fn void Color (const std::string & Col);
 */
void Color (const std::string & Col);


/**
 * @brief Display the grid according to the parameters
 * @param[in] Mat : Game grid
 * @param[in] Params : : List of usefull parameters
 * @fn void DisplayGrid (const CMat & Mat, const CMyParam & Params, bool ShowLineNumber = true, bool ShowColor = true);
 */
void DisplayGrid (const CMat & Mat, const CMyParamV2 & Param );


/*!
 * \brief Initialization of the Matrix from scratch with the teleporter and the monster and the the collectible and the wall
 * \param[out] Mat the matrix to be initialized
 * \param[in] Param Set of game's parameters
 * \param[out] PosPlayer1 position of the first player's token in Mat
 * \param[out] PosPlayer2 position of the second player's token in Mat
 * \param[out] Tp1 position of the first Teleporter in Mat
 * \param[out] Tp2 position of the second Teleporter in Mat
 * \param[out] PosMonster position of Monsters in Mat
 * @fn void InitGrid (CMat & Mat, const CMyParam & Params, CPosition & PosPlayer1, CPosition & PosPlayer2);
 */
void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2, const CMyParamV2 & Param, CPosition & Tp1, CPosition & Tp2, std::vector <CPosition> & PosMonster);





/*!
 * \brief The function will move all monsters acording to the player if he's near and if he's not in the safe zone, or the monster will be moved randomly
 * \param[in, out] PosMonster position of Monsters in Mat
 * \param[in, out] Mat the matrix to be initialized
 * \param[in] Param Set of game's parameters
 * \param[in] PosPlayer1 position of the first player's token in Mat
 * \param[in] PosPlayer2 position of the second player's token in Mat
 * @fn void MoveMonster(std::vector <CPosition> & PosMonster, CMat &  Mat, const CMyParamV2 & param, const CPosition & PosPlayer1,const CPosition & PosPlayer2);
 */

void MoveMonster(std::vector <CPosition> & PosMonster, CMat &  Mat, const CMyParamV2 & param, const CPosition & PosPlayer1,const CPosition & PosPlayer2);

#endif // GRIDMANAGEMENT_H
