struct rtc_time
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_wday;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int cs;
};

int m41t11_get_datetime(struct rtc_time *dt);
int m41t11_set_datetime(struct rtc_time *dt);
