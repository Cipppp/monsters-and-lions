class Werewolf : public Monster {
   public:
    //? Create an empty constructor that initialize foodPreference to random
    Werewolf() {
        foodPreference = generateFoodPreference();
        //? Intialize makeupPricePerDay to 555
        makeupPricePerDay = 555;
    }

    //? Constructor with actorName and actorRole
    Werewolf(std::string actorName, std::string actorRole) {
        //? Initialize foodPreference to random
        foodPreference = generateFoodPreference();

        //? intialize makeupPricePerDay to 555
        makeupPricePerDay = 555;

        //? Initialize actorName and actorRole
        this->actorName = actorName;
        this->actorRole = actorRole;
    }
};
