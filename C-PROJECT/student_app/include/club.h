#ifndef CLUB_H
#define CLUB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "config.h"

// Club structure
typedef struct {
    int id;
    char name[MAX_CLUB_LENGTH];
    char description[500];
    char category[50];
    int president_id;
    int advisor_id;
    int member_count;
    int max_members;
    time_t founded_date;
    time_t last_meeting;
    char meeting_day[20];
    char meeting_time[20];
    char meeting_location[100];
    float budget;
    int is_active;
} Club;

// Club membership structure
typedef struct {
    int id;
    int student_id;
    int club_id;
    time_t join_date;
    char role[50];  // member, secretary, treasurer, president, etc.
    int is_active;
} ClubMembership;

// Club list structure
typedef struct {
    Club* clubs;
    int count;
    int capacity;
} ClubList;

// Membership list structure
typedef struct {
    ClubMembership* memberships;
    int count;
    int capacity;
} MembershipList;

// Club management functions
ClubList* club_list_create(void);
void club_list_destroy(ClubList* list);
int club_list_add(ClubList* list, Club club);
int club_list_remove(ClubList* list, int club_id);
Club* club_list_find_by_id(ClubList* list, int club_id);
Club* club_list_find_by_name(ClubList* list, const char* name);
Club* club_list_find_by_category(ClubList* list, const char* category);
void club_list_display_all(ClubList* list);
void club_list_display_club(Club* club);
void club_list_display_by_category(ClubList* list, const char* category);

// Club validation
int club_validate_name(const char* name);
int club_validate_description(const char* description);
int club_validate_category(const char* category);
int club_validate_member_limit(int max_members);
int club_validate_budget(float budget);

// Club input/output
Club club_input_new(void);
void club_input_edit(Club* club);
void club_display_summary(ClubList* list);

// Membership management functions
MembershipList* membership_list_create(void);
void membership_list_destroy(MembershipList* list);
int membership_list_add(MembershipList* list, ClubMembership membership);
int membership_list_remove(MembershipList* list, int membership_id);
ClubMembership* membership_list_find_by_id(MembershipList* list, int membership_id);
ClubMembership* membership_list_find_by_student(MembershipList* list, int student_id);
ClubMembership* membership_list_find_by_club(MembershipList* list, int club_id);
ClubMembership* membership_list_find_student_club(MembershipList* list, int student_id, int club_id);

// Membership operations
int join_club(MembershipList* list, int student_id, int club_id, const char* role);
int leave_club(MembershipList* list, int student_id, int club_id);
int update_membership_role(MembershipList* list, int student_id, int club_id, const char* new_role);
int is_student_member(MembershipList* list, int student_id, int club_id);

// Membership display
void membership_list_display_all(MembershipList* list);
void membership_list_display_student_memberships(MembershipList* list, int student_id);
void membership_list_display_club_members(MembershipList* list, int club_id);
void membership_display(ClubMembership* membership);

// Club statistics
typedef struct {
    int total_clubs;
    int active_clubs;
    int total_memberships;
    int active_memberships;
    float average_members_per_club;
    int most_popular_club_id;
    int least_popular_club_id;
    char most_common_category[50];
} ClubStatistics;

ClubStatistics* calculate_club_statistics(ClubList* clubs, MembershipList* memberships);
void display_club_statistics(ClubStatistics* stats);
void free_club_statistics(ClubStatistics* stats);

// Student club information
typedef struct {
    int student_id;
    int club_count;
    int* club_ids;
    char** club_names;
    char** roles;
} StudentClubInfo;

StudentClubInfo* get_student_club_info(MembershipList* memberships, ClubList* clubs, int student_id);
void display_student_club_info(StudentClubInfo* info);
void free_student_club_info(StudentClubInfo* info);

// Club reports
int generate_club_membership_report(ClubList* clubs, MembershipList* memberships, const char* filename);
int generate_student_club_report(MembershipList* memberships, ClubList* clubs, int student_id, const char* filename);
int generate_club_statistics_report(ClubStatistics* stats, const char* filename);

// File operations
int club_list_save_to_file(ClubList* list, const char* filename);
int club_list_load_from_file(ClubList* list, const char* filename);
int membership_list_save_to_file(MembershipList* list, const char* filename);
int membership_list_load_from_file(MembershipList* list, const char* filename);

// Club sorting
void club_list_sort_by_name(ClubList* list);
void club_list_sort_by_member_count(ClubList* list);
void club_list_sort_by_category(ClubList* list);
void club_list_sort_by_founded_date(ClubList* list);

// Membership sorting
void membership_list_sort_by_student(MembershipList* list);
void membership_list_sort_by_club(MembershipList* list);
void membership_list_sort_by_join_date(MembershipList* list);
void membership_list_sort_by_role(MembershipList* list);

// Utility functions
const char* get_club_category_name(const char* category);
int is_valid_club_role(const char* role);
int can_student_join_club(MembershipList* memberships, int student_id, int club_id);
int update_club_member_count(ClubList* clubs, MembershipList* memberships, int club_id);

// Club categories
#define CLUB_CATEGORY_ACADEMIC "Academic"
#define CLUB_CATEGORY_SPORTS "Sports"
#define CLUB_CATEGORY_ARTS "Arts"
#define CLUB_CATEGORY_SERVICE "Service"
#define CLUB_CATEGORY_CULTURAL "Cultural"
#define CLUB_CATEGORY_TECHNOLOGY "Technology"
#define CLUB_CATEGORY_SOCIAL "Social"
#define CLUB_CATEGORY_RELIGIOUS "Religious"

// Club roles
#define CLUB_ROLE_MEMBER "Member"
#define CLUB_ROLE_SECRETARY "Secretary"
#define CLUB_ROLE_TREASURER "Treasurer"
#define CLUB_ROLE_VICE_PRESIDENT "Vice President"
#define CLUB_ROLE_PRESIDENT "President"

#endif // CLUB_H
