

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


/**
 * @brief new main
 * @return 0 if everything is OK
 * @fn int ppal ();
 */
int ppal ();
#endif // GAME_H
