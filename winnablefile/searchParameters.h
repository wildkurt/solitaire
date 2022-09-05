//
// Created by wendellbest on 8/31/22.
//

#ifndef SOLITAIRE_SEARCHPARAMETERS_H
#define SOLITAIRE_SEARCHPARAMETERS_H


class searchParameters {
private:
    bool limitedSearch;
    long numberLimitedSearch;
    bool useHashTable;
    bool useSafeMoves;
    bool useVerboseMode;
public:
    searchParameters();
    searchParameters(bool limitedSearch, long numberLimitedSearch, bool useHashTable, bool useSafeMoves, bool useVerboseMode);
    ~searchParameters()= default;
};


#endif //SOLITAIRE_SEARCHPARAMETERS_H
