#!/bin/bash

# Point de départ des nouveaux numéros
start_number=34

# Numéro actuel dans la série (équivalent à 21)
current_number=21

# Boucle à travers tous les fichiers correspondants
for file in loding*.xpm; do
  # Calculer le nouveau numéro en fonction de la différence
  new_number=$((start_number + current_number - 21))

  # Construire le nouveau nom de fichier
  new_file="loding${new_number}.xpm"

  # Renommer le fichier
  mv "$file" "$new_file"

  echo "Renommé : $file -> $new_file"

  # Incrémenter le numéro actuel
  current_number=$((current_number + 1))
done
