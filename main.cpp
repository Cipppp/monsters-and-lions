#include <iostream>

#include "./utils.h"
#include "./data/model/Monster.h"
#include "./data/model/Human.h"
#include "./data/model/Seers.h"
#include "./data/model/Siren.h"
#include "./data/model/Vampire.h"
#include "./data/model/Werewolf.h"

using namespace std;

// get the total numbers of vegetarians, flexitarians and anything eaters
void getFoodPreferences(vector<Monster *> monsters, int &vegetarians, int &flexitarians, int &anythingEaters) {
    // get the total numbers of vegetarians, flexitarians and anything eaters
    for (auto monster : monsters) {
        if (monster->foodPreference == "vegetarian") {
            vegetarians++;
        } else if (monster->foodPreference == "flexitarian") {
            flexitarians++;
        } else {
            anythingEaters++;
        }
    }
}

// Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
int calculateTotalFoodPrice(vector<Monster *> monsters) {
    int vegetarians = 0;
    int flexitarians = 0;
    int anythingEaters = 0;

    getFoodPreferences(monsters, vegetarians, flexitarians, anythingEaters);

    // calculate the total price of the menu based on vegetarian, flexitarian and anything eaters
    int totalPrice = vegetarians * 33 + flexitarians * 46 + anythingEaters * 40;

    // convert the total price to dolars
    totalPrice = convertLeiToDolars(totalPrice);

    return totalPrice;
}

// Calculate the total price of makeup per day 
int calculateTotalMakeupPrice(vector<Monster *> monsters) {
    int totalPrice = 0;

    for (auto monster : monsters) {
        totalPrice += monster->makeupPricePerDay;
    }

    // convert the total price to dolars
    totalPrice = convertLeiToDolars(totalPrice);

    return totalPrice;
}


PeriodPrice getPeriodPrice(int days, vector<Monster *> monsters, vector<Person> mainPersons, vector<Person> newPersons) {

    // Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
    int totalFoodPrice = calculateTotalFoodPrice(monsters) * days;

    // Calculate the total price of makeup per day
    int totalMakeupPrice = calculateTotalMakeupPrice(monsters) * days;

    // Calculate the total price of the room per day
    double totalRoomPrice = getRoomPrice(mainPersons, newPersons) * days;

    // Calculate the total price of Water, Coffee and Soda per day
    double totalWaterCoffeSodaPrice = getWaterCoffeSodaPrice(mainPersons) * days + getWaterCoffeSodaPrice(newPersons) * days;

    // Calculate the total price of the transport
    double totalTransportPrice = (getTransportCost(mainPersons) + getTransportCost(newPersons)) * 2;

    // Calculate the total price of the castle rental
    double totalCastleRentalPrice = getCastleRentalPrice(days) * days;

    // Calculate the total price for the movie production based on the number of days
    double totalPrice = totalFoodPrice + totalMakeupPrice + totalRoomPrice + totalWaterCoffeSodaPrice + totalTransportPrice  + totalCastleRentalPrice;

    // Add the prices to a PeriodPrice object
    PeriodPrice periodPrice;
    periodPrice.period = "Period " + to_string(days) + " days";
    periodPrice.transportPrice = totalTransportPrice;
    periodPrice.roomPrice = totalRoomPrice;
    periodPrice.makeupPrice = totalMakeupPrice;
    periodPrice.foodPrice = totalFoodPrice;
    periodPrice.rentPrice = totalCastleRentalPrice;
    periodPrice.totalPrice = totalPrice;

    // return the PeriodPrice object
    return periodPrice;
    
}

void getTotalPrice(vector<int> days, vector<Monster *> monsters, vector<Person> mainPersons, vector<Person> newPersons) {

    // For every period calculate the total price
    for (int i = 0; i < days.size(); i++) {
        // Get the total price for the period
        PeriodPrice periodPrice = getPeriodPrice(days[i], monsters, mainPersons, newPersons);

        // Export all details for the period (Appending to exsting finalPrices.csv file if it exists)
        exportPrices(periodPrice, "./data/generated/finalPrices.csv");
    }

}


// generate monsters
// For every person generate a class randomly and add it to an array of monsters
vector<Monster *> generateMonsters(vector<Person> persons) {
    int personsSize = persons.size();

    // For every person generate a class randomly and add it to an array of monsters
    vector<Monster *> monsters;
    for (int i = 0; i < personsSize; i++) {
        // Get a random number between 0 and 4
        int randomNumber = rand() % 5;

        // Create a monster
        Monster *monster;

        // Set the person name and role
        string personName = persons[i].name;
        string personRole = persons[i].role;

        // Create a monster based on the random number
        switch (randomNumber) {
            case 0:
                monster = new Human(personName, personRole);
                break;
            case 1:
                monster = new Seers(personName, personRole);
                break;
            case 2:
                monster = new Siren(personName, personRole);
                break;
            case 3:
                monster = new Vampire(personName, personRole);
                break;
            case 4:
                monster = new Werewolf(personName, personRole);
                break;
        }

        // Add the monster to the array
        monsters.push_back(monster);
    }

    return monsters;
}

// initialize every monster with a menu based on the food preference
void initializeMonstersMenu(vector<Monster *> monsters) {
    // generate a menu based on the food preference (choose betwen 'v', 'f' and 'a')
    Menu vegetarianMenu = generateMenu("vegetarian");
    Menu flexitarianMenu = generateMenu("flexitarian");
    Menu anythingMenu = generateMenu("anything");

    // initialize every monster with a menu based on the food preference
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->foodPreference == "vegetarian") {
            monsters[i]->menu = vegetarianMenu;
        } else if (monsters[i]->foodPreference == "flexitarian") {
            monsters[i]->menu = flexitarianMenu;
        } else {
            monsters[i]->menu = anythingMenu;
        }
    }

    // export every menu to a csv file
    exportMenu(vegetarianMenu, flexitarianMenu, anythingMenu, "./data/generated/finalMenu.csv");

}
// generate a README.md file for this project


int main() {

    //* ############## Main configuration ################
   // get the initial cast
   vector<Person> initialCast = readPersons("./data/raw/wednesdayCast.csv");

   // get the actors from the csv file
    vector<Person> actors = readActors("./data/raw/wednesdayCast.csv");
    // write actors to csv using function from utils
    writePersons(actors, "./data/generated/actors.csv");

    // generate the figurants
    vector<Person> figurants = generateFigurants();

    // write figurants to csv using function from utils
    writePersons(figurants, "./data/generated/figurants.csv");

    // read all persons from wednesdayCast.csv
    vector<Person> persons = readPersons("./data/raw/wednesdayCast.csv");
    
    // add to persons the generated figurants and then write to finalCast.csv
    persons.insert(persons.end(), figurants.begin(), figurants.end());

    //* ############## Actorii, castul extins și figuranții (1 CSV) ################
    writePersons(persons, "./data/generated/finalCast.csv");

    // generate monsters from actors and figurants and then combine it in one array
    vector<Monster *> monsters = generateMonsters(actors);

    // add to monsters the generated monsters figurants
    monsters.insert(monsters.end(), generateMonsters(figurants).begin(), generateMonsters(figurants).end());

    //* ############## Meniul de mâncare (1 CSV) ################
    // initialize every monster with a menu based on the food preference
    initializeMonstersMenu(monsters);

    //* ############### Costul pentru fiecare perioadă (1 CSV) ################
    // Create a vector of days
    vector<int> days = {30, 45, 60, 100};

    // get the total price for the movie production based on the number of days
    getTotalPrice(days, monsters, persons, figurants);


    return 0;
 
}


