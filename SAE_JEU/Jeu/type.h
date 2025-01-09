#ifndef TYPE_H
#define TYPE_H
/*!
 * \file type.h
 * \brief Definition of usefull types or aliases for the project
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include <string>
#include <vector>
#include <map>
#include <optional>


/**
 * @brief CVLine : alias to a line of the matrix
 */
typedef std::vector <char> CVLine;

/**
 * @brief CMat : alias to a game grid type
 * @typedef std::vector <CVLine> CMat;
 */
typedef std::vector <CVLine> CMat;

/**
 * @brief CPosition : a pair gathering the coordinates in the grid
 */
typedef std::pair <unsigned, unsigned> CPosition;



/**
 * @brief Struct containing all the authorized keys in the struct CMyParam
 */
struct AuthorizedKey {
    /** List of authorized key for the type char in a struct CMyParam*/
    const std::vector <std::string> VParamChar {"KeyUp", "KeyDown", "KeyLeft", "KeyRight", "TokenP1", "TokenP2"};
    /** List of authorized key for the type string in a struct CMyParam*/
    const std::vector <std::string> VParamString {"ColorP1", "ColorP2"};
    /** List of authorized key for the type unsigned in a struct CMyParam*/
    const std::vector <std::string> VParamUnsigned {"NbRow", "NbColumn"};
};

struct CMyParam {
    std::map <std::string, char> MapParamChar;
    std::map <std::string, unsigned> MapParamUnsigned;
    std::map <std::string, std::string> MapParamString;
};



/**
 * @brief KAuthorizedKey
 */
const AuthorizedKey KAuthorizedKey;

/**
  * @brief KColor : map between the "human" color and its correspondence for the Unix terminal
  */

const std::map <std::string, std::string> KColor
{
  {"KReset", "0"},
  {"KBlack", "30"},
  {"KRed", "31"},
  {"KGreen", "32"},
  {"KYellow", "33"},
  {"KBlue", "34"},
  {"KMAgenta", "35"},
  {"KCyan", "36"},

};

/**
 * @struct CMyParamV2
 * @brief Structure contenant les paramètres de configuration du jeu
 */
struct CMyParamV2{
	/**
     * @brief la forme du joueur 1
     */
    char tokenP1;
    /**
     * @brief la forme du joueur 1
     */
    char tokenP2;
	/**
     * @brief la touche pour faire monter le token
     */
    char KeyUp;
	/**
     * @brief la touche pour faire descendre le token
     */
    char KeyDown;
	/**
     * @brief la touche pour faire aller à gauche le token
     */
    char KeyLeft;
	/**
     * @brief la touche pour faire aller à droite le token
     */
    char KeyRight;
	/**
     *  @brief le nombre de colone qu'il doit avoir dans la map
     */
    std::size_t NbColumn;
    /**
     * @brief le nombre de ligne qu'il doit avoir dans la map
     */
    std::size_t NbRow;
    /**
     * @brief la couleur du player 1
     */
    std::string ColorP1;
    /**
     * @brief la couleur du player 2
     */
    std::string ColorP2;
};

struct Form
{
    std::string nom;
    std::pair<size_t,size_t> dim;
    std::vector< std::vector<char>> piece;
};

struct Collectible
{
    std::string nom;
    int id;
    int point;
    char token;
    std::pair<size_t,size_t> pos;
};

/**
 * @brief KEmpty : character for an empty cell
 */
const char KEmpty        = ' ';




/**
 * @struct Node
 * @brief Structure représentant un noeud dans un graphe dans Movemonster()
 * struct représentant un noeud dans un graphe, avec pos sa position, f_cost un coût estimé et son parent.
 */
struct Node{
    CPosition Pos;
    size_t f_cost;
    CPosition Parent;
};

#endif // TYPE_H
