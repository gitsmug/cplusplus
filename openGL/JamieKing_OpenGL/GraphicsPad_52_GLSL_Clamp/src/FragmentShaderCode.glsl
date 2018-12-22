#version 430

out vec4 daColor;
in vec3 normalWorld; // out from vertex shader
in vec3 vertexPositionWorld; // out from vertex shader

uniform vec3 lightPositionWorld;
uniform vec4 ambientLight;

void main()
{
	vec3 lightVector = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVector, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

	// clamp puts end caps on the supplied value.
	daColor = clamp(diffuseLight, 0, 1) + ambientLight;
}