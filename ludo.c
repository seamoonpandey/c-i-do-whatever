#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 

int main() {
    int turn = 0;
    char player[3][20]; 
    int finalscore[3] = {0}; 

    for (int i = 0; i < 3; i++) {
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
    }

    while (finalscore[0] < 100 && finalscore[1] < 100 && finalscore[2] < 100) {
        int current = rand() % 6 + 1;
        printf("%s got %d \n", player[turn % 3], current);
        sleep(1);

		finalscore[turn % 3] += current;

        if (current == 6) {
            printf("Wow! %s rolled a 6 and gets another chance.\n", player[turn % 3]);
        } else {
            printf("%s's current score is now %d \n", player[turn % 3], finalscore[turn % 3]);
            printf("Loading next turn .... \n");
            sleep(2);
            turn += 1;
        }
    }

    if (finalscore[0] >= 100) {
        printf("%s is the fucking winner", player[0]);
    } else if (finalscore[1] >= 100) {
        printf("%s is the fucking winner", player[1]);
    } else {
        printf("%s is the sucking winner", player[2]);
    }

    return 0;
}
