#include <iostream>
#include <iomanip>
#include "time.h"

using namespace std;

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(uintptr_t anHour, uintptr_t aMinute, uintptr_t aSecond) {
	hour = anHour;
	minute = aMinute;
	second = aSecond;
}

uintptr_t Time::getHour() const {
	return hour;
}

uintptr_t Time::getMinute() const {
	return minute;
}

uintptr_t Time::getSecond() const {
	return second;
}

void Time::setHour(uintptr_t h) {
	hour = h;
}

void Time::setMinute(uintptr_t m) {
	minute = m;
}

void Time::setSecond(uintptr_t s) {
	second = s;
}

void Time::Pruintptr_tAmPm() const {
	if (hour == 0 && minute == 0 && second == 0){
		cout << "12:00:00am" << endl;
	}
	else if (hour < 12) {
		cout << setw(2) << setfill('0') << hour << ':' << setw(2) << setfill('0') << minute << ':'\
			<< setw(2) << setfill('0') << second << "am" << endl;
	}
	else if (hour == 12){
		cout << "12:" << setw(2) << setfill('0') << minute << ':'\
			<< setw(2) << setfill('0') << second << "pm" << endl;
	}
	else if (hour > 12 && hour < 24){
		cout << setw(2) << setfill('0') << hour - 12 << ':' << setw(2) << setfill('0') << minute << ':'\
			<< setw(2) << setfill('0') << second << "pm" << endl; 
	}
	else if (hour == 24 && minute == 0 && second == 0){
		cout << "12:00:00am" << endl;
	}
}

bool IsEarlierThan( const Time &t1, const Time &t2){
	if ((t1.getHour()*3600 + t1.getMinute()*60 + t1.getSecond()) < (t2.getHour()*3600 + t2.getMinute()*60 + t2.getSecond()))
		return true;
	else
		return false;
}