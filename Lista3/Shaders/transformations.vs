#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 finalColor;

uniform int modelCode;
uniform mat4 model1;
uniform mat4 model2;
uniform mat4 model3;
uniform mat4 projection;

void main()
{
    if (modelCode == 1) {
        gl_Position = projection * model1 * vec4(position, 1.0f);
    }
    else if (modelCode == 2) {
        gl_Position = projection * model2 * vec4(position, 1.0f);
    }
    else {
        gl_Position = projection * model3 * vec4(position, 1.0f);
	}
    finalColor = vec4(color,1.0);
}