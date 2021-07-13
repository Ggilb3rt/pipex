echo 'Cherche "la" dans tests/Nina\n'
./pipex tests/Nina "grep la" "wc -l" tests/out
cat tests/out

echo "Cherche '!' dans tests/in\n"
./pipex tests/in "grep !" "wc -l" test/out
cat tests/out

echo "0 commandes"
./pipex tests/in "" "" tests/out
cat tests/out