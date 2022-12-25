std::string generateFoodPreference();

class Werewolf : public Monster {
   public:
    // create an empty constructor that initialize foodPreference to random
    Werewolf() {
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 555
        makeupPricePerDay = 555;
    }

    // constructor with actorName and actorRole
    Werewolf(std::string actorName, std::string actorRole) {
        // initialize foodPreference to random
        foodPreference = generateFoodPreference();
        // intialize makeupPricePerDay to 555
        makeupPricePerDay = 555;
        // initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }

};
