//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "foundations.h"
void initializeFoundations(Foundations *foundation){
    Card temp = {0,0,0};
    for(int i = 0; i < 4; i++){
        foundation->foundation[i] = temp;
    }
}
/**Find the foundations if they are in horizontal or vertical orientation. They must be in the correct order clubs,
 * diamonds, hearts, and spades. Rank can be empty "_". **/
int getFoundations(Foundations *foundation, int *line, FILE *filelink, char *buffer){
    //Since FOUNDATIONS: should be in buffer, need to check for it and any cards first
    int found = 0;
    char cleanBuffer[MAX_BUFFER] = {0};
    initializeFoundations(foundation);
    do{
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\0'; i++){
            cleanBuffer[i]=buffer[i];
        }
        if(strstr(cleanBuffer, "FOUNDATIONS:") != 0){
            found++;
        }
        for(int i = 0; cleanBuffer[i]!= '\0'; i++){
            if(found == 1 && cleanBuffer[i] == 'c'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] =='_'){
                    foundation->foundation[0].suit = cleanBuffer[i];
                    foundation->foundation[0].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 0 && cleanBuffer[i] == 'c' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 1;
            }
            if(found == 2 && cleanBuffer[i] == 'd'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[1].suit = cleanBuffer[i];
                    foundation->foundation[1].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 1 && cleanBuffer[i] == 'd' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
            if(found == 3 && cleanBuffer[i] == 'h'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[2].suit = cleanBuffer[i];
                    foundation->foundation[2].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 2 && cleanBuffer[i] == 'h' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
            if(found == 4 && cleanBuffer[i] == 's'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[3].suit = cleanBuffer[i];
                    foundation->foundation[3].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 3 && cleanBuffer[i] == 'h' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
        }
        if(found == 5)
            return 0;
        (*line)++;
        memset(buffer,0,MAX_BUFFER);
        memset(cleanBuffer, 0, MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, filelink));

    return 3;
}

void printFoundations(Foundations *foundation){
    printf("FOUNDATIONS:\n");
    printf("\t");
    for(int i = 0; i < 4; i++){
        printf("%c%c ", foundation->foundation[i].rank, foundation->foundation[i].suit);
    }
    printf("\n");
}

void countFoundationCards(Foundations *foundation, Card *countingdeck){
        //52 cards in a deck, 13 cards per suit, array index starts at 0. An "Ac" would be index zero.
        //Also, if the rank is greater than 1, then need to count back from the number to count the number of
        //cards.
        for(int i = 0; i < 4; i++){
            if(i == 0){
                int index = isRank(foundation->foundation[i].rank) - 1;
                for(int j = index; j >= 0; j--){
                    Card temp = {getRank(j + 1), 'c', 't', 0};
                    temp.cardCount++;
                    countingdeck[j] = temp;
                }
            }
            if(i == 1){
                int index = 13 - 1 + isRank(foundation->foundation[i].rank);
                for(int j = index; j >= 12; j--){
                    Card temp = {getRank(j - 12), 'd', 't', 0};
                    temp.cardCount++;
                    countingdeck[j] = temp;
                }
            }
            if(i == 2){
                int index = 26 - 1 + isRank(foundation->foundation[i].rank);
                for(int j = index; j >= 25; j--){
                    Card temp = {getRank(j - 25), 'h', 't', 0};
                    temp.cardCount++;
                    countingdeck[j] = temp;
                }
            }
            if(i == 3){
                int index = 39 - 1 + isRank(foundation->foundation[i].rank);
                for(int j = index; j >= 38; j--){
                    Card temp = {getRank(j - 38), 's', 't', 0};
                    temp.cardCount++;
                    countingdeck[j] = temp;
                }
            }
        }
}

int addCardToFoundations(Foundations *foundation, Card source){
    for(int i = 0; i < 4; i++){
        if(foundation->foundation[i].rank == '_' && source.rank == 'A' && foundation->foundation[i].suit == source.suit){
            foundation->foundation[i] = source;
            return 0;
        }
        else if(isRank(source.rank) - 1 == isRank(foundation->foundation[i].rank) && source.suit == foundation->foundation[i].suit){
            foundation->foundation[i] = source;
            return 0;
        }
    }
    return 1;
}

void printFoundationToFile(FILE *outputtofile, Foundations *foundation){
    fprintf(outputtofile, "FOUNDATIONS:\n");
    fprintf(outputtofile,"\t");
    for(int i = 0; i < 4; i++){
        fprintf(outputtofile,"%c%c ", foundation->foundation[i].rank, foundation->foundation[i].suit);
    }
    fprintf(outputtofile,"\n");
}