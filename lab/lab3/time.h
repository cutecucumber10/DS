class Time {
public:
	Time();
	Time(uintptr_t anHour, uintptr_t aMinute, uintptr_t aSecond);
	
	// ACCESSORS
	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;
	
	// MODIFIERS
	void setHour(uintptr_t anHour);
	void setMinute(uintptr_t aMinute);
	void setSecond(uintptr_t aSecond);
	
	// More functions
	void Pruintptr_tAmPm() const;
	
private:
	uintptr_t hour, minute, second;
};

bool IsEarlierThan(const Time &t1, const Time &t2);