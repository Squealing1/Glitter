#version 330 core
out vec4 FragColor;

uniform vec3 light_color;
uniform vec3 object_color;

void main(){
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * light_color;
    vec3 result = ambient * object_color;
    FragColor = vec4(result, 1.0f);
}