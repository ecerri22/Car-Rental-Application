#include <stdio.h>
#include <string.h>
#include "ATEA.h"
#include "ROSELA.h"
#include "ENIA.h"
#include "DANIELA.h"

int main() {

    //DELETE RESERVATION TO BE FIXED/DONE -> Put the vehicle with that plate in available_vehicles
    //DELETE CLIENT TO BE DONE

    //AVAILABLE AFTER X DAYS TO BE DONE

    //MODIFY VEHICLES DOESNT MODIFY IN AVAILABLE VEHICLES
    //When new reservation is done, add +1 to the clients reservationCount and +1 to the vehicles rentCount

    int option;

    struct Vehicle *head = NULL;
    struct Vehicle *tail = NULL;

    struct Reservation *head2 = NULL;
    struct Reservation *tail2 = NULL;

    struct Client *head3 = NULL;
    struct Client *tail3 = NULL;

    //for (;;) {
        printf("MENU\n");
        printf("Choose one:\n");
        printf("1- Reservation related\n"
               "2- Vehicle related\n"
               "3- Client related\n");

        scanf("%d", &option);

        if(option==1){
            printf("Choose what you want to do:\n");
            printf( "1- Create reservation\n"
                    "2- Delete reservation\n"
                    "3- Display all reservations\n"
                    "4- Save all reservations with a total cost exceeding X to a new file\n"
               );

            scanf("%d", &option);

            switch (option) {
                case 1: {
                    addNewReservation(&head2, &tail2);
                    break;
                }
                case 2: {
                    //DELETE RESERVATION TO BE FIXED/DONE!!!
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
            printf("Choose what you want to do:\n");
            printf("1- Create vehicle\n"
                "2- Delete vehicle\n"
                "3- Display all vehicles\n"
                "4- Modify vehicle information \n"
                "5- Display available vehicles right now\n"
                "6- Display 3 most reserved vehicles\n"
                "7- Sort and display vehicles according to their daily rental price\n"
                "8- Search vehicle by plate number\n");

            scanf("%d", &option);


            switch (option) {
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
                    scanf("%9s", plateNumber);
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
            printf("Choose what you want to do:\n");
            printf( "1- Create client\n"
                    "2- Remove client\n"
                    "3- Display the name, surname and client ID of all clients more than 3 times\n"
               );

                scanf("%d", &option);

               switch (option) {
                case 1: {
                    addNewClient(&head3, &tail3);
                    break;
                }
                case 2: {
                    //DELETE CLIENT TO BE DONE
                    break;
                }
                case 3: {
                    printTop3Clients();
                    break;
                }
                case 0:{
                    return 0;
                }

            }
        }

   // }
    return 0;
}
