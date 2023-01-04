class Siren : public Monster {
   public:
    //? Create an empty constructor that initialize foodPreference to random
    Siren() {
        foodPreference = generateFoodPreference();
        //? Intialize makeupPricePerDay to 345
        makeupPricePerDay = 345;
    }

    //? Constructor with actorName and actorRole
    Siren(std::string actorName, std::string actorRole) {
        //? Initialize foodPreference to random
        foodPreference = generateFoodPreference();

        //? Intialize makeupPricePerDay to 345
        makeupPricePerDay = 345;

        //? Initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }
};
