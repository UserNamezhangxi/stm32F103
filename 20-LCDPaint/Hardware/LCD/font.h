#ifndef  _FONT_H_
#define  _FONT_H_

#include "stm32f10x.h"

#define      WIDTH_CH_CHAR		                16	    //中文字符宽度 
#define      HEIGHT_CH_CHAR		              	16		  //中文字符高度 

typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;

extern sFONT Font24x32;
extern sFONT Font16x24;
extern sFONT Font8x16;


uint8_t * GetGBKCode_from_sd ( uint8_t * pBuffer, uint16_t c);


#endif
