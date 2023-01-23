//
// Created by wendellbest on 1/22/23.
//

#ifndef SOLITAIRE_SEARCHSETTINGS_H
#define SOLITAIRE_SEARCHSETTINGS_H


class SearchSettings {
private:
    bool limitedSequences;
    long int nMoves;
    bool useHashTable;
    bool useSafeMoves;
    bool useVerboseMode;
public:
    SearchSettings(bool b, long i, bool b1, bool b2, bool b3);
    bool getLimitedSequence();
    long int getnMoves();
    bool getUseHashTable();
    bool getUseSafeMoves();
    bool getVerboseMode();
};


#endif //SOLITAIRE_SEARCHSETTINGS_H
