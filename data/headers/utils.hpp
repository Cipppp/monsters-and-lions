#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

using namespace std;
#include "../headers/types.hpp"
#include "../model/Monster.hpp"
#include "../model/Person.hpp"
#include "../model/Seers.hpp"
#include "../model/Siren.hpp"
#include "../model/Vampire.hpp"
#include "../model/Werewolf.hpp"

//! A map that associates language codes with the appropriate currency symbol
const std::map<std::string, std::string> CURRENCY_SYMBOLS = {
    {"en", "$"},
    {"ro", "lei"}};

//? Format a price in the specified language
std::string formatPrice(double price, const std::string &language) {
    // Look up the currency symbol for the specified language
    auto it = CURRENCY_SYMBOLS.find(language);
    std::string symbol = it != CURRENCY_SYMBOLS.end() ? it->second : "";

    // Format the price with the appropriate symbol
    return symbol + std::to_string(price);
}

//? Populate Menu struct with random values from csv files
Menu generateMenu(string foodPreference) {
    // Create a menu with random values
    Menu menu;

    // Open the files
    ifstream soupsFile("./data/menus/soups.csv");
    ifstream mainFoodsFile;
    ifstream dessertsFile("./data/menus/desserts.csv");

    // Based on the foodPreference, open the file (using switch)
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

    // Read the files
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

    // Close the files
    soupsFile.close();
    mainFoodsFile.close();
    dessertsFile.close();

    // Set the menu properties (there are strings)
    menu.soup = soups[rand() % soups.size()];
    menu.mainFood = mainFoods[rand() % mainFoods.size()];
    menu.dessert = desserts[rand() % desserts.size()];

    return menu;
}

//? Convert lei to dolars
double convertLeiToDolars(int lei) {
    return lei / 4.8;
}

//? Read persons from csv file
vector<PersonType> readPersons(string filename) {
    // Create an array of persons
    vector<PersonType> persons;

    // Open the file
    ifstream file(filename);

    // Read the file
    string line;
    while (getline(file, line)) {
        // Create an person
        PersonType person;

        // Split the line into name and role
        auto comma = line.find(",");
        person.name = line.substr(0, comma);
        person.role = line.substr(comma + 1);

        // Add the person to the array
        persons.push_back(person);
    }

    // Close the file
    file.close();

    // Return the array of persons
    return persons;
}

//? Read persons from csv file (containing "person" in role string) and return a vector of persons
vector<PersonType> readActors(string filename) {
    // Create an array of persons
    vector<PersonType> persons;

    // Open the file
    ifstream file(filename);

    // Read the file
    string line;
    while (getline(file, line)) {
        // Create an person
        PersonType person;

        // Split the line into name and role
        auto comma = line.find(",");
        person.name = line.substr(0, comma);
        person.role = line.substr(comma + 1);

        // Add the person to the array only if role contains "actor"
        if (person.role.find("actor/actress") != string::npos) {
            persons.push_back(person);
        }
    }

    // Close the file
    file.close();

    // Return the array of persons
    return persons;
}

// Print out the persons
void printPersons(vector<PersonType> persons) {
    for (auto person : persons) {
        cout << person.name << " played " << person.role << endl;
    }
}

//? Generate another 132 random persons using PersonType struct from names.txt and roles.txt
vector<PersonType> generateFigurants() {
    // Create an array of persons
    vector<PersonType> persons;

    // Open the files
    ifstream namesFile("./data/raw/names.txt");
    ifstream rolesFile("./data/raw/roles.txt");

    // Read the files
    vector<string> names;
    vector<string> roles;

    string name;
    string role;

    while (getline(namesFile, name)) {
        names.push_back(name);
    }

    while (getline(rolesFile, role)) {
        roles.push_back(role);
    }

    // Seed the random number generator
    mt19937 rng(random_device{}());

    // Generate 10 random names and roles
    for (int i = 0; i < 132; i++) {
        // Create a new Person object
        PersonType person;

        // Assign a random name and role to the person
        person.name = names[uniform_int_distribution<size_t>{0, names.size() - 1}(rng)];
        person.role = roles[uniform_int_distribution<size_t>{0, roles.size() - 1}(rng)];

        // Add the person to the vector
        persons.push_back(person);
    }

    // close the files
    namesFile.close();
    rolesFile.close();

    // return the array of persons
    return persons;
}

//? Write persons to csv file
void writePersons(vector<PersonType> persons, string filename) {
    // Open the file
    ofstream file(filename);

    // Write the persons to the file
    for (auto person : persons) {
        file << person.name << "," << person.role << endl;
    }

    // Close the file
    file.close();
}

//? Get the number of persons from a csv file
int getNumberOfPersons(string filename) {
    // Open the file
    ifstream file(filename);

    // Read the file
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }

    // Close the file
    file.close();

    // Return the number of persons
    return count;
}

//? Calculate the number of busses needed to transport the persons (1 bus = 50 people)
int getNumberOfBusses(vector<PersonType> persons) {
    // Calculate the number of busses needed
    int numberOfBusses = persons.size() / 50;
    if (persons.size() % 50 != 0) {
        numberOfBusses++;
    }

    // Return the number of busses
    return numberOfBusses;
}

//? Calculate the transport cost (1 bus = 50 people, 1 bus = 5680 lei)
int getTransportCost(vector<PersonType> persons) {
    // Calculate the transport cost
    int transportCost = getNumberOfBusses(persons) * 5680;

    // Convert the transport cost from lei to dolars
    transportCost = convertLeiToDolars(transportCost);

    // Return the transport cost
    return transportCost;
}

//? Get the price of rooms per night based on main persons and new persons, main persons stay 2 in a room and pay 350, new persons stay 3 in a room and pay 420
int getRoomPrice(vector<PersonType> mainPersons, vector<PersonType> newPersons) {
    // Calculate the price of rooms per night
    int roomPrice = (mainPersons.size() / 2) * 350 + (newPersons.size() / 3) * 420;

    // Convert the room price from lei to dolars
    roomPrice = convertLeiToDolars(roomPrice);

    // Return the price of rooms per night
    return roomPrice;
}

//? Get water, coffe and soda price per day, 1L of water per person, 0.5L of coffee per person, 0.8L of soda per person, 2L of water costs 6 dolars, 1L of coffee costs 30 dolars, 2L of soda costs 8 dolars
int getWaterCoffeSodaPrice(vector<PersonType> allPersons) {
    // Calculate the price of water, coffee and soda per day
    int waterCoffeSodaPrice = (allPersons.size() * 3 + allPersons.size() * 0.5 * 30 + allPersons.size() * 0.8 * 4);

    // Convert the water,coffe and soda price from lei to dolars
    waterCoffeSodaPrice = convertLeiToDolars(waterCoffeSodaPrice);

    // Return the price of water, coffee and soda per day
    return waterCoffeSodaPrice;
}

//? Get price for castle rental, 10000 dolars per day, every 10 days the price is reduced by 2%
int getCastleRentalPrice(int days) {
    // Calculate the price for castle rental
    int castleRentalPrice = 10000 * days;
    int discount = days / 10;
    castleRentalPrice -= castleRentalPrice * discount * 0.02;

    // Convert the castle rental price from lei to dolars
    castleRentalPrice = convertLeiToDolars(castleRentalPrice);

    // Return the price for castle rental
    return castleRentalPrice;
}

//? Add to CSV all details for period price using a PeriodPrice struct
void exportPrices(PeriodPrice periodPrice, string filename) {
    // Append the period price to the file
    ofstream file(filename, ios::app);

    // Write to CSV all details from periodPrice struct
    file << periodPrice.period << endl;
    file << "Transport: " << fixed << setprecision(0) << periodPrice.transportPrice << "$" << endl;
    file << "Room: " << fixed << setprecision(0) << periodPrice.roomPrice << "$" << endl;
    file << "Makeup: " << fixed << setprecision(0) << periodPrice.makeupPrice << "$" << endl;
    file << "Food: " << fixed << setprecision(0) << periodPrice.foodPrice << "$" << endl;
    file << "Rent: " << fixed << setprecision(0) << periodPrice.rentPrice << "$" << endl;
    file << "Total: " << fixed << setprecision(0) << periodPrice.totalPrice << "$" << endl;
    file << endl;

    // Close the file
    file.close();
}

//? Export every menu from paramter to a csv file (Menu vegetarianMenu,Menu flexitarianMenu,Menu anythingMenu, filename)
void exportMenu(Menu vegetarianMenu, Menu flexitarianMenu, Menu anythingMenu, string filename) {
    // Open the file
    ofstream file(filename);

    // Write the menus to the file
    file << "Vegetarian menu" << endl;
    file << "Soup," << vegetarianMenu.soup << endl;
    file << "Main food," << vegetarianMenu.mainFood << endl;
    file << "Dessert," << vegetarianMenu.dessert << endl;
    file << endl;
    file << "Flexitarian menu" << endl;
    file << "Soup," << flexitarianMenu.soup << endl;
    file << "Main food," << flexitarianMenu.mainFood << endl;
    file << "Dessert," << flexitarianMenu.dessert << endl;
    file << endl;
    file << "Anything menu" << endl;
    file << "Soup," << anythingMenu.soup << endl;
    file << "Main food," << anythingMenu.mainFood << endl;
    file << "Dessert," << anythingMenu.dessert << endl;

    // Close the file
    file.close();
}

//? Get the total numbers of vegetarians, flexitarians and anything eaters
void getFoodPreferences(vector<Monster *> monsters, int &vegetarians, int &flexitarians, int &anythingEaters) {
    // Get the total numbers of vegetarians, flexitarians and anything eaters
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

//? Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
int calculateTotalFoodPrice(vector<Monster *> monsters) {
    int vegetarians = 0;
    int flexitarians = 0;
    int anythingEaters = 0;

    getFoodPreferences(monsters, vegetarians, flexitarians, anythingEaters);

    // Calculate the total price of the menu based on vegetarian, flexitarian and anything eaters
    int totalPrice = vegetarians * 33 + flexitarians * 46 + anythingEaters * 40;

    // Convert the total price to dolars
    totalPrice = convertLeiToDolars(totalPrice);

    return totalPrice;
}

//? Calculate the total price of makeup per day
int calculateTotalMakeupPrice(vector<Monster *> monsters) {
    int totalPrice = 0;

    for (auto monster : monsters) {
        totalPrice += monster->makeupPricePerDay;
    }

    // Convert the total price to dolars
    totalPrice = convertLeiToDolars(totalPrice);

    return totalPrice;
}

PeriodPrice getPeriodPrice(int days, vector<Monster *> monsters, vector<PersonType> mainPersons, vector<PersonType> newPersons) {
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
    double totalPrice = totalFoodPrice + totalMakeupPrice + totalRoomPrice + totalWaterCoffeSodaPrice + totalTransportPrice + totalCastleRentalPrice;

    // Add the prices to a PeriodPrice object
    PeriodPrice periodPrice;
    periodPrice.period = "Period " + to_string(days) + " days";
    periodPrice.transportPrice = totalTransportPrice;
    periodPrice.roomPrice = totalRoomPrice;
    periodPrice.makeupPrice = totalMakeupPrice;
    periodPrice.foodPrice = totalFoodPrice;
    periodPrice.rentPrice = totalCastleRentalPrice;
    periodPrice.totalPrice = totalPrice;

    // Return the PeriodPrice object
    return periodPrice;
}

void getTotalPrice(vector<int> days, vector<Monster *> monsters, vector<PersonType> mainPersons, vector<PersonType> newPersons) {
    // For every period calculate the total price
    for (int i = 0; i < days.size(); i++) {
        // Get the total price for the period
        PeriodPrice periodPrice = getPeriodPrice(days[i], monsters, mainPersons, newPersons);

        // Export all details for the period (Appending to exsting finalPrices.csv file if it exists)
        exportPrices(periodPrice, "./data/generated/finalPrices.csv");
    }
}

//? For every person generate a class randomly and add it to an array of monsters
vector<Monster *> generateMonsters(vector<PersonType> persons) {
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
                monster = new Person(personName, personRole);
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

//? Initialize every monster with a menu based on the food preference
void initializeMonstersMenu(vector<Monster *> monsters) {
    // Generate a menu based on the food preference (choose betwen 'v', 'f' and 'a')
    Menu vegetarianMenu = generateMenu("vegetarian");
    Menu flexitarianMenu = generateMenu("flexitarian");
    Menu anythingMenu = generateMenu("anything");

    // Initialize every monster with a menu based on the food preference
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->foodPreference == "vegetarian") {
            monsters[i]->menu = vegetarianMenu;
        } else if (monsters[i]->foodPreference == "flexitarian") {
            monsters[i]->menu = flexitarianMenu;
        } else {
            monsters[i]->menu = anythingMenu;
        }
    }

    // Export every menu to a csv file
    exportMenu(vegetarianMenu, flexitarianMenu, anythingMenu, "./data/generated/finalMenu.csv");
}
