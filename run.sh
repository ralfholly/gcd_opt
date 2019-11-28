echo
echo "Regular GCD algorithm"
echo "---------------------"
make CPPFLAGS='-W -Wall -O3 -funroll-all-loops -DALGORITHM=ALG_REGULAR -DARGUMENTS=ARG_NOSWAP -DOUTER_ITERATIONS=1000 -DINNER_ITERATIONS=10000'

echo
echo "Optimized GCD algorithm"
echo "-----------------------"
make CPPFLAGS='-W -Wall -O3 -funroll-all-loops -DALGORITHM=ALG_OPTIMIZED -DARGUMENTS=ARG_NOSWAP -DOUTER_ITERATIONS=1000 -DINNER_ITERATIONS=10000'
