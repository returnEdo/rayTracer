#pragma once

#include <vector>
#include <iostream>
#include <string>

const std::string 	EMPTY = "empty";

class IntervalSet;
class Interval;

class Interval{
	
	private:
	
	float a = .0f;
	float b = .0f;
	
	bool empty = false;
	
	public:
	
	Interval(float a_, float b_);
	Interval(const Interval& other);		
	Interval(void);							//	empty interval
	
	/* getters */
		
	float get_a(void) 		const;
	float get_b(void) 		const;
	float getLength(void)	const;

	inline bool isEmpty(void) const	{ return empty; }

	/* setters */
	void set_a(float a_);
	void set_b(float b_);
	
	/* operations */
	
	inline friend float max(const Interval& interval)	{ return interval.a; }
	inline friend float min(const Interval& interval)	{ return interval.b; }
	
	friend bool operator ==(const Interval& i1, const Interval& i2);

	friend IntervalSet Union(const Interval& i1, const Interval& i2);
	friend IntervalSet Difference(const Interval& i1, const Interval& i2);
	friend IntervalSet Intersection(const Interval& i1, const Interval& i2);

	friend IntervalSet operator +(const Interval& i1, const Interval& i2);
	friend IntervalSet operator -(const Interval& i1, const Interval& i2);
	friend IntervalSet operator &(const Interval& i1, const Interval& i2);
	
	friend std::ostream& operator <<(std::ostream& os, const Interval& i);

	friend class IntervalSet;
};



class IntervalSet{

	private:

	std::vector<Interval> intervals;	// disjoint intervals

	bool empty = false;

	public:

	IntervalSet(const std::vector<Interval>& intervals_);
	IntervalSet(const Interval& interval);
	IntervalSet(const IntervalSet& set);
	IntervalSet(void);


	/* getters */

	inline const std::vector<Interval>& getIntervals(void) 	const { return intervals; }
	inline bool isEmpty(void)								const { return empty; }
	inline int getSize(void)								const { return intervals.size(); }
	
	
	/* operators */
	
	void operator =(const IntervalSet& set);

	friend std::ostream& operator <<(std::ostream& os, const IntervalSet& set);

	inline friend float max(IntervalSet& set)	{ set.sort();	return set.intervals[0].get_a(); }
	inline friend float min(IntervalSet& set)	{ set.sort();	return set.intervals[set.intervals.size() - 1].get_b(); }

	void sort(void);
	void insertInterval(const Interval& i);
};
