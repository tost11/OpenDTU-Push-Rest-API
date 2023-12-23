// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "../commands/ActivePowerControlCommand.h"
#include "../parser/AlarmLogParser.h"
#include "../parser/DevInfoParser.h"
#include "../parser/GridProfileParser.h"
#include "../parser/PowerCommandParser.h"
#include "../parser/StatisticsParser.h"
#include "../parser/SystemConfigParaParser.h"
#include "HoymilesRadio.h"
#include "types.h"
#include "BaseInverter.h"
#include <Arduino.h>
#include <cstdint>
#include <list>

enum {
    FRAGMENT_ALL_MISSING_RESEND = 255,
    FRAGMENT_ALL_MISSING_TIMEOUT = 254,
    FRAGMENT_RETRANSMIT_TIMEOUT = 253,
    FRAGMENT_HANDLE_ERROR = 252,
    FRAGMENT_OK = 0
};

#define MAX_RF_FRAGMENT_COUNT 13

class CommandAbstract;

class InverterAbstract : public BaseInverter<StatisticsParser,DevInfoParser,SystemConfigParaParser,AlarmLogParser,GridProfileParser,PowerCommandParser> {
public:
    explicit InverterAbstract(HoymilesRadio* radio, uint64_t serial);
    void init();
    uint64_t serial() override;
    virtual const byteAssign_t* getByteAssignment() = 0;
    virtual uint8_t getByteAssignmentSize() = 0;

    bool isProducing() override;
    bool isReachable() override;

    void clearRxFragmentBuffer();
    void addRxFragment(uint8_t fragment[], uint8_t len);
    uint8_t verifyAllFragments(CommandAbstract* cmd);

    virtual bool sendStatsRequest() = 0;
    virtual bool sendAlarmLogRequest(bool force = false) = 0;
    virtual bool sendDevInfoRequest() = 0;
    virtual bool sendSystemConfigParaRequest() = 0;
    //virtual bool sendActivePowerControlRequest(float limit, PowerLimitControlType type) = 0;
    virtual bool resendActivePowerControlRequest() = 0;
    //virtual bool sendPowerControlRequest(bool turnOn) = 0;
    //virtual bool sendRestartControlRequest() = 0;
    //virtual bool resendPowerControlRequest() = 0;
    virtual bool sendChangeChannelRequest();
    virtual bool sendGridOnProFileParaRequest() = 0;

    inverter_type getInverterType() override;

    HoymilesRadio* getRadio();
protected:
    HoymilesRadio* _radio;

private:
    serial_u _serial;

    fragment_t _rxFragmentBuffer[MAX_RF_FRAGMENT_COUNT];
    uint8_t _rxFragmentMaxPacketId = 0;
    uint8_t _rxFragmentLastPacketId = 0;
    uint8_t _rxFragmentRetransmitCnt = 0;
};