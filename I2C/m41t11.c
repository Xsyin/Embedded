#include <string.h>
#include "m41t11.h"
#include "i2c.h"

struct rtc_registers{
	unsigned char secs;
	unsigned char mins;
	unsigned char hours;
	unsigned char wday;
	unsigned char mday;
	unsigned char mon;
	unsigned char year;
	unsigned char cs;
};

#define BCD_TO_BIN(val)   (((val)&15) + ((val)>>4)*10)
#define BIN_TO_BCD(val)   ((((val)/10)<<4) + (val)%10)

static unsigned long epoch = 2000;

static const unsigned char days_in_mo[] = 
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int m41t11_set_datetime(struct rtc_time *dt)
{
	unsigned char leap_yr;
	struct {
		unsigned char addr;
		struct rtc_registers rtc;
	} __attribute__ ((packed)) addr_and_regs;
	memset(&addr_and_regs, 0, sizeof(addr_and_regs));

	leap_yr = ((!(dt->tm_year % 4) && (dt->tm_year % 100)) || !(dt->tm_year % 400));
	
	if((dt->tm_mon < 1) || (dt->tm_mon > 12) || (dt->tm_mday == 0))
		return -1;
	if(dt->tm_mday > (days_in_mo[dt->tm_mon] + ((dt->tm_mon == 2) && leap_yr)))
		return -2;
	if((dt->tm_hour >= 24) || (dt->tm_min >= 60) || (dt->tm_sec >= 60))
		return -3;
	if((dt->tm_year -= epoch) > 255)
		return -4;
	if(dt->tm_year >= 100)
		dt->tm_year -= 100;

	addr_and_regs
	
}
