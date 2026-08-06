#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 view_pos;

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};


uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main(){
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(light.position - FragPos);
    
    float diff = max(dot(norm,light_dir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));
    
    vec3 view_dir = normalize(view_pos - FragPos);
    vec3 reflect_dir = normalize(reflect(-light_dir,norm));
    
    float spec = pow(max(dot(view_dir,reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular );
    

    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}