#ifndef DANIELA_H_INCLUDED
#define DANIELA_H_INCLUDED
#include "structures.h"

void displayReservations() {
    FILE* f = fopen("reservations.txt", "r");
    if (f == NULL) {
        printf("Cannot open file 'reservations.txt'!\n");
        return;
    }

    struct Reservation currentReservation;

    while (fscanf(f, "%d %s %s %s %d %f", &currentReservation.ID, currentReservation.date,
                  currentReservation.clientID, currentReservation.plateNumber, &currentReservation.nrOfDays,
                  &currentReservation.totalPrice) != EOF) {
        printf("Reservation ID: %d\n", currentReservation.ID);
        printf("Reservation Date: %s\n", currentReservation.date);
        printf("Client ID: %s\n", currentReservation.clientID);
        printf("Plate Number: %s\n", currentReservation.plateNumber);
        printf("Number of Days: %d\n", currentReservation.nrOfDays);
        printf("Total Price: %.2f\n", currentReservation.totalPrice);
        printf("\n");
    }

    fclose(f);
}

void displayAvailable() {

    FILE* f = fopen("available_vehicles.txt", "r");
    if (f == NULL) {
        printf("Cannot open file 'available_vehicles.txt'!\n");
        return;
    }

    struct Vehicle currentVehicle;

    while (fscanf(f, "%s %d %s %s %f %d %f %d",
                  currentVehicle.plate, &currentVehicle.year,
                  currentVehicle.model, currentVehicle.fuelType,
                  &currentVehicle.consumption, &currentVehicle.seats,
                  &currentVehicle.dailyPrice, &currentVehicle.rentCount) != EOF) {
        printf("Plate Number: %s\n", currentVehicle.plate);
        printf("Year: %d\n", currentVehicle.year);
        printf("Model: %s\n", currentVehicle.model);
        printf("Fuel Type: %s\n", currentVehicle.fuelType);
        printf("Consumption: %.2f\n", currentVehicle.consumption);
        printf("Seats: %d\n", currentVehicle.seats);
        printf("Daily Price: %.2f\n", currentVehicle.dailyPrice);
        printf("Rent Count: %d\n", currentVehicle.rentCount);
        printf("\n");
    }

    fclose(f);
}

void printTop3Vehicles() {

    FILE *vehiclesFile = fopen("vehicles.txt", "r");
    char line[100];
    int vehicleCount = 0;
    struct Vehicle vehicles[100];

    if (vehiclesFile == NULL) {
        printf("Couldn't open the file\n");
        return 1;
    }

    // Read each line of the file and store the vehicle information
    while (fgets(line, sizeof(line), vehiclesFile) != NULL) {
        sscanf(line, "%s %d %s %s %f %d %f %d", vehicles[vehicleCount].plate, &vehicles[vehicleCount].year,
               vehicles[vehicleCount].model, vehicles[vehicleCount].fuelType, &vehicles[vehicleCount].consumption,
               &vehicles[vehicleCount].seats, &vehicles[vehicleCount].dailyPrice, &vehicles[vehicleCount].rentCount);
        vehicleCount++;
    }

    // Bubble sort to sort in descending order based on rentCount
    for (int i = 0; i < vehicleCount - 1; i++) {
        for (int j = 0; j < vehicleCount - i - 1; j++) {
            if (vehicles[j].rentCount < vehicles[j + 1].rentCount) {
                struct Vehicle temp = vehicles[j];
                vehicles[j] = vehicles[j + 1];
                vehicles[j + 1] = temp;
            }
        }
    }

    printf("Top 3 Most Reserved Vehicles:\n");

    // Print the top 3 vehicles
    for (int i = 0; i < 3 && i < vehicleCount; i++) {
        printf("%s %d %s %s %.2f %d %.2f %d\n", vehicles[i].plate, vehicles[i].year, vehicles[i].model,
               vehicles[i].fuelType, vehicles[i].consumption, vehicles[i].seats, vehicles[i].dailyPrice,
               vehicles[i].rentCount);
    }

    fclose(vehiclesFile);
    return 0;
}

void printClientsWithReservationCountGreaterThan3() {
    FILE* clientsFile = fopen("clients.txt", "r");
    char client[100];
    int reservationCount;

    if (clientsFile == NULL) {
        printf("Couldn't open the file \n");
        return;
    }

    printf("Clients with Reservation Count > 3:\n");

    while (fgets(client, sizeof(client), clientsFile) != NULL) {
        sscanf(client, "%*d %*s %*s %*s %*s %*s %d", &reservationCount);
        if (reservationCount > 3) {
            printf("%s", client);
        }
    }

    fclose(clientsFile);
}


#endif // DANIELA_H_INCLUDED
