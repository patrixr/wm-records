#version 150


//uniform float intensity;
//uniform mat4 modelViewProjectionMatrix;
//in vec4 position;

//void main()
//{
//   vec4 modifiedPosition = modelViewProjectionMatrix * position;
//    modifiedPosition.z -= position.y / 8; //intensity * 10.0;
//    gl_Position = modifiedPosition;
//}

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

// the time value is passed into the shader by the OF app.
uniform float intensity;

void main()
{
    // the sine wave travels along the x-axis (across the screen),
    // so we use the x coordinate of each vertex for the calculation,
    // but we displace all the vertex along the y axis (up the screen)/
    float displacementHeight = intensity * 50;
    float displacementY = sin(0 + (position.y / 100.0)) * displacementHeight;

    vec4 modifiedPosition = modelViewProjectionMatrix * position;
    //modifiedPosition.w = intensity * modifiedPosition.z * 4;
    //modifiedPosition.y -= displacementHeight;
    //modifiedPosition.z -= displacementHeight;
    gl_Position = modifiedPosition;
}