#pragma once
#include  "atlstr.h"
#include  <math.h>
#include  <time.h>

#include <windows.h>

namespace  TimeCounters
{
	class  CTimeCounter
	{
	public:

		CTimeCounter();
		~CTimeCounter() {};

		void  vSetStartNow();
		bool  bGetTimePassed(double  *pdTimePassedSec);
		bool  bSetFinishOn(double  dTimeToFinishSec);
		bool  bIsFinished();

	private:
		bool  b_start_inited;
		LARGE_INTEGER  li_start_position;
		LARGE_INTEGER  li_freq;

		bool  b_finish_inited;
		LARGE_INTEGER  li_finish_position;

	};
};