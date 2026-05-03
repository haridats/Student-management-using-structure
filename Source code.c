#include <stdio.h>
#include <stdlib.h>

// Structure to store student data
struct student {
    int roll;
    char name[30];
    float m1, m2, m3;
    float total;
};

// Function to add student
void add() {
    FILE *fp;
    struct student s;

    fp = fopen("students.dat", "ab"); // open file to add data

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name); // simple input (no spaces)

    printf("Enter marks of 3 subjects: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    // calculate total
    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp); // write to file

    fclose(fp);

    printf("Record Added!\n");
}

// Function to display all students
void display() {
    FILE *fp;
    struct student s;

    fp = fopen("students.dat", "rb"); // open file to read

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.1f %.1f %.1f", s.m1, s.m2, s.m3);
        printf("\nTotal: %.1f\n", s.total);
    }

    fclose(fp);
}

// Function to show rank list
void rankList() {
    FILE *fp;
    struct student s[50];
    int n = 0, i, j;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    // read all students into array
    while (fread(&s[n], sizeof(struct student), 1, fp)) {
        n++;
    }

    fclose(fp);

    // simple sorting (descending order of total)
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i].total < s[j].total) {
                struct student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");

    for (i = 0; i < n; i++) {
        printf("\nRank %d", i + 1);
        printf("\nRoll: %d", s[i].roll);
        printf("\nName: %s", s[i].name);
        printf("\nTotal: %.1f\n", s[i].total);
    }
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Rank List");
        printf("\n4. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                rankList();
                break;
            case 4:
                exit(0);
            default:
                printf("Wrong choice!\n");
        }
    }

    return 0;
}
