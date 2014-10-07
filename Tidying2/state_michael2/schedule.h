#ifndef schedule_h
#define schedule_h

#define WAIT_ARRAY_SIZE 10


class schedule{
	public:
		schedule(int scheduleTime);
		bool ready(void);

	private:
		unsigned long prevCall;
		unsigned long scheduleTime;
		bool scheduleReady;
};


bool wait (int instance, unsigned long delayTime);

#endif
