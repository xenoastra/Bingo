#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//#include "listADT.h"


char card(){
char userinput;
printf(" B I N G O \n");
printf("Enter a character to roll or press q to quit.\n");
scanf("%s", &userinput);

    while(userinput != "q") { // make this into a do while loop
        
    }
    while(winningRows != true) { // make this into a do while}
// minor
}

char markCard() 
{ 
double target;
    int target = [1];
    int column;

    if (target > 0 && target < 16){
        column = 0;
    }
    else if (target < 31){
        column = 1;
    }
    else if (target < 46){
        column = 2;
    }
    else if (target < 61){
        column = 3;
    }
    else if (target < 76){
        column = 4;
    }
    if (target < 10){
        target = "0"+ target;
    }
} 

char roll() 
{
    int number = 0;
    // math.random;
    number = (1 + "$RANDOM" % 75)    
    while (grep "$num" "$callRow"[*]){

    }      // checks if the number has already been called or not
    do                                  //# continues to generate numbers until it reaches a number that it has not called
        num = (1 + "$RANDOM" % 75);

   // # will add the new number to the call rown in the correct format with the letter
   //this really 
    for (i >= 1; i <= 15; i++) {
//         if (num < 10){ //# checks if the number generated is a single digit so it will be displayed as double digits
//             callRow = printf("L0", num); //this might be wrong
//         }
        if (num <= 1 && num > 15){ //# checks if the number generated is a single digit so it will be displayed as double digits
            callRow = printf("B", num); //this might be wrong
        }
        // else    //# Everything else after assumes that the numbers are double digits
        //      callRow["$counter"]="L${num}"        
        if (num < 16 && num > 30){
            callRow = printf("I", num); //this might be wrong ";
        }
        if (num < 31 && num > 46){
            callRow = printf("N", num);
        }
        if (num < 47 && num > 60){
            callRow = printf("G", num);
        }
        if (num < 61 && num > 75){
            callRow = printf("O", num);
        }          
    }   
    markCard "$num";
    counter = counter + 1;
}
