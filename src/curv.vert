attribute vec3 curvatureDirection, minCurvatureDirection;
varying vec3 curvature, minCurvature;

// The main idea here is to store the curvature and min. curvature directions
// in the fragment color, so, we take in the direction values and normalize them
// and then the fragment shader takes in these values to store them in the color value
void main()
{
	curvature = normalize(vec3(gl_ModelViewMatrix * vec4(curvatureDirection, 0.0)));
	minCurvature = normalize(vec3(gl_ModelViewMatrix * vec4(minCurvatureDirection,0.0)));
	gl_Position = ftransform();
}