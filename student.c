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
    printf("1. Thêm sinh viên\n");
    printf("2. Hiển thị danh sách\n");
    printf("3. Tìm sinh viên theo ID\n");
    printf("4. Xoá sinh viên\n");
    printf("5. Cập nhật sinh viên\n");
    printf("6. Lưu vào file\n");
    printf("7. Đọc từ file\n");
    printf("0. Thoát\n");
    printf("==================\n");
}

void addStudent(Student students[], int *n) {
    if (*n >= MAX) {
        printf("Danh sách đầy!\n");
        return;
    }

    Student s;
    printf("Nhập ID: "); scanf("%d", &s.id);
    getchar();  // Xoá Enter
    printf("Nhập tên: "); fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Nhập GPA: "); scanf("%f", &s.gpa);

    students[*n] = s;
    (*n)++;
    printf("✅ Đã thêm sinh viên.\n");
}

void showAll(Student students[], int n) {
    if (n == 0) {
        printf("Danh sách trống.\n");
        return;
    }

    printf("\n%-5s %-20s %-5s\n", "ID", "Tên", "GPA");
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
    printf("Nhập ID cần tìm: ");
    scanf("%d", &id);
    int idx = findById(students, n, id);
    if (idx == -1) {
        printf("❌ Không tìm thấy sinh viên.\n");
    } else {
        printf("✅ Tìm thấy: %d - %s - %.2f\n", students[idx].id, students[idx].name, students[idx].gpa);
    }
}

void deleteStudent(Student students[], int *n) {
    int id;
    printf("Nhập ID cần xoá: ");
    scanf("%d", &id);
    int idx = findById(students, *n, id);
    if (idx == -1) {
        printf("❌ Không tìm thấy sinh viên.\n");
        return;
    }

    for (int i = idx; i < *n - 1; i++) {
        students[i] = students[i + 1];
    }
    (*n)--;
    printf("✅ Đã xoá sinh viên.\n");
}

void updateStudent(Student students[], int n) {
    int id;
    printf("Nhập ID cần cập nhật: ");
    scanf("%d", &id);
    int idx = findById(students, n, id);
    if (idx == -1) {
        printf("❌ Không tìm thấy sinh viên.\n");
        return;
    }

    getchar();
    printf("Nhập tên mới: "); fgets(students[idx].name, MAX_NAME, stdin);
    students[idx].name[strcspn(students[idx].name, "\n")] = '\0';
    printf("Nhập GPA mới: "); scanf("%f", &students[idx].gpa);
    printf("✅ Đã cập nhật sinh viên.\n");
}

void saveToFile(Student students[], int n, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("❌ Không thể mở file để ghi.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
    fclose(f);
    printf("✅ Đã lưu vào file.\n");
}

void loadFromFile(Student students[], int *n, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ Không thể mở file để đọc.\n");
        return;
    }

    *n = 0;
    while (fscanf(f, "%d,%[^,],%f\n", &students[*n].id, students[*n].name, &students[*n].gpa) == 3) {
        (*n)++;
    }
    fclose(f);
    printf("✅ Đã đọc dữ liệu từ file.\n");
}

int main() {
    Student students[MAX];
    int n = 0;
    int choice;

    do {
        printMenu();
        printf("Chọn chức năng: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(students, &n); break;
            case 2: showAll(students, n); break;
            case 3: searchStudent(students, n); break;
            case 4: deleteStudent(students, &n); break;
            case 5: updateStudent(students, n); break;
            case 6: saveToFile(students, n, FILENAME); break;
            case 7: loadFromFile(students, &n, FILENAME); break;
            case 0: printf("👋 Thoát chương trình.\n"); break;
            default: printf("❗ Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);

    return 0;
}
