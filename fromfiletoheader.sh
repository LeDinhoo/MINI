#!/bin/bash

# Vérifie si le nombre d'arguments est correct
if [ $# -lt 2 ]; then
    echo "Usage: $0 <source_directory> <header_file>"
    exit 1
fi

source_directory="$1"
header_file="$2"

# Vérifie si le fichier d'en-tête existe, sinon le crée
if [ ! -e "$header_file" ]; then
    touch "$header_file"
fi

# Parcours récursivement le répertoire source
find "$source_directory" -type f -name "*.c" | while read -r source_file; do                                                                                                                                                 ─╯
    grep -E "^[a-zA-Z_].*\(.*\)" "$source_file" >> "$header_file"
done

echo "Déclarations de fonctions extraites avec succès et ajoutées à $header_file"
