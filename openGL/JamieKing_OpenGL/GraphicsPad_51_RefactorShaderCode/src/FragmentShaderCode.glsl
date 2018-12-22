#version 430

out vec4 daColor;
in vec3 normalWorld; // out from vertex shader
in vec3 vertexPositionWorld; // out from vertex shader

uniform vec3 lightPositionWorld;

void main()
{
	vec3 lightVector = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVector, normalize(normalWorld));
	daColor = vec4(brightness, brightness, brightness, 1.0);
}