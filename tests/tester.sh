#!/bin/bash

RED='\033[0;31m'
ORANGE='\033[0;33m'
LGRAY='\033[;37m'
LBLUE='\033[1;34m'
PURP='\033[0;35m'
NC='\033[0m'

printf "\n${ORANGE}0 commandes${NC}\n"
../pipex ./in "" "" ./out
cat -e ./out

printf "\n${ORANGE}1 commandes sur deux${NC}\n"
../pipex ./in "" "ls" ./out
cat -e ./out

printf "${ORANGE}Cherche 'la' dans tests/Nina${NC}\n"
../pipex Nina "grep la" "wc -l" ./out
cat -e ./out

printf "\n${ORANGE}Cherche '!' dans tests/in${NC}\n"
../pipex ./in "grep !" "wc -l"./out
cat -e ./out

printf "\n${ORANGE}Une part de clafouti !${NC}\n"
../pipex ./in "une part" "de clafouti" ./out
cat -e ./out

printf "\n${ORANGE}Vrai commande faux arguments${NC}\n"
../pipex ./in "cat -mi-ours mi-scorpion" "wc mi-ours" ./out
cat -e ./out

printf "\n${ORANGE}path in cmd${NC}\n"
../pipex ./in "" "/bin/ls" ./out
cat -e ./out