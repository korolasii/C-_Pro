#include <iostream>            
#include <memory>               
#include <string>               
#include <vector>               


class IDevice {
public:
    IDevice(const IDevice&) = delete;

    virtual ~IDevice() {
        std::cout << "IDevice virtual destrucreate\n";
    }

    virtual void init() = 0;                      
    virtual void shutdown() = 0;                  
    virtual std::string name() const = 0;    

protected:
    IDevice() = default;
};

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
    std::cout << "Polymorphic devices collection \n"; 

    std::vector<std::unique_ptr<IDevice>> devices;         
    devices.emplace_back(std::make_unique<Camera>());         
    devices.emplace_back(std::make_unique<Microphone>());     
    devices.emplace_back(std::make_unique<Storage>());        

    for (const auto& dev : devices) {                         
        dev->init();                                          
        std::cout << "Device name: " << dev->name() << "\n";  
        dev->shutdown();                                      
        std::cout << "\n";                                 
    }
    std::cout << "Derived-specific actions (direct downcast just for demo) \n";
    if (auto cam = dynamic_cast<Camera*>(devices[0].get())) { 
        cam->init();                                          
        cam->capture();                                      
        cam->shutdown();                                      
    }
    if (auto mic = dynamic_cast<Microphone*>(devices[1].get())) { 
        mic->init();                                          
        mic->record();                                        
        mic->shutdown();                                      
    }
    if (auto st = dynamic_cast<Storage*>(devices[2].get())) { 
        st->init();                                           
        st->writeBlock();                                     
        st->shutdown();                                       
    }

    std::cout << "Deletion via base pointer (virtual destrucreate demo) \n"; 
    IDevice* p = new Camera;                                  
    p->init();                                                
    p->shutdown();                                            
    delete p;                                                 

    std::cout << "Early vs Late binding \n";           

    std::cout << "Early binding demo \n";
    DerivedNV dnv;                                            
    dnv.foo();                                                
    BaseNV* bnv = &dnv;                                      
    bnv->foo();                                               

    std::cout << "Late binding demo \n";
    DerivedV dv;                                              
    BaseV* bv = &dv;                                          
    bv->foo();                                                

    std::cout << "End\n";                             
    return 0;                                                 
}
