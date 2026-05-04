#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};


void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "a");

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter 3 marks: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fprintf(fp, "%d %s %f %f %f %f\n",
            s.roll, s.name, s.m1, s.m2, s.m3, s.total);

    fclose(fp);

    printf("Student added!\n");
}


void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fscanf(fp, "%d %s %f %f %f %f",
           &s.roll, s.name, &s.m1, &s.m2, &s.m3, &s.total) != EOF) {

        printf("\nRoll: %d", s.roll);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.1f %.1f %.1f", s.m1, s.m2, s.m3);
        printf("\nTotal: %.1f\n", s.total);
    }

    fclose(fp);
}


void rankList() {
    FILE *fp;
    struct Student s[100], temp;
    int i = 0, j, count = 0;

    fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }


    while (fscanf(fp, "%d %s %f %f %f %f",
           &s[i].roll, s[i].name, &s[i].m1,
           &s[i].m2, &s[i].m3, &s[i].total) != EOF) {
        i++;
    }

    count = i;
    fclose(fp);


    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (s[i].total < s[j].total) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");

    for (i = 0; i < count; i++) {
        printf("\nRank %d", i + 1);
        printf("\nName: %s", s[i].name);
        printf("\nTotal: %.1f\n", s[i].total);
    }
}


int main() {
    int choice;

    do {
        printf("\n\n===== MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Rank List\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: printf("Bye!\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
