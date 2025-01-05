#pragma once

#include "types.h"
#include "BaseInverter.h"
#include "parser/HoymilesWDevInfo.h"
#include "parser/HoymilesWSystemConfigPara.h"
#include "parser/HoymilesWAlarmLog.h"
#include "parser/HoymilesWGridProfile.h"
#include "parser/StatisticsParser.h"
#include "parser/SystemConfigParaParser.h"
#include "parser/PowerCommandParser.h"
#include <Arduino.h>
#include <cstdint>
#include <list>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <TimeoutHelper.h>

#define MAX_NAME_HOST 32

class HoymilesWInverter : public BaseInverter<StatisticsParser,HoymilesWDevInfo,SystemConfigParaParser,HoymilesWAlarmLog,HoymilesWGridProfile,PowerCommandParser> {
public:
    explicit HoymilesWInverter(uint64_t serial,Print & print);
    virtual ~HoymilesWInverter() = default;

    uint64_t serial() const override;

    String typeName() const override;

    bool isProducing() override;

    bool isReachable() override;

    bool sendActivePowerControlRequest(float limit, PowerLimitControlType type) override;

    bool resendPowerControlRequest() override;

    bool sendRestartControlRequest() override;

    bool sendPowerControlRequest(bool turnOn) override;

    void update();

    inverter_type getInverterType() const override;

    static String serialToModel(uint64_t serial);

    void setEnableCommands(const bool enabled) override;
private:
    Print & _messageOutput;
    uint64_t _serial;
};