/*************************************************************
* Copyright (C) 2018
*    Philip Dukshtau
*************************************************************/

/* FILE NAME   : ds_lexer.h
 * PURPOSE     : Dukshtau script language project.
 *               Lexer support handle.
 * PROGRAMMER  : Philip Dukshtau.
 * LAST UPDATE : 03.06.2018.
 * NOTE        : Module namespace 'ds'.
 *
 * No part of this file may be changed without agreement of
 * Philip Dukshtau
 */


#ifndef __DS_LEXER_H_
#define __DS_LEXER_H_

#include <fstream>
#include <vector>
#include <string>
#include <map>

// ds namespace
namespace ds
{
  // Lexer class declaration
  class lexer
  {
  private:
    // Token enum
    enum TOKEN
    {
      IDENTIFIER,
      KEYWORD,
      SEPARATOR,
      OPERATOR,
      LITERAL,
      //COMMENT
    };

    // Const map of literals
    const std::map<std::string, TOKEN> tokenValues_ =
    {
      // OPERATORS
      {"+",  OPERATOR},
      {"-",  OPERATOR},
      {"=",  OPERATOR},
      {"*",  OPERATOR},
      {"/",  OPERATOR},
      {"%",  OPERATOR},
      {":",  OPERATOR},
      {"++", OPERATOR},
      {"--", OPERATOR},
      {"==", OPERATOR},
      {"+=", OPERATOR},
      {"-=", OPERATOR},
      {"*=", OPERATOR},
      {"/=", OPERATOR},
      {"<",  OPERATOR},
      {">",  OPERATOR},
      {"<=", OPERATOR},
      {">=", OPERATOR},
      // END OF OPERATORS

      // KEYWORDS
      {"if",      KEYWORD},
      {"else",    KEYWORD},
      {"while",   KEYWORD},
      {"void",    KEYWORD},
      {"return",  KEYWORD},
      // END OF KEYWORDS

      // SEPARATORS
      {"(", SEPARATOR},
      {")", SEPARATOR},
      {"{", SEPARATOR},
      {"}", SEPARATOR},
      {"[", SEPARATOR},
      {"]", SEPARATOR},
      // END OF SEPARATORS
    };

    std::ifstream iFile_;                                  //Work file
    std::vector<std::pair<TOKEN, std::string>> tokenList_; //Token list where TOKEN: string

   /* Create list of tokens.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    void createTokenList();
  public:
    /* Default constructor.
     * ARGUMENTS:
     *   - Input file name:
     *       const std::string &;
     * RETURNS: None.
     */
    lexer(const std::string &);

    /* Get copy of result vector.
     * ARGUMENTS: None.
     * RETURNS: (std::vector<std::pair<TOKEN, std::string>>)Result vector.
     */
    std::vector<std::pair<TOKEN, std::string>> getVector();

    /* Default destructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~lexer();
  }; // END OF 'lexer' CLASS
} // END OF 'ds' NAMESPACE

#endif // __DS_LEXER_H_

// END OF 'ds_lexer.h' FILE
