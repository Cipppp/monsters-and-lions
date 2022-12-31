<br/>
<p align="center">
  <h1 align="center">Monsters and lions</h1>

  <p align="center">
    Movie Production cost program
    <br/>
    <br/>
    <a href="https://github.com/Cipppp/monsters-and-lions"><strong>Explore the docs »</strong></a>
    <br/>
    <br/>
    <a href="https://github.com/Cipppp/monsters-and-lions/issues">Report Bug</a>
    <!-- add a white space -->
    |
    <a href="https://github.com/Cipppp/monsters-and-lions/issues">Request Feature</a>
  </p>
</p>


## Table Of Contents

* [About the Project](#about-the-project)
* [Compiling and Running](#compiling-and-running)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Structs](#structs)
* [Functions](#functions)
* [Additional Information](#additional-information)
* [Contributing](#contributing)
* [Creating A Pull Request](#creating-a-pull-request)
* [License](#license)
* [Authors](#authors)

## About The Project

This program calculates the total cost of producing a movie based on the number of days of filming, the food preferences of the cast, and the makeup and transport costs of the main and new cast members.


### Compiling and Running

1. Clone the repo

```sh
git clone https://github.com/Cipppp/monsters-and-lions.git
```

To compile the program, you can use the following command:

``` 
g++ -std=c++11 main.cpp -o main
```

## Usage

To run the program, you can use the following command:

```
./main
```

## Roadmap

See the [open issues](https://github.com/Cipppp/monsters-and-lions/issues) for a list of proposed features (and known issues).


## Structs

The following structs are defined in utils.h:

- `Person`: Represents a person with a `name` and `role` field.
- `Menu`: Represents a menu with a `soup`, `mainFood`, and `dessert` field.

- `PeriodPrice`: Represents the cost of a movie production period with `period`, `transportPrice`, `roomPrice`, `makeupPrice`, `foodPrice`, `rentPrice`, and `totalPrice` fields.

## Functions

The following functions are defined in utils.h:

- `showMenuDetails`: Takes a `Menu` struct as an argument and prints its fields to the standard output.

- `generateMenu`: Takes a string as an argument and returns a `Menu` struct. It reads three files (soups, main foods, and desserts) and creates a Menu struct with random values chosen from those files. The type of food to be chosen depends on the value of the `foodPreference` argument.

- `convertLeiToDolars`: Takes an int as an argument and returns a double. It converts the input value from lei to dolars.

- `readPersons`: Takes a string as an argument and returns a vector of `Person` structs. It reads a file with lines in the format "name,role" and creates a `Person` struct for each line, adding it to the vector.

- `readActors`: Takes a string as an argument and returns a vector of `Person` structs. It works the same way as readPersons, but it only adds a Person to the vector if the role field contains the word "person".

The following functions are defined in **main.cpp**:

- `getFoodPreferences`: Takes a vector of pointers to `Monster` objects, and three integers by reference (`vegetarians`, `flexitarians`, and `anythingEaters`). It iterates over the vector of monsters and increments the appropriate counter based on the value of the `foodPreference` field of each `Monster` object.

- `calculateTotalFoodPrice`: Takes a vector of pointers to `Monster` objects and calculates the total price of food for the duration of the movie based on the number of vegetarians, flexitarians, and anything eaters among the monsters. It does this by calling the `getFoodPreferences` function and then using the counters to calculate the total price.

- `calculateTotalMakeupPrice`: Takes a vector of pointers to `Monster` objects and calculates the total price of makeup for the duration of the movie by summing the `makeupPricePerDay` field of each `Monster` object.

- `getPeriodPrice`: Takes as arguments the number of days of the movie, a vector of pointers to `Monster` objects, and two vectors of `Person` structs (`mainPersons` and `newPersons`). It calculates the total cost of producing the movie for the given number of days based on the food preferences, makeup costs, and transport costs of the cast and crew.


- `getTotalPrice`: Takes as arguments a vector of integers (days), a vector of pointers to `Monster` objects, and two vectors of `Person` structs (`mainPersons` and `newPersons`). It iterates over the days vector and calls the `getPeriodPrice` function for each element, printing the resulting `PeriodPrice` struct to the standard output.

`main`: Reads the file **"wednesdayCast.csv"** and creates a `Person` struct for each line in the file, adding it to a vector of `Person` structs. It then creates a few `Monster` objects, adds them to a vector of pointers to `Monster` objects, and calls the `getTotalPrice` function with the vector of `Monster` objects and the vector of `Person` structs as arguments.


## Additional Information

The program writes the following files:

- **./data/generated/actors.csv**
- **./data/generated/figurants.csv**
- **./data/generated/finalCast.csv**
- **./data/generated/finaMenu.csv**
- **./data/generated/finalPrices.csv**


## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.
* If you have suggestions for adding or removing projects, feel free to [open an issue](https://github.com/Cipppp/monsters-and-lions/issues/new) to discuss it, or directly create a pull request after you edit the *README.md* file with necessary changes.
* Please make sure you check your spelling and grammar.
* Create individual PR for each suggestion.
* Please also read through the [Code Of Conduct](https://github.com/Cipppp/monsters-and-lions/blob/main/CODE_OF_CONDUCT.md) before posting your first idea as well.

### Creating A Pull Request

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/amazingFeature`)
3. Commit your Changes (`git commit -m 'Add some amazingFeature'`)
4. Push to the Branch (`git push origin feature/amazingFeature`)
5. Open a Pull Request

## License

Distributed under the MIT License. See [LICENSE](https://github.com/Cipppp/monsters-and-lions/blob/main/LICENSE.md) for more information.

## Authors

* **Ciprian Pirvu** - *Computer Science Student* - [Ciprian Pirvu](https://github.com/Cipppp/)


