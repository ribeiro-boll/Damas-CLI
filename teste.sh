#!/usr/bin/env bash

DELAY_TYPE=0.5      
DELAY_BEFORE_ENTER=1 
DELAY_AFTER_ENTER=1  
MOVES=(
    C6 D5
D3 C4
E6 F5
F3 E4
G6 H5
H3 G4
A6 B5
B3 A4
D5 F3
G2 E4 G6
B7 C6
C4 A6
C8 B7
A6 C8 
H5 F3
E2 G4
F7 H5 F3
C8 g4 e2

)
default_ifs=$IFS
read -p "Foque na janela do jogo de damas e pressione Enter para iniciar..."
sleep 3
for mv in "${MOVES[@]}"; do
  xdotool type --delay $(echo "$DELAY_TYPE*1000" | bc | awk '{print int($1)}') "$mv"
  sleep "$DELAY_BEFORE_ENTER"
  xdotool key Return
  sleep "$DELAY_AFTER_ENTER"
done