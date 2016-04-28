#pragma once

class Course{
public:
	Course(int _track, int _num)
	{
		track = _track;
		num = _num;
	}

	int get_track(){ return track; }
	int get_num(){ return num; }

private:
	int track;
	int num;
};