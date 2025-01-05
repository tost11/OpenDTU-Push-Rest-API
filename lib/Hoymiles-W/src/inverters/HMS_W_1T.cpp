#include "HMS_W_1T.h"

//todo move positions
static const byteAssign_t byteAssignment[] = {
        //type, channel, field,  uint, first, byte in buffer, number of bytes in buffer, divisor, isSigned; // allow negative numbers, digits; // number of valid digits after the decimal point
        { TYPE_DC, CH0, FLD_UDC, UNIT_V, 2, 2, 10, false, 1 },
        { TYPE_DC, CH0, FLD_IDC, UNIT_A, 4, 2, 10, false, 2 },
        //{ TYPE_DC, CH0, FLD_PDC, UNIT_W, 6, 2, 10, false, 1 },
        { TYPE_DC, CH0, FLD_PDC, UNIT_W, CALC_PDC, CH0, CMD_CALC, false, 2 },
        { TYPE_DC, CH0, FLD_YD, UNIT_KWH, 14, 2, 100, false, 1 },
        { TYPE_DC, CH0, FLD_YT, UNIT_KWH, 10, 2, 10, false, 0 },
        { TYPE_DC, CH0, FLD_IRR, UNIT_PCT, CALC_CH_IRR, CH0, CMD_CALC, false, 3 },

        { TYPE_AC, CH0, FLD_UAC, UNIT_V, 18, 2, 10, false, 1 },
        { TYPE_AC, CH0, FLD_IAC, UNIT_A, 28, 2, 10, false, 2 },
        { TYPE_AC, CH0, FLD_PAC, UNIT_W, 22, 4, 10, false, 1 },
        //{ TYPE_AC, CH0, FLD_Q, UNIT_VAR, 26, 2, 10, false, 1 },
        { TYPE_AC, CH0, FLD_F, UNIT_HZ, 20, 2, 100, false, 2 },
        { TYPE_AC, CH0, FLD_PF, UNIT_NONE, 30, 2, 1000, false, 3 },

        { TYPE_INV, CH0, FLD_T, UNIT_C, 32, 2, 100, true, 1 },
        { TYPE_INV, CH0, FLD_EVT_LOG, UNIT_NONE, 34, 2, 1, false, 0 },//current status

        //{ TYPE_AC, CH0, FLD_YD, UNIT_WH, CALC_YD_CH0, 0, CMD_CALC, false, 0 },
        { TYPE_INV, CH0, FLD_YD, UNIT_KWH, 36, 2, 100, false, 1 },
        //{ TYPE_AC, CH0, FLD_YT, UNIT_KWH, CALC_YT_CH0, 0, CMD_CALC, false, 3 },
        { TYPE_INV, CH0, FLD_YT, UNIT_KWH, 38, 4, 10, false, 0 },
        { TYPE_INV, CH0, FLD_PDC, UNIT_W, CALC_TOTAL_PDC, 0, CMD_CALC, false, 1 },
        { TYPE_INV, CH0, FLD_EFF, UNIT_PCT, CALC_TOTAL_EFF, 0, CMD_CALC, false, 3 }
};

HMS_W_1T::HMS_W_1T(uint64_t serial,const String & modelType,Print & print):
HoymilesWInverter(serial,print){
    _devInfoParser->setHardwareModel(modelType);
    _statisticsParser->setByteAssignment(byteAssignment,sizeof(byteAssignment) / sizeof(byteAssignment[0]));
}
