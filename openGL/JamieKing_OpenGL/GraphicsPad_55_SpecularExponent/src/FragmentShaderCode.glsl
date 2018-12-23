#version 430

out vec4 daColor;
in vec3 normalWorld; // out from vertex shader
in vec3 vertexPositionWorld; // out from vertex shader

uniform vec3 lightPositionWorld;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;

void main()
{
	// Diffuse
	vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
	float brightness = dot(lightVectorWorld, normalize(normalWorld));
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

	// Specular
	vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
	vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
	float specularity = dot(reflectedLightVectorWorld, eyeVectorWorld);
	specularity = pow(specularity, 8);
	vec4 specularLight = vec4(specularity, specularity, specularity, 1);
	//vec4 specularLight = vec4(0, 0, specularity, 1);

	daColor = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
	//daColor = clamp(specularLight, 0, 1);
}