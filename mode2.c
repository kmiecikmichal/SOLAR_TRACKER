#include "mode2.h"

int servo2PositionTab[24] = {15,15,15,15,15,15,15,20,25,30,35,40,45,50,55,60,65,70,75,15,15,15,15,15}; 											// servo2 position

int januaryTabX[24] = {250,250,250,250,250,250,250,200,205,211,217,222,217,211,205,200,250,250,250,250,250,250,250,250}; 		// accel X
int januaryTabZ[24] = {192,192,192,192,192,192,192,226,217,211,205,202,205,211,217,226,192,192,192,192,192,192,192,192}; 		// accel Z

int februaryTabX[24] = {250,250,250,250,250,250,250,200,205,211,217,227,227,217,211,205,200,250,250,250,250,250,250,250}; 	// accel X
int februaryTabZ[24] = {192,192,192,192,192,192,192,226,217,211,205,200,200,205,211,217,226,192,192,192,192,192,192,192};		// accel Z

int marchTabX[24] = {250,250,250,250,250,250,200,205,210,215,220,224,227,224,220,215,210,205,200,250,250,250,250,250};			// accel X
int marchTabZ[24] = {192,192,192,192,192,192,226,217,218,206,202,201,200,201,202,206,218,217,226,192,192,192,192,192}; 			// accel Z

int aprilTabX[24] = {250,250,250,250,250,200,205,211,217,222,227,233,233,227,222,217,211,205,200,250,250,250,250,250}; 			// accel X
int aprilTabZ[24] = {192,192,192,192,192,226,217,211,205,202,200,196,196,200,202,205,211,217,226,192,192,192,192,192}; 			// accel Z

int mayTabX[24] = {250,250,250,250,250,200,205,211,217,224,230,233,238,238,233,230,224,217,211,205,200,250,250,250}; 				// accel X
int mayTabZ[24] = {192,192,192,192,192,230,217,211,205,201,198,196,195,195,196,198,201,205,211,217,230,192,192,192};				// accel Z

int juneTabX[24] = {250,250,250,250,250,200,210,217,222,227,233,238,242,245,242,238,233,227,222,217,210,200,250,250}; 			// accel X
int juneTabZ[24] = {192,192,192,192,192,226,225,205,202,200,196,195,194,193,194,195,196,200,202,205,225,226,192,192}; 			// accel Z

int julyTabX[24] = {250,250,250,250,200,210,216,221,226,232,237,242,245,242,237,232,226,221,216,210,200,250,250,250};		 		// accel X
int julyTabZ[24] = {192,192,192,192,230,225,220,215,210,205,200,196,193,196,200,205,210,215,220,225,230,192,192,192}; 			// accel Z

int augustTabX[24] = {250,250,250,250,250,200,205,211,217,224,230,233,238,238,233,230,224,217,211,205,200,250,250,250}; 		// accel X
int augustTabZ[24] = {192,192,192,192,192,230,217,211,205,201,198,196,195,195,196,198,201,205,211,217,230,192,192,192}; 		// accel Z

int septemberTabX[24] = {250,250,250,250,250,250,200,205,211,217,222,227,233,233,227,222,217,211,205,200,250,250,250,250};	// accel X
int septemberTabZ[24] = {192,192,192,192,192,192,226,217,211,205,202,200,196,196,200,202,205,211,217,226,192,192,192,192};	// accel Z
	
int octoberTabX[24] = {250,250,250,250,250,250,200,205,210,215,220,224,227,224,220,215,210,205,200,250,250,250,250,250}; 		// accel X
int octoberTabZ[24] = {293,192,192,192,192,192,226,217,218,206,202,201,200,201,202,206,218,217,226,192,192,192,192,192}; 		// accel Z

int novemberTabX[24] = {250,250,250,250,250,250,250,200,205,211,217,227,227,217,211,205,200,250,250,250,250,250,250,250}; 	// accel X
int novemberTabZ[24] = {192,192,192,192,192,192,192,226,217,211,205,200,200,205,211,217,226,192,192,192,192,192,192,192}; 	// accel Z

int decemberTabX[24] = {250,250,250,250,250,250,250,200,205,211,217,222,217,211,205,200,250,250,250,250,250,250,250,250}; 	// accel X
int decemberTabZ[24] = {192,192,192,192,192,192,192,226,217,211,205,202,205,211,217,226,192,192,192,192,192,192,192,192}; 	// accel Z

int *monthTabX[12] = {januaryTabX, februaryTabX, marchTabX, aprilTabX, juneTabX, julyTabX, augustTabX, septemberTabX, octoberTabX, novemberTabX, decemberTabX};
int *monthTabZ[12] = {januaryTabZ, februaryTabZ, marchTabZ, aprilTabZ, juneTabZ, julyTabZ, augustTabZ, septemberTabZ, octoberTabZ, novemberTabZ, decemberTabZ};

void servoMode2SmoothOperator(uint8_t accelXPositionValue,uint8_t accelZPositionValue, uint32_t delayTime){
	uint8_t accelXFlag = 0;
	uint8_t accelZFlag = 0;
	uint8_t accelReadValueX, accelReadValueZ;
	uint8_t absX, absZ;
	uint8_t absVal = 4;

	while (accelXFlag != 1 || accelZFlag != 1) {
		
		accelReadValueX = accelReadX();
		uartSendString(" x:");
		decToStringAndSendUart(accelReadValueX);
		
		accelReadValueZ = accelReadZ();
		uartSendString(" z:");
		decToStringAndSendUart(accelReadValueZ);
		
		absX = abs(accelXPositionValue - accelReadValueX);
		absZ = abs(accelZPositionValue - accelReadValueZ);
		
		if (absX <= absVal && absZ <= absVal){
			accelXFlag = 1;
			accelZFlag = 1;
		}
		else if (absX <= absVal && absZ > absVal){
			accelXFlag = 1;
			accelZFlag = 0;
			
			if (accelReadValueZ < accelZPositionValue){
				actualServo1Position += 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
			else{
				actualServo1Position -= 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
		}
		else if (absX > absVal && absZ <= absVal){
			accelXFlag = 0;
			accelZFlag = 1;

			if (accelReadValueX < accelXPositionValue){
				actualServo1Position -= 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
			else{
				actualServo1Position += 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
		}
		else if (absX > absVal && absZ > absVal){
			accelXFlag = 0;
			accelZFlag = 0;
			
			if (accelReadValueX < accelXPositionValue && accelReadValueZ > accelZPositionValue){
				actualServo1Position -= 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
			else if (accelReadValueX > accelXPositionValue && accelReadValueZ < accelZPositionValue){
				actualServo1Position += 1;
				pwmServo1(actualServo1Position);
				delay(delayTime);
			}
		}
	}
}

void mode2(uint8_t month, uint16_t day, uint8_t hour, uint16_t hourDelay){
	
	uint16_t i,j,k;
	
	for (i = month; i < 12; i++){			// year loop
		for (j = day; j < 30; j++){			// month loop 
			for (k = hour; k < 24; k++){ 	// day loop
				servoMode2SmoothOperator(monthTabX[i][k],monthTabZ[i][k],1000);
				servoMode1SmoothOperator(actualServo1Position,servo2PositionTab[k],1000);
				actualServo2Position = servo2PositionTab[k];
				delay(hourDelay);
			}
		}
	}
}
