//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_TABLEAUS_H
#define SOLITAIRE_TABLEAUS_H
#include <vector>
#include "cardHeader.h"
class Tableaus {
private:
    std::vector<Card> col7;
    std::vector<Card> col6;
    std::vector<Card> col5;
    std::vector<Card> col4;
    std::vector<Card> col3;
    std::vector<Card> col2;
    std::vector<Card> col1;
    bool column7Filled;
    bool column6Filled;
    bool column5Filled;
    bool column4Filled;
    bool column3Filled;
    bool column2Filled;
    bool column1Filled;
public:
    Tableaus();
    ~Tableaus()=default;
    bool addCardToTableau(Card c, int col);
    bool isColumnFilled(int i);
    void columnFilled(int i);
    Card getCard(int index, int col);
    int getTableauColSize(int i);
};


#endif //SOLITAIRE_TABLEAUS_H
