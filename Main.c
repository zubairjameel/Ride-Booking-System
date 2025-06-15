#include <stdio.h>
#include <string.h>

struct Passenger {
    char name[50];
    char phone[15];
    int id;
};

struct Driver {
    char name[50];
    char phone[15];
    char car[30];
    int id;
    int available; 
};

struct Ride {
    int passenger_id;
    int driver_id;
    char pickup[50];
    char destination[50];
    float fare;
    int status; 
};

struct Passenger passengers[10];
struct Driver drivers[10];
struct Ride rides[20];

int passenger_count = 0;
int driver_count = 0;
int ride_count = 0;

void showMenu();
void addPassenger();
void addDriver();
void bookRide();
void showRides();
void showDrivers();
void showPassengers();

int main() {
    int choice;

    printf("=== SIMPLE RIDE BOOKING SYSTEM ===\n\n");

    while(1) {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
if(choice == 1) {
            addPassenger();
        }
        else if(choice == 2) {
            addDriver();
        }
        else if(choice == 3) {
            bookRide();
        }
        else if(choice == 4) {
            showRides();
        }
        else if(choice == 5) {
            showPassengers();
        }
        else if(choice == 6) {
            showDrivers();
        }
        else if(choice == 7) {
            printf("Thank you for using our service!\n");
            break;
        }
        else {
            printf("Invalid choice! Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}

void showMenu() {
    printf("\n--- MAIN MENU ---\n");
    printf("1. Add Passenger\n");
    printf("2. Add Driver\n");
    printf("3. Book a Ride\n");
    printf("4. Show All Rides\n");
    printf("5. Show All Passengers\n");
    printf("6. Show All Drivers\n");
    printf("7. Exit\n");
}

void addPassenger() {
    if(passenger_count >= 10) {
        printf("Sorry! Maximum 10 passengers allowed.\n");
        return;
    }

    printf("\n--- ADD PASSENGER ---\n");
    passengers[passenger_count].id = passenger_count + 1;

    printf("Enter passenger name: ");
    scanf(" %[^\n]", passengers[passenger_count].name);

    printf("Enter phone number: ");
    scanf("%s", passengers[passenger_count].phone);

    printf("Passenger added successfully!\n");
    printf("Passenger ID: %d\n", passengers[passenger_count].id);

    passenger_count++;
}

void addDriver() {
    if(driver_count >= 10) {
        printf("Sorry! Maximum 10 drivers allowed.\n");
        return;
    }

    printf("\n--- ADD DRIVER ---\n");

    drivers[driver_count].id = driver_count + 1;
    drivers[driver_count].available = 1; // Available by default

    printf("Enter driver name: ");
    scanf(" %[^\n]", drivers[driver_count].name);

    printf("Enter phone number: ");
    scanf("%s", drivers[driver_count].phone);

    printf("Enter car details: ");
    scanf(" %[^\n]", drivers[driver_count].car);

    printf("Driver added successfully!\n");
    printf("Driver ID: %d\n", drivers[driver_count].id);

    driver_count++;
}

void bookRide() {
    int passenger_id, driver_id;
    int i, found;

    if(passenger_count == 0) {
        printf("No passengers registered! Please add a passenger first.\n");
        return;
    }

    if(driver_count == 0) {
        printf("No drivers available! Please add a driver first.\n");
        return;
    }

    printf("\n--- BOOK A RIDE ---\n");

    // Show available passengers
    printf("Available Passengers:\n");
    for(i = 0; i < passenger_count; i++) {
        printf("ID: %d, Name: %s\n", passengers[i].id, passengers[i].name);
    }

    printf("Enter Passenger ID: ");
    scanf("%d", &passenger_id);

    // Check if passenger exists
    found = 0;
    for(i = 0; i < passenger_count; i++) {
        if(passengers[i].id == passenger_id) {
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Passenger not found!\n");
        return;
    }

    // Show available drivers
    printf("\nAvailable Drivers:\n");
    found = 0;
    for(i = 0; i < driver_count; i++) {
        if(drivers[i].available == 1) {
            printf("ID: %d, Name: %s, Car: %s\n", 
                   drivers[i].id, drivers[i].name, drivers[i].car);
            found = 1;
        }
    }

    if(!found) {
        printf("No drivers available right now!\n");
        return;
    }

    printf("Enter Driver ID: ");
    scanf("%d", &driver_id);

    found = 0;
    for(i = 0; i < driver_count; i++) {
        if(drivers[i].id == driver_id && drivers[i].available == 1) {
            found = 1;
            drivers[i].available = 0; // Make driver busy
            break;
        }
    }

    if(!found) {
        printf("Driver not found or not available!\n");
        return;
    }

    // Get ride details
    rides[ride_count].passenger_id = passenger_id;
    rides[ride_count].driver_id = driver_id;

    printf("Enter pickup location: ");
    scanf(" %[^\n]", rides[ride_count].pickup);

    printf("Enter destination: ");
    scanf(" %[^\n]", rides[ride_count].destination);

    printf("Enter fare amount: ");
    scanf("%f", &rides[ride_count].fare);

    rides[ride_count].status = 0; 

    printf("\nRide booked successfully!\n");
    printf("Ride Number: %d\n", ride_count + 1);
    printf("Fare: Rs. %.2f\n", rides[ride_count].fare);

    ride_count++;
}

void showRides() {
    int i, j;

    if(ride_count == 0) {
        printf("No rides booked yet!\n");
        return;
    }

    printf("\n--- ALL RIDES ---\n");
    printf("Ride# | Passenger | Driver | From | To | Fare | Status\n");
    printf("------------------------------------------------------\n");

    for(i = 0; i < ride_count; i++) {
        char passenger_name[50] = "Unknown";
        for(j = 0; j < passenger_count; j++) {
            if(passengers[j].id == rides[i].passenger_id) {
                strcpy(passenger_name, passengers[j].name);
                break;
            }
        }
        char driver_name[50] = "Unknown";
        for(j = 0; j < driver_count; j++) {
            if(drivers[j].id == rides[i].driver_id) {
                strcpy(driver_name, drivers[j].name);
                break;
            }
        }

        printf("%-5d | %-9s | %-6s | %-4s | %-2s | %-4.0f | %s\n",
               i + 1,
               passenger_name,
               driver_name,
               rides[i].pickup,
               rides[i].destination,
               rides[i].fare,
               rides[i].status ? "Done" : "Ongoing");
    }
}

void showPassengers() {
    int i;

    if(passenger_count == 0) {
        printf("No passengers registered!\n");
        return;
    }

    printf("\n--- ALL PASSENGERS ---\n");
    printf("ID | Name | Phone\n");
    printf("-------------------\n");

    for(i = 0; i < passenger_count; i++) {
        printf("%-2d | %-4s | %s\n",
               passengers[i].id,
               passengers[i].name,
               passengers[i].phone);
    }
}

void showDrivers() {
    int i;

    if(driver_count == 0) {
        printf("No drivers registered!\n");
        return;
    }

    printf("\n--- ALL DRIVERS ---\n");
    printf("ID | Name | Phone | Car | Status\n");
    printf("----------------------------------\n");

    for(i = 0; i < driver_count; i++) {        printf("%-2d | %-4s | %-5s | %-3s | %s\n",
               drivers[i].id,
               drivers[i].name,
               drivers[i].phone,
               drivers[i].car,
               drivers[i].available ? "Free" : "Busy");
    }
}