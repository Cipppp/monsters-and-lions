// generate food preference, choose between "anything", "vegetarian" and "flexitarian"
string generateFoodPreference() {
    // create an array of food preferences
    vector<string> foodPreferences = {"anything", "vegetarian", "flexitarian"};

    // generate a random number between 0 and 2
    int randomNumber = rand() % 3;

    // return the food preference
    return foodPreferences[randomNumber];
}