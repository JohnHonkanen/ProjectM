#version 330

out vec4 FragColor;

uniform sampler2D texture0;

in vec2 out_UV;
uniform float alpha;

void main(void) {
	vec4 texture = texture(texture0, out_UV);
	if(texture.a < 0.5)
	{
		discard;
	}
	FragColor = texture;
	FragColor.a = alpha;
}