#version 430

out vec4 daColor;
in vec3 theNormal; // out from vertex shader
in vec3 thePosition; // out from vertex shader

uniform vec3 lightPosition;

void main()
{
	vec3 lightVector = normalize(lightPosition - thePosition);
	float brightness = dot(lightVector, theNormal);
	daColor = vec4(brightness, brightness, brightness, 1.0);
}