#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <utility>

class Person {
    std::string name;
    int age;
public:
    explicit Person(std::string name = "DEFAULT_NAME", const int age = 18) : name{std::move(name)}, age{age} {}

    bool operator==(const Person &person) const {
        return name == person.name && age == person.age;
    }

    friend std::ostream &operator<<(std::ostream &out, const Person &person) {
        return out << person.name << " IS " << person.age;
    }

    struct PersonComparator {
        bool operator()(const Person &person1, const Person &person2) const {
            return person1.name == person2.name && person1.age == person2.age;
        }
    };

    struct PersonHasher {
        std::size_t operator()(const Person &person) const {
            using std::size_t;
            using std::hash;
            using std::string;

            size_t res = 17;
            res = res * 31 + hash<string>()(person.name);
            return res * 31 + hash<int>()(person.age);
        }
    };
};

int main() {

    Person p1{"PER_A", 15};
    Person p2{"PER_A", 15};
    Person p3{"PER_B", 10};
    Person p4{"PER_B", 10};
    Person p5{"PER_C", 21};
    Person p6{"PER_C", 21};

    std::unordered_map<Person, std::string, Person::PersonHasher, Person::PersonComparator> people_with_hobbies;

    people_with_hobbies.try_emplace(p1, "SPORT");
    people_with_hobbies.insert_or_assign(p2, "BOOKS");
    people_with_hobbies.insert(std::make_pair(p3, "MUSIC"));
    people_with_hobbies[p4] = "MUSIC";
    people_with_hobbies[p5] = "MUSIC";
    people_with_hobbies[p6] = "MUSIC";

    std::for_each(
            people_with_hobbies.begin(),
            people_with_hobbies.end(),
            [](const auto &pair) { std::cout << pair.first << " AND HAS HOBBY: " << pair.second << std::endl; }
    );

    return 0;
}


