#include <stdio.h>
#include <string.h>
#include "ATEA.h"
#include "ROSELA.h"
#include "ENIA.h"
#include "DANIELA.h"

int main() {

    int option;
    int option2;

    struct Vehicle *head = NULL;
    struct Vehicle *tail = NULL;

    struct Reservation *head2 = NULL;
    struct Reservation *tail2 = NULL;

    struct Client *head3 = NULL;
    struct Client *tail3 = NULL;

    for (;;) {

        printf("\n");
        printf("******************\n");
        printf("*      MENU      *\n");
        printf("******************\n");
        printf("Choose one option:\n");
        printf("******************\n");
        printf("1- Reservation related\n"
               "2- Vehicle related\n"
               "3- Client related\n"
               "0- Close program\n");
        printf("******************\n");

        scanf("%d", &option);

        if(option==1){

            printf("---------------------------\n");
            printf("Choose what you want to do:\n");
            printf("---------------------------\n");
            printf( "1- Create reservation\n"
                    "2- Delete reservation\n"
                    "3- Display all reservations\n"
                    "4- Save all reservations with a total cost exceeding X to a new file\n"
               );
            scanf("%d", &option2);

            switch (option2) {
                case 1: {
                    addNewReservation(&head2, &tail2);
                    break;
                }
                case 2: {
                    int reservationID;
                    printf("Enter reservation ID: ");
                    scanf("%d", &reservationID);
                    deleteReservation(reservationID);
                    break;
                }
                case 3: {
                    displayReservations();
                    break;
                }
                case 4: {
                    float price;
                    printf("Enter the price: ");
                    scanf("%f", &price);
                    filterReservations(price);
                    break;
                }
                case 0:{
                    return 0;
                }

            }
      }


        if(option==2){

            printf("---------------------------\n");
            printf("Choose what you want to do:\n");
            printf("---------------------------\n");
            printf("1- Create vehicle\n"
                "2- Delete vehicle\n"
                "3- Display all vehicles\n"
                "4- Modify vehicle information \n"
                "5- Display available vehicles right now\n"
                "6- Display 3 most reserved vehicles\n"
                "7- Sort and display vehicles according to their daily rental price\n"
                "8- Search vehicle by plate number\n");

            scanf("%d", &option2);

            switch (option2) {
                case 1: {
                    addNewVehicle(&head,&tail);
                    break;
                }
                case 2: {
                    char plateForRemoving[10];
                    printf("Enter the plate number of the vehicle you want to remove: ");
                    scanf("%s", plateForRemoving);
                    removeVehicle(plateForRemoving);
                    break;

                }
                case 3:{
                    displayAllVehicles();
                    break;
                }
                case 4: {
                    char plateNumber[10];
                    printf("Enter the plate number of the vehicle to modify: ");
                    scanf("%s", plateNumber);
                    modifyVehicle(plateNumber);
                    break;
                }
                case 5:{
                    displayAvailable();
                    break;
                }
                case 6: {
                    printTop3Vehicles();
                    break;
                }
                case 7: {
                    sorting();
                    break;
                }
                case 8: {
                    char plate[20];
                    printf("ENTER THE PLATE NUMBER: ");
                    scanf("%s", plate);
                    searchVehicleByPlateNumber(plate);
                    break;
                }
                case 0:{
                    return 0;
                }

            }
        }

        if(option==3){
            printf("---------------------------\n");
            printf("Choose what you want to do:\n");
            printf("---------------------------\n");
            printf( "1- Create client\n"
                    "2- Display the name, surname and client ID of all clients who have reserved more than 3 times\n"
               );
                scanf("%d", &option2);

               switch (option2) {
                case 1: {
                    addNewClient(&head3, &tail3);
                    break;
                }
                case 2: {
                    printClientsWithReservationCountGreaterThan3();
                    break;
                }
                case 0:{
                    return 0;
                }

            }
        }

        if(option==0){
            return 0;
        }

    }
    return 0;
}
