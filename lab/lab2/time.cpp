#include "time.h"
#include <iostream>
#include <iomanip>

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int h) {
	hour = h;
}

void Time::setMinute(int m) {
	minute = m;
}

void Time::setSecond(int s) {
	second = s;
}

bool IsEarlierThan(const Time& time1, const Time& time2 )  {
	if (time1.getHour() < time2.getHour()) {
		return true;
	}
	else if (time1.getHour() == time2.getHour()) {
		if (time1.getMinute() < time2.getMinute()) {
			return true;
		}
		else if (time1.getMinute() == time2.getMinute()) {
			if (time1.getSecond() < time2.getSecond()) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}










void Time::print() const {
	std::cout << hour << ":" << minute << ":" <<second;
}

void Time::PrintAmPm() const {
	if (hour < 12 && hour > 0) {
		std::cout << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " am";
	}
	else if (hour == 12) {
		std::cout << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " pm";
	}
	else if (hour < 24 and hour > 12) {
		//hour = hour - 12;
		std::cout << hour-12 << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " pm";
	}
	else if (hour == 24 or hour == 0) {
		std::cout << 12 << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " am";
	}
}

