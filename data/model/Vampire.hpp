class Vampire : public Monster {
   public:
    //? Create an empty constructor that initialize foodPreference to random
    Vampire() {
        foodPreference = generateFoodPreference();
        //? Intialize makeupPricePerDay to 230
        makeupPricePerDay = 230;
    }

    //? Constructor with actorName and actorRole
    Vampire(std::string actorName, std::string actorRole) {
        //? Initialize foodPreference to random
        foodPreference = generateFoodPreference();

        //? Intialize makeupPricePerDay to 230
        makeupPricePerDay = 230;

        //? Initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }
};
