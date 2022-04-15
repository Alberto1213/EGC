#pragma once

#include "components/simple_scene.h"
#include <math.h>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:

        void Init() override;

     private:
        void FrameStart() override;
        
        void Update(float deltaTimeSeconds) override;
        
        void OnInputUpdate(float deltaTime, int mods) override;
        
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

        void OnWindowResize(int width, int height) override;

     protected:
        float localX, localY;
        float unghi;

        float time_1 = -1, time_2 = -1, time_3 = -1, time_4 = -1;
        float x_res, y_res, x_stanga, y_stanga, x_dreapta, y_dreapta, resolution_x, resolution_y, X_jucator, Y_jucator;

        //coordonatele gloantelor
        float x_glont1, y_glont1;
        float x_glont2, y_glont2;
        float x_glont3, y_glont3;
        float x_glont4, y_glont4;

        //unghiurile gloantelor
        float unghi1, unghi2, unghi3, unghi4;

        float xrel_glont1, yrel_glont1;
        float xrel_glont2, yrel_glont2;
        float xrel_glont3, yrel_glont3;
        float xrel_glont4, yrel_glont4;
        //pozitiile relative ale  gloantelor

        int viteza1 = 1;
        int viteza2 = 1;
        int viteza3 = 1;
        int viteza4 = 1;
        // viteza gloantelor

        int glont1_desen = 1;
        int glont2_desen = 1;
        int glont3_desen = 1;
        int glont4_desen = 1;

        //coordonatele inamiciilor
        float x_inamic1 = 0, y_inamic1 = 0;
        float x_inamic2 = 0, y_inamic2 = 0;

        //deplasarea inamiciilor
        float x_inamicf1, y_inamicf1;
        float x_inamicf2, y_inamicf2;

        // unghiurile inamiciilor
        float unghi_inamic1 = 0;
        float unghi_inamic2 = 0;

        //flag pt desenarea inamicilor,in caz ca dispar
        int ok_inamic1 = 1;
        int ok_inamic2 = 1;

        int inamic1_desen = 1, inamic2_desen2 = 1;

        float x1_local, y1_local;
        float x2_local, y2_local;

        float dt = 3;

        int viata = -400;
        int experienta = 0;
        int gen = 25;


        glm::vec3 cam_jucator;
        glm::vec3 colt = glm::vec3(0, 0, 0);

        glm::mat3 Mat_map;

        glm::mat3 Mat_wall;
        glm::mat3 Mat_wall2;
        glm::mat3 Mat_wall3;
        glm::mat3 Mat_model;

        glm::mat3 MatLeft_model;
        glm::mat3 MatRight_model;

        glm::mat3 Mat_glont1;
        glm::mat3 Mat_glont2;
        glm::mat3 Mat_glont3;
        glm::mat3 Mat_glont4;

        glm::mat3 Mat_obstacol1;
        glm::mat3 Mat_obstacol2;
        glm::mat3 Mat_obstacol3;

        glm::mat3 Mat_health;
        glm::mat3 Mat_health2;

        glm::mat3 Mat_experienta;

        glm::mat3 Mat_inamic1;
        glm::mat3 Mat_inamic2;

        glm::mat3 mousePosition;

        float translateX, translateY;
        float scaleX, scaleY;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
