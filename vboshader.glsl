#version 440

struct Particle{
	vec4 pos;
	vec3 vel;
	vec4 color;
};

layout(std140, binding=0) buffer particle{
    Particle p[];
};

uniform float time;
layout(local_size_x = 20, local_size_y = 1, local_size_z = 1) in;
void main(){
    int ix = int(gl_GlobalInvocationID.x);
    int wd = int(gl_GlobalInvocationID.y);

	float Wc = 1350/2;
	float Hc = 1080/2;

	float x = (p[ix].pos.x);
	float y = (p[ix].pos.y);
	float z = (p[ix].pos.z);
	float w = p[ix].pos.w;

	float velx = p[ix].vel.x;
	float vely = p[ix].vel.y;
	float velz = p[ix].vel.z;

	float xmid = x - Wc;
	float ymid = y - Hc;

	float r = p[ix].color.r;
	float g = p[ix].color.g;
	float b = p[ix].color.b;
	float a = p[ix].color.a;

	float dt = 0.01;
	float ax = velx - 10*xmid;
	float ay = vely - 10*(g-r)*ymid*z;
	float az = velz*velx + vely*vely - 100*(r/g);

	velx += dt*ax;
	vely += dt*ay;
	velz += dt*az;

	p[ix].pos.x = x + dt*velx;
        p[ix].pos.y = y + dt*vely;
        p[ix].pos.z = z + dt*velz;

	p[ix].color.r = mod(r + .01*(x/y), 1);
	p[ix].color.g = mod(g - .01*vely/velx, 1);
	p[ix].color.b = mod(b, 1);
	p[ix].color.a = 1;
	
}
