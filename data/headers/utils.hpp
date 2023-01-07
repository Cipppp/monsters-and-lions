#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
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
    // Catch the error if the language is not found
    try {
        if (CURRENCY_SYMBOLS.find(language) == CURRENCY_SYMBOLS.end()) {
            throw "Invalid language";
        }

        // Look up the currency symbol for the specified language
        auto it = CURRENCY_SYMBOLS.find(language);
        std::string symbol = it != CURRENCY_SYMBOLS.end() ? it->second : "";

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << price << symbol;

        return stream.str();
    } catch (const std::exception &e) {
        // Handle the exception here
        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
    }
}

//? Populate Menu struct with random values from csv files
Menu generateMenu(string foodPreference, const std::string &language) {
    // Create a menu with random values
    Menu menu;
    // Open the files based on the language
    ifstream soupsFile;
    ifstream mainFoodsFile;
    ifstream dessertsFile;

    // Catch the error if the files are not found
    try {
        // Open the files based on the language and food preference
        if (language == "en") {
            soupsFile.open("./data/menus/soups.csv");
            if (foodPreference == "v") {
                mainFoodsFile.open("./data/menus/vegetarianMenu.csv");
            } else if (foodPreference == "f") {
                mainFoodsFile.open("./data/menus/flexitarianMenu.csv");
            } else {
                mainFoodsFile.open("./data/menus/normalMenu.csv");
            }
            dessertsFile.open("./data/menus/desserts.csv");
        } else if (language == "ro") {
            soupsFile.open("./data/menus/soupsRO.csv");
            if (foodPreference == "v") {
                mainFoodsFile.open("./data/menus/vegetarianMenuRO.csv");
            } else if (foodPreference == "f") {
                mainFoodsFile.open("./data/menus/flexitarianMenuRO.csv");
            } else {
                mainFoodsFile.open("./data/menus/normalMenuRO.csv");
            }
            dessertsFile.open("./data/menus/dessertsRO.csv");
        } else {
            throw "Invalid language";
        }
    } catch (const std::exception &e) {
        // Handle the exception here
        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
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

    // Catch the error if the file is not found
    try {
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

        // Throw an error if the files are not found
        if (!file.is_open()) {
            throw "Could not open file";
        }

        // Close the file
        file.close();
    } catch (const std::exception &e) {
        // Handle the exception here
        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
    }

    // Return the array of persons
    return persons;
}

//? Read persons from csv file (containing "person" in role string) and return a vector of persons
vector<PersonType> readActors(string filename) {
    // Create an array of persons
    vector<PersonType> persons;

    try {
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

        // Throw an error if the files are not found
        if (!file.is_open()) {
            throw "Could not open file";
        }

        // Close the file
        file.close();
    } catch (const std::exception &e) {
        // Print an error message
        std::cerr << "Error: " << e.what() << std::endl;

        // Return an empty array of persons
        return vector<PersonType>();
    }

    // Return the array of persons
    return persons;
}

//? Print out the persons
void printPersons(vector<PersonType> persons) {
    for (auto person : persons) {
        cout << person.name << " played " << person.role << endl;
    }
}

//? Generate another 132 random persons using PersonType struct from names.txt and roles.txt
vector<PersonType> generateFigurants() {
    // Create an array of persons
    vector<PersonType> persons;

    try {
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

    } catch (const std::exception &e) {
        // Print an error message
        std::cerr << "Error: " << e.what() << std::endl;

        // Return an empty array of persons
        return vector<PersonType>();
    }

    // return the array of persons
    return persons;
}

//? Write persons to a csv file
void writePersons(vector<PersonType> persons, string filename) {
    try {
        // Open the file
        ofstream file(filename);

        // Throw an error if the files are not found
        if (!file.is_open()) {
            throw "Could not open file";
        }

        // Write the persons to the file
        for (auto person : persons) {
            file << person.name << "," << person.role << endl;
        }

        // Close the file
        file.close();
    } catch (exception &e) {
        // Print the error message
        cout << "Error: " << e.what() << endl;
    }
}

//? Get the number of persons from a csv file
int getNumberOfPersons(string filename) {
    int count = 0;
    try {
        // Open the file
        ifstream file(filename);

        // Throw an error if the files are not found
        if (!file.is_open()) {
            throw "Could not open file";
        }

        // Read the file
        string line;
        while (getline(file, line)) {
            count++;
        }

        // Close the file
        file.close();
    } catch (const exception &e) {
        // An error occurred while trying to open the file
        // Return a default value of 0
        count = 0;
    }

    // Return the number of persons
    return count;
}

//? Calculate the number of busses needed to transport the persons (1 bus = 50 people)
int getNumberOfBusses(vector<PersonType> persons) {
    // Calculate the number of busses needed
    int numberOfBusses = persons.size() / 50;

    // If the number of persons is not a multiple of 50, add 1 bus
    if (persons.size() % 50 != 0) {
        numberOfBusses++;
    }

    // Return the number of busses
    return numberOfBusses;
}

//? Calculate the transport cost (1 bus = 50 people, 1 bus = 5680 lei)
int getTransportCost(vector<PersonType> persons) {
    try {
        // Catch the exception if the number of persons is 0
        if (persons.size() == 0) {
            throw "The number of persons is 0";
        }
        // Calculate the transport cost
        int transportCost = getNumberOfBusses(persons) * 5680;

        // Convert the transport cost from lei to dolars
        transportCost = convertLeiToDolars(transportCost);

        // Return the transport cost
        return transportCost;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

//? Get the price of rooms per night based on main persons and new persons, main persons stay 2 in a room and pay 350, new persons stay 3 in a room and pay 420
int getRoomPrice(vector<PersonType> mainPersons, vector<PersonType> newPersons) {
    try {
        // Catch the exception if the number of persons is 0
        if (mainPersons.size() == 0 && newPersons.size() == 0) {
            throw "The number of persons is 0";
        }
        // Calculate the price of rooms per night
        int roomPrice = (mainPersons.size() / 2) * 350 + (newPersons.size() / 3) * 420;

        // Convert the room price from lei to dolars
        roomPrice = convertLeiToDolars(roomPrice);

        // Return the price of rooms per night
        return roomPrice;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

//? Get water, coffe and soda price per day, 1L of water per person, 0.5L of coffee per person, 0.8L of soda per person, 2L of water costs 6 dolars, 1L of coffee costs 30 dolars, 2L of soda costs 8 dolars
int getWaterCoffeSodaPrice(vector<PersonType> allPersons) {
    try {
        // Catch the exception if the number of persons is 0
        if (allPersons.size() == 0) {
            throw "The number of persons is 0";
        }
        // Calculate the price of water, coffee and soda per day
        int waterCoffeSodaPrice = (allPersons.size() * 3 + allPersons.size() * 0.5 * 30 + allPersons.size() * 0.8 * 4);

        // Convert the water,coffe and soda price from lei to dolars
        waterCoffeSodaPrice = convertLeiToDolars(waterCoffeSodaPrice);

        // Return the price of water, coffee and soda per day
        return waterCoffeSodaPrice;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

//? Get price for castle rental, 10000 dolars per day, every 10 days the price is reduced by 2%
int getCastleRentalPrice(int days) {
    try {
        // Catch the exception if the number of days is 0
        if (days == 0) {
            throw "The number of days is 0";
        }

        // Calculate the price for castle rental
        int castleRentalPrice = 10000 * days;
        int discount = days / 10;
        castleRentalPrice -= castleRentalPrice * discount * 0.02;

        // Convert the castle rental price from lei to dolars
        castleRentalPrice = convertLeiToDolars(castleRentalPrice);

        // Return the price for castle rental
        return castleRentalPrice;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

//? Add to CSV all details for period price using a PeriodPrice struct
void exportPrices(PeriodPrice periodPrice, string filename, const std::string &language) {
    try {
        // Append the period price to the file
        std::ofstream file(filename, std::ios::app);

        // Write to CSV all details from periodPrice struct based on language, if language is "en" write in english, if language is "ro" write in romanian, set the price using setprecision(2) and fixed
        if (language == "en") {
            file << "Period," << periodPrice.period << endl;
            file << "Transport price," << setprecision(2) << fixed << periodPrice.transportPrice << "$" << endl;
            file << "Room price," << setprecision(2) << fixed << periodPrice.roomPrice << "$" << endl;
            file << "Makeup price," << setprecision(2) << fixed << periodPrice.makeupPrice << "$" << endl;
            file << "Food and water price," << setprecision(2) << fixed << periodPrice.foodPrice << "$" << endl;
            file << "Castle rental price," << setprecision(2) << fixed << periodPrice.rentPrice << "$" << endl;
            file << "Total price," << setprecision(2) << fixed << periodPrice.totalPrice << "$" << endl;
            file << endl;
        } else if (language == "ro") {
            file << "Perioada," << periodPrice.period << endl;
            file << "Cost transport," << setprecision(2) << fixed << periodPrice.transportPrice * 4.8 << "lei" << endl;
            file << "Cost camere," << setprecision(2) << fixed << periodPrice.roomPrice * 4.8 << "lei" << endl;
            file << "Cost machiaj," << setprecision(2) << fixed << periodPrice.roomPrice * 4.8 << "lei" << endl;
            file << "Cost mancare si apa," << setprecision(2) << fixed << periodPrice.foodPrice * 4.8 << "lei" << endl;
            file << "Cost inchiriere castel," << setprecision(2) << fixed << periodPrice.rentPrice * 4.8 << "lei" << endl;
            file << "Cost total," << setprecision(2) << fixed << periodPrice.totalPrice * 4.8 << "lei" << endl;
            file << endl;
        }

        // Close the file
        file.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

//? Export every menu from paramter to a csv file (Menu vegetarianMenu,Menu flexitarianMenu,Menu anythingMenu, filename)
void exportMenu(vector<Menu> menus, string filename, const std::string &language) {
    try {
        // Open the file
        ofstream file(filename);

        // Write the headers to the file
        if (language == "en") {
            file << "Day,Soup,Main Food,Dessert" << endl;
        } else if (language == "ro") {
            file << "Zi,Ciorba,Fel Principal,Desert" << endl;
        } else {
            throw "Language not supported";
        }

        // Write the details for each menu to the file
        for (int i = 0; i < menus.size(); i++) {
            // Write the day number
            int dayNumber = (i) / 3 + 1;
            file << dayNumber << ",";

            // Write the menu details
            file << menus[i].soup << "," << menus[i].mainFood << "," << menus[i].dessert << endl;
        }
        // Close the file
        file.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

//? Get the total numbers of vegetarians, flexitarians and anything eaters
void getFoodPreferences(vector<Monster *> monsters, int &vegetarians, int &flexitarians, int &anythingEaters) {
    try {
        // Throw an exception if the vector is empty
        if (monsters.empty()) {
            throw "The vector is empty";
        }

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
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

//? Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
int calculateTotalFoodPrice(vector<Monster *> monsters) {
    try {
        // Throw an exception if the vector is empty
        if (monsters.empty()) {
            throw "The vector is empty";
        }

        int vegetarians = 0;
        int flexitarians = 0;
        int anythingEaters = 0;

        getFoodPreferences(monsters, vegetarians, flexitarians, anythingEaters);

        // Calculate the total price of the menu based on vegetarian, flexitarian and anything eaters
        int totalPrice = vegetarians * 33 + flexitarians * 46 + anythingEaters * 40;

        // Convert the total price to dolars
        totalPrice = convertLeiToDolars(totalPrice);
        return totalPrice;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

//? Calculate the total price of makeup per day
int calculateTotalMakeupPrice(vector<Monster *> monsters) {
    try {
        // Throw an exception if the vector is empty
        if (monsters.empty()) {
            throw "The vector is empty";
        }

        int totalPrice = 0;

        for (auto monster : monsters) {
            totalPrice += monster->makeupPricePerDay;
        }

        // Convert the total price to dolars
        totalPrice = convertLeiToDolars(totalPrice);

        return totalPrice;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

//? Get the price of the room per day
PeriodPrice getPeriodPrice(int days, vector<Monster *> monsters, vector<PersonType> mainPersons, vector<PersonType> newPersons) {
    try {
        // Throw an exception if the monsters vector is empty
        if (monsters.empty() || mainPersons.empty() || newPersons.empty()) {
            throw "The vector is empty";
        }

        // Calculate the total price of makeup per day
        int totalMakeupPrice = calculateTotalMakeupPrice(monsters) * days;

        // Calculate the total price of the room per day
        double totalRoomPrice = getRoomPrice(mainPersons, newPersons) * days;

        // Calculate the total price of Water, Coffee and Soda per day
        double totalWaterCoffeSodaPrice = getWaterCoffeSodaPrice(mainPersons) * days + getWaterCoffeSodaPrice(newPersons) * days;

        // Calculate the total price per day of the menu based on vegetarian, flexitarian and anything eaters
        int totalFoodPrice = calculateTotalFoodPrice(monsters) * days + totalWaterCoffeSodaPrice;

        // Calculate the total price of the transport
        double totalTransportPrice = (getTransportCost(mainPersons) + getTransportCost(newPersons)) * 2;

        // Calculate the total price of the castle rental
        double totalCastleRentalPrice = getCastleRentalPrice(days);

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
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return PeriodPrice();
}

void getTotalPrice(vector<int> days, vector<Monster *> monsters, vector<PersonType> mainPersons, vector<PersonType> newPersons, string language) {
    try {
        // Throw an exception if the monsters vector is empty
        if (monsters.empty() || mainPersons.empty() || newPersons.empty() || days.empty()) {
            throw "The vector is empty";
        }

        // For every period calculate the total price
        for (int i = 0; i < days.size(); i++) {
            // Get the total price for the period
            PeriodPrice periodPrice = getPeriodPrice(days[i], monsters, mainPersons, newPersons);

            // Export all details for the period (Appending to exsting finalPrices.csv file if it exists)
            exportPrices(periodPrice, "./data/generated/finalPrices.csv", language);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

//? For every person generate a class randomly and add it to an array of monsters
vector<Monster *> generateMonsters(vector<PersonType> persons) {
    try {
        // Throw an error if the persons vector is empty
        if (persons.empty()) {
            throw "The persons vector is empty!";
        }

        // Get the size of the persons vector
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
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return vector<Monster *>();
}

//? Initialize every monster with a menu based on the food preference
void initializeMonstersMenu(vector<Monster *> monsters, const std::string &language) {
    try {
        // Throw an exception if the language is not supported
        if (language != "ro" && language != "en") {
            throw "Language not supported";
        }

        // Throw an exception if the monsters vector is empty
        if (monsters.empty()) {
            throw "The monsters vector is empty!";
        }
        // Generate a menu based on the food preference (choose betwen 'v', 'f' and 'a')
        // Create an array with 3 vegetarian menus, 3 flexitarian menus and 3 anything menus
        vector<Menu> menus;

        // generate a random seed
        srand(static_cast<unsigned int>(time(nullptr)));

        // Generate 3 vegetarian menus
        for (int i = 0; i < 3; i++) {
            menus.push_back(generateMenu("v", language));
        }

        // Generate 3 flexitarian menus
        for (int i = 0; i < 3; i++) {
            menus.push_back(generateMenu("f", language));
        }

        // Generate 3 anything menus
        for (int i = 0; i < 3; i++) {
            menus.push_back(generateMenu("a", language));
        }

        // Initialize every monster with a menu based on the food preference
        for (int i = 0; i < monsters.size(); i++) {
            if (monsters[i]->foodPreference == "vegetarian") {
                monsters[i]->menu = menus[0];
            } else if (monsters[i]->foodPreference == "flexitarian") {
                monsters[i]->menu = menus[3];
            } else {
                monsters[i]->menu = menus[5];
            }
        }

        // Export every menu to a csv file
        exportMenu(menus, "./data/generated/finalMenu.csv", language);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

// Convert the string to lowercase
string toLower(string str) {
    try {
        // Throw an exception if the string is empty
        if (str.empty()) {
            throw "The string is empty";
        }

        // Convert the string to lowercase
        for (int i = 0; i < str.length(); i++) {
            str[i] = tolower(str[i]);
        }

        return str;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return "";
}