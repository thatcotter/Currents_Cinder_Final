#version 150

uniform sampler2D uTex0; // object texture
uniform sampler2D uTex1; // depth map
uniform sampler2D uTex2; // dig canvas fbo
uniform float uBaseline;
uniform float uThreshold;
uniform float uSmooth;

in vec2 TexCoord0;

out vec4 oColor;

void main(void) {
	oColor = texture(uTex0, TexCoord0);
	float depth = texture(uTex1, TexCoord0).r + texture(uTex2, TexCoord0).r + uBaseline;
	float depthMask = smoothstep(uThreshold - uSmooth / 2, uThreshold + uSmooth / 2, depth);
	oColor.a *= depthMask;
}
