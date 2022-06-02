// ConsoleComposite.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <assert.h>

// Component 
class Unit
{
   
public:
    
    virtual int getStrength() = 0;
    virtual void addUnit(Unit* p) {
        assert(false);
    }
    virtual ~Unit() {}
    static int getCount() { return 0; }
};

// Primitives
class Archer : public Unit
{
    static int id;

public:
    Archer() { id++; }
    virtual int getStrength() {
        return 1;
    }
    static int getCount() { return id; }


};

class Infantryman : public Unit
{
protected:
    static int id;

public:
    Infantryman() { id++; }
    virtual int getStrength() {
        return 2;
    }
    static int getCount() { return id; }

};

class Horseman : public Unit
{
protected:
    static int id;

public:
    Horseman() { id++; }
    virtual int getStrength() {
        return 3;
    }
    static int getCount() { return id; }

};


// Composite
class CompositeUnit : public Unit
{
private:
    std::vector<Unit*> c;

public:
    int getStrength() {
        int total = 0;
        for (int i = 0; i < c.size(); ++i)
            total += c[i]->getStrength();
        return total;
    }
    void addUnit(Unit* p) {
        c.push_back(p);
    }
    ~CompositeUnit() {
        for (int i = 0; i < c.size(); ++i)
            delete c[i];
    }
};


// Вспомогательная функция для создания легиона
CompositeUnit* createLegion()
{
    // Римский легион содержит:
    CompositeUnit* legion = new CompositeUnit;
    // 3000 тяжелых пехотинцев
    for (int i = 0; i < 1; ++i)
        legion->addUnit(new Infantryman);
    // 1200 легких пехотинцев
    for (int i = 0; i < 1; ++i)
        legion->addUnit(new Archer);
    // 300 всадников
    for (int i = 0; i < 1; ++i)
        legion->addUnit(new Horseman);

    return legion;

}

 
int Archer::id = 0;
int Infantryman::id = 0;
int Horseman::id = 0;


int main()
{
    setlocale(LC_ALL, "Russian");
 
    CompositeUnit* army = new CompositeUnit;
    //for (int i = 0; i < 400000; ++i)
    while(1)
    {
        for (int j = 0; j < 400000; ++j)
        {
            army->addUnit(createLegion());
        }

        delete army;
        army = new CompositeUnit;
    }
    std::cout << "В римской армии \nпехотинцев "
        << Infantryman::getCount() << std::endl;
    std::cout << "лучников "
        << Archer::getCount() << std::endl;
    std::cout << "кавалеристов "
        << Horseman::getCount() << std::endl;
  
    std::cout << "Сила римской армии "
        << army->getStrength() << std::endl;

 
    delete army;
    return 0;
}