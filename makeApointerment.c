#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100
#define MAX_APPOINTMENTS 7

struct Person {
    char name[100];
    char dob[9];
    int sum_dob;
};

struct Appointment {
    int day;
    int hour;
    int minute;
    int num_people;
};

int is_good_time(int sum_dob, int hour) {
    int remainder = sum_dob % 4; // Only good hours are 0, 1, 2, or 3
    return hour >= 0 && hour <= 23 && (hour % 4) == remainder;
}

void sort_appointments(struct Appointment appointments[], int n) {
    int i, j;
    struct Appointment temp;
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (appointments[i].num_people < appointments[j].num_people) {
                temp = appointments[i];
                appointments[i] = appointments[j];
                appointments[j] = temp;
            }
        }
    }
}
int main() {
    int n, i, j, k, num_appointments = 0;
    printf("Enter number of people: ");
    scanf("%d", &n);
    struct Person people[MAX_PEOPLE];
    struct Appointment appointments[MAX_APPOINTMENTS];
    Input people
    for (i = 0; i < n; i++) {
        printf("Person %d\n", i+1);
        printf("Enter name: ");
        scanf(" %[^\n]s", people[i].name);
        printf("Enter birth date (yyyymmdd): ");
        scanf(" %s", people[i].dob);
        people[i].sum_dob = 0;
        for (j = 0; j < 8; j++) {
            if (people[i].dob[j] >= '0' && people[i].dob[j] <= '9') {
                people[i].sum_dob += people[i].dob[j] - '0';
            }
        }
    }
    // Input appointments 
    for (i = 0; i < MAX_APPOINTMENTS; i++) {
        printf("Enter appointment for day %d (hh:mm & num people dating or -1 to stop): ", i+1);
        scanf(" %d", &appointments[i].hour);
        if (appointments[i].hour == -1) {
            break;
        }
        scanf(" :%d %d", &appointments[i].minute, &appointments[i].num_people);
        appointments[i].day = i+1;
        num_appointments++;
    }
    // Sort appointments by number of people
    sort_appointments(appointments, num_appointments);
    // Schedule appointments
    for (i = 0; i < num_appointments; i++) {
        struct Appointment app = appointments[i];
        printf("Appointments for day %d (num people: %d)\n", app.day, app.num_people);
        for (j = 0; j < n && app.num_people > 0; j++) {
            if (is_good_time(people[j].sum_dob, app.hour)) {
                printf("%s at %02d:%02d\n", people[j].name, app.hour, app.minute);
                app.num_people--;
            }
        }
    }
    return 0;
}
