#ifndef ENIA_H_INCLUDED
#define ENIA_H_INCLUDED
#include "structures.h"

/*
displayAvailable - Will print what is on the available_vehicles - kinda Works
printTop3Vehicles - Works!!!
*/

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
                  &currentVehicle.dailyPrice, &currentVehicle.rentCount) == EOF) {
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
    //this opens the file in reading mode & assigns the file pointer to the variable
    FILE *vehiclesFile = fopen("vehicles.txt", "r");
    //this array will store each line from the file
    char vehicle[100];
    //the variable will count the nr. of vehicles read
    int vehicleCount = 0;
    //this array will save all the rentCounts of each vehicle
    int reservationCount[100];

   //if file isn't opened return
    if (vehiclesFile == NULL) {
        printf("Couldn't open the file \n");
        return;
    }

    //this read each line of the file using fgets
    while (fgets(vehicle, sizeof(vehicle), vehiclesFile) != NULL) {
        //it skips the first 8, and reads the last one of each line (index)
        sscanf(vehicle, "%*s %*d %*s %*s %*f %*d %*f %d", &reservationCount[vehicleCount]);
        //continue with the next line
        vehicleCount++;
    }

    //bubble sort to sort in descending order
    for (int i=0; i<vehicleCount-1; i++) {
        for (int j=0; j<vehicleCount-i-1; j++) {
            if (reservationCount[j]<reservationCount[j+1]) {
                int temp = reservationCount[j];
                reservationCount[j] = reservationCount[j+1];
                reservationCount[j+1] = temp;
            }
        }
    }

    printf("Top 3 Most Reserved Vehicles:\n");
    // Reset file position indicator to the beginning
    //closes and reopens file
    rewind(vehiclesFile);

    // Counter for reading lines
    int count = 0;

    //reads the lines until the third one
    while (fgets(vehicle, sizeof(vehicle), vehiclesFile) != NULL && count < 3) {
        printf("%s\n", vehicle);
        count++;
    }

    //close file
    fclose(vehiclesFile);
}


#endif // ENIA_H_INCLUDED
