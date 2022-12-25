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

    return totalPrice;
}

// Calculate the total price of makeup per day 
int calculateTotalMakeupPrice(vector<Monster *> monsters) {
    int totalPrice = 0;

    for (auto monster : monsters) {
        totalPrice += monster->makeupPricePerDay;
    }

    return totalPrice;
}

// get the total price for the movie production based on the number of days
double getTotalPrice(int days, vector<Monster *> monsters, vector<Actor> mainActors, vector<Actor> newActors) {

    // Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
    int totalFoodPrice = calculateTotalFoodPrice(monsters);

    // Calculate the total price of makeup per day
    int totalMakeupPrice = calculateTotalMakeupPrice(monsters);

    // Calculate the total price of the room per day
    double totalRoomPrice = getRoomPrice(mainActors, newActors);

    // Calculate the total price of Water, Coffee and Soda per day
    double totalWaterCoffeSodaPrice = getWaterCoffeSodaPrice(mainActors) + getWaterCoffeSodaPrice(newActors);

    // Calculate the total price of the transport
    double totalTransportPrice = (getTransportCost(mainActors) + getTransportCost(newActors)) * 2;

    // Calculate the total price of the castle rental
    double totalCastleRentalPrice = getCastleRentalPrice(days);

    // Calculate the total price for the movie production based on the number of days
    double totalPrice = days * (totalFoodPrice + totalMakeupPrice + totalRoomPrice + totalWaterCoffeSodaPrice + totalTransportPrice  + totalCastleRentalPrice);

    // convert the total price to dolars
    totalPrice = convertLeiToDolars(totalPrice);

    // return the total price for the movie production
    return totalPrice;
}

// generate monsters
// For every actor generate a class randomly and add it to an array of monsters
vector<Monster *> generateMonsters(vector<Actor> actors) {
    int actorsSize = actors.size();

    // For every actor generate a class randomly and add it to an array of monsters
    vector<Monster *> monsters;
    for (int i = 0; i < actorsSize; i++) {
        // Get a random number between 0 and 4
        int randomNumber = rand() % 5;

        // Create a monster
        Monster *monster;

        // Set the actor name and role
        string actorName = actors[i].name;
        string actorRole = actors[i].role;

        // Create a monster based on the random number
        switch (randomNumber) {
            case 0:
                monster = new Human(actorName, actorRole);
                break;
            case 1:
                monster = new Seers(actorName, actorRole);
                break;
            case 2:
                monster = new Siren(actorName, actorRole);
                break;
            case 3:
                monster = new Vampire(actorName, actorRole);
                break;
            case 4:
                monster = new Werewolf(actorName, actorRole);
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

}

int main() {
    // number of days const = 30
    const int DAYS = 30;

    // Read actors from backup.csv file
    vector<Actor> actors = readActors("./data/actors/backup.csv");
    
    // Create an array of actors and read main actors
    vector<Actor> newActors;
    newActors = generateActors();

    // Combine the two arrays and write to actors.csv
    newActors.insert(newActors.end(), actors.begin(), actors.end());
    writeActors(newActors, "./data/actors/finalActors.csv");

    // generate monsters
    vector<Monster *> monsters = generateMonsters(newActors);
    
    // show the total price for the movie production based on the number of days using printf
    printf("The total price for the movie production is: %.0f dolars", getTotalPrice(DAYS, monsters, actors, newActors));
    return 0;
}
