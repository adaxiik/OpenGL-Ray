#version 330 core
out vec4 FragColor;
uniform vec2 res;
uniform float time;

#define steps 128
#define hitDist 0.01
#define maxDist 100.0

float sphere(vec3 point, vec3 coords, float radius) {
   return (length( point - coords) - radius);
}
float box(vec3 point, vec3 coords, vec3 size) {
   return length(max(abs(point + coords) - size, 0.0));
}

float map(vec3 p) {
   float sphere1 = sphere(p, vec3(0.0, 0.0, -2.0), 1.0);
   float box1 = box(p, vec3(0.0, -0.5, 0), vec3(1.0));
   return min(min(box1,p.y+0.5),sphere1);
}
vec3 calculateNormal(vec3 p) {
   vec2 step = vec2(0.001, 0.0);
   float gradientX = map(p + step.xyy) - map(p - step.xyy);
   float gradientY = map(p + step.yxy) - map(p - step.yxy);
   float gradientZ = map(p + step.yyx) - map(p - step.yyx);
   return normalize(vec3(gradientX, gradientY, gradientZ));
}


vec3 rayMarch(vec3 rayOrigin, vec3 rayDirection){
   float distanceTraveled = 0.0;
   vec3 lightPos = vec3(2.0, -5.0, 3.0);
   for(int i = 0; i < steps; i++){
      if(distanceTraveled > maxDist){
         return vec3(0.0, 0.0, 0.0);
      }
      vec3 currentPos = rayOrigin + rayDirection * distanceTraveled;
      float closestDistace = map(currentPos);
      
      if(closestDistace < hitDist){
         vec3 normal = calculateNormal(currentPos);
         vec3 dirToLight = normalize(currentPos - lightPos);
         float lightIntensity = max(dot(normal, dirToLight), 0.0);
         return vec3(1.0)*lightIntensity;
      }

      distanceTraveled += closestDistace;
   }
}


vec3 lookAt(vec2 uv, vec3 camera, vec3 target, float z){
   vec3 up = vec3(0.0, 1.0, 0.0);
   vec3 forward = normalize(target - camera);
   vec3 right = normalize(cross(up, forward));
   vec3 up_ = cross(forward, right);
   vec3 c = camera + forward * z;
   vec3 i = c + right * uv.x + up_ * uv.y;
   return normalize(i - camera);
}

void main()
{
   vec2 uv = (gl_FragCoord.xy-.5*res)/res.y;

   vec3 cameraPos = vec3(5.0*sin(time), 3.0, 5*cos(time));
   
   vec3 view = lookAt(uv, cameraPos, vec3(0.0, 0.0, 0.0), 0.7);
   FragColor = vec4(rayMarch(cameraPos,view), 1.0f);
}
