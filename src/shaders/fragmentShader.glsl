#version 330 core
out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float smileyValue;

void main()
{
    vec2 invertedYCoord = vec2(TexCoord.x,TexCoord.y);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, invertedYCoord), smileyValue);//* vec4(VertexColor* 2);
    //FragColor=vec4(abs(VertexColor.x), abs(VertexColor.y), abs(VertexColor.z),1.f);
}