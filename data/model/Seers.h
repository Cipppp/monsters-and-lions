std::string generateFoodPreference();

class Seers : public Monster {
   public:
    // create an empty constructor that initialize foodPreference to random
    Seers() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 157
        makeupPricePerDay = 157;
    }

    // constructor with actorName and actorRole
    Seers(std::string actorName, std::string actorRole) {
        // initialize foodPreference to random
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 157
        makeupPricePerDay = 157;
        // initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }

};
