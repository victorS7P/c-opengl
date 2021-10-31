#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec2 text;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 vColor;
out vec2 vText;

void main(){
   gl_Position = projection * view * model * vec4(pos, 1.0f);

   vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
   vText = text;
}
