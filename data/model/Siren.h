std::string generateFoodPreference();

class Siren {
    int makeupPricePerDay;
    int totalPrice;
    std::string foodPreference;

   public:
    // create an empty constructor that initialize foodPreference to random
    Siren() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 345
        makeupPricePerDay = 345;
    }

    // show makeup price per day
    void showMakeupPricePerDay() {
        std::cout << "Makeup Price Per Day: " << makeupPricePerDay << std::endl;
    }
};
