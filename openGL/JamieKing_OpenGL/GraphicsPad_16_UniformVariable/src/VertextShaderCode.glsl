#version 430

// 0 corresponds to 0 in glVertexAttribPointer(0, ...
// vec2 corresponds to glVertexAttribPointer(0, 3, ...
in layout(location=0) vec3 position;
// =1 is the index of the RGB points in verts.
in layout(location=1) vec3 vertexColor;

uniform vec3 dominatingColor; // uniform is same for all vertex calls
uniform float yFlip;

out vec3 theColor;

void main()
{
	gl_Position = vec4(position, 1.0);
	gl_Position.y = gl_Position.y * yFlip;

	//theColor = vertexColor;
	theColor = dominatingColor;
};