class Person : public Monster {
   public:
    //? Create an empty constructor that initialize foodPreference to random
    Person() {
        foodPreference = generateFoodPreference();
        //? Intialize makeupPricePerDay to 55
        makeupPricePerDay = 55;
    }

    //? Constructor with actorName and actorRole
    Person(std::string actorName, std::string actorRole) {
        //? Initialize foodPreference to random
        foodPreference = generateFoodPreference();

        //? Intialize makeupPricePerDay to 55
        makeupPricePerDay = 55;

        //? Initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }
};
