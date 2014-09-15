#include <math.h>

float position[3];
ZRState myState;
float asteroid[3];
float safeZone[3];
float targetRate[3];
float posAnchor[3];
float negAnchor[3];
int var; //var is a value that defines the robot's state

void init(){
	//Sets State Vars
	for (int i = 0; i < 3; i++){
		asteroid[i] = 0.0f;
	}
	safeZone[0] = 0.4f;
	safeZone[1] = 0.0f;
	safeZone[2] = 0.0f;
	negAnchor = {-0.6 , 0 , 0};
	posAnchor = {0.6 , 0 , 0};
	var = 0;
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
	if (getDist(position , asteroid) < 0.42) {
		//Robot must move AWAY from asteroid now
		if (position[0] < 0) {
			api.setPositionTarget(negAnchor);
		}
		else {
			api.setPositionTarget(posAnchor);
		}
	}
}

void moveToInner(){
	if (getDist(position , asteroid) > 0.33) {
		api.setPositionTarget(asteroid);
	}
	if (getDist(position , asteroid) < 0.33) {
		if (position[0] < 0) {
			api.setPositionTarget(negAnchor);
		}
		else {
			api.setPositionTarget(posAnchor);
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
	for (int i = 0; i < 3; i++) {
		position[i] = myState[i];
	}
}

void decision(){
	//Check var state based on position and time
	//Use switch statement?????


	//Decides what to do based on the value of 'var'
	switch (var) {
		case 0:
			//State where sphere is not in either of the zones
			moveToOuter();
			break;
		case 1:
			//State where sphere is in the outer or inner ring
			orbit();
			break;
		default:
			//What to do if things aren't done
			break;
	}
}

void loop(){
	//This function is called once per second.  Use it to control the satellite.
	//Check if the photos should be uploaded
	checkUpload();
	updatePosition();
	decision();
}


