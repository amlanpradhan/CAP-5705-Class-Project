varying vec4 diffuse, ambientGlobal, ambient;
varying vec3 normal, lightDirection, halfVector, lightDir;

void main()
{
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	float NdotL, NdotHV;
	vec4 color = ambientGlobal;
	NdotL = max(dot(normal, lightDirection), 0.0);
	if(NdotL > 0.0)
	{
		color += (diffuse*NdotL + ambient);
	}
	gl_FragColor = color;
}