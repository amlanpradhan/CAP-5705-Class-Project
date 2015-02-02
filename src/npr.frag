uniform sampler2D texSrc;
uniform sampler2D texCur;
uniform sampler2D tempTex;
uniform sampler2D edgeTex;

// Remember that we had stored the curvature directions through an encoding scheme.
// Here we are decoding the vector using a similar scheme to get back the curvature vectors
vec3 decode(vec2 n)
{
	vec3 normal;
	normal.z = dot(n, n) * 2.0 - 1.0;
	normal.xy = normalize(n) * sqrt(1.0 - normal.z * normal.z);
	return normal;
}

// The method to rotate the vector uv along the direction vector dir.
vec2 rotateDirections(vec2 dir, vec2 uv)					
{
	return vec2(dir.x * uv.x - dir.y * uv.y, dir.x * uv.y + dir.y * uv.x);
}

void main()
{
	// Background color  : Black
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

	vec4 edgeColor = texture2D(edgeTex, gl_TexCoord[0].st);
	if(edgeColor.r==1.0 && edgeColor.g==1.0 && edgeColor.b==1.0)
		color=color;
	else if(edgeColor.r > 0.0 || edgeColor.g > 0.0 || edgeColor.b > 0.0)
		color = -edgeColor;

	// Required for the object color, to identify whether the tex coordinate contains the object or not
	vec4 srcColor = texture2D(texSrc, gl_TexCoord[0].st);

	//gl_FragColor = srcColor;

	// In the source texture, we have the object red in the background black
	// So, we give the texture color only for a coordinate containing the object
	if(edgeColor.r > 0.0 || edgeColor.g > 0.0 || edgeColor.b > 0.0)
	{

		// Get the required curvature values from the curv texture object
		vec4 curvature = texture2D(texCur, gl_TexCoord[0].st);

		// Getting the curvature value
		vec3 curv = decode(curvature.xy);
		vec3 zDir = vec3(0.0,0.0,1.0);
		vec3 strokeDir = vec3(1.0,0.0,0.0);
		vec3 direction = curv - dot(curv, zDir)*zDir;

		// Getting the angle through which teh texture image has to be rotated
		float rotAngle = acos(dot(direction, strokeDir)/length(direction));

		// Rotating the texture image rotating through the given rotating angle
		//color += texture2D(tempTex, 5.0 * rotateDirections(vec2(cos(rotAngle), sin(rotAngle)), gl_TexCoord[0].st));

		//  Completing a sort of 3 way blending to give a more realistic feature
		color += texture2D(tempTex, 5.0 * rotateDirections(vec2(cos(0.2), sin(0.2)), gl_TexCoord[0].st));
		color += texture2D(tempTex, 5.0 * rotateDirections(vec2(cos(-2.6), sin(-2.6)), gl_TexCoord[0].st));

		// Darken the color to better simulate the pencil stroke color.
		color *= 0.6;
		color *= color;	
		color *= srcColor;

		gl_FragColor = color;
	}

}