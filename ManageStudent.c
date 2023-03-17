#include <stdio.h>
#include <string.h>
#include <time.h>

struct date {
    int day;
    int month;
    int year;
};

struct student {
    int id; 
    char name[50];
    char gender[5];
    int age;
    float point_1;
    float point_2;
    float point_3;
    struct date date_of_birth;
    float average;
    char academic_rank[10];
    char codeClass[30];
};

typedef struct student sv;

void remove_enter(char x[]) {
    size_t len = strlen(x);
    if(x[len-1] == '\n') {
        x[len-1] = '\0';
    }
}

void input_student(sv* s) {
    printf("\nID : "); scanf("%d", &s->id);
    printf("\nName : ");fflush(stdin); fgets(s->name, sizeof(s->name),stdin);remove_enter(s->name);
    printf("\nGender : ");fflush(stdin); fgets(s->gender, sizeof(s->gender),stdin);remove_enter(s->gender);
    printf("\nDay of birth : "); scanf("%d%d%d", &s->date_of_birth.day,&s->date_of_birth.month,&s->date_of_birth.year);
    printf("\nPoint 1 : "); scanf("%f", &s->point_1);
    printf("\nPoint 2 : "); scanf("%f", &s->point_2);
    printf("\nPoint 3 : "); scanf("%f", &s->point_3);
    printf("\nCode Class: ");fflush(stdin); fgets(s->codeClass, sizeof(s->codeClass),stdin);remove_enter(s->codeClass);
}

void enter_student(sv list[], int *n) {
    do {
        printf("\nHow many students do you want to enter? ");
        scanf("%d", n);
    } while (*n <= 0); 
    for (int i = 0; i < *n; i++) {
        printf("\n Enter Student %d\n", i+1);
        input_student(&list[i]);
    }
}

void calculate_average(sv *s) {
    s->average = (s->point_1 + s->point_2 + s->point_3) / 3.0;
}

void calculate_age(sv *s) {
    time_t TIME = time(0);
    struct tm* NOW = localtime(&TIME);
    int current_year = NOW->tm_year + 1900;
    s->age = current_year - s->date_of_birth.year;
}
void rank (sv *s) {
    if(s->average > 9) {
        strcpy(s->academic_rank, "Excellent");
    } else if(s->average > 8) {
        strcpy(s->academic_rank, "Good");
    } else if(s->average > 7) {
        strcpy(s->academic_rank, "Fair");
    } else if(s->average > 5) {
        strcpy(s->academic_rank, "Average");
    } else {
        strcpy(s->academic_rank, "Weak");
    }
}
void print_student(sv s) {
    printf ("%4d %15s %7s %02d/%02d/%4d %2d %6.2f %6.2f %6.2f %6.2f %10s %10s\n", s.id, s.name, s.gender, s.date_of_birth.day, s.date_of_birth.month, s.date_of_birth.year, s.age, s.point_1, s.point_2, s.point_3, s.average, s.academic_rank, s.codeClass);
}

void print_excellent_students(sv list[], int n) {
    for (int i = 0; i < n; i++) {
    if (strcmp(list[i].academic_rank, "Excellent") == 0) {
            print_student(list[i]);
        }
    }
}
int main() {
    sv student_list[100];
    int n;
    enter_student(student_list, &n);
    printf("\nID \t Name \t Gender \t Day Of Birth \t Age \t Point 1 \t Point 2 \t Point 3 \t Average \t Academic Rank \t Code Class\n");
    for (int i = 0; i < n; i++) {
        calculate_average(&student_list[i]);
        calculate_age(&student_list[i]);
        rank(&student_list[i]);
        print_student(student_list[i]);
    }
    int has_excellent = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(student_list[i].academic_rank, "Excellent") == 0) {
            has_excellent = 1;
            break;
        }
    }
    if (has_excellent) {
        printf("\nList of excellent students:\n");
        print_excellent_students(student_list, n);
    } else {
        printf("\nNo have excellent student\n");
    }

    return 0;
}