std::string generateFoodPreference();

class Werewolf {
    int makeupPricePerDay;
    int totalPrice;
    std::string foodPreference;

   public:
    // create an empty constructor that initialize foodPreference to random
    Werewolf() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 555
        makeupPricePerDay = 555;
    }
};
