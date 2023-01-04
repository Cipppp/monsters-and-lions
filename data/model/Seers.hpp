class Seers : public Monster {
   public:
    //? Create an empty constructor that initialize foodPreference to random
    Seers() {
        foodPreference = generateFoodPreference();
        //? Intialize makeupPricePerDay to 157
        makeupPricePerDay = 157;
    }

    //? Constructor with actorName and actorRole
    Seers(std::string actorName, std::string actorRole) {
        //? Initialize foodPreference to random
        foodPreference = generateFoodPreference();

        //? Intialize makeupPricePerDay to 157
        makeupPricePerDay = 157;

        //? Initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }
};
