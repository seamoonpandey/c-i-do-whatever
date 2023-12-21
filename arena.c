#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ANSI escape codes for text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    char name[20];
    int finalHP;
    int turnsToWin;
} HallOfFameEntry;

void sleepMilliseconds(int milliseconds) {
    clock_t start = clock();
    while ((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void playGame(int numPlayers, int initialHP, int luckyHpThreshold) {
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
    while (1) {
        if (healthPoints[turn % numPlayers] <= 0) {
            turn++;
            continue;
        }

        int attack = rand() % 7;
        printf("%s%s attacks with a damage of %d %s\n", ANSI_COLOR_YELLOW, player[turn % numPlayers], attack, ANSI_COLOR_RESET);
        sleepMilliseconds(1000);

        // Decrease health points of other players
        for (int i = 0; i < numPlayers; i++) {
            if (i != turn % numPlayers) {
                healthPoints[i] -= attack;

                // Ensure health points don't go below zero
                if (healthPoints[i] < 0) {
                    healthPoints[i] = 0;
                    printf("%s%s has run out of health and is eliminated!\n", ANSI_COLOR_RED, player[i]);
                }
            }
        }

        // Display current health points
        printf("Health Points:\n");
        for (int i = 0; i < numPlayers; i++) {
            printf("%s%s: %d  ", ANSI_COLOR_BLUE, player[i], healthPoints[i]);
        }
        printf("%s\n", ANSI_COLOR_RESET);

        if (attack == 6) {
            if (healthPoints[turn % numPlayers] <= luckyHpThreshold) {
                // If the player's health is below or equal to the lucky HP threshold, gain 5 HP
                printf("%s%s's attack was successful, and they gain 5 HP.\n", ANSI_COLOR_GREEN, player[turn % numPlayers]);
                healthPoints[turn % numPlayers] += 5;
            } else {
                printf("%s%s got lucky. Gets another chance\n", ANSI_COLOR_GREEN, player[turn % numPlayers]);
                continue;
            }
        }

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
            // Display the winner and store them in the Hall of Fame
            printf("%s%s is the last person standing with %d HP! They are the winner!\n", ANSI_COLOR_GREEN, player[lastStandingPlayerIndex], healthPoints[lastStandingPlayerIndex]);

            // Store the winner in the Hall of Fame
            HallOfFameEntry winner;
            strcpy(winner.name, player[lastStandingPlayerIndex]);
            winner.finalHP = healthPoints[lastStandingPlayerIndex];
            winner.turnsToWin = turns;

            // Append the winner to the Hall of Fame file
            FILE *fameFile = fopen("hall_of_fame.txt", "a");
            if (fameFile != NULL) {
                fprintf(fameFile, "Name: %s, HP: %d, Turns to Win: %d\n", winner.name, winner.finalHP, winner.turnsToWin);
                fclose(fameFile);
            } else {
                printf("Unable to open the Hall of Fame file for writing.\n");
            }

            // Free dynamically allocated memory
            for (int i = 0; i < numPlayers; i++) {
                free(player[i]);
            }
            free(player);
            free(healthPoints);

            return;
        }

        // Display loading message and proceed to the next turn
        printf("Loading next turn .... \n");
        sleepMilliseconds(1500);
        turn += 1;
        turns++;
        printf("\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < numPlayers; i++) {
        free(player[i]);
    }
    free(player);
    free(healthPoints);
}

int main() {
    int numPlayers, initialHP, luckyHpThreshold;

    // Get input from the user
    printf("Enter the number of players: ");
    scanf("%d", &numPlayers);

    printf("Enter the initial health points for each player: ");
    scanf("%d", &initialHP);

    // Ask for the lucky HP threshold (same for all players)
    printf("Enter the lucky HP threshold: ");
    scanf("%d", &luckyHpThreshold);

    // Start the game
    playGame(numPlayers, initialHP, luckyHpThreshold);

    return 0;
}
