
#include "InverterHandler.h"
#include "Hoymiles.h"
#include "DeyeSun.h"
#include "HoymilesW.h"

InverterHandlerClass InverterHandler;

bool InverterHandlerClass::isAllRadioIdle() {

    for (const auto &item: _handlers){
        if(!item->isAllRadioIdle()){
            return false;
        }
    }

    return true;
}

void InverterHandlerClass::init() {
    _handlers.push_back(reinterpret_cast<BaseInverterHandlerClass*>(&Hoymiles));
    _handlers.push_back(reinterpret_cast<BaseInverterHandlerClass*>(&DeyeSun));
}

size_t InverterHandlerClass::getNumInverters() {
    size_t res = 0;
    for (const auto &item: _handlers){
        res+=item->getNumInverters();
    }
    return res;
}

std::shared_ptr<BaseInverterClass> InverterHandlerClass::getInverterByPos(uint8_t pos) {
    int i=0;
    for (const auto &item: _handlers){
        for(int j = 0;j<item->getNumInverters();j++){
            if(i == pos){
                return item->getInverterByPos(j);
            }
            i++;
        }
    }
    return nullptr;
}

uint32_t InverterHandlerClass::PollInterval() const {
    return _pollInterval;
}

void InverterHandlerClass::setPollInterval(uint32_t interval) {
    for (const auto &item: _handlers){
        item->setPollInterval(interval);
    }
}

std::shared_ptr<BaseInverterClass> InverterHandlerClass::getInverterBySerial(uint64_t serial,inverter_type inverterType) {
    if(inverterType == inverter_type::Inverter_Hoymiles){
        return std::reinterpret_pointer_cast<BaseInverterClass>(Hoymiles.getInverterBySerial(serial));
    }
    if(inverterType == inverter_type::Inverter_DeyeSun){
        return std::reinterpret_pointer_cast<BaseInverterClass>(DeyeSun.getInverterBySerial(serial));
    }
    return nullptr;
}

void InverterHandlerClass::removeInverterBySerial(uint64_t serial,inverter_type inverterType) {
    if(inverterType == inverter_type::Inverter_Hoymiles){
        Hoymiles.removeInverterBySerial(serial);
    }else if(inverterType == Inverter_DeyeSun){
        DeyeSun.removeInverterBySerial(serial);
    }
}
