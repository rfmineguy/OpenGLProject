//
// Created by RFMinePC on 2/14/2021.
//

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Camera.h"

#include "handlers/InputHandler.h"

Camera::Camera(glm::vec3 pos, glm::vec3 target)
    :m_CamPos(pos), m_TargetPos(target) {

    LookAt(m_CamPos);
    m_Direction = glm::normalize(m_CamPos - m_TargetPos);
    m_CameraRight = glm::normalize(glm::cross(m_Up, m_Direction));
    m_CameraUp = glm::cross(m_Direction, m_CameraRight);

    m_View = glm::lookAt(pos, target, m_Up);
}

Camera::~Camera() {

}

void Camera::Update(float dt) {
    const float camSpeed = 2.5f * dt;
    //Keyboard Input
    {
        //W (FORWARDS)
        if (Input.keys[87]) {
            m_CamPos += camSpeed * m_CameraFront;
        }
        //S (BACKWARDS)
        if (Input.keys[83]) {
            m_CamPos -= m_CameraFront * camSpeed;
        }
        //A (LEFT)
        if (Input.keys[65]) {
            m_CamPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * camSpeed;
        }
        //D (RIGHT)
        if (Input.keys[68]) {
            m_CamPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * camSpeed;
        }
        //Q (UP)
        if (Input.keys[81]) {
            m_CamPos += m_CameraUp * camSpeed;
        }
        //E (DOWN)
        if (Input.keys[69]) {
            m_CamPos -= m_CameraUp * camSpeed;
        }
    }

    //Mouse Input
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(Input.yaw)) * cos(glm::radians(Input.pitch));
        direction.y = sin(glm::radians(Input.pitch));
        direction.z = sin(glm::radians(Input.yaw)) * cos(glm::radians(Input.pitch));
        m_CameraFront = glm::normalize(direction);
    }
    LookAt(m_CamPos);
}

void Camera::LookAt(glm::vec3 position) {
    m_CamPos = position;
    m_View = glm::lookAt(m_CamPos, m_CamPos + m_CameraFront, m_CameraUp);
}

