// #include "inconspicuuuuuus.h"

// typedef void (*fp)();

// typedef struct{
//     char name[20];
//     int age;
// } Person;

// typedef struct{
//     char type[20];
//     int height;
//     int width;
// } Furniture;

// typedef struct{
//     int name[10];
//     int Furniture[12];
// } Room;


// typedef struct House {
//     char address[50];
//     Person owner;
//     Room bathroom;
//     Room bedroom;
//     Room kitchen;
//     Room livingroom;
//     Room* otherrooms[50];
//     struct House* neighbor_on_right;
//     struct House* neighbor_on_left;
//     struct House* neighbor_on_front;
//     struct House* neighbor_on_back;
//     void (*garage)();
// } House;


// fp garage(struct House* self){
//     void garage_inner(){
//         printf("house on \"%s\" belongs to \"%s\"", self->address, self->owner.name);
//     }
//     return garage_inner;
// }

// House newHouse(){
//     House house;
//     strcpy(house.owner.name, "Jeremiah");
//     strcpy(house.address, "the sreet with no name");
//     house.garage = garage(&house);
//     return house;
// }



// digit pLaCe_wHeRe_pRoGrAm_sTaRtS(){
//     House house = newHouse();
//     house.garage();
// }







#include <stdio.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int main()
{
    printf("%sred\n", KRED);
    printf("%sgreen\n", KGRN);
    printf("%syellow\n", KYEL);
    printf("%sblue\n", KBLU);
    printf("%smagenta\n", KMAG);
    printf("%scyan\n", KCYN);
    printf("%swhite\n", KWHT);
    printf("%snormal\n", KNRM);

    return 0;
}