#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Expense {
    char category[30];
    float amount;
};

struct Expense expenses[MAX];
int count = 0;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int compareIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        unsigned char ca = (unsigned char)*a;
        unsigned char cb = (unsigned char)*b;

        if (tolower(ca) != tolower(cb)) {
            return tolower(ca) - tolower(cb);
        }
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

void addExpense() {
    char input[100];

    if (count >= MAX) {
        printf("\nExpense limit reached!\n");
        return;
    }

    printf("\nEnter expense category: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading category.\n");
        return;
    }

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Category cannot be empty.\n");
        return;
    }

    snprintf(expenses[count].category, sizeof(expenses[count].category), "%s", input);

    do {
        printf("Enter amount: Rs. ");
        if (scanf("%f", &expenses[count].amount) != 1) {
            printf("Invalid amount. Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }

        if (expenses[count].amount <= 0) {
            printf("Amount must be greater than 0.\n");
            continue;
        }

        break;
    } while (1);

    clearInputBuffer();
    count++;
    printf("\nExpense added successfully!\n");
}

void displayExpenses() {
    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    printf("\n========== EXPENSE LIST ==========\n");

    for (int i = 0; i < count; i++) {
        printf("%d. %-20s Rs. %.2f\n",
               i + 1,
               expenses[i].category,
               expenses[i].amount);
    }
}

void calculateTotal() {
    float total = 0.0;

    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }

    printf("\nTotal Expense: Rs. %.2f\n", total);
}

void highestExpense() {
    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    int index = 0;

    for (int i = 1; i < count; i++) {
        if (expenses[i].amount > expenses[index].amount) {
            index = i;
        }
    }

    printf("\nHighest Expense:\n");
    printf("Category: %s\n", expenses[index].category);
    printf("Amount: Rs. %.2f\n", expenses[index].amount);
}

void lowestExpense() {
    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    int index = 0;

    for (int i = 1; i < count; i++) {
        if (expenses[i].amount < expenses[index].amount) {
            index = i;
        }
    }

    printf("\nLowest Expense:\n");
    printf("Category: %s\n", expenses[index].category);
    printf("Amount: Rs. %.2f\n", expenses[index].amount);
}

void calculateAverage() {
    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    float total = 0.0;

    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }

    printf("\nAverage Expense: Rs. %.2f\n", total / count);
}

void searchCategory() {
    char search[30];
    int found = 0;

    if (count == 0) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    printf("\nEnter category to search: ");
    if (fgets(search, sizeof(search), stdin) == NULL) {
        printf("Error reading category.\n");
        return;
    }

    search[strcspn(search, "\n")] = '\0';

    printf("\n========== SEARCH RESULTS ==========\n");

    for (int i = 0; i < count; i++) {
        if (compareIgnoreCase(expenses[i].category, search) == 0) {
            printf("%d. %s - Rs. %.2f\n",
                   i + 1,
                   expenses[i].category,
                   expenses[i].amount);
            found = 1;
        }
    }

    if (!found) {
        printf("No expense found for this category.\n");
    }
}

int main() {
    int choice;

    printf("====================================\n");
    printf("     SMART STUDENT EXPENSE TRACKER\n");
    printf("====================================\n");

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. Calculate Total Expense\n");
        printf("4. Find Highest Expense\n");
        printf("5. Find Lowest Expense\n");
        printf("6. Calculate Average Expense\n");
        printf("7. Search by Category\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
            case 1:
                addExpense();
                break;

            case 2:
                displayExpenses();
                break;

            case 3:
                calculateTotal();
                break;

            case 4:
                highestExpense();
                break;

            case 5:
                lowestExpense();
                break;

            case 6:
                calculateAverage();
                break;

            case 7:
                searchCategory();
                break;

            case 8:
                printf("\nThank you for using the Expense Tracker!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}