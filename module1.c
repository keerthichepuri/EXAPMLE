#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Structure to hold session details
struct Session {
    char topic[50];
    char language[30];
    float hours;
    char difficulty[10];
};

// Checks if string is empty or newline
int isEmpty(char str[]) {
    return (strlen(str) == 0 || str[0] == '\n');
}

// Assigns difficulty based on hours
const char* getSystemDifficulty(float hrs) {
    if (hrs < 2) return "Easy";
    else if (hrs <= 4) return "Medium";
    else return "Hard";
}

int main() {
    struct Session sessions[100];
    int i = 0;
    char cont;

    printf("===== CODING PRACTICE SESSION LOGGER =====\n");

    do {
        printf("\n--- Enter details for session %d ---\n", i + 1);

        // Input topic
        do {
            printf("Enter the programming topic: ");
            getchar(); // clear buffer
            fgets(sessions[i].topic, sizeof(sessions[i].topic), stdin);
            sessions[i].topic[strcspn(sessions[i].topic, "\n")] = '\0';
            if (isEmpty(sessions[i].topic))
                printf("❌ Topic cannot be empty. Try again.\n");
        } while (isEmpty(sessions[i].topic));

        // Input language
        do {
            printf("Enter the programming language: ");
            fgets(sessions[i].language, sizeof(sessions[i].language), stdin);
            sessions[i].language[strcspn(sessions[i].language, "\n")] = '\0';
            if (isEmpty(sessions[i].language))
                printf("❌ Language cannot be empty. Try again.\n");
        } while (isEmpty(sessions[i].language));

        // Input hours
        do {
            printf("Enter hours spent on the session (0.5 to 10): ");
            scanf("%f", &sessions[i].hours);
            if (sessions[i].hours < 0.5 || sessions[i].hours > 10)
                printf("❌ Invalid hours. Enter between 0.5 and 10.\n");
        } while (sessions[i].hours < 0.5 || sessions[i].hours > 10);

        // Motivation feedback
        if (sessions[i].hours < 1)
            printf("⚠️  Less than 1 hour – Try to practice longer.\n");
        else if (sessions[i].hours >= 5)
            printf("💪 Long session! Keep up the focus!\n");

        // User selects difficulty
        int diffChoice;
        do {
            printf("\nSelect your perceived difficulty level:\n");
            printf("1. Easy\n2. Medium\n3. Hard\nEnter choice: ");
            scanf("%d", &diffChoice);

            switch (diffChoice) {
                case 1: strcpy(sessions[i].difficulty, "Easy"); break;
                case 2: strcpy(sessions[i].difficulty, "Medium"); break;
                case 3: strcpy(sessions[i].difficulty, "Hard"); break;
                default: printf("❌ Invalid option. Try again.\n");
            }
        } while (diffChoice < 1 || diffChoice > 3);

        // Auto vs user difficulty comparison
        const char* autoDiff = getSystemDifficulty(sessions[i].hours);
        if (strcmp(autoDiff, sessions[i].difficulty) != 0) {
            printf("⚠️  Based on hours (%.1f hrs), system suggests '%s' difficulty.\n", sessions[i].hours, autoDiff);
            printf("Note: Your choice was '%s'. Try to match actual effort.\n", sessions[i].difficulty);
        }

        // Continue or exit
        i++;
        printf("\nDo you want to add another session? (y/n): ");
        scanf(" %c", &cont); // note the space before %c
    } while (tolower(cont) == 'y');

    // Summary
    printf("\n======= SESSION SUMMARY =======\n");
    for (int j = 0; j < i; j++) {
        printf("Session %d:\n", j + 1);
        printf("Topic      : %s\n", sessions[j].topic);
        printf("Language   : %s\n", sessions[j].language);
        printf("Hours Spent: %.2f\n", sessions[j].hours);
        printf("Difficulty : %s\n", sessions[j].difficulty);
        printf("------------------------------\n");
    }

    return 0;
}