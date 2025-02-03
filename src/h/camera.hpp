#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera3 {

    public:
        Camera3();
        ~Camera3();

        glm::vec3 getPosition() const;
        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;
        glm::mat4 getViewMatrix() const;
        glm::mat4 getRotationMatrix() const;
        void move (const glm::vec3 &offset);
        void lookAt(const glm::vec3 &target);
        void reset();


    private:
        glm::vec3 _position;
        glm::vec3 _right;
        glm::vec3 _up;
        glm::mat4 _rotationMatrix;
};


#endif // CAMERA_HPP