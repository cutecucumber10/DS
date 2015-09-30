class Time {
public:
	Time();
	Time(int aHour, int aMinute, int aSecond);

	//Accessors:
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	//Modifiers
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);

	//non member functions
	void print() const;
	void PrintAmPm() const;

private:
	int hour;
	int minute;
	int second;


};
bool IsEarlierThan(const Time& time1, const Time& time2 ) ;

