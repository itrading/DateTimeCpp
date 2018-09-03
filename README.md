# DateTimeCpp
c++时间相关简单封装 : time_t 和 tm 封装在一起, 增加了毫秒微妙纳秒字段, 通过chrono取值

建立对象时选择精确度:
DateTime Now(); //精确到秒
//精确到毫秒,微妙,纳秒
DateTime NowWithMilliseconds(); 
DateTime NowWithMicroseconds();
DateTime NowWithNanoseconds();
