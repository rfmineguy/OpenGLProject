//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_CAMERA_H
#define OPENGLPROJECT_CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera {
public:
    Camera(glm::vec3 pos, glm::vec3 target);
    ~Camera();
    void Update(float dt);
    void LookAt(glm::vec3 position);
    glm::mat4 GetProjView() {
        return m_Proj * m_View;
    }

    glm::vec3 m_CamPos;
    glm::vec3 m_CameraFront = glm::vec3(0, 0, -1);
private:
    glm::vec3 m_TargetPos;
    glm::vec3 m_Up = glm::vec3(0, 1, 0);
    glm::vec3 m_Direction;
    glm::vec3 m_CameraRight;
    glm::vec3 m_CameraUp = glm::vec3(0, 1, 0);

    glm::mat4 m_Proj = glm::perspective(glm::radians(45.f), 960.f / 540.f, 0.1f, 100.f);
public:
    glm::mat4 m_View = glm::mat4(1.0);
};
#endif //OPENGLPROJECT_CAMERA_H
