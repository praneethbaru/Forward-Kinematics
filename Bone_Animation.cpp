#include "Bone_Animation.h"
int i, j, k;


Bone_Animation::Bone_Animation()
{

}


Bone_Animation::~Bone_Animation()
{
}

void Bone_Animation::init()
{
	root_position = { 2.0f,0.0f,2.0f };

	scale_vector =
	{
		{1.0f,1.0f,1.0f},
		{0.5f,4.0f,0.5f},
		{0.5f,3.0f,0.5f},
		{0.5f,2.0f,0.5f}
	};

	rotation_degree_vector =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};

	colors =
	{
		{0.7f,0.0f,0.0f,1.0f},
		{0.7f,0.7f,0.0f,1.0f},
		{0.7f,0.0f,0.7f,1.0f},
		{0.0f,0.7f,0.7f,1.0f}
	};
	reset();
}

void Bone_Animation::update(float delta_time)
{

}


/*****************************************************************
* This function rotates BONE 1 and all bones attached over it.
*****************************************************************/
void Bone_Animation::bone_1_rotate()
{

	bone_1_mat = rotate_1(bone_1_mat, bone_1_rotation);
	bone_2_mat = rotate_1(bone_2_mat, bone_1_rotation);
	bone_3_mat = rotate_1(bone_3_mat, bone_1_rotation);

	printf("BONE 1\n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%f ", bone_1_mat[i][j]);
		}
		printf("\n");
	}

	printf("BONE 2\n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%f ", bone_2_mat[i][j]);
		}
		printf("\n");
	}

	printf("BONE 3\n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%f ", bone_3_mat[i][j]);
		}
		printf("\n");
	}
}

/*****************************************************************
* This function rotates BONE 2 and all bones attached over it.
*****************************************************************/
void Bone_Animation::bone_2_rotate()
{
	bone_2_mat = rotate_2(bone_2_mat, bone_2_rotation);
	bone_3_mat = rotate_2(bone_3_mat, bone_2_rotation);
}


/*****************************************************************
* This function rotates BONE 3
*****************************************************************/
void Bone_Animation::bone_3_rotate()
{
	bone_3_mat = rotate_3(bone_3_mat, bone_3_rotation);
}

/*****************************************************************
* This function rotates any given matrix passed
* as parameter in given x,y,z orientations relative to BONE 2.
*****************************************************************/
glm::mat4 Bone_Animation::rotate_3(glm::mat4 bone, glm::vec3 rotationVector)
{
	glm::mat4 result_mat;
	float angle_x, angle_y, angle_z;

	angle_x = glm::radians(rotationVector.x);
	angle_y = glm::radians(rotationVector.y);
	angle_z = glm::radians(rotationVector.z);

	// Translating to the joint - tip of Bone 2
	bone[3][0] = bone[3][0] - bone_2_mat[3][0];
	bone[3][1] = bone[3][1] - bone_2_mat[3][1] - (scale_vector[2][1]/2);
	bone[3][2] = bone[3][2] - bone_2_mat[3][2];

	// Rotating Y
	y = {
			{cos(angle_y), 0, -sin(angle_y), 0},
			{ 0, 1, 0, 0 },
			{ sin(angle_y), 0, cos(angle_y),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * y[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	//Rotating Z
	z = {
		{cos(angle_z), sin(angle_z), 0, 0},
		{ -sin(angle_z), cos(angle_z), 0, 0 },
		{ 0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * z[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Rotating X
	x = {
			{1, 0, 0, 0},
			{ 0, cos(angle_x), sin(angle_x), 0 },
			{ 0, -sin(angle_x), cos(angle_x),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * x[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	//Translating to its new position
	bone[3][0] = bone[3][0] + bone_2_mat[3][0];
	bone[3][1] = bone[3][1] + bone_2_mat[3][1] + (scale_vector[2][1]/2);
	bone[3][2] = bone[3][2] + bone_2_mat[3][2];

	return bone;
}

/*****************************************************************
* This function rotates any given matrix passed
* as parameter in given x,y,z orientations relative to BONE 1.
*****************************************************************/

glm::mat4 Bone_Animation::rotate_2(glm::mat4 bone, glm::vec3 rotationVector)
{
	glm::mat4 result_mat;
	float angle_x, angle_y, angle_z;

	angle_x = glm::radians(rotationVector.x);
	angle_y = glm::radians(rotationVector.y);
	angle_z = glm::radians(rotationVector.z);

	// Translating to the joint - tip of Bone 1
	bone[3][0] = bone[3][0] - bone_1_mat[3][0];
	bone[3][1] = bone[3][1] - bone_1_mat[3][1] - (scale_vector[1][1]/2);
	bone[3][2] = bone[3][2] - bone_1_mat[3][2];

	// Rotating Y
	y = {
			{cos(angle_y), 0, -sin(angle_y), 0},
			{ 0, 1, 0, 0 },
			{ sin(angle_y), 0, cos(angle_y),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * y[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Rotating Z
	z = {
		{cos(angle_z), sin(angle_z), 0, 0},
		{ -sin(angle_z), cos(angle_z), 0, 0 },
		{ 0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * z[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Rotating X
	x = {
			{1, 0, 0, 0},
			{ 0, cos(angle_x), sin(angle_x), 0 },
			{ 0, -sin(angle_x), cos(angle_x),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * x[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Translating to new position
	bone[3][0] = bone[3][0] + bone_1_mat[3][0];
	bone[3][1] = bone[3][1] + bone_1_mat[3][1] + (scale_vector[1][1]/2);
	bone[3][2] = bone[3][2] + bone_1_mat[3][2];

	return bone;
}

/*****************************************************************
* This function rotates any given matrix passed 
* as parameter in given x,y,z orientations relative to ROOT.
*****************************************************************/

glm::mat4 Bone_Animation::rotate_1(glm::mat4 bone, glm::vec3 rotationVector)
{
	glm::mat4 result_mat;
	float angle_x, angle_y, angle_z;

	angle_x = glm::radians(rotationVector.x);
	angle_y = glm::radians(rotationVector.y);
	angle_z = glm::radians(rotationVector.z);

	// Translating to the joint - tip of ROOT
	bone[3][0] = bone[3][0] - root_bone_mat[3][0];
	bone[3][1] = bone[3][1] - root_bone_mat[3][1] - (scale_vector[0][1]/2);
	bone[3][2] = bone[3][2] - root_bone_mat[3][2];

	// Rotating Y
	y = {
			{cos(angle_y), 0, -sin(angle_y), 0},
			{ 0, 1, 0, 0 },
			{ sin(angle_y), 0, cos(angle_y),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * y[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Rotating Z
	z = {
		{cos(angle_z), sin(angle_z), 0, 0},
		{ -sin(angle_z), cos(angle_z), 0, 0 },
		{ 0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * z[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Rotating X
	x = {
			{1, 0, 0, 0},
			{ 0, cos(angle_x), sin(angle_x), 0 },
			{ 0, -sin(angle_x), cos(angle_x),0},
			{0, 0, 0, 1}
	};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			result_mat[i][j] = 0;
			for (k = 0; k < 4; k++)
				result_mat[i][j] += bone[i][k] * x[k][j];
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			bone[i][j] = result_mat[i][j];
		}
	}

	// Translating to new position
	bone[3][0] = bone[3][0] + root_bone_mat[3][0];
	bone[3][1] = bone[3][1] + root_bone_mat[3][1] + (scale_vector[0][1]/2);
	bone[3][2] = bone[3][2] + root_bone_mat[3][2];

	return bone;
}

/*****************************************************************
* Reset function sets the position and orientation of all bones 
* to the initial position.
*****************************************************************/
void Bone_Animation::reset()
{
	//draw root bone
	root_bone_mat = glm::mat4(1.0f);
	root_bone_mat = glm::translate(root_bone_mat, glm::vec3(0, 0.5f, 0));
	root_bone_mat = glm::translate(root_bone_mat, root_position);


	//draw bone 1
	bone_1_mat = glm::mat4(1.0f);
	bone_1_mat = glm::scale(bone_1_mat, glm::vec3(scale_vector[1]));
	bone_1_mat = glm::translate(bone_1_mat, glm::vec3(root_position[0] / scale_vector[1].x, ((scale_vector[0].y + 0.5*(scale_vector[1].y)) / scale_vector[1].y), root_position[2] / scale_vector[1].z));

	//draw bone 2
	bone_2_mat = glm::mat4(1.0f);
	bone_2_mat = glm::scale(bone_2_mat, glm::vec3(scale_vector[2]));
	bone_2_mat = glm::translate(bone_2_mat, glm::vec3(root_position[0] / scale_vector[2].x, ((scale_vector[0].y + scale_vector[1].y + 0.5*(scale_vector[2].y)) / scale_vector[2].y), root_position[2] / scale_vector[2].z));

	//draw bone 3
	bone_3_mat = glm::mat4(1.0f);
	bone_3_mat = glm::scale(bone_3_mat, glm::vec3(scale_vector[3]));
	bone_3_mat = glm::translate(bone_3_mat, glm::vec3(root_position[0] / scale_vector[3].x, ((scale_vector[0].y + scale_vector[1].y + scale_vector[2].y + 0.5*(scale_vector[3].y)) / scale_vector[3].y), root_position[2] / scale_vector[3].z));
}


