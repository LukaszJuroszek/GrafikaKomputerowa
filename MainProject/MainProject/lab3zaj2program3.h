#pragma once

void gltAddVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);

void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);

// Scales a vector by a scalar
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
{
	vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale;
}
