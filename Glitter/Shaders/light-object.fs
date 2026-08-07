#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 view_pos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


uniform Material material;

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cut_off;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SpotLight spot_light;




struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dir_light;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 view_dir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 view_dir);

void main(){
    vec3 result = vec3(0.0f);
    vec3 view_dir = normalize(view_pos - FragPos);
    result += calcDirLight(dir_light, Normal, view_dir);
    result += calcSpotLight(spot_light, Normal, view_dir);
    
    FragColor = vec4(result, 1.0f);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 view_dir){
     vec3 result;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - FragPos);
    
    float theta = dot(light.direction, normalize(-light_dir));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off)/epsilon, 0.0f, 1.0f);
    
    float diff = max(dot(norm,light_dir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

    
    vec3 reflect_dir = normalize(reflect(-light_dir,norm));
    
    float spec = pow(max(dot(view_dir,reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));
    

    diffuse *= intensity;
    specular *= intensity;
    
    result = ambient + diffuse + specular;
    
    return result;
}   



vec3 calcDirLight(DirLight light, vec3 normal, vec3 view_dir){
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(-light.direction);
    
    float diff = max(dot(norm,light_dir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));
    
    vec3 reflect_dir = normalize(reflect(-light_dir,norm));
    
    float spec = pow(max(dot(view_dir,reflect_dir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));
    

    
    vec3 result = ambient + diffuse + specular;
    return result;
}