std::string generateFoodPreference();

class Seers {
    int makeupPricePerDay;
    int totalPrice;
    std::string foodPreference;

   public:
    // create an empty constructor that initialize foodPreference to random
    Seers() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 157
        makeupPricePerDay = 157;
    }
};
