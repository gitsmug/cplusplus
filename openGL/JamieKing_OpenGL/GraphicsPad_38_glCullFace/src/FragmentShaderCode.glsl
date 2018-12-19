#version 430

out vec4 daColor;
in vec3 theColor; // out from vertex shader

void main()
{
	daColor = vec4(theColor, 1.0);
}