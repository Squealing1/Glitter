#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 object_color;

void main(){
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * light_color;
    
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);
    
    float diff = max(dot(norm,light_dir), 0.0f);
    vec3 diffuse = diff * light_color;

    
    vec3 result = (ambient + diffuse) * object_color;
    FragColor = vec4(result, 1.0f);
}