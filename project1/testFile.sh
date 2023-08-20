#!/bin/bash

# checking the number of arguments given from the command line
count=$#
if [ $count -ne 4 ]
then
    echo "Wrong number of arguments"
    exit -1
fi

# checking the viruses file
file=$1
# checking if it exists
if [ -f "$file" ]
then
    echo
else
    echo "File does not exist"
    exit -1
fi
viruses=()
viruses_size=0;

# saving each line from the file in an array
while read line; 
do
    len=${#line}
    viruses[viruses_size]=${line:0:len-1}
    ((viruses_size++))
done < $file

# checking the countries file
file=$2
# checking if it exists
if [ -f "$file" ]
then
    echo
else
    echo "File does not exist"
    exit -1
fi
countries=()
countries_size=0;

# saving each line from the file in an array
while read line; 
do
    len=${#line}
    countries[countries_size]=${line:0:len-1}
    ((countries_size++))
done < $file

numLines=$3
duplicatesAllowed=$4

# cretaing the file
touch inputFile.txt

ids=()
# creating and shuffling an array of ids we will use for the script
for(( i=0; i<10000; i++))
do
    ids[i]="$i";
done

for(( i=0; i<10000; i++))
do
    j=$RANDOM
    let "j %= 10000"
    temp=${ids[j]}
    ids[j]=${ids[i]}
    ids[i]=$temp;
done

ids_size=0
index=-1
space=" "
for(( record=1; record<=numLines; record++ ))
do

    # randomizing if we will use the same citizen or not
    same_id=$RANDOM
    let "same_id %= 2"

    # if we don't have the same id or this is the first one
    if [[ ($same_id -eq 0 || ids_size -eq 0) ]]
    then

        ((index++))
        duplicate_id=$RANDOM
        let "duplicate_id %= 2"

         # we won't have a duplicate id since they won't be allowed or chosen by chance
        if [[ ($duplicatesAllowed -eq 0 || $duplicate_id -eq 0 || ids_size -eq 0) ]]
        then
            # creating an id 
            id=${ids[index]}
        fi

        ((ids_size++))

        # determining the length 
        fn_length=$RANDOM
        let "fn_length %= 10"
        ((fn_length+=3))

        # pool of letters in order to randomize the names
        caps=ABCDEFGHIJKLMNOPQRSTUVWXYZ
        letters=abcdefghijklmnopqrstuvwxyz

        # randomizing the first and only capital letter of the first name
        first_name=${caps:RANDOM%${#caps}:1}

        # randomizing the rest of the letters for the name
        for (( char=1; char<fn_length; char++ ))
        do
            # appending all the letters together to form the name itself
            first_name+="${letters:RANDOM%${#letters}:1}"
        done

        # determining the length 
        ln_length=$RANDOM
        let "ln_length %= 10"
        ((ln_length+=3))

        # randomizing the first and only capital letter of the last name
        last_name=${caps:RANDOM%${#caps}:1}

        # randomizing the rest of the letters for the name
        for (( char=1; char<ln_length; char++ ))
        do
            # appending all the letters together to form the name itself
            last_name+="${letters:RANDOM%${#letters}:1}"
        done

        # choosing a random country from the countries array made from the file
        country_index=$RANDOM
        let "country_index %= countries_size"
        country=${countries[country_index]}

        # creating an age and turning it into a string
        age=$RANDOM
        let "age %= 121"
        age="$age"

    fi

    # choosing a random virus from the viruses array made from the file
    virus_index=$RANDOM
    let "virus_index %= viruses_size"
    virusName=${viruses[virus_index]}

    # choosing randomly if the citizen is randomly vaccinated or not
    is_vaccinated=$RANDOM
    let "is_vaccinated %= 2"

    yesno="NO"

    # adding a date if the citizen is vaccinated or not
    if [ $is_vaccinated -eq 1 ]
    then
        yesno="YES"
    fi

    date=""
    date_exists=$RANDOM
    let "date_exists %= 2" 

    if [ $date_exists -eq 1 ]
    then
        zero="0"

        # determining the day randomly
        day=$RANDOM
        let "day %= 30"
        ((day++))
        day="$day"

        # adding additional 0 if we have single digit
        if [ $day -lt 10 ]
        then 
            day="$zero$day"
        fi

        # determining the month randomly
        month=$RANDOM
        let "month %= 12"
        ((month++))
        month="$month"

        # adding additional 0 if we have single digit
        if [ $month -lt 10 ]
        then 
            month="$zero$month"
        fi

        # determining the year randomly ranging between his age
        # year=$RANDOM
        # let "year %= age+1"
        # ((year=2021-year))

        # appending day-month-year to date
        date="$day-$month-2020"
    fi
    

    # storing the record in an array of records
    current_record1="$id $first_name $last_name $country $age $virusName $yesno $date" 
    echo ${current_record1}>>inputFile.txt

done

exit 0