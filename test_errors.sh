./quad < ./error_test_cases/testError1-1.txt | grep 'error 1' &&
./quad < ./error_test_cases/testError1-2.txt | grep 'error 1' &&
./quad < ./error_test_cases/testError1-3.txt | grep "error 1" &&
./quad < ./error_test_cases/testError2-1.txt | grep "error 2" &&
./quad < ./error_test_cases/testError2-2.txt | grep "error 2" &&
./quad < ./error_test_cases/testError2-3.txt | grep "error 2" &&
./quad < ./error_test_cases/testError3-1.txt | grep "error 3" &&
./quad < ./error_test_cases/testError3-2.txt | grep "error 3" &&
./quad < ./error_test_cases/testError3-3.txt | grep "error 3" &&
./quad < ./error_test_cases/testError4-1.txt | grep "error 4" &&
./quad < ./error_test_cases/testError4-2.txt | grep "error 4" &&
./quad < ./error_test_cases/testError4-3.txt | grep "error 4"
