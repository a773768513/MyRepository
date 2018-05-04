#include "CRCChecksum.h"



/***************************************************
@brief  check NMEA data correctness
@param  unsigned long ulCount, Number of bytes in the data block
ucBuffer Data block
@author  YHF
@data   2018/5/4
@
********************************************************/
unsigned char NMEA_Check(
	unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer) /* Data block */
{

	unsigned char ulCRC = 0;
	while (ulCount-- != 0)
	{
		ulCRC = (ulCRC ^ *ucBuffer++);
	}
	return(ulCRC);
}
/***************************************************
@brief  check CRCValue data correctness
@param  i 
@author  YHF
@data   2018/5/4
@
********************************************************/
unsigned long CRC32Value(int i)
{
	int j;
	unsigned long ulCRC;
	ulCRC = i;
	for (j = 8; j > 0; j--)
	{
		if (ulCRC & 1)
			ulCRC = (ulCRC >> 1) ^ CRC32_POLYNOMIAL;
		else
			ulCRC >>= 1;
	}
	return ulCRC;
}
/***************************************************
@brief  check CRCValue data correctness
@param  unsigned long ulCount, Number of bytes in the data block
        ucBuffer Data block
@author  YHF
@data   2018/5/4
@
********************************************************/
unsigned long CalculateBlockCRC32(
	unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer) /* Data block */
{
	unsigned long ulTemp1;
	unsigned long ulTemp2;
	unsigned long ulCRC = 0;
	while (ulCount-- != 0)
	{
		ulTemp1 = (ulCRC >> 8) & 0x00FFFFFFL;
		ulTemp2 = CRC32Value(((int)ulCRC ^ *ucBuffer++) & 0xff);
		ulCRC = ulTemp1 ^ ulTemp2;
	}
	return(ulCRC);
}