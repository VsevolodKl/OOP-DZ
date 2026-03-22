#include <iostream>
#include <string>
#include <locale>
#include <vector>

using namespace std;

class ServiceOrder {
protected:
    int orderNumber;
    string carBrand;
    string workDescription;
    double baseCost;

public:
    ServiceOrder(int number, string brand, string description, double cost) {
        orderNumber = number;
        carBrand = brand;
        workDescription = description;
        baseCost = cost;
    }

    virtual ~ServiceOrder() {
        cout << "Заказ №" << orderNumber << " удален." << endl;
    }

    virtual double calcTotalCost() = 0;
    virtual string getServiceReport() = 0;
};

class RepairOrder : public ServiceOrder {
private:
    string repairType;
    double sparePartsCost;

public:
    RepairOrder(int number, string brand, string description, double cost, string type, double parts)
        : ServiceOrder(number, brand, description, cost) {
        repairType = type;
        sparePartsCost = parts;
    }

    double calcTotalCost() override {
        return baseCost + sparePartsCost;
    }

    string getServiceReport() override {
        return "РЕМОНТ [" + repairType + "] для " + carBrand + ". Запчасти: " + to_string(sparePartsCost) + " руб. Итого: " + to_string(calcTotalCost());
    }
};


class MaintenanceOrder : public ServiceOrder {
private:
    string maintenanceType;
    string oilBrand;

public:
    MaintenanceOrder(int number, string brand, string description, double cost, string mType, string oil)
        : ServiceOrder(number, brand, description, cost) {
        maintenanceType = mType;
        oilBrand = oil;
    }

    double calcTotalCost() override {
        return baseCost + 2000.0;
    }

    string getServiceReport() override {
        return "ТО [" + maintenanceType + "] для " + carBrand + ". Масло: " + oilBrand + ". Итого: " + to_string(calcTotalCost());
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ServiceOrder* orders[2];

    orders[0] = new RepairOrder(101, "BMW X5", "Замена рычагов", 5000.0, "Подвеска", 15000.0);
    orders[1] = new MaintenanceOrder(102, "Toyota Camry", "Плановый осмотр", 3000.0, "ТО-1", "Shell Helix");

    cout << "Список заказов на СТО" << endl;
    for (int i = 0; i < 2; i++) {
        cout << orders[i]->getServiceReport() << endl;
    }

    cout << "\nУдаление объектов" << endl;
    for (int i = 0; i < 2; i++) {
        delete orders[i];
    }

    return 0;
}
