#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"

// Attendance record structure
typedef struct {
    int id;
    int student_id;
    int course_id;
    time_t date;
    int status;  // 0=absent, 1=present, 2=late, 3=excused
    char reason[200];
    int teacher_id;
    time_t recorded_time;
} AttendanceRecord;

// Attendance list structure
typedef struct {
    AttendanceRecord* records;
    int count;
    int capacity;
} AttendanceList;

// Attendance statistics structure
typedef struct {
    int student_id;
    int course_id;
    int total_days;
    int present_days;
    int absent_days;
    int late_days;
    int excused_days;
    float attendance_percentage;
    int consecutive_absences;
    int consecutive_presents;
} AttendanceStats;

// Attendance management functions
AttendanceList* attendance_list_create(void);
void attendance_list_destroy(AttendanceList* list);
int attendance_list_add(AttendanceList* list, AttendanceRecord record);
int attendance_list_remove(AttendanceList* list, int record_id);
AttendanceRecord* attendance_list_find_by_id(AttendanceList* list, int record_id);
AttendanceRecord* attendance_list_find_by_student_date(AttendanceList* list, int student_id, time_t date);
AttendanceRecord* attendance_list_find_by_course_date(AttendanceList* list, int course_id, time_t date);

// Attendance operations
int mark_attendance(AttendanceList* list, int student_id, int course_id, time_t date, int status, int teacher_id);
int update_attendance(AttendanceList* list, int record_id, int new_status, const char* reason);
int excuse_absence(AttendanceList* list, int record_id, const char* reason);
int get_attendance_for_date(AttendanceList* list, int course_id, time_t date, AttendanceRecord** records, int* count);

// Attendance display
void attendance_list_display_all(AttendanceList* list);
void attendance_list_display_student_attendance(AttendanceList* list, int student_id);
void attendance_list_display_course_attendance(AttendanceList* list, int course_id);
void attendance_list_display_date_attendance(AttendanceList* list, time_t date);
void attendance_display_record(AttendanceRecord* record);

// Attendance statistics
AttendanceStats* calculate_student_attendance_stats(AttendanceList* list, int student_id, int course_id);
AttendanceStats* calculate_course_attendance_stats(AttendanceList* list, int course_id);
void display_attendance_stats(AttendanceStats* stats);
void free_attendance_stats(AttendanceStats* stats);

// Attendance validation
int attendance_validate_status(int status);
int attendance_validate_date(time_t date);
int attendance_validate_reason(const char* reason);
int attendance_validate_student_course(int student_id, int course_id);

// Attendance input/output
AttendanceRecord attendance_input_new(int student_id, int course_id, int teacher_id);
void attendance_input_edit(AttendanceRecord* record);
void attendance_display_summary(AttendanceList* list, int student_id);

// Bulk attendance operations
int mark_class_attendance(AttendanceList* list, int course_id, time_t date, int* student_ids, int* statuses, int count, int teacher_id);
int import_attendance_from_file(AttendanceList* list, const char* filename);
int export_attendance_to_file(AttendanceList* list, const char* filename);

// Attendance reports
int generate_student_attendance_report(AttendanceList* list, int student_id, const char* filename);
int generate_course_attendance_report(AttendanceList* list, int course_id, const char* filename);
int generate_daily_attendance_report(AttendanceList* list, time_t date, const char* filename);
int generate_attendance_summary_report(AttendanceList* list, const char* filename);

// File operations
int attendance_list_save_to_file(AttendanceList* list, const char* filename);
int attendance_list_load_from_file(AttendanceList* list, const char* filename);

// Attendance sorting
void attendance_list_sort_by_student(AttendanceList* list);
void attendance_list_sort_by_course(AttendanceList* list);
void attendance_list_sort_by_date(AttendanceList* list);
void attendance_list_sort_by_status(AttendanceList* list);

// Attendance analysis
int identify_absent_students(AttendanceList* list, int course_id, time_t date);
int identify_frequently_absent_students(AttendanceList* list, int course_id, float threshold);
int calculate_attendance_trends(AttendanceList* list, int student_id, int course_id);
int get_attendance_patterns(AttendanceList* list, int student_id);

// Utility functions
const char* attendance_status_to_string(int status);
int string_to_attendance_status(const char* status_str);
int is_attendance_present(int status);
int is_attendance_absent(int status);
int is_attendance_late(int status);
int is_attendance_excused(int status);

// Date utilities
time_t get_today_date(void);
time_t get_class_date(int course_id, int day_of_week);
int is_weekend(time_t date);
int is_holiday(time_t date);
int get_days_between_dates(time_t start_date, time_t end_date);

// Attendance constants
#define ATTENDANCE_ABSENT 0
#define ATTENDANCE_PRESENT 1
#define ATTENDANCE_LATE 2
#define ATTENDANCE_EXCUSED 3

#define ATTENDANCE_THRESHOLD_WARNING 0.85  // 85% attendance warning
#define ATTENDANCE_THRESHOLD_CRITICAL 0.75  // 75% attendance critical
#define MAX_CONSECUTIVE_ABSENCES 5

// Attendance status strings
#define ATTENDANCE_STATUS_ABSENT_STR "Absent"
#define ATTENDANCE_STATUS_PRESENT_STR "Present"
#define ATTENDANCE_STATUS_LATE_STR "Late"
#define ATTENDANCE_STATUS_EXCUSED_STR "Excused"

#endif // ATTENDANCE_H
