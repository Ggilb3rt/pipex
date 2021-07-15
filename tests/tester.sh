#!/bin/bash

RED='\033[0;31m'
ORANGE='\033[0;33m'
LGRAY='\033[;37m'
LBLUE='\033[1;34m'
PURP='\033[0;35m'
NC='\033[0m'

#des=`jq '.[0].description' list.json` | `awk '{print substr($0, 2, length($0) - 2)}'`
des=`jq '.[0].description' list.json | awk '{print substr($0, 2, length($0) - 2)}'`
printf "$des"

printf "\n${ORANGE}0 commandes${NC}\n"
../pipex ./in "" "" ./out
< ./in "" | "" > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}cmd1 vide${NC}\n"
../pipex ./in "" "ls" ./out
< ./in "" | ls > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}cmd2 vide${NC}\n"
../pipex ./in "cat" "" ./out
< ./in cat | "" > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "${ORANGE}Cherche 'la' dans tests/Nina et affiche le nombe de lignes${NC}\n"
../pipex ./Nina "grep la" "wc -l" ./out
< ./Nina grep la | wc -l > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}Cherche '!' dans tests/in${NC}\n"
../pipex ./in "grep !" "wc -l" ./out
< ./in grep ! | wc -l > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}Une part de clafouti !${NC}\n"
../pipex ./in "une part" "de clafouti" ./out
< ./in une part | de clafouti > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}Vrai commande faux arguments${NC}\n"
../pipex ./in "cat -mi-ours mi-scorpion" "wc mi-ours" ./out
< ./in cat mi-ours mi-scorpion | wc mi-ours > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}path in cmd (first cmd empty)${NC}\n"
../pipex ./in "" "/bin/ls" ./out
< ./in "" | /bin/ls > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}paths in cmd${NC}\n"
../pipex ./in "/usr/bin/grep w" "cat -e" ./out
< ./in /usr/bin/grep w | cat -e > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR

printf "\n${ORANGE}Wrong path to in file${NC}\n"
../pipex ./pouet "/usr/bin/grep w" "cat -e" ./out
< ./pouet /usr/bin/grep w | cat -e > ./outR
cat -e ./out
cat -e ./outR
diff ./out ./outR
rm ./out
rm ./outR