#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 result;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 object_color;
uniform vec3 view_pos;

void main(){
    gl_Position = projection * view * model * vec4(aPos,1.0);
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal; // Expensive operation, move to cpu
    FragPos = vec3(model * vec4(aPos,1.0));
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * light_color;
    
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);
    
    float diffuse_strength = 1.0f;
    float diff = max(dot(norm,light_dir), 0.0f);
    vec3 diffuse = diffuse_strength * diff * light_color;
    
    float specular_strength = 0.5f;
    vec3 view_dir = normalize(view_pos - FragPos);
    vec3 reflect_dir = normalize(reflect(-light_dir,norm));
    
    float spec = pow(max(dot(view_dir,reflect_dir), 0.0), 32);
    vec3 specular = spec * specular_strength * light_color;
    

    
    vec3 result = (ambient + diffuse + specular) * object_color;
}