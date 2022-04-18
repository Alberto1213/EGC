#pragma once

#include "components/simple_scene.h"
namespace implemented
{
    class Camera
    {
    public:
        Camera()
        {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            Set(position, center, up);
        }

        ~Camera()
        { }

        // Update camera
        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            // Translates the camera using the `dir` vector computed from
            // `forward`. Movement will always keep the camera at the same
            // height. For example, if you rotate your head up/down, and then
            // walk forward, then you will still keep the same relative
            // distance (height) to the ground!
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            // TODO(student): Translate the camera using the `forward` vector.
            // What's the difference between `TranslateForward()` and
            // `MoveForward()`?
            position += forward * distance;
        }

        void TranslateUpward(float distance)
        {
            // TODO(student): Translate the camera using the `up` vector.
            position += up * distance;
        }

        void TranslateRight(float distance)
        {
            // TODO(student): See instructions below. Read the entire thing!
            // You need to translate the camera using the `right` vector.
            // Usually, however, translation using camera's `right` vector
            // is not very useful, because if the camera is rotated around the
            // `forward` vector, then the translation on the `right` direction
            // will have an undesired effect, more precisely, the camera will
            // get closer or farther from the ground. The solution is to
            // actually use the projected `right` vector (projected onto the
            // ground plane), which makes more sense because we will keep the
            // same distance from the ground plane.
            glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
            position += dir * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            // TODO(student): Compute the new `forward` and `up` vectors.
            // Don't forget to normalize the vectors! Use `glm::rotate()`.
           // forward = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1))));
           // up = glm::normalize(glm::cross(right, forward));

            // Rotation matrix
            glm::mat4 rot_mat = glm::rotate(glm::mat4(1.f), angle, right);

            // New forward (vec4)
            glm::vec4 new_fwd = glm::normalize(rot_mat * glm::vec4(forward, 1));

            // Extract fwd (vec3)
            forward = glm::vec3(new_fwd);

            // Up vector
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OY(float angle)
        {
            // TODO(student): Compute the new `forward`, `up` and `right`
            // vectors. Use `glm::rotate()`. Don't forget to normalize the
            // vectors!
            forward = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1))));
            right = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1))));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle)
        {
            // TODO(student): Compute the new `right` and `up`. This time,
            // `forward` stays the same. Use `glm::rotate()`. Don't forget
            // to normalize the vectors!
            right = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 1))));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OX(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OX axis. Use `distanceToTarget` as translation distance.
            position += forward * distanceToTarget;
            RotateFirstPerson_OX(angle);
            position -= forward * distanceToTarget;
        }

        void RotateThirdPerson_OY(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OY axis.
            position += forward * distanceToTarget;
            RotateFirstPerson_OY(angle);
            position -= forward * distanceToTarget;
        }

        void RotateThirdPerson_OZ(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OZ axis.
            position += forward * distanceToTarget;
            RotateFirstPerson_OZ(angle);
            position -= forward * distanceToTarget;
        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}
namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void display(float length, float height);

        // TODO(student): Class variables go here
        glm::mat4 headMatrix;
        glm::mat4 torsoMatrix;
        glm::mat4 legMatrix1;
        glm::mat4 legMatrix2;
        glm::mat4 armMatrix1;
        glm::mat4 armMatrix2;
        glm::mat4 projectile;
        glm::mat4 floor[1000];
        glm::mat4 ceil[1000];
        glm::mat4 wall[1000];
        glm::mat4 enemyMatrix[400];
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 position;
        glm::mat4 View, FinalView;
        glm::mat4 projectionMatrix;
        glm::mat4 healthMatrix;
        glm::mat4 timeMatrix;
        bool renderCameraTarget;
        implemented::Camera* camera;
        float fov = 60;
        float orthoDelta = 0;

    };
}   // namespace m1
