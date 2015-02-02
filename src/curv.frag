varying vec3 curvature, minCurvature;

// The reason behind encoding here is that we need to store the 2 vec3 values inside a single vec4 value,
// so, converting vec3 value to vec2 value by the following encoding scheme. 
vec2 encode(vec3 n)
{
	return normalize(n.xy) * sqrt(n.z * 0.5 + 0.5);
}

// Encoding the 2 curvature directions and storing them in the fragment color.
void main()
{
	gl_FragColor = vec4(encode(curvature),encode(minCurvature));
}