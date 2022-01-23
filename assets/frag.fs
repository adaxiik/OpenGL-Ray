#version 330 core
out vec4 FragColor;
uniform vec2 res;
void main()
{
   vec2 uv = (gl_FragCoord.xy-.5*res)/res.y;
   FragColor = vec4(uv, 0.0f, 1.0f);
}