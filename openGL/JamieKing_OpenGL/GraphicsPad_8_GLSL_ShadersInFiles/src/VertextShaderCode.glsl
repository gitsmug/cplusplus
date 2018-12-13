#version 430

// 0 corresponds to 0 in glVertexAttribPointer(0, ...
// vec2 corresponds to glVertexAttribPointer(0, 2, ...
in layout(location=0) vec2 position;
// =1 is the index of the RGB points in verts.
in layout(location=1) vec3 vertexColor;

out vec3 theColor;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	theColor = vertexColor;
};