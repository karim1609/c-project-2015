#include "../include/student.h"
#include "../include/config.h"
#include "../include/crypto.h"
#include "../include/validation.h"
#include "../include/ui.h"
#include "../include/file.h"
#include "../include/report.h"
#include "../include/stats.h"
#include "../include/auth.h"
#include "../include/attendance.h"
#include "../include/grade.h"
#include "../include/club.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StudentList* student_list_create(void) {
    StudentList* list = (StudentList*)malloc(sizeof(StudentList));
    if (list == NULL) {
        printf("Error: Failed to create student list\n");
        return NULL;
    }
    
    // Allocate memory for the students array
    list->students = (Student*)malloc(MAX_STUDENTS * sizeof(Student));
    if (list->students == NULL) {
        printf("Error: Failed to allocate memory for students array\n");
        free(list);
        return NULL;
    }
    
    // Initialize all fields
    list->count = 0;
    list->capacity = MAX_STUDENTS;
    list->is_loaded = 0;
    // Set the first character of the filename to the null terminator,
    // making the filename an empty string to indicate no file is set yet.
    list->filename[0] = '\0';
    list->auto_save_enabled = 1;
    list->last_save_time = 0;
    
    return list;
}

void student_list_destroy(StudentList* list) {
    if (list == NULL) {
        return;
    }
    
    // Free the students array if it was allocated
    if (list->students != NULL) {
        free(list->students);
    }
    
    // Free the list structure itself
    free(list);
}
int student_list_add(StudentList* list, Student student){
    if (list == NULL || list->students == NULL) {
        printf("ERROR DE LISTE OR STUDENT  ");
        return 0;
    }else{
        if (list->count >= list->capacity) {
            printf("Error: Student list is full, cannot add new student.\n");
            return 0;
        }
        list->students[list->count] = student;
        list->count++;
        return 1;
    }

    


}
int student_list_remove(StudentList* list, int student_id) {
    if (list == NULL || list->students == NULL) {
        printf("Error: Invalid student list\n");
        return 0;
    }

    for (int i = 0; i < list->count; i++) {
        if (list->students[i].id == student_id) {
            for (int j = i; j < list->count - 1; j++) {
                list->students[j] = list->students[j + 1];
            }

            memset(&list->students[list->count - 1], 0, sizeof(Student));
            list->count--;
            return 1;
        }
    }

    printf("Error: Student with ID %d not found\n", student_id);
    return 0;
}
Student* student_list_find_by_id(StudentList* list, int student_id) {
    if (list == NULL || list->students == NULL) {
        printf("Error: Invalid student list\n");
        return NULL;
    }
    
    for (int i = 0; i < list->count; i++) {
        if (list->students[i].id == student_id) {
            return &list->students[i];
        }
    }
    
    return NULL;
}
Student* student_list_find_by_name(StudentList* list, const char* first_name, const char* last_name) {
    if (list == NULL || list->students == NULL) {
        printf("Error: Invalid student list\n");
        return NULL;
    }

    if (first_name == NULL || last_name == NULL) {
        printf("Error: Invalid name parameters\n");
        return NULL;
    }

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->students[i].first_name, first_name) == 0 && 
            strcmp(list->students[i].last_name, last_name) == 0) {
            return &list->students[i];
        }
    }
    
    return NULL;
}
Student* student_list_find_by_email(StudentList* list, const char* email) {
    if (list == NULL || list->students == NULL) {
        printf("Error: Invalid student list\n");
        return NULL;
    }

    if (email == NULL) {
        printf("Error: Invalid email parameter\n");
        return NULL;
    }

    if (!student_validate_email(email)) {
        printf("Error: Invalid email format\n");
        return NULL;
    }

    for (int i = 0; i < list->count; i++) {
        if (list->students[i].email != NULL && strcmp(list->students[i].email, email) == 0) {
            return &list->students[i];
        }
    }

    return NULL;
}
void student_list_display_all(StudentList* list){
    if (list == NULL || list->students == NULL) {
       printf("Error: Invalid student list\n");
       return;
    }
    if(list->count==0){
       printf("LIST IS EMPTY \n");
       return;
    }
    for(int i = 0; i < list->count; i++) {
       printf("\nStudent %d:\n", i + 1);
       printf("ID: %d\n", list->students[i].id);
       printf("First Name: %s\n", list->students[i].first_name);
       printf("Last Name: %s\n", list->students[i].last_name);
       printf("Email: %s\n", list->students[i].email);
       printf("age: %s\n", list->students[i].age);
       printf("Phone: %s\n", list->students[i].phone);
       printf("Address: %s\n", list->students[i].address);
       printf("--------------------\n");
    }
}
void student_list_display_student(Student* student) {
    if (student == NULL) {
        printf("Error: Invalid student\n");
        return;
    }
    
    printf("\nStudent information:\n");
    printf("ID: %d\n", student->id);
    printf("First Name: %s\n", student->first_name);
    printf("Last Name: %s\n", student->last_name);
    printf("Email: %s\n", student->email);
    printf("AGE: %d\n", student->age);
    printf("Phone: %s\n", student->phone);
    printf("Address: %s\n", student->address);
}


int student_list_save_to_file(StudentList* list, const char* filename) {
    if (list == NULL || list->students == NULL || filename == NULL) {
        printf("Error: Invalid arguments to student_list_save_to_file\n");
        return 0;
    }
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s for writing\n", filename);
        return 0;
    }
    // Save students as CSV (or adjust fields as necessary)
    for (int i = 0; i < list->count; i++) {
        Student* s = &list->students[i];
        fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%s,%d,%.2f,%ld,%d\n",
            s->id,
            s->first_name,
            s->last_name,
            s->email,
            s->phone,
            s->address,
            s->age,
            s->course,
            s->year,
            s->gpa,
            (long)s->enrollment_date,
            s->is_active
        );
    }
    fclose(file);
    return 1;
}
int student_list_load_from_file(StudentList* list, const char* filename){
    if (list == NULL || filename == NULL) {
        printf("Error: Invalid arguments to student_list_load_from_file\n");
        return 0;
    }
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s for reading\n", filename);
        return 0;
    }

    // We'll read each line and parse it into student fields
    char line[512];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        Student s;
        // Adjust sscanf format string to match the fields written in save_to_file
        int fields = sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%d,%f,%ld,%d",
            &s.id,
            s.first_name,
            s.last_name,
            s.email,
            s.phone,
            s.address,
            &s.age,
            s.course,
            &s.year,
            &s.gpa,
            &s.enrollment_date,
            &s.is_active
        );
        // 12 fields expected
        if (fields == 12) {
            if (index < list->capacity) {
                list->students[index++] = s;
            } else {
                // Reallocate if necessary
                int new_capacity = list->capacity ? list->capacity * 2 : 16;
                Student *new_students = realloc(list->students, sizeof(Student) * new_capacity);
                if (!new_students) {
                    printf("Error: Unable to allocate more memory for students\n");
                    fclose(file);
                    return 0;
                }
                list->students = new_students;
                list->capacity = new_capacity;
                list->students[index++] = s;
            }
        }
    }
    list->count = index;
    fclose(file);
    return 1;
}
void student_list_sort_by_name(StudentList* list) {
    if (list == NULL || list->students == NULL) {
        printf("Error: Invalid student list\n");
        return;
    }
    // Simple bubble sort by last_name, then first_name if last names equal
    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - 1 - i; j++) {
            int cmp = strcmp(list->students[j].last_name, list->students[j + 1].last_name);
            if (cmp > 0 || (cmp == 0 && strcmp(list->students[j].first_name, list->students[j + 1].first_name) > 0)) {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
}

// Sort students by ID in ascending order
void student_list_sort_by_id(StudentList* list) {
    if (list == NULL || list->students == NULL || list->count < 2) return;
    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->students[j].id > list->students[j + 1].id) {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
}

// Sort students by GPA in descending order
void student_list_sort_by_gpa(StudentList* list) {
    if (list == NULL || list->students == NULL || list->count < 2) return;
    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (list->students[j].gpa < list->students[j + 1].gpa) {
                Student temp = list->students[j];
                list->students[j] = list->students[j + 1];
                list->students[j + 1] = temp;
            }
        }
    }
    int student_list_get_count(StudentList* list) {
        if (list == NULL) return 0;
        return list->count;
    }
}
Student* student_list_get_student(StudentList* list, int index){
    if(list == NULL || list->students == NULL){
        return NULL;
    }
    // Is true if index is in valid range
    if(index >= 0 && index < list->count) {
        return &list->students[index];
    } else {
        return NULL;
    }
}