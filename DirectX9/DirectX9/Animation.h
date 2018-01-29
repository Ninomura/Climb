#pragma once

class Animation
{
private:
	int time, num;
public:
	Animation();
	~Animation();

	int getNum() { return num; };
	void processing(int setTime, int setNum);
};

Animation::Animation()
{
	time = 0;
	num = 0;
}

Animation::~Animation()
{
}

void Animation::processing(int setTime, int setNum)
{
	time++;

	if (time >= setTime)
	{
		time = 0;
		num++;
		if (num >= setNum)
		{
			num = 0;
		}
	}
}