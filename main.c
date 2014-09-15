#include <math.h>

float position[3];
float myState[12];
float asteroid[3];
float safeZone[3];
float targetRate[3];

void init(){
	//Sets State Vars
	for (i = 0; i < 3; i++){
		asteroid[i] = 0.0f;
	}
	safeZone[0] = 0.4f;
	safeZone[1] = 0.0f;
	safeZone[2] = 0.0f;
}

void moveToSafeZone(){
	//Tells the Robot to move to the safe zone
	if (position[1] < 0) {
		api.setPositionTarget({0.4 , position[1] , position[2]});
	}
	else {
		api.setPositionTarget({-0.4 , position[1] , position[2]});
	}
	if (position[0] > 0.2) {
		api.setPositionTarget(safeZone);
	}
}

float getDist(float start[3] , float end[3]){
	return sqrt(pow(start[0] - end[0] , 2) + pow(start[1] - end[1] , 2) + pow(start[2] - end[2] , 2));
}

void orbit(){
	
}

void moveToOuter(){
	if (getDist(position , asteroid) > 0.5) {
		api.setPositionTarget(asteroid);
	}
	if (getDist(position , asteroid) < 0. 42) {
		//Robot must move AWAY from asteroid now
		if (position[0] < 0) {
			api.setPositionTarget({-0.6 , 0 , 0});
		}
		else {
			api.setPositionTarget({0.6 , 0 , 0});
		}
	}
}

void moveToInner(){
	if (getDist(position , asteroid) > 0.33) {
		api.setPositionTarget(asteroid);
	}
	if (getDist(position , asteroid) < 0.33) {
		if (position[0] < 0) {
			api.setPositionTarget({-0.6 , 0 , 0});
		}
		else {
			api.setPositionTarget({0.6 , 0 , 0});
		}
	}
}

void checkUpload(){
	if (game.getMemoryFilled() == game.getMemorySize()) {
		game.uploadPic();
	}
	if (game.getNextFlare() < 5) {
		game.uploadPic();
		moveToSafeZone();
	}
}

void updatePosition(){
	api.getMyZRState(myState);
	for (i = 0; i < 3; i++) {
		position[i] = positionBuffer[i];
	}
}

void loop(){
	//This function is called once per second.  Use it to control the satellite.
	//Check if the photos should be uploaded
	checkUpload();
	updatePosition();
}

