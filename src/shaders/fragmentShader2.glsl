#version 330 core
out vec4 FragColor;

in vec4 VertexColor;

uniform vec4 multiplicator;

void main()
{
    FragColor=vec4(abs(VertexColor.x) * multiplicator.x, abs(VertexColor.y)* multiplicator.y, abs(VertexColor.z)* multiplicator.z,1.f);
}