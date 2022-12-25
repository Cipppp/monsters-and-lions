std::string generateFoodPreference();

class Human {
    int makeupPricePerDay;
    int totalPrice;
    std::string foodPreference;

   public:
    // create an empty constructor that initialize foodPreference to random
    Human() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 55
        makeupPricePerDay = 55;
    }
};
