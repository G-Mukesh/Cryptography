#include<stdio.h>
int gcd(int a, int b) 
{
	if (b == 0)
	return a;
	return gcd(b, a % b);
}
int main() 
{
	int a;
	printf("Values of 'a' not allowed (because they are not relatively prime with 26):\n");
	for (a = 0; a < 26; a++) {
		if (gcd(a, 26) != 1){
			printf("%d",a);
		} 
		printf("\n");
		
	}
	
	return 0;
}
