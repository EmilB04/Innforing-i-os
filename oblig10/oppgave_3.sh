#!/bin/bash

# Sjekk om filnavn er gitt som parameter
if [ $# -ne 1 ];
then
    echo "usage: $0 filename"
    exit 1
fi

# Sjekk om filen eksisterer
if [ ! -e "$1" ];
then
    echo "Feil: Filen $1 finnes ikke."
    exit 1
fi

# Finn filstørrelse for første gang
if [[ "$OSTYPE" == "darwin"* ]];
then
    size=$(stat -f "%z" "$1")  # For MacOS
else
    size=$(stat -c "%s" "$1")  # For Linux
fi

# Start en evig løkke som overvåker filstørrelsen
while true;
do
    sleep 60  # Vent i ett minutt

    # Sjekk filstørrelse på nytt
    if [[ "$OSTYPE" == "darwin"* ]];
    then
        new_size=$(stat -f "%z" "$1")  # For MacOS
    else
        new_size=$(stat -c "%s" "$1")  # For Linux
    fi

    # Sjekk om filstørrelsen har endret seg
    if [ "$new_size" -ne "$size" ];
    then
        echo "Filen $1 har endret størrelse."
        exit 0
    fi
done
