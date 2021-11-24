/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#ifndef RYAN_MOON_H
#define RYAN_MOON_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>

class Moon
{
private:
	// distance from its planet
	const float distanceFromPlanet;

	// time it takes to complete 1 orbit
	const float orbitTime;

	// time it takes to spin 360 degrees
	const float rotationTime;

	// radius of the moon itself
	const float radius;

	// the texture used for rendering
	const GLuint textureHandle;

	// its position in 3d space relative to the planet
	const float position[3];
	// its rotation around its axis
	const float rotation;

public:
	// Distance is in units of km (kilometers) and time is in units of earth days
	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle, float[3], float rotation);

	Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Calculate its position in 3d space relative to the planet in the orbit using the given time value
	static Moon calculatePosition(float time, Moon moon);

	// Render it to the screen
	static void render(Moon moon);

	// render this moons orbit circle
	static void renderOrbit(Moon moon);
};

#endif