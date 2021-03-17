#include "Interval.h"

#include <algorithm>


bool comparef(float a, float b){

	float diff = (a - b > .0f? a - b: b - a);

	return (diff < EPSILON); 
}


Interval::Interval(float a_, float b_):
		a((a_ <= b_? a_: b_)),
		b((b_ >= a_? b_: a_)),
		empty(false) {

}

Interval::Interval(const Interval& other):
		a(other.a),
		b(other.b),
		empty(other.empty) {

}

Interval::Interval(void):
		empty(true) {

}


float Interval::get_a(void) const{
	
	if (empty)	{ throw EMPTY; }
	
	return a;
}
		
float Interval::get_b(void) const{
	
	if (empty)	{ throw EMPTY; }
	
	return b;
}

float Interval::getLength(void) const{
	
	if (empty)	{ throw EMPTY; }
	
	return (b - a);
}


void Interval::set_a(float a_){

	a = (a_ < b? a_: b);
	b = (a_ > b? a_: b);
}

void Interval::set_b(float b_){

	a = (b_ > a? a: b_);
	b = (b_ < a? a: b_);
}


bool operator ==(const Interval& i1, const Interval& i2){

	return (comparef(i1.a, i2.a) and comparef(i1.b, i2.b));
}



IntervalSet Union(const Interval& i1, const Interval& i2){
	
	if (i1.empty and not i2.empty)		{ return IntervalSet(i2); }
	else if (i2.empty and not i1.empty)	{ return IntervalSet(i1); }
	else if (i1.empty and i2.empty)		{ return IntervalSet(); }
	else{
		/* there is no intersection */
		if (i1.a > i2.b or i2.a > i1.b) { 
			
			std::vector<Interval> intervals = {i1, i2};

			return IntervalSet(intervals);
		}
		
		/* there is intersection */
		float min = (i1.a < i2.a? i1.a: i2.a);
		float max = (i1.b > i2.b? i1.b: i2.b);
		
		Interval temp(min, max);
		
		return IntervalSet(temp);
	}
}

IntervalSet Difference(const Interval& i1, const Interval& i2){
	/* i1 - i2 */
	
	if (i1.empty) { return IntervalSet(); }
	else{	
		/* find the intersection */
		IntervalSet set = i1 & i2;

		if (set.isEmpty()) { return IntervalSet(i1); }
		else{	
			Interval i3 = set.getIntervals()[0];

			/* i1 and i3 are non empty */

			if (i1 == i3) 			{ return IntervalSet(); }
			else if(comparef(i1.a, i3.a)){ 

				Interval interval(i3.b, i1.b);
				return IntervalSet(interval);
			}
			else if(comparef(i1.b, i3.b)){ 

				Interval interval(i1.a, i3.a);
				return IntervalSet(interval);
			}
			else{
			
				Interval intervalDx(i1.a, i3.a);
				Interval intervalSx(i3.b, i1.b);

				std::vector<Interval> intervals = {intervalDx, intervalSx};

				return IntervalSet(intervals);
			}
		}
	}
}

IntervalSet Intersection(const Interval& i1, const Interval& i2){
	
	if (i1.empty or i2.empty) { return IntervalSet(); }
	else{

		if (i1.b < i2.a or i2.b < i1.a){
			/* there is no intersection */

			return IntervalSet();
		}
		else{
			/* there is intersection */
		
			float max = (i1.a > i2.a? i1.a: i2.a);
			float min = (i1.b < i2.b? i1.b: i2.b);
			
			Interval temp(max, min);
			
			return IntervalSet(temp);
		}
	}
}

IntervalSet operator +(const Interval& i1, const Interval& i2)	{ return Union(i1, i2); }
IntervalSet operator -(const Interval& i1, const Interval& i2)	{ return Difference(i1, i2); }
IntervalSet operator &(const Interval& i1, const Interval& i2)	{ return Intersection(i1, i2); }

std::ostream& operator <<(std::ostream& os, const Interval& i){
	
	if (i.empty){

		os << "empty";
	}
	else{

		os << "[" << i.a << ", " << i.b << "]";
	}
	
	return os;
}


IntervalSet::IntervalSet(const std::vector<Interval>& intervals_){
	
	/* pushes non empty intervals */
	for (const Interval& interval: intervals_){

		if (not interval.isEmpty()){

			intervals.push_back(interval);
		}
	}
	if (intervals.size() != 0){

		empty = false;
	}
}


IntervalSet::IntervalSet(const Interval& interval){

	if (not interval.isEmpty()){

		intervals.push_back(interval);
	}

	empty = interval.isEmpty();

	if (not empty)	{ sort(); }
}


IntervalSet::IntervalSet(const IntervalSet& set):
		IntervalSet(set.intervals) {

}

IntervalSet::IntervalSet(void):
		empty(true) {

}


void IntervalSet::operator =(const IntervalSet& set){

	intervals = set.intervals;
	empty = set.empty;
}


std::ostream& operator <<(std::ostream& os, const IntervalSet& set){

	if (set.empty){

		os << "empty";
	}
	else{
		os << "{";

		for (int i = 0; i < set.intervals.size() - 1; i++){

			os << set.intervals[i] << ", ";
		}

		os << set.intervals[set.intervals.size() - 1] << "}";
	}

	return os;
}


void IntervalSet::sort(void){
	/* sorts the sets in increasing .a order (insertion sort) */

	for (int i = 1; i < intervals.size(); i++){

		Interval key(intervals[i]);
		int j = i - 1;

		while (key.get_a() < intervals[j].get_a() and j >= 0){
			
			intervals[j + 1] = intervals[j];
			j--;
		}
		intervals[j + 1] = key;
	}
}

void IntervalSet::insertInterval(const Interval& interval){
	
	if (interval.isEmpty())	{ return; }

	intervals.push_back(interval);
	sort();
	
	/* find the indx of the newly inserted interval */
	std::vector<Interval>::iterator it;
	it  = std::find(intervals.begin(), intervals.end(), interval);
	int indx = it - intervals.begin();

	if (indx >= 1 and intervals[indx - 1].get_b() > interval.get_a()){
		/* first overlapping interval */
		
		indx--;
	}

	int i = indx;
	while (i < intervals.size() - 1 and intervals[i].get_b() >= intervals[i + 1].get_a()){
		
		if (intervals[i].get_b() < intervals[i + 1].get_b()){
			/* merge if necessary */

			intervals[i].set_b(intervals[i + 1].get_b());
		}
		/* in any case get rid of the unnecessary interval */
		intervals.erase(intervals.begin() + i + 1);
	}
}

