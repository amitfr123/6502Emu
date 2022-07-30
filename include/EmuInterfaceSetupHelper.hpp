#pragma once 

template <typename T> 
class EmuInterfaceSetupHelper {
protected:
    virtual void InterfaceSetup(T param) = 0;
};