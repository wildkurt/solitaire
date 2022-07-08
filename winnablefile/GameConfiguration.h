//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include <string>
#include <vector>
#include "Rules.h"
#include "Foundation.h"
#include "Tableau.h"
#include "Stock.h"
#include "Moves.h"

class GameConfiguration {
private:
    std::string inputfilename;
    Rules rules;
    Foundation foundation;
    Tableau tableau;
    Stock stock;
    std::vector<Moves> moves;
    bool winningGameConfiguration;
    long gameID;
public:
    GameConfiguration();
    explicit GameConfiguration(std::string inputfilename);
    ~GameConfiguration()=default;
    GameConfiguration(GameConfiguration const &game);
    GameConfiguration &operator=(GameConfiguration const &game);
    int getRulesTurn();
    int getRulesLimit();
    bool isGameFoundationFilled();
    void printGameFoundation();
    void printGameTableau();
    void printGameStock();
    bool isGameWinnable();
    void setWinningGameConfiguration(bool c){winningGameConfiguration = c;}
    void addMove(Moves move);
    void gameConfigurationId();
    long getGameConfigurationID(){return gameID;}
    long numberOfMoves(){return moves.size();}
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
