#include "Servo.h"
#include "WaveArm.h"
/* Functions to move the sweeper arms */


WaveArm::WaveArm(void)
{
  angle = 0;
}

bool WaveArm::sweepIn(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle<ANGLE_MAX){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle += 1;
                temp_dir = ARMS_OUT;
	}else{
		temp_dir = ARMS_IN;
	}
    return temp_dir;
}

bool WaveArm::sweepOut(Servo sweepArmLeft, Servo sweepArmRight){
	if(angle>ANGLE_MIN){
		sweepArmLeft.write(angle);
		sweepArmRight.write(ANGLE_MAX - angle);
		angle -= 1;
                temp_dir = ARMS_IN;
	}else{
		temp_dir = ARMS_OUT;
	}
    return temp_dir;
}

//250kHz clock input is in ms delay between movement 6 optimal, 3 max
void WaveArm::collect(Servo sweepArmLeft, Servo sweepArmRight){
 	curr_time = millis();
	delta_ms = (curr_time-prev_time);
	if(delta_ms>SPEED_MS && armLocation==ARMS_OUT){
		armLocation = sweepIn(sweepArmLeft, sweepArmRight);
		prev_time = curr_time;
	}
	else if(collected()==false && ARMS_IN){
	}else{
	//if(delta_ms>SPEED_MS && armLocation==ARMS_IN){
		armLocation = sweepOut(sweepArmLeft, sweepArmRight);
		prev_time = curr_time;
	}
	Serial.print("angle: ");
	Serial.println(armLocation);
}

void WaveArm::knockOver(){
	//if(whisker_detect && left_bumber){
                //knock_left
        //}
        //if(whisker_detect && right_bumber){
                //knock_right
        //}
        //if(right_bumper && notWhisker_detect)
                //getouttathere
        //}
        //if(left_bumper && notWhisker_detect)
                //getouttathere
        //}
}

bool WaveArm::collected(void){
        collector = analogRead(A2);
        if(collector == 0){
          result = false;
        }else{
          result = true;
        }
        
        Serial.print("     col?: ");
	Serial.println(result);
        
        return result;
}
