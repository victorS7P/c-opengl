#version 330

uniform vec3 triangleColor;
uniform sampler2D triangleText;

in vec4 vColor;
in vec2 vText;

out vec4 color;

void main(){
  color = texture(triangleText, vText);
}
