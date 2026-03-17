#include <iostream>
#include <string>
#include <locale>

using namespace std;

class ServiceOrder {
private:

    int orderNumber;
    string carBrand;
    string workDescription;
    double totalCost;

public:

    ServiceOrder() {
        orderNumber = 0;
        carBrand = "Не указана";
        workDescription = "Диагностика";
        totalCost = 0.0;
    }


    ServiceOrder(int number, string brand, string description, double cost) {
        orderNumber = number;
        setCarBrand(brand);
        workDescription = description;
        setTotalCost(cost); 
    }


    ~ServiceOrder() {
        cout << "Заказ №" << orderNumber << " удален из оперативной памяти." << endl;
    }

    string getCarBrand() { return carBrand; }

    void setCarBrand(string brand) {
        if (!brand.empty()) {
            carBrand = brand;
        }
        else {
            cout << "Ошибка: Марка машины не может быть пустой!" << endl;
        }
    }

    double getTotalCost() { return totalCost; }

    void setTotalCost(double cost) {
        if (cost >= 0) {
            totalCost = cost;
        }
        else {
            cout << "Ошибка: Стоимость не может быть отрицательной!" << endl;
            totalCost = 0;
        }
    }

    void addWork(string newWork, double price) {
        if (price > 0) {
            workDescription += " + " + newWork;
            totalCost += price;
            cout << "Добавлено: " << newWork << ". Новая стоимость: " << totalCost << " руб." << endl;
        }
        else {
            cout << "Ошибка: Стоимость доп. работ должна быть положительной!" << endl;
        }
    }

    void applyDiscount(double percent) {
        if (percent > 0 && percent <= 50) { 
            double discount = totalCost * (percent / 100.0);
            totalCost -= discount;
            cout << "Применена скидка " << percent << "%. Итого к оплате: " << totalCost << " руб." << endl;
        }
        else {
            cout << "Ошибка: Некорректный процент скидки (0-50%)." << endl;
        }
    }

    void printInfo() {
        cout << "\nЗАКАЗ №" << orderNumber << " " << endl;
        cout << "Автомобиль:  " << carBrand << endl;
        cout << "Список работ: " << workDescription << endl;
        cout << "Сумма заказа: " << totalCost << " руб." << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ServiceOrder order1; 
    ServiceOrder order2(55, "Toyota Camry", "Замена масла", 4500.0); 
    cout << "Данные первого заказа (пустой):" << endl;
    order1.printInfo();

    cout << "\nОбновление данных для первого заказа:" << endl;
    order1.setCarBrand("BMW X5");
    order1.addWork("Замена тормозных колодок", 12000.0);
    order1.printInfo();

    cout << "\nРабота со вторым заказом:" << endl;
    order2.addWork("Замена фильтра", 1500.0);
    order2.applyDiscount(15);
    order2.printInfo();

    
    cout << "\nПроверка валидации (отрицательная цена и огромная скидка):" << endl;
    order2.setTotalCost(-500);
    order2.applyDiscount(99);

    return 0;
}