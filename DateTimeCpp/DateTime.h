#pragma once
#include <chrono>
#include <string>

enum DtFormat
{
	yyyy_MM_dd_hh_mm_ss,
	yyyy_MM_dd_hh_mm_ss_ms,
	yyyy_MM_dd_hh_mm_ss_ms_us,
	yyyy_MM_dd_hh_mm_ss_ms_us_ns,
	yyyy_MM_dd,
	hh_mm_ss,
};

class DateTime
{
public:
public:
	DateTime();
	DateTime(time_t seconds);
	~DateTime();

	
	time_t m_totalSeconds; //总秒数

	//field	和tm不同, 修正了月份 和 年
 	int m_ns; //纳秒数值 0-999
	int m_us; //微妙数值 0-999
	int m_ms; //毫秒数值 0-999
	//tm filed
	int m_sec;  /*秒，正常范围0-59， 但允许至61*/
	int m_min;  /*分钟，0-59*/
	int m_hour; /*小时， 0-23*/
	int m_mday; /*日，即一个月中的第几天，1-31*/
	int m_mon;  /*月， 从一月算起，1-12*/  //1 + p->tm_mon;
	int m_year;  /*年*/
	int m_wday; /*星期，一周中的第几天， 从星期日算起，0-6*/
	int m_yday; /*从今年1月1日到目前的天数，范围0-365*/
	int m_isdst; /*日光节约时间的旗标*/

	static DateTime FromSeconds(time_t s);
	static DateTime FromMilliseconds(__int64 ms);
	static DateTime FromMicroseconds(__int64 us);
	static DateTime FromNanoseconds(__int64 ns);

	static DateTime Now();
	static DateTime NowWithMilliseconds();
	static DateTime NowWithMicroseconds();
	static DateTime NowWithNanoseconds();

	tm GetTmFromField();
	tm GetTmFromTotalSeconds();

	void FixField();
	void FixFieldFromSeconds(time_t seconds);

	void FixTotalSeconds();
	void FixTotalSecondsFromTm(tm newTm);

	DateTime AddYears(int num);
	DateTime AddMonths(int num);
	DateTime AddDays(int num);
	DateTime AddHours(int num);
	DateTime AddMinutes(int num);
	DateTime AddSeconds(int num);
	DateTime AddMilliseconds(int num);

	std::string ToString(DtFormat fmt = yyyy_MM_dd_hh_mm_ss) const;
	std::string ToString(char buf[], const int32_t buf_len, DtFormat fmt/* = yyyy_MM_dd_hh_mm_ss_ms*/) const;
};

	//void FixTotalSecondsFromTm();
	//std::string ToString() const;
