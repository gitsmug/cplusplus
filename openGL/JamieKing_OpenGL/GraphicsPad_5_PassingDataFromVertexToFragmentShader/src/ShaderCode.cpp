

const char* vertexShaderCode =
	"#version 430\r\n"
	""
	// 0 corresponds to 0 in glVertexAttribPointer(0, ...
	// vec2 corresponds to glVertexAttribPointer(0, 2, ...
	"in layout(location=0) vec2 position;"
	// =1 is the index of the RGB points in verts.
	"in layout(location=1) vec3 vertexColor;"
	""
	"out vec3 theColor;"
	""
	"void main()"
	"{"
	"	gl_Position = vec4(position, 0.0, 1.0);"
	"	theColor = vertexColor;"
	"}";

const char* fragmentShaderCode =
	"#version 430\r\n"
	""
	"out vec4 daColor;"
	"in vec3 theColor;" // out from vertex shader
	""
	"void main()"
	"{"
	"	daColor = vec4(theColor, 1.0);"
	"}";