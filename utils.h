#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// create a struct based on wednesdayCast.csv
struct Person {
    string name;
    string role;
};

// generate a struct Menu with 4 properties (soup, mainFood, dessert, price)
struct Menu {
    string soup;
    string mainFood;
    string dessert;
};

// Create a struct for period price
struct PeriodPrice {
    string period;
    double transportPrice;
    double roomPrice;
    double makeupPrice;
    double foodPrice;
    double rentPrice;
    double totalPrice;
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

// convert lei to dolars
double convertLeiToDolars(int lei) {
    // convert lei to dolars
    double dolars = lei / 4.8;

    // return the dolars
    return dolars;
}

// read persons from csv file 
vector<Person> readPersons(string filename) {
    // create an array of persons
    vector<Person> persons;

    // open the file
    ifstream file(filename);

    // read the file
    string line;
    while (getline(file, line)) {
        // create an person
        Person person;

        // split the line into name and role
        auto comma = line.find(",");
        person.name = line.substr(0, comma);
        person.role = line.substr(comma + 1);

        // add the person to the array
        persons.push_back(person);
    }

    // close the file
    file.close();

    // return the array of persons
    return persons;
}


// read persons from csv file (containing "person" in role string) and return a vector of persons 
vector<Person> readActors(string filename) {
    // create an array of persons
    vector<Person> persons;

    // open the file
    ifstream file(filename);

    // read the file
    string line;
    while (getline(file, line)) {
        // create an person
        Person person;

        // split the line into name and role
        auto comma = line.find(",");
        person.name = line.substr(0, comma);
        person.role = line.substr(comma + 1);

        // add the person to the array only if role contains "actor"
        if (person.role.find("actor/actress") != string::npos) {
            persons.push_back(person);
        }
    }

    // close the file
    file.close();

    // return the array of persons

    return persons;
}

// print out the persons
void printPersons(vector<Person> persons) {
    for (auto person : persons) {
        cout << person.name << " played " << person.role << endl;
    }
}

// generate another 132 random persons using Person struct from names.txt and roles.txt
vector<Person> generateFigurants() {
    // create an array of persons
    vector<Person> persons;

    // open the files
    ifstream namesFile("./data/raw/names.txt");
    ifstream rolesFile("./data/raw/roles.txt");

    // read the files
    string name;
    string role;
    while (getline(namesFile, name) && getline(rolesFile, role)) {
        // create an person
        Person person;

        // set the name and role
        person.name = name;
        person.role = role;

        // add the person to the array
        persons.push_back(person);
    }

    // close the files
    namesFile.close();
    rolesFile.close();

    // return the array of persons
    return persons;
}

// write persons to csv file
void writePersons(vector<Person> persons, string filename) {
    // open the file
    ofstream file(filename);

    // write the persons to the file
    for (auto person : persons) {
        file << person.name << "," << person.role << endl;
    }

    // close the file
    file.close();
}


int getNumberOfPersons(string filename) {
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

    // return the number of persons
    return count;
}

// Calculate the number of busses needed to transport the persons (1 bus = 50 people)
int getNumberOfBusses(vector<Person> persons) {
    // Calculate the number of busses needed
    int numberOfBusses = persons.size() / 50;
    if (persons.size() % 50 != 0) {
        numberOfBusses++;
    }

    // return the number of busses
    return numberOfBusses;
}

// Calculate the transport cost (1 bus = 50 people, 1 bus = 5680 lei)
int getTransportCost(vector<Person> persons) {
    // Calculate the transport cost
    int transportCost = getNumberOfBusses(persons) * 5680;

    // convert the transport cost from lei to dolars
    transportCost = convertLeiToDolars(transportCost);

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

// get the price of rooms per night based on main persons and new persons, main persons stay 2 in a room and pay 350, new persons stay 3 in a room and pay 420
int getRoomPrice(vector<Person> mainPersons, vector<Person> newPersons) {
    // Calculate the price of rooms per night
    int roomPrice = (mainPersons.size() / 2) * 350 + (newPersons.size() / 3) * 420;

    // convert the room price from lei to dolars
    roomPrice = convertLeiToDolars(roomPrice);

    // return the price of rooms per night
    return roomPrice;
}

// get water,coffe and soda price per day, 1L of water per person, 0.5L of coffee per person, 0.8L of soda per person, 2L of water costs 6 dolars, 1L of coffee costs 30 dolars, 2L of soda costs 8 dolars
int getWaterCoffeSodaPrice(vector<Person> allPersons) {
    // Calculate the price of water, coffee and soda per day
    int waterCoffeSodaPrice = (allPersons.size() * 3 + allPersons.size() * 0.5 * 30 + allPersons.size() * 0.8 * 4);

    // convert the water,coffe and soda price from lei to dolars
    waterCoffeSodaPrice = convertLeiToDolars(waterCoffeSodaPrice);

    // return the price of water, coffee and soda per day
    return waterCoffeSodaPrice;
}

// get price for castle rental, 10000 dolars per day, every 10 days the price is reduced by 2%
int getCastleRentalPrice(int days) {
    // Calculate the price for castle rental
    int castleRentalPrice = 10000 * days;
    int discount = days / 10;
    castleRentalPrice -= castleRentalPrice * discount * 0.02;

    // convert the castle rental price from lei to dolars
    castleRentalPrice = convertLeiToDolars(castleRentalPrice);

    // return the price for castle rental
    return castleRentalPrice;
}



// assign every person to a class, randomly choose between Human, Seers, Siren, Vampire, Werewolf
string generateClass() {
    // create an array of classes
    vector<string> classes = {"Human", "Seers", "Siren", "Vampire", "Werewolf"};

    // generate a random number between 0 and 4
    int randomNumber = rand() % 5;

    // return the class
    return classes[randomNumber];
}

// add to CSV all details for period price using a PeriodPrice struct
void exportPrices(PeriodPrice periodPrice, string filename) {
    // Append the period price to the file
    ofstream file(filename, ios::app);

    // write to CSV all details from periodPrice struct
    file << periodPrice.period << endl;
    file << "Transport: " << fixed << setprecision(0) << periodPrice.transportPrice << "$" << endl;
    file << "Room: " << fixed << setprecision(0) << periodPrice.roomPrice << "$" << endl;
    file << "Makeup: " << fixed << setprecision(0) << periodPrice.makeupPrice << "$" << endl;
    file << "Food: " << fixed << setprecision(0) << periodPrice.foodPrice << "$" << endl;
    file << "Rent: " << fixed << setprecision(0) << periodPrice.rentPrice << "$" << endl;
    file << "Total: " << fixed << setprecision(0) << periodPrice.totalPrice << "$" << endl;
    file << endl;
    

    // close the file
    file.close();
}

// export every menu from paramter to a csv file (Menu vegetarianMenu,Menu flexitarianMenu,Menu anythingMenu, filename)
// Menu = { string soup; string mainFood; string dessert; };
void exportMenu(Menu vegetarianMenu, Menu flexitarianMenu, Menu anythingMenu, string filename) {
    // open the file
    ofstream file(filename);

    // write the menus to the file
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

    // close the file
    file.close();
}
