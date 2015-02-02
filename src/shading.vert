varying vec4 diffuse, ambientGlobal, ambient;
varying vec3 normal, lightDirection, halfVector;

void main()
{
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	normal = normalize(gl_Normal);
	lightDirection = vec3(0.0, 0.0, 1.0);

	gl_Position = ftransform();
}