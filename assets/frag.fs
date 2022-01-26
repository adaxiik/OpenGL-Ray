#version 330 core
out vec4 FragColor;
uniform vec2 res;
uniform float time;

#define steps 256
#define hitDist 0.005
#define maxDist 10000.0

//https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
float subtraction(float d1, float d2 ){   
   return max(-d1,d2); 
}
float intersection( float d1, float d2 ){ 
   return max(d1,d2); 
}
float smoothUnion( float d1, float d2, float k ) {
   float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
   return mix( d2, d1, h ) - k*h*(1.0-h); 
}
float smoothSubtraction( float d1, float d2, float k ) {
   float h = clamp( 0.5 - 0.5*(d2+d1)/k, 0.0, 1.0 );
   return mix( d2, -d1, h ) + k*h*(1.0-h); 
}   

   
float sphere(vec3 point, vec3 coords, float radius) {
   return (length( point - coords) - radius);
}
float box(vec3 point, vec3 coords, vec3 size) {
   return length(max(abs(point + coords) - size, 0.0));
}

float map(vec3 p) {
   vec3 c = vec3(5.0);
   vec3 q = mod(p+0.5*c,c)-0.5*c; //infinite repetitions

   float sphere1 = sphere(q, vec3(0.0, 0.0, 0.0), 1.0);
   float box1 = box(q, vec3(0.0, 0.0, 0.0), vec3(1.0));
   //float box2 = box(p, vec3(1.0, -0.5, 0), vec3(1.0));
   //return min(smoothSubtraction(sphere1,box1,0.5),p.y+0.5);
   //return subtraction(box1,box2);
   return sphere1;
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
   //vec3 lightPos = vec3(3.0*sin(time/2), 2.0, 4.0*cos(time/2));
   vec3 lightPos = vec3(3.0, 3.0, 1.0);
   vec3 color = vec3(1.0);
   for(int i = 0; i < steps; i++){
      if(distanceTraveled > maxDist){
         return vec3(0.0, 0.0, 0.0);
      }
      vec3 currentPos = rayOrigin + rayDirection * distanceTraveled;
      float closestDistace = map(currentPos);
      
      if(closestDistace < hitDist){
         vec3 normal = calculateNormal(currentPos);
         vec3 dirToLight = normalize(currentPos - lightPos);
         float lightIntensity = max(dot(-normal, dirToLight), 0.0);
         
         return normal;
         //return color*lightIntensity;
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
   //vec3 cameraPos = vec3(4.0, 3.0, 3.0);
   
   vec3 view = lookAt(uv, cameraPos, vec3(0.0, 3.0,0.0), 0.7);
   FragColor = vec4(rayMarch(cameraPos,view), 1.0f);
}
