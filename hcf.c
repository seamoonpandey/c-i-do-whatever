/ *
This is euclidean algorithm to calculate the hcf of a numbers using subtraction shit
*/

#include <stdio.h>


int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    while (a != b)
        a > b ? (a -= b) : (b -= a);

    printf("HCF is %d\n", a);
    return 0;
}

