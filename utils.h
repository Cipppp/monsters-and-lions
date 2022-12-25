#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// create a struct based on wednesdayCast.csv
struct Actor {
    string name;
    string role;
};

// generate a struct Menu with 4 properties (soup, mainFood, dessert, price)
struct Menu {
    string soup;
    string mainFood;
    string dessert;
};

// void show menu details
void showMenuDetails(Menu menu) {
    cout << "Soup: " << menu.soup << endl;
    cout << "Main Food: " << menu.mainFood << endl;
    cout << "Dessert: " << menu.dessert << endl;
}


// populate Menu struct with random values from csv files
Menu generateMenu(string foodPreference) {
    // create a menu with random values
    Menu menu;

    // open the files
    ifstream soupsFile("./data/menus/soups.csv");
    ifstream mainFoodsFile;
    ifstream dessertsFile("./data/menus/desserts.csv");

    // based on the foodPreference, open the file (using switch)
    switch (foodPreference[0]) {
        case 'v':
            mainFoodsFile.open("./data/menus/vegetarianMenu.csv");
            break;
        case 'f':
            mainFoodsFile.open("./data/menus/flexitarianMenu.csv");
            break;
        default:
            mainFoodsFile.open("./data/menus/normalMenu.csv");
            break;
    }

    // read the files
    vector<string> soups;
    vector<string> mainFoods;
    vector<string> desserts;

    string soup;
    string mainFood;
    string dessert;

    while (getline(soupsFile, soup)) {
        soups.push_back(soup);
    }

    while (getline(mainFoodsFile, mainFood)) {
        mainFoods.push_back(mainFood);
    }

    while (getline(dessertsFile, dessert)) {
        desserts.push_back(dessert);
    }

    // close the files
    soupsFile.close();
    mainFoodsFile.close();
    dessertsFile.close();

    // set the menu properties (there are strings)
    menu.soup = soups[rand() % soups.size()];
    menu.mainFood = mainFoods[rand() % mainFoods.size()];
    menu.dessert = desserts[rand() % desserts.size()];

    return menu;
}

// read actors from csv file and return a vector of actors
vector<Actor> readActors(string filename) {
    // create an array of actors
    vector<Actor> actors;

    // open the file
    ifstream file(filename);

    // read the file
    string line;
    while (getline(file, line)) {
        // create an actor
        Actor actor;

        // split the line into name and role
        auto comma = line.find(",");
        actor.name = line.substr(0, comma);
        actor.role = line.substr(comma + 1);

        // add the actor to the array
        actors.push_back(actor);
    }

    // close the file
    file.close();

    // return the array of actors

    return actors;
}

// print out the actors
void printActors(vector<Actor> actors) {
    for (auto actor : actors) {
        cout << actor.name << " played " << actor.role << endl;
    }
}

// generate another 132 random actors using Actor struct from names.txt and roles.txt
vector<Actor> generateActors() {
    // create an array of actors
    vector<Actor> actors;

    // open the files
    ifstream namesFile("./data/actors/names.txt");
    ifstream rolesFile("./data/actors/roles.txt");

    // read the files
    string name;
    string role;
    while (getline(namesFile, name) && getline(rolesFile, role)) {
        // create an actor
        Actor actor;

        // set the name and role
        actor.name = name;
        actor.role = role;

        // add the actor to the array
        actors.push_back(actor);
    }

    // close the files
    namesFile.close();
    rolesFile.close();

    // return the array of actors
    return actors;
}

// write actors to csv file
void writeActors(vector<Actor> actors, string filename) {
    // open the file
    ofstream file(filename);

    // write the actors to the file
    for (auto actor : actors) {
        file << actor.name << "," << actor.role << endl;
    }

    // close the file
    file.close();
}

int getNumberOfActors(string filename) {
    // open the file
    ifstream file(filename);

    // read the file
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }

    // close the file
    file.close();

    // return the number of actors
    return count;
}

// Calculate the number of busses needed to transport the actors (1 bus = 50 actors)
int getNumberOfBusses(vector<Actor> actors) {
    // Calculate the number of busses needed
    int numberOfBusses = actors.size() / 50;
    if (actors.size() % 50 != 0) {
        numberOfBusses++;
    }

    // return the number of busses
    return numberOfBusses;
}

// Calculate the transport cost (1 bus = 50 actors, 1 bus = 5680 lei)
int getTransportCost(vector<Actor> actors) {
    // Calculate the transport cost
    int transportCost = getNumberOfBusses(actors) * 5680;

    // return the transport cost
    return transportCost;
}

// generate food preference, choose between "anything", "vegetarian" and "flexitarian"
string generateFoodPreference() {
    // create an array of food preferences
    vector<string> foodPreferences = {"anything", "vegetarian", "flexitarian"};

    // generate a random number between 0 and 2
    int randomNumber = rand() % 3;

    // return the food preference
    return foodPreferences[randomNumber];
}

// get the price of rooms per night based on main actors and new actors, main actors stay 2 in a room and pay 350, new actors stay 3 in a room and pay 420
int getRoomPrice(vector<Actor> mainActors, vector<Actor> newActors) {
    // Calculate the price of rooms per night
    int roomPrice = (mainActors.size() / 2) * 350 + (newActors.size() / 3) * 420;

    // return the price of rooms per night
    return roomPrice;
}

// get water,coffe and soda price per day, 1L of water per person, 0.5L of coffee per person, 0.8L of soda per person, 2L of water costs 6 dolars, 1L of coffee costs 30 dolars, 2L of soda costs 8 dolars
int getWaterCoffeSodaPrice(vector<Actor> allActors) {
    // Calculate the price of water, coffee and soda per day
    int waterCoffeSodaPrice = (allActors.size() * 3 + allActors.size() * 0.5 * 30 + allActors.size() * 0.8 * 4);

    // return the price of water, coffee and soda per day
    return waterCoffeSodaPrice;
}

// get price for castle rental, 10000 dolars per day, every 10 days the price is reduced by 2%
int getCastleRentalPrice(int days) {
    // Calculate the price for castle rental
    int castleRentalPrice = 10000 * days;
    int discount = days / 10;
    castleRentalPrice -= castleRentalPrice * discount * 0.02;

    // return the price for castle rental
    return castleRentalPrice;
}



// assign every actor to a class, randomly choose between Human, Seers, Siren, Vampire, Werewolf
string generateClass() {
    // create an array of classes
    vector<string> classes = {"Human", "Seers", "Siren", "Vampire", "Werewolf"};

    // generate a random number between 0 and 4
    int randomNumber = rand() % 5;

    // return the class
    return classes[randomNumber];
}

// convert lei to dolars
double convertLeiToDolars(int lei) {
    // convert lei to dolars
    double dolars = lei / 4.8;

    // return the dolars
    return dolars;
}


