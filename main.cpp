#include "./data/headers/utils.hpp"

int main() {
    //* ############## Main configuration ################
    // get the initial cast
    vector<PersonType> initialCast = readPersons("./data/raw/wednesdayCast.csv");

    // get the actors from the csv file
    vector<PersonType> actors = readActors("./data/raw/wednesdayCast.csv");
    // write actors to csv using function from utils
    writePersons(actors, "./data/generated/actors.csv");

    // generate the figurants
    vector<PersonType> figurants = generateFigurants();

    // write figurants to csv using function from utils
    writePersons(figurants, "./data/generated/figurants.csv");

    // read all persons from wednesdayCast.csv
    vector<PersonType> persons = readPersons("./data/raw/wednesdayCast.csv");

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
