//? Generate food preference, choose between "anything", "vegetarian" and "flexitarian"
string generateFoodPreference() {
    // Create an array of food preferences
    vector<string> foodPreferences = {"anything", "vegetarian", "flexitarian"};

    // Generate a random number between 0 and 2
    int randomNumber = rand() % 3;

    // Return the food preference
    return foodPreferences[randomNumber];
}