#ifndef schedule_h
#define schedule_h

class schedule{
	public:
		schedule(int delayTime);
		bool ready(void);

	private:
		unsigned long current_time;
		unsigned long prev_time;
		unsigned long delay_time;
		bool progress;
		unsigned long delta_time;
};



#endif
