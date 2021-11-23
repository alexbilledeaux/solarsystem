/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#ifndef RYAN_CAMERA_H
#define RYAN_CAMERA_H

class Camera
{
private:
	// a vector pointing in the directio nyoure facing
	const float forwardVec[3];

	// a vector pointing to the right of where your facing (to describe orientation
	const float rightVec[3];

	// a vector pointing upwards from where youre facing
	const float upVec[3];

	// a vector describing the position of the camera
	const float position[3];

	// the camera speed
	const float cameraSpeed;
	float cameraTurnSpeed;

public:
	Camera(void);

	Camera(float, float, float[3], float[3], float[3], float[3]);

	static float* getPosition(Camera);

	static float* getForwardVector(Camera);

	static float* getRightVector(Camera);

	static float* getUpVector(Camera);

	// transform the opengl view matrix for the orientation
	void transformOrientation(void);

	// transform the opoengl view matrix for the translation
	void transformTranslation(void);

	// points the camera at the given point in 3d space
	static Camera pointAt(float* targetVec, Camera);

	// speed up the camera speed
	static Camera speedUp(Camera);

	// slow down the camera speed
	static Camera slowDown(Camera);

	// move the camera forward
	static Camera forward(Camera);

	// strafe left
	static Camera left(Camera);

	// strafe right
	static Camera right(Camera);

	// move the camera backward
	static Camera backward(Camera);

	// roll the camera to the right
	static Camera rollRight(Camera);

	// roll the camera to the left
	static Camera rollLeft(Camera);

	// pitch the camera up
	static Camera pitchUp(Camera);

	// pitch the camera down
	static Camera pitchDown(Camera);

	// yaw left
	static Camera yawLeft(Camera);

	// yaw right
	static Camera yawRight(Camera);

};

#endif