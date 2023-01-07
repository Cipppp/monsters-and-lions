#include "./modelsMethods.hpp"

//? create a struct based on wednesdayCast.csv
struct PersonType {
    string name;
    string role;
};

//? generate a struct Menu with 4 properties (soup, mainFood, dessert, price)
struct Menu {
    string soup;
    string mainFood;
    string dessert;

    // Create a function to display the menu
    void displayMenu() {
        cout << "Soup: " << soup << endl;
        cout << "Main food: " << mainFood << endl;
        cout << "Dessert: " << dessert << endl;
    }
};

//? Create a struct for period price
struct PeriodPrice {
    string period;
    double transportPrice;
    double roomPrice;
    double makeupPrice;
    double foodPrice;
    double rentPrice;
    double totalPrice;
};
