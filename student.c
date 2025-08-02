#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_NAME 50
#define FILENAME "students.csv"

typedef struct {
    int id;
    char name[MAX_NAME];
    float gpa;
} Student;

void printMenu() {
    printf("\n====== MENU ======\n");
    printf("1. Add student\n");
    printf("2. Show student list\n");
    printf("3. Search student by ID\n");
    printf("4. Delete student\n");
    printf("5. Update student\n");
    printf("6. Save to file\n");
    printf("7. Load from file\n");
    printf("0. Exit\n");
    printf("==================\n");
}

void addStudent(Student students[], int *n) {
    if (*n >= MAX) {
        printf("❌ Student list is full!\n");
        return;
    }

    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();  // Clear newline
    printf("Enter name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[*n] = s;
    (*n)++;
    printf("✅ Student added successfully.\n");
}

void showAll(Student students[], int n) {
    if (n == 0) {
        printf("❌ Student list is empty.\n");
        return;
    }

    printf("\n%-5s %-20s %-5s\n", "ID", "Name", "GPA");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-5.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

int findById(Student students[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void searchStudent(Student students[], int n) {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    int idx = findById(students, n, id);
    if (idx == -1) {
        printf("❌ Student not found.\n");
    } else {
        printf("✅ Found: %d - %s - %.2f\n", students[idx].id, students[idx].name, students[idx].gpa);
    }
}

void deleteStudent(Student students[], int *n) {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    int idx = findById(students, *n, id);
    if (idx == -1) {
        printf("❌ Student not found.\n");
        return;
    }

    for (int i = idx; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }
    (*n)--;
    printf("✅ Student deleted successfully.\n");
}

void updateStudent(Student students[], int n) {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    int idx = findById(students, n, id);
    if (idx == -1) {
        printf("❌ Student not found.\n");
        return;
    }

    getchar();
    printf("Enter new name: ");
    fgets(students[idx].name, MAX_NAME, stdin);
    students[idx].name[strcspn(students[idx].name, "\n")] = '\0';
    printf("Enter new GPA: ");
    scanf("%f", &students[idx].gpa);
    printf("✅ Student updated successfully.\n");
}

void saveToFile(Student students[], int n, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("❌ Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
    fclose(f);
    printf("✅ Data saved to file.\n");
}

void loadFromFile(Student students[], int *n, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ Unable to open file for reading.\n");
        return;
    }

    *n = 0;
    while (fscanf(f, "%d,%[^,],%f\n", &students[*n].id, students[*n].name, &students[*n].gpa) == 3) {
        (*n)++;
    }
    fclose(f);
    printf("✅ Data loaded from file.\n");
}

int main() {
    Student students[MAX];
    int n = 0;
    int choice;

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(students, &n); break;
            case 2: showAll(students, n); break;
            case 3: searchStudent(students, n); break;
            case 4: deleteStudent(students, &n); break;
            case 5: updateStudent(students, n); break;
            case 6: saveToFile(students, n, FILENAME); break;
            case 7: loadFromFile(students, &n, FILENAME); break;
            case 0: printf("👋 Exiting program.\n"); break;
            default: printf("❗ Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}