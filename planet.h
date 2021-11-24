/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#ifndef RYAN_PLANET_H
#define RYAN_PLANET_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <vector>
#include "moon.h"

class Planet
{
private:
	// distance from the sun
	const float distanceFromSun;

	// time it takes to complete 1 orbit
	const float orbitTime;

	// time it takes to spin 360 degrees
	const float rotationTime;

	// radius of the planet itself
	const float radius;

	// the texture used for rendering
	const GLuint textureHandle;

	// its position in 3d space
	const float position[3];
	// its rotation around its axis
	const float rotation;

	// list of moons attached to this planet
	const std::vector<Moon> moons;

public:
	// Distance is in units of km (kilometers) and time is in units of earth days (365.25 orbit time for earth)
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
	
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle, float[3], float rotation, std::vector<Moon> moons);

	// Calculate its position in 3d spacein the orbit using the given time value
	static Planet calculatePosition(float time, Planet);

	// Render it to the screen
	static void render(Planet);

	// render this planets orbit circle
	static void renderOrbit(Planet);

	// Get its position in 3d world space units (after scaling) and put it into the 3d vector
	static void getPosition(float* vec, Planet planet);

	static float* getPosition(Planet planet);

	// get the radius of this planet
	float getRadius(void);

	// add a moon to this planet
	static Planet addMoon(Planet planetState, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
};

#endif