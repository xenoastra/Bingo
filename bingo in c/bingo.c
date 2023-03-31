#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
// card checker aka exit cases


int card_checker(int card[][4],char *argv[])
{
    int numRow = 0;
    int numColumn = 0;
    int counter = 0;
    char tempNum[100];
    FILE *fp;

    //exit 3, Invalid file
    if ((fp = fopen(argv[2], "r")) == NULL){
        fprintf(stderr, "%s is nonexistent or unreadable\n", argv[2]);
        exit(3); 
    }


    //exit 4, Incorrect card Format
    while(fgets(tempNum, 100, fp) != NULL){
        if (isdigit (tempNum)){
            int num = atoi(tempNum);
            if(numRow > 4){
                fprintf(stderr, "%s has bad format\n", argv[2]);
                exit(4);
            }
            if (num > 0 && num < 16 && numColumn == 0){
                card[numRow][numColumn] = num;
                numColumn++;
            }
            else if (num < 31 && numColumn == 1){
                card[numRow][numColumn] = num;
                numColumn++;
            }
            else if (num < 46 && numColumn == 2){
                if(numRow == 2 && num == 0){
                    card[numRow][numColumn] = num;
                } else {
                    fprintf(stderr, "%s has bad format\n", argv[2]);
                    exit(4);
                }
                numColumn++;
            }
            else if (num < 61 && numColumn == 3){
                card[numRow][numColumn] = num;
                numColumn++;
            }
            else if (num < 76 && numColumn == 4){
                card[numRow][numColumn] = num;
                numColumn = 0;
                numRow++;
            }
        } else {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
        }
    }

    //exit 2
    if(atoi(argv[1]) == 0){
        fprintf(stderr, "the seed, %s, is not valid\n", argv[2]);
        exit(2);
    }

    fclose(fp);
    return(1);
}

char markCard(int card[][4], char markings[][4], int calls[], int max){ 
    int num = calls[max-1];

    for(int i=0; i<5; i++){ 
        for(int j=0; j<5; j++){
            if(card[i][j] == num){
                markings[i][j] = 'm';
            }
        }
    }
}   

int contains_int(int nums[],int target, int max){
    for(int i=0; i<max; i++){
        if(nums[i] == target){
            return(1);
        }
    }
    return(0);
}


int roll(int called[], int counter ) 
{
    int num;
    do{
        num = (1 + rand() % 75);  // gets a random number from 1 to 75    
    } while (contains_int(called, num, counter) == 1);

    called[counter] = num;
    counter = counter++;
}

int printCallRow(int called[], int max){
    if(max != 0){
        printf("Call Row: ");
        for(int i=0; i<max; i++){
            switch (called[i])
            {
            case 1 ... 15:
                printf("B%02d ", called[i]);
                break;
            case 16 ... 30:
                printf("I%d ", called[i]);
                break;
            case 31 ... 45:
                printf("N%d ", called[i]);
                break;
            case 46 ... 60:
                printf("G%d ", called[i]);
            case 61 ... 75:
                printf("O%d ", called[i]);
                break;
            
            }
        }
    }
}

int printCard(int card[][4], char marks[][4]){
    printf(" B  I  N  G  O \n");
    for (int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("\n");
            printf("%02d%c ", card[i][j], marks[i][j]);
        }
    }
}

int winningRows(char markings[][4])
{
    for (int i = 0; i >= 4; i++){
        if (markings[i][0] == 'm' && markings[i][1] == 'm' && markings[i][2] == 'm' && markings[i][3] == 'm' && markings[i][4] == 'm'){
            return 0;
        } else if (markings[0][i] == 'm' && markings[1][i] == 'm' && markings[2][i] == 'm' && markings[3][i] == 'm' && markings[4][i] == 'm'){
            return(0);
        }  
    }
    if (markings[0][0] == 'm' && markings[4][0] == 'm' && markings[0][4] == 'm' && markings[4][4] == 'm'){
        return(0);
    }   
    return(0);
}

char card(int card[][4]){
    char userinput[50];
    int calledNums[75];
    char cardMarkings[4][4];
    int callRowCounter;

    cardMarkings[2][2] = 'm';

    do {
        printCallRow(calledNums, callRowCounter);
        printCard(card, cardMarkings);
        printf("Enter any character to roll or press q to quit.\n");
        scanf("%s", userinput);
        if (strlen(userinput) > 0) {    // ensures it doesnt run when no characters are entered
            for(int i=0; i<= strlen(userinput); i++) {   // handles for any amount of characters given
                if (userinput[i] != 'q') {
                    roll(calledNums, callRowCounter);
                    markCard(card, cardMarkings, calledNums, callRowCounter);
                    if(winningRows(cardMarkings) == 0){
                        system("clear");
                        printCallRow(calledNums, callRowCounter);
                        printCard(card, cardMarkings);
                        printf("WINNER!\n");
                        exit(0);
                    }
                } else {
                    exit(0);     // quits the game prematurely
                }
            }
            printCard(card, cardMarkings);
            system("clear");    // clears the screen for the next card
        }
        
    } while(winningRows(cardMarkings) != 1);  // checks if it is a winning card
    
}

int main(int argc, char *argv[]){

    char cardName[30];
    int cardNums[4][4];
    int seed;

    if (argc == 3){     
        if(card_checker(cardNums, argv) == 1){
            seed = (int)*argv[1];
            card(cardNums);
        }
    } else {
        fprintf(stderr, "Usage: %s() seed cardFile\n", __FILE__);
        exit(1);
    }
}
