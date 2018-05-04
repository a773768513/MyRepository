#ifndef  __CRC_CHECKSUM__
#define  __CRC_CHECKSUM__


#ifndef CRC32_POLYNOMIAL
#define CRC32_POLYNOMIAL 0xEDB88320L
#endif
unsigned char NMEA_Check(
	unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer) /* Data block */;

unsigned long CRC32Value(int i);

unsigned long CalculateBlockCRC32(
	unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer) /* Data block */;


#endif