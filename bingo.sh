#!/bin/bash

card_checker(){
    if [[! -f "$cardName" ]]; then
        echo "the file from the input cannot be read" >&2; exit 1;
    fi
    if [[! $(`wc -l "$cardName" < "$cardName"`) -eq 6 ]]; then
        echo "there must be 6 lines in the input" >&2; exit 2;
    fi
    if [[ !`$(head -n 1 "$cardName")` ]]; then
        echo "there is a error in the seed line" >&2; exit 3;
    fi
    local temp=`(tail -n 5 "$cardName")`
    if [[ ! $(echo "$temp" | tr " " "\n" | wc -l "$temp" < "$temp") -eq 25 ]]; then
        echo "card format error" >&2; exit 4;
    else
        for num in "$temp"; do
            if [[ ! $(echo "$num" | grep -E '[0-9]{2}') ]]; then
                echo "card format error" >&2; exit 4;
            fi
        done
    fi
}
#fix last two if statements

markCard(){
    target="$1" # the rolled number
    # determines which column
    if (( "$target" > 0 && "$target" < 16 )); then
        column = 0
    elif (( "$target" < 31 )); then
        column = 1
    elif (( "$target" < 46 )); then
        column = 2
    elif (( "$target" < 61 )); then
        column = 3
    elif (( "$target" < 76 )); then
        column = 4
    fi
    if (( "$target" < 10 )); then # adds a 0 infront if it is a single digit number to do exact grep search later
        target="0${target}"
    fi
    if [[ $(grep \<$target\> "$cardNums") ]]; then   # if the number target is in the card then add m after the number in the 2d array
        for i in [0-4]; do
            if (( "$cardNums["$i", "$column"]" == "$target" )); then
                cardNums["$i", "$column"] = "${cardNums["$i", "$column"]}m"
            fi
        done
    fi
}


roll(){
    num=(1 + "$RANDOM" % 75)        # generates a random number
    while [[ $(grep "$num" "$callRow"[*]) ]]       # checks if the number has already been called or not
    do                                  # continues to generate numbers until it reaches a number that it has not called
        num=(1 + "$RANDOM" % 75)
    done
    # will add the new number to the call rown in the correct format with the letter
    case "$num" in
            [1-15])
                if [num < 10]; then # checks if the number generated is a single digit so it will be displayed as double digits
                    callRow["$counter"]="L0${num}"
                else    # Everything else after assumes that the numbers are double digits
                     callRow["$counter"]="L${num}"
                fi
                ;;
            [16-30])
                callRow["$counter"]="I${num}"
                ;;
            [31-46])
                callRow["$counter"]="N${num}"
                ;;
            [46-60])
                callRow["$counter"]="U${num}"
                ;;
            [61-75])
                callRow["$counter"]="X${num}"
                ;;
        esac       
    markCard "$num"
    counter="$counter" + 1
}


winningRows(){
    for i in [0-4]; do
        if [[ ${cardNums[$i,0]} == "??m" ]] && [[ ${cardNums[$i,1]} == "??m" ]] && [[ ${cardNums[$i,2]} == "??m" ]] && [[ ${cardNums[$i,3]} == "??m" ]] && [[ ${cardNums[$i,4]} == "??m" ]]
        then
            echo "WINNER" 
            exit 0;
        fi

        if [[ ${cardNums[0,$i]} == "??m" ]] && [[ ${cardNums[1,$i]} == "??m" ]] && [[ ${cardNums[2,$i]} == "??m" ]] && [[ ${cardNums[3,$i]} == "??m" ]] && [[ ${cardNums[4,$i]} == "??m" ]]
        then
            echo "WINNER" 
            exit 0;
        fi
    done
    if [[${cardNums[0,0]} == "??m" ]] && [[ ${cardNums[0,4]} == "??m" ]] && [[ ${cardNums[4,4]} == "??m" ]] && [[ ${cardNums[4,0]} == "??m" ]]
    then
        echo "WINNER"  
        exit 0;
    fi
}

RANDOM="$(head -n 1)"

counter=0 
callRow[0]="" #initializes the array to be global
cardName="$1"
cardNums="$(tail -n 5 "$cardName")" #Get 5x5 matrix from file

#code that marks 00
cardNums[2,2]="${cardNums[2,2]}m"

# prints the card
echo " B I N G O"
echo "$cardNums"
# asks for user input to roll or to quit
echo "Enter any character to roll or press q to quit: " 
read userInput
while [[ "$userInput" != "q" ]]
do 
    roll
    echo "Call Row:${callRow}"
    echo " B I N G O"
    echo "$cardNums"
    winningRows
done

exit 0;
