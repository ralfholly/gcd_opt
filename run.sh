echo
echo "Regular GCD algorithm"
echo "---------------------"
make CPPFLAGS='-W -Wall -O3 -funroll-all-loops -DALGORITHM=ALG_REGULAR -DARGUMENTS=ARG_SMALLFIRST -DOUTER_ITERATIONS=1000 -DINNER_ITERATIONS=10000'

echo
echo "Optimized GCD algorithm"
echo "-----------------------"
make CPPFLAGS='-W -Wall -O3 -funroll-all-loops -DALGORITHM=ALG_OPTIMIZED -DARGUMENTS=ARG_SMALLFIRST -DOUTER_ITERATIONS=1000 -DINNER_ITERATIONS=10000'

echo
echo "Optimized2 GCD algorithm"
echo "------------------------"
make CPPFLAGS='-W -Wall -O3 -funroll-all-loops -DALGORITHM=ALG_OPTIMIZED2 -DARGUMENTS=ARG_SMALLFIRST -DOUTER_ITERATIONS=1000 -DINNER_ITERATIONS=10000'
