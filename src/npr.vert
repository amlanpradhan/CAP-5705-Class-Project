void main()
{
	//gl_Position = gl_Vertex;
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
}