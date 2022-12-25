std::string generateFoodPreference();

class Vampire {
    int makeupPricePerDay;
    int totalPrice;
    std::string foodPreference;

   public:
    // create an empty constructor that initialize foodPreference to random
    Vampire() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 230
        makeupPricePerDay = 230;
    }

    // show makeup price per day
    void showMakeupPricePerDay() {
        std::cout << "Makeup Price Per Day: " << makeupPricePerDay << std::endl;
    }
};
