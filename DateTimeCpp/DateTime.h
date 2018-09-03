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

	
	time_t m_totalSeconds; //������

	//field	��tm��ͬ, �������·� �� ��
 	int m_ns; //������ֵ 0-999
	int m_us; //΢����ֵ 0-999
	int m_ms; //������ֵ 0-999
	//tm filed
	int m_sec;  /*�룬������Χ0-59�� ��������61*/
	int m_min;  /*���ӣ�0-59*/
	int m_hour; /*Сʱ�� 0-23*/
	int m_mday; /*�գ���һ�����еĵڼ��죬1-31*/
	int m_mon;  /*�£� ��һ������1-12*/  //1 + p->tm_mon;
	int m_year;  /*��*/
	int m_wday; /*���ڣ�һ���еĵڼ��죬 ������������0-6*/
	int m_yday; /*�ӽ���1��1�յ�Ŀǰ����������Χ0-365*/
	int m_isdst; /*�չ��Լʱ������*/

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
