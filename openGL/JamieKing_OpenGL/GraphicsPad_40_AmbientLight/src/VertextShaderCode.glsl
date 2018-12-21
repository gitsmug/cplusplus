#version 430

// 0 corresponds to 0 in glVertexAttribPointer(0, ...
// vec2 corresponds to glVertexAttribPointer(0, 3, ...
in layout(location=0) vec3 position;
// =1 is the index of the RGB points in verts.
in layout(location=1) vec3 vertexColor;
uniform vec3 ambientLight;

uniform mat4 fullTrasnformMatrix;

out vec3 theColor;

void main()
{
	vec4 v = vec4(position, 1.0);
	gl_Position = fullTrasnformMatrix * v;

	//theColor = vertexColor * ambientLight;
	theColor = ambientLight;
};