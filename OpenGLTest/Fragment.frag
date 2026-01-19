#version 330 core
out vec4 FragColor;
  
uniform vec3 centre;
uniform float radius;
uniform vec3 SphereColor;
uniform vec2 ScreenRes;

uniform vec3 lightPos;



float hitSphere(vec3 center, float radius, vec3 rayOrigin, vec3 rayDirection){
    vec3 CentreDiff = rayOrigin - center;
    float a = dot(rayDirection, rayDirection);
    float b = 2.0 * dot(CentreDiff, rayDirection);
    float c = dot(CentreDiff, CentreDiff) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;
    if (discriminant > 0.0){
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
    else{
        return -1.0;
    }
    }

void castRay(vec2 uv){
    vec3 rayOrigin = vec3(0.0, 0.0, 0.0);
    vec3 rayDirection = normalize(vec3(uv, -1.0));
    float t = hitSphere(centre, radius, rayOrigin, rayDirection);
    if (t > 0.0){
    vec3 hitPoint = rayOrigin + t * rayDirection;
    vec3 normal = normalize(hitPoint - centre);
    vec3 lightDir = normalize(lightPos - hitPoint);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 ambient = 0.1 * SphereColor;
    vec3 color = ambient + SphereColor * diff * vec3(1.0,1.0,1.0);
    FragColor = vec4(color, 1.0);

    }
    else{
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}




void main()
{
    vec2 uv = (gl_FragCoord.xy / ScreenRes) * 2.0 - 1.0;
    float aspectRatio = ScreenRes.x / ScreenRes.y;
    uv.x *= aspectRatio;

    castRay(uv);
}