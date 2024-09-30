for fichier in sfxreload*.xpm; do
    numero=$(echo "$fichier" | sed 's/[^0-9]*\([0-9]\+\).*/\1/')
    nouveau_numero=$((numero + 11))
    mv "$fichier" "sfxgun${nouveau_numero}.xpm"
done