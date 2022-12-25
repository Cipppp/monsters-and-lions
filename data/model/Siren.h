std::string generateFoodPreference();

class Siren : public Monster {
   public:
    // create an empty constructor that initialize foodPreference to random
    Siren() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 345
        makeupPricePerDay = 345;

        // show some message
    }

    // constructor with actorName and actorRole
    Siren(std::string actorName, std::string actorRole) {
        // initialize foodPreference to random
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 345
        makeupPricePerDay = 345;
        // initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;

    }
    

};
