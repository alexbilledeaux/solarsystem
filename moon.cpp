/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#include "moon.h"
#include <cmath>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include "globals.h"

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
	:	distanceFromPlanet{ distanceFromPlanet },
		orbitTime { orbitTime },
		rotationTime { rotationTime },
		radius { radius },
		textureHandle { textureHandle },
		position { 0.00, 0.00, 0.00 },
		rotation { 0.00 }
{}

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle, float position[3], float rotation )
	:	distanceFromPlanet { distanceFromPlanet },
		orbitTime { orbitTime },
		rotationTime { rotationTime },
		radius { radius },
		textureHandle { textureHandle },
		position { position[0], position[1], position[2] },
		rotation { rotation }
{}

// Calculate its position in 3d space relative to the planet in the orbit using the given time value
Moon Moon::calculatePosition(float time, Moon moon)
{
	// find the angle of orientation of the orbit around the planet
	float angle = time * 3.1419f / moon.orbitTime;
	
	// use trig to find the position in space relative to the planet
	float pos[3];
	pos[0] = sin(angle) * moon.distanceFromPlanet;
	pos[1] = cos(angle) * moon.distanceFromPlanet;
	pos[2] = 0;

	// find the rotation of the moon around its axis
	float rotation = time * 360 / moon.rotationTime;

	Moon newMoon = Moon(moon.distanceFromPlanet, moon.orbitTime, moon.rotationTime, moon.radius, moon.textureHandle, pos, rotation);
	return newMoon;
}

// Render it to the screen
void Moon::render(Moon moon)
{
	glPushMatrix();

	// bind the moons texture
	glBindTexture(GL_TEXTURE_2D, moon.textureHandle);

	// translate to the right positon and rotate for the moons spinning
	glTranslatef(moon.position[0] * distanceScale, moon.position[1] * distanceScale, moon.position[2] * distanceScale);
	glRotatef(-moon.rotation, 0.0f, 0.0f, 1.0f);
	
	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	gluSphere(quadric, moon.radius * planetSizeScale, 30, 30);

	glPopMatrix();
}

// render this planets orbit circle
void Moon::renderOrbit(Moon moon)
{
	// draw a line strip
	glBegin(GL_LINE_STRIP);

	// loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
	{
		glVertex3f(sin(angle) * moon.distanceFromPlanet * distanceScale, cos(angle) * moon.distanceFromPlanet * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, moon.distanceFromPlanet * distanceScale, 0.0f);

	glEnd();
}