#version 150

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;
uniform mat3 normal_matrix;

in vec3 a_Vertex;
in vec2 a_TexCoord0;

out vec4 color;
out vec2 texCoord0;

void main(void) 
{
	vec4 pos = modelview_matrix * vec4(a_Vertex, 1.0);
	
	color = vec4(1.0f, 1.0f, 1.0f, 0.3f);
	texCoord0 = a_TexCoord0;
	gl_Position = projection_matrix * pos;	
}
