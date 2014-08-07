#define CW 1
#define CCW -1

unsigned int target = Wavearm.currentAngle;
unsigned int rotation = 0;
unsigned int current = Magno.currentAngle;
unsigned int p_rotation = 0;
unsigned int motor_speed = 0;

int P = 0;
int D = 0;
int KP = 1;
int KD = 1;


//Aligns the robot to a detected weight

bool align(void){
	//since arm on the right, assume target always clockwise of current
	//input detector arm if 2 are used to determine dir to turn
	aligned = false;
	//check arm pos, note mag pos
	//change pos, check mag, change by D_armpos

	change_rotation = current - Magno.currentAngle;
	//want absolute change
	if(change_rotation < 0){
		change_rotation *= (-1);
	}
	
	rotation += change_rotation;

	//drive robo proportional to angle/target  etc.
	//PD control
	P = target - rotation; //-->0
	D = (rotation - p_rotation); //-->0
	
	//as a percentage
	motor_speed = 90 + (KP*P + KD*D);
	Motors.turn(motor_speed, CW)	
			
	if(rotation == target){
		aligned = true;
	}

	p_rotation = rotation;
	return aligned;
}
