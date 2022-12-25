std::string generateFoodPreference();

class Vampire : public Monster {
   public:
    // create an empty constructor that initialize foodPreference to random
    Vampire() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 230
        makeupPricePerDay = 230;

    }

    // constructor with actorName and actorRole
    Vampire(std::string actorName, std::string actorRole) {
        // initialize foodPreference to random
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 230
        makeupPricePerDay = 230;
        // initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;


    }

};
