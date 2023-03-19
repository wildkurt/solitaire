//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_SEARCHSETTINGS_H
#define SOLITAIRE_SEARCHSETTINGS_H


class SearchSettings {
private:
    //Search limited to a number of moves, default is 1000
    bool limitedMoves;
    int numberOfLimitedMoves;
    //Use a hashtable
    bool useHashtable;
    //force safe moves to the foundation
    bool useSafeMoves;
    //Use verbose move to search
    bool useVerboseMode;
    //The Filename to parse
    std::string filename;
public:
    SearchSettings();
    void getSettingsFromCL(int number, char *arr[]);
    void printSettingsFromCL();
    bool getLimitedMoves(){return limitedMoves;}
    int getNumberOfLimitedMoves(){return numberOfLimitedMoves;}
    bool getUseHashtable(){return useHashtable;}
    bool getUseSafeMoves(){return useSafeMoves;}
    bool getUseVerbosMode(){return useVerboseMode;}
    std::string getFilename(){return filename;}
};


#endif //SOLITAIRE_SEARCHSETTINGS_H
