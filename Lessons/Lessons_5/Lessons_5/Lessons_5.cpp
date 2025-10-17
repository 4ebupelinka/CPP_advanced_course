#include <iostream>
#include <string>
using namespace std;

class Fastfood {
private:
    bool money_washing = 1;
    void print_hello() {
        cout << "hello" << name << endl;
    }
protected:
    string name;
    string owner;
    double capitalisation;

public:
    string Test = 0;
    Fastfood(string fastfood_name, string fastfood_owner, double fastfood_capitalisation)
        : name(fastfood_name), owner(fastfood_owner), capitalisation(fastfood_capitalisation) {
        cout << "Создан объект Fastfood: " << name << endl;
    }

    virtual ~Fastfood() {
        cout << "Снесли Fastfood: " << name << endl;
    }

    virtual void make_food() const {
        cout << "В заведении " << name << " готовят еду" << endl;
    }

    void burn() const {
        cout << name << " сгорел" << endl;
    }

    string getName() const { return name; }
    string getOwner() const { return owner; }
    bool getMoney_washing() const{ return money_washing; }
    double getCapitalisation() const { return capitalisation; }

    void setName(string fastfood_name) {
        if (!fastfood_name.empty()) {
            name = fastfood_name;
        }
    }

    void setOwner(string fastfood_owner) {
        if (!fastfood_owner.empty()) {
            owner = fastfood_owner;
        }
    }
};

class Kebab : private Fastfood {
private:
    bool use_dog_meat;

public:
    Kebab(string kebab_name, string kebab_owner, double kebab_capitalisation, bool use_dog_meat)
        : Fastfood(kebab_name, kebab_owner, kebab_capitalisation),
        use_dog_meat(use_dog_meat) {
        cout << "Создан объект Kebab: " << name << endl;
    }

    ~Kebab() {
        cout << "Уничтожен объект Kebab: " << name << endl;
    }

    void make_food() const override {
        cout << "В заведении " << name << " готовят шаурму" << endl;
    }

    void poison() const {
        cout << "В шаурмечке " << name << " отравился клиент!" << endl;
    }

    bool isUsingDogMeat() const { return use_dog_meat; }
};

int main() {
    Kebab k("Шаурма у Ашота", "Ашот", 100000, false);
    k.make_food();
    k.poison();
    cout << "Отмыв "<<k.getMoney_washing()<< endl;
    cout << "Владелец " << k.getOwner() << endl;
    //cout << "Владелец " << k.money_washing << endl;
    cout << "Владелец " << k.Test << endl;

    return 0;
}
