#include <stdio.h>
#include <math.h>


double factorial(int n) {
	int i;
    double result = 1;
    for (i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}


double log2Factorial(int n) {
    return log2(factorial(n));
}

int main() {
    
    double possibleKeys = factorial(25);
    double log2PossibleKeys = log2Factorial(25);
    
 
    printf("Number of possible Playfair keys: %.0f (approx 2^%.2f)\n", possibleKeys, log2PossibleKeys);
    
    
    double uniqueKeys = possibleKeys / 24;
    double log2UniqueKeys = log2PossibleKeys - log2(24);
    
 
    printf("Number of effectively unique Playfair keys: %.0f (approx 2^%.2f)\n", uniqueKeys, log2UniqueKeys);
    
    return 0;
}

