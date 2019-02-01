/*************************************************************
* Copyright (C) 2018
*    Philip Dukshtau
*************************************************************/

/* FILE NAME   : ds_lexer.cpp
 * PURPOSE     : Dukshtau script language project.
 *               Lexer support handle.
 * PROGRAMMER  : Philip Dukshtau.
 * LAST UPDATE : 03.06.2018.
 * NOTE        : Module namespace 'ds'.
 *
 * No part of this file may be changed without agreement of
 * Philip Dukshtau
 */

#include <cctype>
#include <iostream>

#include "ds_lexer.h"

/* Default constructor.
 * ARGUMENTS:
 *   - Input file name:
 *       const std::string &;
 * RETURNS: None.
 */
ds::lexer::lexer(const std::string &Ifname)
{
  iFile_.open(Ifname);

  if (!iFile_.is_open())
    throw std::runtime_error("Can't open file: " + Ifname);

  createTokenList();
} // END OF 'ds::lexer::lexer' FUNCTION


/* Default destructor.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
ds::lexer::~lexer()
{
  iFile_.close();
} // END OF 'ds::lexer::~lexer' FUNCTION

/* Create list of tokens.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void ds::lexer::createTokenList()
{
  std::string word;

  while (iFile_ >> word)
  {
    // Try to find in tiken list that contains KEYWORDS, SEPARATORS, OPERATORS
    if (tokenValues_.find(word) == tokenValues_.end())
    {
      // Check if word is "true" or "false"
      if (word == "true" || word == "false")
        tokenList_.push_back({LITERAL, word});
      // Check if word is literal
      else if (std::isdigit(word[0]))
      {
        for (auto c : word)
          if (!std::isdigit(c) || c != 'e' || c != '.')
          {
            std::cout << "Unknown character: " + c << " at: " << iFile_.tellg() << std::endl;
            throw std::runtime_error("Unknown character:" + c);
          }
        tokenList_.push_back({LITERAL, word});
      }
      // Check if word string
      else if (word[0] == '"' || word[0] == '\'')
      {
        for (size_t i = 1; i < word.length() - 1; i++)
          if (!std::isalnum(word[i]))
          {
            std::cout << "Unknown character: " << word[i] << " at: " << iFile_.tellg() << std::endl;
            throw std::runtime_error("Unknown character:" + word[i]);
          }

        if (word[word.length() - 1] != '"' || word[word.length() - 1]  == '\'')
        {
          std::cout << "Unknown character: " << word[word.length() - 1] << " at: " << iFile_.tellg() << std::endl << "Expect \" or \'" << std::endl;
          throw std::runtime_error("Unknown character:" + word[word.length() - 1]);
        }

        tokenList_.push_back({LITERAL, word});
      }
      // Add word as identifier but check correction of it
      else
      {
        for (auto c : word)
          if (!std::isalnum(c))
            {
              std::cout << "Unknown character: " << c << " at: " << iFile_.tellg() << std::endl;
              throw std::runtime_error("Unknown character:" + c);
            }

        tokenList_.push_back({IDENTIFIER, word});
      }
    }
    else
      tokenList_.push_back({tokenValues_.at(word), word});
  }
} // END OF 'ds::lexer::createTokenList' FUNCTION

/* Get copy of result vector.
 * ARGUMENTS: None.
 * RETURNS: (std::vector<std::pair<TOKEN, std::string>>)Result vector.
 */
std::vector<std::pair<ds::lexer::TOKEN, std::string>> ds::lexer::getVector()
{
  return tokenList_;
} // END OF 'ds::lexer::getVector' FUNCTION

// END OF 'ds_lexer.cpp' FILE
