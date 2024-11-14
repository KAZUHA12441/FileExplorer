#include "Time_c.hpp"


Time_c* Time_c::Instance = new Time_c();

Time_c::Time_c() {
	Now = new time_t;
}

std::string Time_c::GetNowTime(TimeType_e type)
{
	std::string nowtime;
	time(Now);
	info = localtime(Now);

	if(type == YMD_HMS)
	nowtime = nowtime + std::to_string(info->tm_year + 1900) + "/" + std::to_string(info->tm_mon + 1) + "/" + std::to_string(info->tm_mday)+" "+  std::to_string(info->tm_hour) +":"+ std::to_string(info->tm_min)+ ":"+std::to_string(info->tm_sec);
	else if (type == YMD)
	nowtime = nowtime + std::to_string(info->tm_year + 1900) + "/" + std::to_string(info->tm_mon + 1) + "/" + std::to_string(info->tm_mday);
	return nowtime;
}

Time_c* Time_c::GetInstance()
{
	return Instance;
}


