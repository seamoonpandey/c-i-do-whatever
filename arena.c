#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_TURNS 50

void playGame(int numPlayers, int initialHP, int lucky_hp_threshold) {
    int turn = 0;
    char **player = (char **)malloc(numPlayers * sizeof(char *));
    int *healthPoints = (int *)malloc(numPlayers * sizeof(int));

    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    // Dynamically allocate memory for player names
    for (int i = 0; i < numPlayers; i++) {
        player[i] = (char *)malloc(20 * sizeof(char));
        printf("Enter player %d's name: ", i + 1);
        scanf("%s", player[i]);
        healthPoints[i] = initialHP;
    }

    int turns = 0;
    while (turns < MAX_TURNS) {
        int attack = rand() % 7;
        printf("%s attacks with a damage of %d \n", player[turn % numPlayers], attack);
        sleep(1);

        if (attack == 6) {
            if (healthPoints[turn % numPlayers] <= lucky_hp_threshold) {
                // If the player's health is below the threshold, gaining 5 HP even with a lucky attack
                printf("Lucky! %s's attack was successful, and they gain 5 HP.\n", player[turn % numPlayers]);
                healthPoints[turn % numPlayers] += 5;
            } else {
                printf("Lucky! %s's attack was successful.(Threshold HP rule prohibits hp addition)\n", player[turn % numPlayers]);
            }
        } 
            // Decrease health points of other players
            for (int i = 0; i < numPlayers; i++) {
                if (i != turn % numPlayers) {
                    healthPoints[i] -= attack;

                    // Ensure health points don't go below zero
                    if (healthPoints[i] < 0) {
                        healthPoints[i] = 0;
                        printf("%s has run out of health and is eliminated!\n", player[i]);
                    }
                }
            }

        printf("Health Points:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s: %d  ", player[i], healthPoints[i]);
        }
        printf("\n");

        // Check if any player is left with positive health points
        int remainingPlayers = 0;
        int lastStandingPlayerIndex = -1;

        for (int i = 0; i < numPlayers; i++) {
            if (healthPoints[i] > 0) {
                remainingPlayers++;
                lastStandingPlayerIndex = i;
            }
        }

        if (remainingPlayers == 1) {
            printf("%s is the last man standing with %d HP! They are the winner!\n", player[lastStandingPlayerIndex], healthPoints[lastStandingPlayerIndex]);

            // Free dynamically allocated memory
            for (int i = 0; i < numPlayers; i++) {
                free(player[i]);
            }
            free(player);
            free(healthPoints);

            return;
        }

        printf("Loading next turn .... \n");
        sleep(1.5);
        turn += 1;
        turns++;
        printf("\n");
    }

    printf("Maximum turns reached. The game ends in a draw.\n");

    // Free dynamically allocated memory
    for (int i = 0; i < numPlayers; i++) {
        free(player[i]);
    }
    free(player);
    free(healthPoints);
}

int main() {
    int numPlayers, initialHP, luckyHpThreshold;

    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    printf("Enter the initial health points for each player: ");
    scanf("%d", &initialHP);

    printf("What shall be the threshold hp for the hp gain bonus?\t");
    scanf("%d", &luckyHpThreshold);

    playGame(numPlayers, initialHP, luckyHpThreshold);

    return 0;
}
