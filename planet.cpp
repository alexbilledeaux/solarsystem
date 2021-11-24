/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#include "planet.h"
#include <cmath>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

float planetSizeScale = 0.000005f;

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
	: position{ 0.00, 0.00, 0.00 },
	rotation{ 0.00 },
	textureHandle{ textureHandle },
	radius{ radius },
	rotationTime{ rotationTime },
	orbitTime{ orbitTime },
	distanceFromSun{ distanceFromSun }
{}

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle, float pos[3], float rot, std::vector<Moon> moons)
	:	position { pos[0], pos[1], pos[2] },
		rotation { rot },
		textureHandle { textureHandle },
		radius { radius },
		rotationTime { rotationTime },
		orbitTime { orbitTime },
		distanceFromSun { distanceFromSun },
		moons { moons }
{}

// Calculate its position in 3d spacein the orbit using the given time value
Planet Planet::calculatePosition(float time, Planet planet)
{
	// find the angle of orientation of the orbit around the sun
	float angle = time * 3.1419f / planet.orbitTime;
	
	float pos[3];
	// use trig to find the position in space
	pos[0] = sin(angle) * planet.distanceFromSun;
	pos[1] = cos(angle) * planet.distanceFromSun;
	pos[2] = 0;

	// find the rotation of the planet around its axis
	float rot = time * 360 / planet.rotationTime;

	// calculate positions of moons
	for (int i = 0; i < planet.moons.size(); i++)
	{
		Moon::calculatePosition(time, planet.moons[i]);
	}

	Planet newPlanet = Planet(planet.distanceFromSun, planet.orbitTime, planet.rotationTime, planet.radius, planet.textureHandle, pos, rot, planet.moons);
	return newPlanet;
}

// Render it to the screen
void Planet::render(Planet planet)
{
	glPushMatrix();

	// translate to the right positon
	glTranslatef(planet.position[0] * distanceScale, planet.position[1] * distanceScale, planet.position[2] * distanceScale);

	// Draw the moons
	for (int i = 0; i < planet.moons.size(); i++)
	{
		Moon::render(planet.moons[i]);
	}

	/// rotate for the planet's spin
	glRotatef(planet.rotation, 0.0f, 0.0f, 1.0f);
	
	// bind the planets texture
	glBindTexture(GL_TEXTURE_2D, planet.textureHandle);
	
	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (planet.distanceFromSun < 0.001f) // if this is the sun, dont render it too big, and disable lighting
	{
		float radiusScaled = planet.radius * planetSizeScale;
		if (radiusScaled > 0.5f) radiusScaled = 0.5f;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		glEnable(GL_LIGHTING);
	}
	else
	{
		gluSphere(quadric, planet.radius * planetSizeScale, 30, 30);
	}


	glPopMatrix();
}

// render this planets orbit circle
void Planet::renderOrbit(Planet planet)
{
	// draw a line strip
	glBegin(GL_LINE_STRIP);

	// loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f)
	{
		glVertex3f(sin(angle) * planet.distanceFromSun * distanceScale, cos(angle) * planet.distanceFromSun * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, planet.distanceFromSun * distanceScale, 0.0f);
	
	glEnd();

	// render the moons' orbit
	glPushMatrix();
	// translate to the center of this planet to draw the moon orbit around it
	glTranslatef(planet.position[0] * distanceScale, planet.position[1] * distanceScale, planet.position[2] * distanceScale);
	// draw all moon orbits
	for (int i = 0; i < planet.moons.size(); i++)
	{
		Moon::renderOrbit(planet.moons[i]);
	}
	glPopMatrix();

}


// Get its position in 3d world space units (after scaling) and put it into the 3d vector
void Planet::getPosition(float* vec, Planet planet)
{
	vec[0] = planet.position[0] * distanceScale;
	vec[1] = planet.position[1] * distanceScale;
	vec[2] = planet.position[2] * distanceScale;
}

float* Planet::getPosition(Planet planet)
{
	static float pos[3];
	pos[0] = planet.position[0];
	pos[1] = planet.position[1];
	pos[2] = planet.position[2];
	return pos;
}

// get the radius of this planet
float Planet::getRadius(void)
{
	return radius;
}

// add a moon to this planet
Planet Planet::addMoon(Planet planet, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	std::vector<Moon> moons;
	for (int i = 0; i < planet.moons.size(); i++)
	{
		moons.push_back(planet.moons[i]);
	}
	moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
	
	Planet newPlanet = Planet(planet.distanceFromSun, planet.orbitTime, planet.rotationTime, planet.radius, planet.textureHandle, Planet::getPosition(planet), planet.rotation, moons);
	return newPlanet;
}