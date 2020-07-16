/*
 * xtx.h
 *
 * Created: 2020/05/14 12:47:49
 *  Author: Kolijn
 */ 


#ifndef XTX_H_
#define XTX_H_

struct XTX_configuration {
    uint8_t ss_pin;
};

void XTX_vConfig(void);
void XTX_vDeConfig(void);

void XTX_vSetEnable(bool enabled);
void XTX_SetNReset(bool reset);
bool XTX_bGetEnable(void);

#endif /* XTX_H_ */
