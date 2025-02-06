#version 330 core

// Input vertex data, different for all executions of this shader.
//Gets the data at attrib incdex 0
//converts it and stores it in aPos (Vec3)
layout(location = 0) in vec3 aPos;

//varaible to hold data to pass
//uniform float x;
//uniform float y;
//uniform float z;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	//vec3 newPos = vec3(aPos.x + x, aPos.y + y, aPos.z);
	// gl_Position is a special variable a variable that holds the final position of your vertex.
	//gl_Position = vec4(newPos, 1.0);
	
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
}