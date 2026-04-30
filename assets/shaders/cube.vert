#version 330 core

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform float xOffset;
uniform float yOffset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPos = model * vec4(aPos,1.0);
	gl_Position = projection * view * worldPos + vec4(xOffset, yOffset, 0.0, 0.0);

	fragPos = worldPos.xyz;
	texCoord = aTexCoord;
	normal = mat3(transpose(inverse(model))) * aNormal;
};