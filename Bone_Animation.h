#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

class Bone_Animation
{
public:
	Bone_Animation();
	~Bone_Animation();

	void init();
	void update(float delta_time);
	void reset();

	void bone_1_rotate();
	void bone_2_rotate();
	void bone_3_rotate();

	glm::mat4 rotate_3(glm::mat4 bone, glm::vec3 rotationVector);
	glm::mat4 rotate_2(glm::mat4 bone, glm::vec3 rotationVector);
	glm::mat4 rotate_1(glm::mat4 bone, glm::vec3 rotationVector);

	glm::mat4 get_root_bone_mat() { return root_bone_mat; }
	glm::mat4 get_bone_1_mat() { return bone_1_mat; }
	glm::mat4 get_bone_2_mat() { return bone_2_mat; }
	glm::mat4 get_bone_3_mat() { return bone_3_mat; }


	glm::mat4 rotate_x(glm::mat4 bone, float angle);
	glm::mat4 rotate_y(glm::mat4 bone, float angle);
	glm::mat4 rotate_z(glm::mat4 bone, float angle);

public:

	// Here the head of each vector is the root bone
	std::vector<glm::vec3> scale_vector;
	std::vector<glm::vec3> rotation_degree_vector;
	std::vector<glm::vec4> colors;

	glm::vec3 root_position;
	glm::vec3 bone_1_rotation = { 0, 0, 0 };
	glm::vec3 bone_2_rotation = { 0, 0, 0 };
	glm::vec3 bone_3_rotation = { 0, 0, 0 };

	glm::vec3 bone_1_ori = { 0, 0, 0 };
	glm::vec3 bone_2_ori = { 0, 0, 0 };
	glm::vec3 bone_3_ori = { 0, 0, 0 };

	glm::mat4 root_bone_mat;
	glm::mat4 bone_1_mat;
	glm::mat4 bone_2_mat;
	glm::mat4 bone_3_mat;
	glm::mat4 x;
	glm::mat4 y;
	glm::mat4 z;

};

