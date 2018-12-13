

const char* vertexShaderCode =
	"#version 430\r\n"
	""
	// 0 corresponds to 0 in glVertexAttribPointer(0, ...
	// vec2 corresponds to glVertexAttribPointer(0, 2, ...
	"in layout(location=0) vec2 position;"
	""
	""
	"void main()"
	"{"
	"	gl_Position = vec4(position, 0.0, 1.0);"
	"}";

const char* fragmentShaderCode =
	"#version 430\r\n"
	""
	"out vec4 theColor;"
	""
	"void main()"
	"{"
	"	theColor = vec4(0.0, 1.0, 0.0, 1.0);"
	"}";