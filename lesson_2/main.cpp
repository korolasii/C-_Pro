#include <iostream>            
#include <memory>               
#include <string>               
#include <vector>               

class IDevice {
public:
    IDevice(const IDevice&) = delete;

    virtual ~IDevice() {
        std::cout << "IDevice virtual destrucreate\n";
        instanceExists = false; 
    }

    virtual void init() = 0;
    virtual void shutdown() = 0;
    virtual std::string name() const = 0;

protected:
    IDevice() {
        if (instanceExists) {
            throw std::runtime_error("Only one IDevice instance allowed at a time!");
        }
        instanceExists = true;
    }

private:
    static bool instanceExists;  
};

bool IDevice::instanceExists = false;

class Camera final : public IDevice {
private:
    bool initialized = false;         
    int framesCaptured = 0;           
    std::string model = "Logitech 5000x";   

public:
    Camera() {
        std::cout << "Camera create\n";          
    }

    ~Camera() override {
        std::cout << "Camera delete\n";          
    }

    void init() override {
        initialized = true;                      
        framesCaptured = 0;                      
        std::cout << "Camera:" << model << " initialized\n"; 
    }


    void shutdown() override {
        if (initialized) {                       
            std::cout << "Camera: " << model
                    << " shutting down (frames: " << framesCaptured << ")\n"; 
            initialized = false;                 
        } else {
            std::cout << "Camera: " << model << "already off\n"; 
        }
    }

    std::string name() const override {
        return "Camera: " + model;    
    }      

    void capture() {
        if (initialized) {                       
            ++framesCaptured;                    
            std::cout << "Camera: " << model << "frame #" << framesCaptured << "\n"; 
        } else {
            std::cout << "Camera: " << model << "not initialized\n"; 
        }
    }
};

class Microphone : public IDevice {
private:
    bool initialized = false;         
    int samplesRecorded = 0;          
    std::string model = "Fifine 5A";  

public:
    Microphone() {
        std::cout << "Microphone create\n";      
    }

    ~Microphone() override {
        std::cout << "Microphone delete\n";      
    }

    void init() override {
        initialized = true;                      
        samplesRecorded = 0;                     
        std::cout << "Microphone: " << model << " initialized\n"; 
    }

    void shutdown() override {
        if (initialized) {                       
            std::cout << "Microphone: " << model
                    << "shutting down (samples: " << samplesRecorded << ")\n"; 
            initialized = false;                 
        } else {
            std::cout << "Microphone already off\n"; 
        }
    }

    std::string name() const override {
        return "Microphone(" + model + ")";      
    }

    void record() {
        if (initialized) {                       
            samplesRecorded += 1024;             
            std::cout << "Microphone samples (total: "
                    << samplesRecorded << ")\n"; 
        } else {
            std::cout << "Microphone not initialized\n"; 
        }
    }
};

class Storage : public IDevice {
private:
    bool initialized = false;         
    int writes = 0;                   
    std::string model = "SSD-1TB";    

public:
    Storage() {
        std::cout << "Storage create\n";         
    }

    ~Storage() override {
        std::cout << "Storage delete\n";         
    }

    void init() override {
        initialized = true;                     
        writes = 0;                              
        std::cout << "Storage: " << model << " initialized\n"; 
    }

    void shutdown() override {
        if (initialized) {                       
            std::cout << "Storage: " << model
                    << "shutting down (writes: " << writes << ")\n";
            initialized = false;                 
        } else {
            std::cout << " Storage: already off\n"; 
        }
    }

    std::string name() const override {
        return "Storage(" + model + ")";         
    }

    void writeBlock() {
        if (initialized) {                       
            ++writes;                            
            std::cout << "Storage:writeBlock write #" << writes << "\n"; 
        } else {
            std::cout << "Storage:writeBlock not initialized\n"; 
        }
    }
};

struct BaseNV {
    void foo() {                                  
        std::cout << "BaseNV:foo static binding\n"; 
    }
};

struct DerivedNV : BaseNV {
    void foo() {                                  
        std::cout << "DerivedNV:foo static binding (hides BaseNV::foo)\n"; 
    }
};

struct BaseV {
    virtual void foo() {                          
        std::cout << "BaseV:foo dynamic binding (base)\n"; 
    }

    virtual ~BaseV() = default;                  
};

struct DerivedV : BaseV {
    void foo() override {                        
        std::cout << "DerivedV:foo dynamic binding (derived)\n"; 
    }
};

int main() {
    try {
        auto cam = std::make_unique<Camera>();
        cam->init();
        cam->shutdown();

        auto mic = std::make_unique<Microphone>();
        mic->init();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "End\n";
    return 0;
}
