/*
 * xtx.h
 *
 * Created: 2020/05/14 12:47:49
 *  Author: Kolijn
 */ 


#ifndef XTX_H_
#define XTX_H_


#define XTX_ENABLED              0x01
#define XTX_NRESET               0x02
#define XTX_RDY                  0x03

struct XTX_configuration {
    uint8_t ss_pin;
};

void XTX_vConfig(void);
void XTX_vDeConfig(void);

void XTX_vSetEnable(bool enabled);
bool XTX_bGetEnable(void);

void XTX_SetNReset(bool reset);
bool XTX_bGetNReset(void);

bool XTX_bGetReady(void);
void XTX_vProcess(void);

/*
 * Tell the XTX module if we are using the multitester. If we are, control lines
 * Are toggled using the multitester rather that the gpio pins. 
 */
void XTX_vSetMultitesterEnabled(const bool ena);

void XTX_vSetMultitesterAutoClr(const bool auto_clear);
bool XTX_bGetMultitesterAutoClr(void);

void XTX_vSetMultitesterPins(const uint32_t pinConfig);
void XTX_u32GetMultiTesterPins(void);

#endif /* XTX_H_ */
