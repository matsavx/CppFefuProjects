#include <iostream>

using namespace std;

class Human {
private:
    string name;
    int age;
    int height;
    int weight;
public:
    Human( string name, int age, int height, int weight) : name(name), age(age), height(height), weight(weight) {
        this->age=age;
        this->weight = weight;
        this->height=height;
    }
    const string &getName() const {
        return name;
    }
    virtual void showHuman() {
        cout << "Имя: " + name  << endl;
    }
};

class SportMan : public Human {
private:
    string kindOfSport;
public:
    SportMan(string name, int age, int height, int weight, const string &kindOfSport) : Human(name, age, height, weight),
                                                                           kindOfSport(kindOfSport) {
        this->kindOfSport=kindOfSport;
    }
    const string &getKindOfSport() const {
        return kindOfSport;
    }

    void showHuman() override {
        cout << "Имя спортсмена: " + this->getName() + ", вид спорта: " + kindOfSport << endl;
    }
};

class Rewards {
private:
    SportMan sportMan;
    string rewards;
public:
    Rewards(const SportMan &sportMan, const string &rewards) : sportMan(sportMan), rewards(rewards) {
        this->rewards=rewards;
    }
    void showReward() {
        sportMan.showHuman();
        cout << "Награды: " + rewards << endl;
    }
};

int main() {
    cout << "1. ";
    Human human("Джон", 19, 198, 85);
    human.showHuman();
    cout << "2. ";
    SportMan sportMan("Джон", 19, 198, 85, "Баскетбол");
    sportMan.showHuman();
    cout << "3. ";
    Rewards rewards(sportMan, "Награда лучшего игрока 2020");
    rewards.showReward();
}
