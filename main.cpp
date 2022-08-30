#include <iostream>
#include <cstring>

class Door {
public:
    Door() {};
    virtual ~Door() {}
    virtual void Open() = 0;
};

class GasCarDoor : public Door {
public:
    GasCarDoor() { printf("Making a door for a gas car.\n"); }
    void Open() { printf("Click\n"); }
};

class ElectricCarDoor : public Door {
public:
    ElectricCarDoor() { printf("Making a door for an electric car\n"); }
    void Open() { printf("Shhhhh\n"); }
};

class Engine {
protected:
    char _sound[15];
public:
    Engine() {strcpy(_sound, ""); }
    virtual ~Engine() {}
    virtual void Run() = 0;
};

class GasEngine : public Engine {
public:
    GasEngine(){
        strcpy(_sound, "vroom");
        printf("Making a gas engine.\n");
    }
    void Run() { printf("%s\n", _sound); }
};

class ElectricEngine : public Engine {
public:
    ElectricEngine(){
        strcpy(_sound, "SHHHHH");
        printf("Making an electric engine.\n");
    }
    void Run() { printf("%s\n", _sound); }
};

class CarFactory {
public:
    virtual ~CarFactory() {}
    virtual Door* BuildDoor() = 0;
    virtual Engine* BuildEngine() = 0;
};

class GasCarFactory : public CarFactory {
public:
    Door* BuildDoor(){
        return new GasCarDoor();
    }
    Engine* BuildEngine(){
        return new GasEngine();
    }
};

class ElectricCarFactory : public CarFactory {
public:
    Door* BuildDoor(){
        return new ElectricCarDoor();
    }
    Engine* BuildEngine(){
        return new ElectricEngine();
    }
};

enum type_of_car{
    gas_car = 1,
    electric_car
};

CarFactory* make_factory_for(char type_of_car){
    switch(type_of_car){
        case gas_car: return new GasCarFactory();
        case electric_car: return new ElectricCarFactory();
        default: return nullptr;
    }
}

int main(){
    auto CarPlant = make_factory_for(electric_car);
    auto myDoor = CarPlant->BuildDoor();
    auto myEngine = CarPlant->BuildEngine();
    myDoor->Open();
    myEngine->Run();
    delete CarPlant;

    printf("Done\n");
    return 0;
}
