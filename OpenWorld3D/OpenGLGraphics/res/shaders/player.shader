#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colorcoord;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec3 normal;

out vec3 vertex_position;
out vec3 vertex_color;
out vec2 vertex_texcoord;
out vec3 vertex_normal;

//uniform mat4 u_MatrixViewProjection; 
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_PerspectiveProjection;

void main()
{
	vertex_position = vec4(u_ModelMatrix * vec4(position, 1.f)).xyz;
	vertex_color = colorcoord;
	vertex_texcoord = texcoord;
	vertex_normal = mat3(u_ModelMatrix) * normal;

	gl_Position = u_PerspectiveProjection * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.f);
};

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec3 vertex_position;
in vec3 vertex_color;
in vec2 vertex_texcoord;
in vec3 vertex_normal;

uniform vec4 uniformColor;
layout (binding = 1) uniform sampler2D uniformTexture;
uniform vec3 lightPos;
uniform vec3 camPosition;

void main()
{


	vec3 lightColor = vec3(0.5f, 1.f, 0.8f);
	//Ambient light
	vec3 darkAmbientColor = vec3(0.1f, 0.1f, 0.1f);

	//Diffuse light
	vec3 positionToLightNormalizedDirectionalVec = normalize(lightPos - vertex_position);
	float diffuse = clamp(dot(positionToLightNormalizedDirectionalVec, vertex_normal), 0, 1);
	vec3 diffuseColor = lightColor * diffuse;

	//Specular light
	vec3 lightToPositionNormalizedDirectionVec = normalize(vertex_position - lightPos);
	vec3 reflectNormalizedDirectionVec = normalize(reflect(lightToPositionNormalizedDirectionVec, normalize(vertex_normal)));
	vec3 positionToViewDirection = normalize(camPosition - vertex_position);
	float specularConstat = pow(max(dot(positionToViewDirection, reflectNormalizedDirectionVec), 0), 30);//higher the pow higher the range
	vec3 specularLight = lightColor * specularConstat;


	//Texture light
	color = texture(uniformTexture, vertex_texcoord)  * 
		(vec4(darkAmbientColor, 1.f) + vec4(diffuseColor, 1.f) + vec4(specularLight, 1.f)); //lights

};