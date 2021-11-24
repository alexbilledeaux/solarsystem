/*Published under The MIT License (MIT)

See LICENSE.TXT*/

// Ryan Pridgeon COM2032 rp00091

#include "solarsystem.h"

SolarSystem::SolarSystem()
{
	
}

// calculate the positions of all planets and add a new state to their identities
void SolarSystem::calculatePositions(float time, int observerIndex)
{
	for (int i = 0; i < planetIdentities.size(); i++)
	{
		Planet planetAtNewPosition = Planet::calculatePosition(time, planetIdentities[i][observerIndex]);
		// Add new state to planet identity
		planetIdentities[i].push_back(planetAtNewPosition);
	}
}

// Add a planet identity and initial state
void SolarSystem::addPlanetIdentity(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	std::vector<Planet> planetIdentity = std::vector<Planet>();
	planetIdentity.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
	planetIdentities.push_back(planetIdentity);
}

// Add a moon to the specified planet
void SolarSystem::addMoon(int identityIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	Planet newState = Planet::addMoon(planetIdentities[identityIndex].back(), distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
	planetIdentities[identityIndex].push_back(newState);
}

// render the planets with opengl
void SolarSystem::render(int observerIndex)
{
	for (int i = 0; i < planetIdentities.size(); i++)
	{
		Planet::render(planetIdentities[i][observerIndex]);
	}
}


// render the drawing of the orbits
void SolarSystem::renderOrbits()
{
	for (int i = 0; i < planetIdentities.size(); i++)
	{
		Planet::renderOrbit(planetIdentities[i][0]);
	}
}

// get the position in 3d space units of the given planet (specified by its index in the list) and put it into the 3d vector vec
void SolarSystem::getPlanetPosition(int index, float* vec)
{
	Planet::getPosition(vec, planetIdentities[index].back());
}


// get the radius of the planet at the given index in the planets list
float SolarSystem::getRadiusOfPlanet(int index)
{
	return planetIdentities[index][0].getRadius();
}

int SolarSystem::getPlanetIdentitySize(int index)
{
	return planetIdentities[index].size();
}