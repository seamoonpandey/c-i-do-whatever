#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void playGame(int numPlayers, int top) {
    int turn = 0;
    char player[numPlayers][20];
    int finalscore[numPlayers];
    int consecutiveSixCount[numPlayers];

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    for (int i = 0; i < numPlayers; i++) {
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
        finalscore[i] = 0;
        consecutiveSixCount[i] = 0;
    }

    while (1) {
        int current = rand() % 6 + 1;
        printf("%s got %d \n", player[turn % numPlayers], current);
        sleep(1);

        finalscore[turn % numPlayers] += current;
        if (current == 6) {
            consecutiveSixCount[turn % numPlayers]++;
            printf("Consecutive six count for %s: %d\n", player[turn % numPlayers], consecutiveSixCount[turn % numPlayers]);
            
            if (consecutiveSixCount[turn % numPlayers] == 3) {
                printf("Oh no! %s rolled three consecutive 6s and gets a penalty of -6!\n", player[turn % numPlayers]);
                finalscore[turn % numPlayers] -= 12;
                consecutiveSixCount[turn % numPlayers] = 0; 
            } else {
                printf("Wow! %s rolled a 6 and gets another chance.\n", player[turn % numPlayers]);
            }
        } else {
            consecutiveSixCount[turn % numPlayers] = 0; 
            printf("%s's current score is now %d \n", player[turn % numPlayers], finalscore[turn % numPlayers]);
            printf("Loading next turn .... \n");
            sleep(1.5);
            turn += 1;
        }

        printf("\n");

        // Check if any player has reached the final score
        for (int i = 0; i < numPlayers; i++) {
            if (finalscore[i] >= top) {
                printf("%s is the winner with a score of %d!\n", player[i], finalscore[i]);
                return;
            }
        }
    }
}

int main() {
    int numPlayers, top;

    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    printf("What shall be the final score: ");
    scanf("%d", &top);

    playGame(numPlayers, top);

    return 0;
}
