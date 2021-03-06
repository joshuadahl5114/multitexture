#version 150

uniform sampler2D texture0;

in vec2 texCoord0;

out vec4 outColor;

void main(void) {
	//Sample the texture
	outColor = texture(texture0, texCoord0.st);	

	//If the alpha component is too low then discard
	//this fragment
	if (outColor.a < 0.1) {
		discard;
	}
}
