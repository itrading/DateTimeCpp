#include "stdafx.h"
#include "DateTime.h"
using namespace std;

DateTime::DateTime()
{
	m_totalSeconds = 0;
	m_ns = 0;
	m_us = 0;
	m_ms = 0;
	m_sec = 0;
	m_min = 0;
	m_hour = 0;
	m_mday = 0;
	m_mon = 0;
	m_year = 0;
	m_wday = 0;
	m_yday = 0;
	m_isdst = 0;
}
DateTime::DateTime(time_t seconds):DateTime()
{
	m_totalSeconds = seconds;
	FixFieldFromSeconds(seconds);
}
DateTime::~DateTime()
{
}


DateTime DateTime::FromSeconds(time_t s)
{
	DateTime dt;
	dt.m_totalSeconds = s;
	dt.FixFieldFromSeconds(dt.m_totalSeconds);
	return dt;
}

DateTime DateTime::FromMilliseconds(__int64 ms)
{
	DateTime dt;
	dt.m_totalSeconds = ms / 1000;
	dt.m_ms = ms % 1000;
	dt.FixFieldFromSeconds(dt.m_totalSeconds);
	return dt;
}

DateTime DateTime::FromMicroseconds(__int64 us)
{
	DateTime dt;
	dt.m_totalSeconds = us / 1000000;
	dt.m_ms = (us % 1000000) / 1000;
	dt.m_us = us % 1000;
	dt.FixFieldFromSeconds(dt.m_totalSeconds);
	return dt;
}

DateTime DateTime::FromNanoseconds(__int64 ns)
{
	DateTime dt;
	dt.m_totalSeconds = ns / 1000000000;
	int ms = ns % 1000000000;
	int us = ms % 1000000;
	dt.m_ms = ms / 1000000;
	dt.m_us = us / 1000;
	dt.m_ns = ns % 1000;
	dt.FixFieldFromSeconds(dt.m_totalSeconds);
	return dt;
}

DateTime DateTime::Now()
{
	DateTime dt;
	time_t t;
	time(&t);
	dt.m_totalSeconds = t;
	dt.FixFieldFromSeconds(dt.m_totalSeconds);
	return dt;
}

DateTime DateTime::NowWithMilliseconds()
{
	time_t cnt = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now()).time_since_epoch().count();
	return FromMilliseconds(cnt);
}

DateTime DateTime::NowWithMicroseconds()
{
	time_t cnt = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now()).time_since_epoch().count();
	return FromMicroseconds(cnt);
}

DateTime DateTime::NowWithNanoseconds()
{
	time_t cnt = chrono::time_point_cast<chrono::nanoseconds>(chrono::system_clock::now()).time_since_epoch().count();
	return FromNanoseconds(cnt);
}


tm DateTime::GetTmFromField()
{
	tm tmp;
	tmp.tm_sec = m_sec;
	tmp.tm_min = m_min;
	tmp.tm_hour = m_hour;
	tmp.tm_mday = m_mday;
	tmp.tm_mon = m_mon - 1;
	tmp.tm_year = m_year < 1970 ? 70 : m_year - 1900;
	tmp.tm_wday = m_wday;
	tmp.tm_yday = m_yday;
	tmp.tm_isdst = m_isdst;
	return tmp;
}

tm DateTime::GetTmFromTotalSeconds()
{
	std::tm tmp;
	localtime_s(&tmp, &m_totalSeconds);
	return tmp;
}


void DateTime::FixField()
{
	tm tmp = GetTmFromTotalSeconds();
	m_sec = tmp.tm_sec;
	m_min = tmp.tm_min;
	m_hour = tmp.tm_hour;
	m_mday = tmp.tm_mday;
	m_mon = tmp.tm_mon + 1;
	m_year = tmp.tm_year + 1900;
	m_wday = tmp.tm_wday;
	m_yday = tmp.tm_yday;
	m_isdst = tmp.tm_isdst;
}

void DateTime::FixFieldFromSeconds(time_t seconds)
{
	std::tm tmp;
	localtime_s(&tmp, &seconds);
	m_sec = tmp.tm_sec;
	m_min = tmp.tm_min;
	m_hour = tmp.tm_hour;
	m_mday = tmp.tm_mday;
	m_mon = tmp.tm_mon + 1;
	m_year = tmp.tm_year + 1900;
	m_wday = tmp.tm_wday;
	m_yday = tmp.tm_yday;
	m_isdst = tmp.tm_isdst;
}


void DateTime::FixTotalSeconds()
{
	tm tmp = GetTmFromField();
	FixTotalSecondsFromTm(tmp);
}

void DateTime::FixTotalSecondsFromTm(tm newTm)
{
	m_totalSeconds = mktime(&newTm);
}


DateTime DateTime::AddYears(int num)
{
	DateTime dt(*this);
	dt.m_year += num;
	dt.FixTotalSeconds();
	return dt;
}

DateTime DateTime::AddMonths(int num)
{
	DateTime dt(*this);
	dt.m_mon += num;
	if (dt.m_mon >12)
	{
		dt.m_year += dt.m_mon / 12;
		dt.m_mon = dt.m_mon % 12;
		if (dt.m_mon == 0)
		{
			dt.m_mon = 12;
			dt.m_year -= 1;
		}
	}
	else if(dt.m_mon <= 0)
	{
		dt.m_year += dt.m_mon / 12 - 1;
		dt.m_mon = dt.m_mon % 12 + 12;
	}
	dt.FixTotalSeconds();
	return dt;
}

DateTime DateTime::AddDays(int num)
{
	DateTime dt(*this);
	dt.m_totalSeconds += num * 86400;
	dt.FixField();
	return dt;
}

DateTime DateTime::AddHours(int num)
{
	DateTime dt(*this);
	dt.m_totalSeconds += num * 3600;
	dt.FixField();
	return dt;
}

DateTime DateTime::AddMinutes(int num)
{
	DateTime dt(*this);
	dt.m_totalSeconds += num * 60;
	dt.FixField();
	return dt;
}

DateTime DateTime::AddSeconds(int num)
{
	DateTime dt(*this);
	dt.m_totalSeconds += num;
	dt.FixField();
	return dt;
}

DateTime DateTime::AddMilliseconds(int num)
{
	DateTime dt(*this);
	dt.m_ms += num;
	__int64 sec = 0;
	if (dt.m_ms >=1000)
	{
		sec = dt.m_ms / 1000;
		dt.m_ms = dt.m_ms % 1000;
	}
	dt.m_totalSeconds += num;
	dt.FixField();
	return dt;
}

std::string DateTime::ToString(DtFormat fmt) const
{
	const int32_t buf_len = 32;
	static char buf[buf_len] = { 0 };
	ToString(buf, buf_len, fmt);
	return std::string(buf);
}
std::string DateTime::ToString(char buf[], const int32_t buf_len, DtFormat fmt) const
{
	switch (fmt)
	{
	case yyyy_MM_dd_hh_mm_ss:
		snprintf(buf, buf_len, "%04d-%02d-%02d %02d:%02d:%02d", m_year, m_mon, m_mday, m_hour, m_min, m_sec);
		break;
	case yyyy_MM_dd_hh_mm_ss_ms:
		snprintf(buf, buf_len, "%04d-%02d-%02d %02d:%02d:%02d.%03d", m_year, m_mon, m_mday, m_hour, m_min, m_sec, m_ms);
		break;
	case yyyy_MM_dd_hh_mm_ss_ms_us:
		snprintf(buf, buf_len, "%04d-%02d-%02d %02d:%02d:%02d.%03d.%03d", m_year, m_mon, m_mday, m_hour, m_min, m_sec, m_ms, m_us);
		break;
	case yyyy_MM_dd_hh_mm_ss_ms_us_ns:
		snprintf(buf, buf_len, "%04d-%02d-%02d %02d:%02d:%02d.%03d.%03d.%-3d", m_year, m_mon, m_mday, m_hour, m_min, m_sec, m_ms, m_us,m_ns);
		break;
	case yyyy_MM_dd:
		snprintf(buf, buf_len, "%04d-%02d-%02d", m_year, m_mon, m_mday);
		break;
	case hh_mm_ss:
		snprintf(buf, buf_len, "%02d:%02d:%02d", m_hour, m_min, m_sec);
		break;
	default:
		break;
	}
	return std::string(buf);
}



//from self tm fix seconds
//void DateTime::FixTotalSecondsFromTm()
//{
//	FixTotalSecondsFromTm(GetTmFromField());
//}
//std::string DateTime::ToString() const
//{
//	return ToString(yyyy_MM_dd_hh_mm_ss);
//}
