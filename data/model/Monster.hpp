//? Creates a monster that can inherit Human, Seers, Siren, Vampire, Werewolf classes using multiple inheritance
class Monster {
   public:
    int makeupPricePerDay;
    std::string foodPreference;
    std::string actorName;
    std::string actorRole;
    Menu menu;

   public:
    //? Show details of the monster
    void showDetails() {
        std::cout << std::endl;
        std::cout << "Actor Name: " << actorName << std::endl;
        std::cout << "Actor Role: " << actorRole << std::endl;
        std::cout << "Food Preference: " << foodPreference << std::endl;
        std::cout << "Makeup Price Per Day: " << makeupPricePerDay << std::endl;
        std::cout << std::endl;
    }
};
