//
// Created by wendellbest on 1/22/23.
//

#include "SearchSettings.h"

SearchSettings::SearchSettings(bool b, long i, bool b1, bool b2, bool b3) {
    limitedSequences = b;
    nMoves = i;
    useHashTable = b1;
    useSafeMoves = b2;
    useVerboseMode = b3;
}

bool SearchSettings::getLimitedSequence() {
    return limitedSequences;
}

long int SearchSettings::getnMoves() {
    return nMoves;
}

bool SearchSettings::getUseHashTable() {
    return useHashTable;
}

bool SearchSettings::getUseSafeMoves() {
    return useSafeMoves;
}

bool SearchSettings::getVerboseMode() {
    return useVerboseMode;
}
