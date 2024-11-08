#!/bin/bash                                                                     

# Sjekk om det er nøyaktig to argumenter
if [ $# -ne 2 ]; then
    echo "usage: $0 katalog1 katalog2"
    exit 1
fi

# Sjekk om katalogene er skrivbare og lesbare
if [ ! -d "$1" ] || [ ! -w "$1" ] || [ ! -d "$2" ] || [ ! -w "$2" ]; then
    echo "Feil: $1 og/eller $2 mangler skrive- og/eller lesetilgang"
    exit 1
fi

# Flytt .mp3-filer fra katalog 1 til katalog 2 og tell antall flyttede filer
count=0
for file in "$1"/*.mp3; do
    if [ -e "$file" ]; then
        mv "$file" "$2"
        count=$((count + 1))
    fi
done

# Skriv ut resultat
echo "Flyttet $count mp3-filer fra $1 til $2"
