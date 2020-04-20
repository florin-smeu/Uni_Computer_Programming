#include <stdio.h>

void convert_to_binary(int n)
{
	int i;

	for (i = 7; i > 0; i--) {
		if (n & ((1 << i) != 0)) printf("1");
		else printf("0");
	}
	
	printf(".");
}

void convert_to_32(int n)	//?
{
	if (n / 32 != 0) {	
		printf("%d", n / 32);
	}
	
	if (n % 32 <= 9) {
		printf("%d", n % 32);
	}
	else printf("%c", n % 32 - 10 + 'A');
	
	printf(".");
}

int main(void)
{	
	int num, mask, mask_net, n_sets;
	int ip1_3, ip1_2, ip1_1, ip1_0;
	int ip2_3, ip2_2, ip2_1, ip2_0;
	int net_3, net_2, net_1, net_0;
	int mask1_3, mask1_2, mask1_1, mask1_0;
	int network_addr1_3, network_addr1_2, network_addr1_1, network_addr1_0;	
	int broadcast_addr1_3, broadcast_addr1_2;
	int broadcast_addr1_1, broadcast_addr1_0;
	
	int i, j, k;
	char c; 

	scanf("%d", &n_sets);	//reading the number of data sets
	
	for (i = 0; i < n_sets; i++) {
		
		printf("%d\n", i+1);		
		
		scanf("%d", &ip1_3);	//reading IP_1
		scanf("%c", &c);
		scanf("%d", &ip1_2);
		scanf("%c", &c);
		scanf("%d", &ip1_1);
		scanf("%c", &c);
		scanf("%d", &ip1_0);
		
		scanf("%c", &c); //reading IP_1's subnet mask
		scanf("%d", &mask); 
		scanf("%c", &c);

		scanf("%d", &ip2_3);	//reading IP_2
		scanf("%c", &c);
		scanf("%d", &ip2_2);
		scanf("%c", &c);
		scanf("%d", &ip2_1);
		scanf("%c", &c);
		scanf("%d", &ip2_0);
	
		scanf("%c", &c);
		scanf("%d", &num);	//reading natural integer NUM
		scanf("%c", &c);
 
		while (num != 0) {	//reading the network adresses & their masks
			
			scanf("%d", &net_3);
			scanf("%c", &c);
			scanf("%d", &net_2);
			scanf("%c", &c);
			scanf("%d", &net_1);
			scanf("%c", &c);
			scanf("%d", &net_0);
			
			scanf("%c", &c);
			scanf("%d", &mask_net); 
			scanf("%c", &c);
			
			num--; 
		} 

		printf("\n");
		
		printf("%s", "-0 ");	//task 0
		
		printf("%d", ip1_3);
		printf(".");
		printf("%d", ip1_2);
		printf(".");
		printf("%d", ip1_1);
		printf(".");
		printf("%d\n", ip1_0);

		printf("%s", "-1 ");	//task 1

		if (mask >=1 && mask <=8) {
			mask1_3 = 1;
			for(j = 1; j  < mask; j++) {
				mask1_3 *= 2;
				mask1_3 += 1;	
			}
			for (k = 0; k < (8 - mask); k++) {
				mask1_3 *= 2;
			}
		} else if (mask >=9 && mask <=16) {
			mask1_3 = 255;
			for(j = 9; j  < mask; j++) {
				mask1_2 *= 2;
				mask1_2 += 1;	
			}
			for (k = 0; k < (16 - mask); k++) {
				mask1_2 *= 2;
			}
		}
		if (mask >=17 && mask <=24) {
			mask1_3 = 255;
			mask1_2 = 255;
			for(j = 17; j  < mask; j++) {
				mask1_1 *= 2;
				mask1_1 += 1;	
			}
			for (k = 0; k < (24 - mask); k++) {
				mask1_1 *= 2;
			}

		if (mask >=25 && mask <=32) {
			mask1_3 = 255;
			mask1_2 = 255;
			mask1_1 = 255;
			mask1_0 = 1;
			for(j = 25; j  < mask; j++) {
				mask1_0 *= 2;
				mask1_0 += 1;	
			}
			for (k = 0; k < (32 - mask); k++) {
				mask1_0 *= 2;
			}
		}
		printf("%s", "-2 ");	//task 2

		network_addr1_3 = ip1_3 & mask1_3;
		network_addr1_2 = ip1_2 & mask1_2;
		network_addr1_1 = ip1_3 & mask1_1;
		network_addr1_0 = ip1_3 & mask1_0;

		printf("%d", net_addr1_3);
		printf(".");
		printf("%d", net_addr1_2);
		printf(".");
		printf("%d", net_addr1_1);
		printf(".");
		printf("%d\n", net_addr1_0);

		printf("%s", "-3 ");	//task 3

		broadcast_addr1_3 = ip1_3 | mask1_3;	//?
		broadcast_addr1_2 = ip1_2 | mask1_2;
		broadcast_addr1_1 = ip1_3 | mask1_1;
		broadcast_addr1_0 = ip1_3 | mask1_0;

		printf("%d", broadcast_addr1_3);
		printf(".");
		printf("%d", broadcast_addr1_2);
		printf(".");
		printf("%d", broadcast_addr1_1);
		printf(".");
		printf("%d\n", broadcast_addr1_0);

		printf("%s", "-4 ");	//task 4
	
		printf("%s", "-5 ");	//task 5
	
		printf("%X", ip1_3);	
		printf(".");
		printf("%X", ip1_2);
		printf(".");
		printf("%X", ip1_1);
		printf(".");
		printf("%X", ip1_0);
		printf(" ");

		printf("%o", ip2_3);
		printf(".");
		printf("%o", ip2_2);
		printf(".");
		printf("%o", ip2_1);
		printf(".");
		printf("%o\n", ip2_0);

		printf("%s", "-6 ");	//task 6

		printf("%s", "-7 ");	//task 7
 		
		convert_to_binary(ip1_3);
		printf(".");		
		convert_to_binary(ip1_2);
		printf(".");
		convert_to_binary(ip1_1);
		printf(".");
		convert_to_binary(ip1_0);
		printf(" ");

		convert_to_binary(ip2_3);
		printf(".");		
		convert_to_binary(ip2_2);
		printf(".");
		convert_to_binary(ip2_1);
		printf(".");
		convert_to_binary(ip2_0);
		printf("\n");
		
		printf("%s", "-8 ");	//task 8

		convert_to_32(ip1_3);
		printf(".");		
		convert_to_32(ip1_2);
		printf(".");
		convert_to_32(ip1_1);
		printf(".");
		convert_to_32(ip1_0);
		printf(" ");

		convert_to_32(ip2_3);
		printf(".");		
		convert_to_32(ip2_2);
		printf(".");
		convert_to_32(ip2_1);
		printf(".");
		convert_to_32(ip2_0);
		printf("\n");
		
	}

	return 0;
}
