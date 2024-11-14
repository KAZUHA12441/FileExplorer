#pragma once

#include  <ctime>
#include   <string> 

typedef enum
{
	YMD_HMS,
	YMD,
	
}TimeType_e;


class Time_c
{
  public:
	  static Time_c *Instance;
	  Time_c();
	  time_t *Now = nullptr;
	  struct tm * info =  nullptr;
	  static Time_c* GetInstance();
	  std::string  GetNowTime(TimeType_e type);
};

