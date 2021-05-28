#include<stdio.h>
#include<math.h>

int main() {
	int N , decimal = 0 , i;
	scanf("%d" , &N);
	for(i = 0; N > 0; i++) {
		decimal += pow(2 , i) * (N % 10);
		N /= 10;
	}
	
	printf("%d\n" , decimal);
	
	return 0;
}
