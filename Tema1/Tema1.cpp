#include "lab_m1/Tema1/Tema1.h"
#include <math.h>

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;



void Tema1::Init()
{
    float lat_mapa = 2000;
    float lat_patrat = 50;
    float lat_mana = 15;

    glm::ivec2 resolution = window->GetResolution();

    auto camera = GetSceneCamera();

    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);

    glm::vec3 coltStanga = glm::vec3(0, 0.25, 0);

    glm::vec3 coltMapaStanga = glm::vec3(-1000, -1000, 0);

    x_res = (float)resolution.x/2;//se modifica in fuctie de modificarile facute asupra rezolutiei
    y_res = (float)resolution.y/2; // -||-
    
    resolution_x = x_res;
    resolution_y = y_res;

    camera->SetPosition(glm::vec3(0,0,50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    
    Mesh* Obstacol1 = object2D::CreateRectangle("Obstacol_1", coltMapaStanga, 300, 70, glm::vec3(0.3, 0.3, 0.3), true);

    Mesh* Obstacol2 = object2D::CreateRectangle("Obstacol_2", coltMapaStanga, 70, 300, glm::vec3(0.3, 0.3, 0.3), true);
    
    Mesh* Obstacol3 = object2D::CreateRectangle("Obstacol_3", coltMapaStanga, 400, 1000, glm::vec3(0.3, 0.3, 0.3), true);

    Mesh* Margine_Health = object2D::CreateRectangle("Marginea_Health", colt, 400, 50, glm::vec3(1, 0, 0), false);
    
    Mesh* Margine_Exp = object2D::CreateRectangle("Marginea_Exp", colt, 50, 400, glm::vec3(0, 1, 0.3921 ), false);
    
    Mesh* glont = object2D::CreateRectangle("Glont", glm::vec3(X_jucator, Y_jucator, 0), 25, 10, glm::vec3(0.3725 , 0.1568 , 0.1568), true);
    
    Mesh* Mapa = object2D::CreateSquare("Mapa", coltMapaStanga, lat_mapa, glm::vec3(1, 1, 1),true);
    

    Mesh* Margine_Mapa = object2D::CreateSquare("Marginea_mapei", coltMapaStanga, lat_mapa, glm::vec3(0, 0, 1), false);
    

    Mesh* Jucator = object2D::CreateSquare("Jucator", colt, lat_patrat, glm::vec3(0.9215, 0.745 , 0.2352 ),true);
   

    Mesh* Mana = object2D::CreateSquare("Mana", coltStanga, lat_mana, glm::vec3(0.8235 , 0.6274 , (float)0), true);
   

    Mesh* Inamic = object2D::CreateSquare("Inamic", colt, lat_patrat, glm::vec3(0, 0, 0),true);
    

    AddMeshToList(Obstacol1);

    AddMeshToList(Obstacol2);

    AddMeshToList(Obstacol3);

    AddMeshToList(Inamic);

    AddMeshToList(Jucator);

    AddMeshToList(Mapa);

    AddMeshToList(Margine_Mapa);

    AddMeshToList(Margine_Health);

    AddMeshToList(Mana);

    AddMeshToList(glont);

    AddMeshToList(Margine_Exp);
}


void Tema1::FrameStart()
{
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    Mesh* Health = object2D::CreateRectangle("Health", colt, viata, 50, glm::vec3(1, 0, 0), true);
   
    Mesh* Exp = object2D::CreateRectangle("Exp", colt, 50, experienta, glm::vec3(0, 1, 0.3921), true);
    
    AddMeshToList(Exp);
    AddMeshToList(Health);

    if (viata == 0) 
        return;
    
    x1_local =  X_jucator - x_inamicf1;
    y1_local =  Y_jucator - y_inamicf1;

    x2_local = X_jucator - x_inamicf2;
    y2_local = Y_jucator - y_inamicf2;

    unghi_inamic1 =atan2(y1_local-300, x1_local-300);
    unghi_inamic2 =atan2(y2_local-400, x2_local-400);

    if (((x_inamic1 + x_inamicf1 - x_res - X_jucator) >-10) && 
        ((x_inamic1 + x_inamicf1 - x_res - X_jucator) < 10) && 
        ((y_inamic1 + y_inamicf1 - y_res - Y_jucator) > -10) &&
        ((y_inamic1 + y_inamicf1 - y_res - Y_jucator) < 10)) 
            {
                inamic1_desen = 0; 
                viata += 80;//
                experienta -= 20;
                
            }
    if (((x_inamic2 + x_inamicf2 - x_res - X_jucator) > -10) &&
        ((x_inamic2 + x_inamicf2 - x_res - X_jucator) < 10) &&
        ((y_inamic2 + y_inamicf2 - y_res - Y_jucator) > -10) &&
        ((y_inamic2 + y_inamicf2 - y_res - Y_jucator) < 10))
            {
                inamic2_desen2 = 0;
                viata += 80;
                experienta -= 20;//nu trebuie sa primeasca exp la coliziunea cu inamicul
                

                printf("%f %f", (x_inamic2 + x_inamicf2), (x_res + X_jucator));
            }
    

     Mat_map = glm::mat3(1);

     Mat_model = glm::mat3(1);
     MatLeft_model = glm::mat3(1);
     MatRight_model = glm::mat3(1);

     Mat_health = glm::mat3(1);
     Mat_health2 = glm::mat3(1);

     Mat_experienta = glm::mat3(1);
     
     Mat_inamic1 = glm::mat3(1);
     Mat_inamic2 = glm::mat3(1);

     Mat_obstacol1 = glm::mat3(1);
     Mat_obstacol2 = glm::mat3(1);
     Mat_obstacol3 = glm::mat3(1);

     Mat_glont1 = glm::mat3(1);
     Mat_glont2 = glm::mat3(1);
     Mat_glont3 = glm::mat3(1);
     Mat_glont4 = glm::mat3(1);

     
     x_inamicf1 = x_inamicf1 + 150 * cos(unghi_inamic1)  * deltaTimeSeconds;
     x_inamicf2 = x_inamicf2 + 200 * cos(unghi_inamic2) * deltaTimeSeconds;

     y_inamicf1 = y_inamicf1 + 150 * sin(unghi_inamic1) * deltaTimeSeconds;
     y_inamicf2 = y_inamicf2 + 200 * sin(unghi_inamic2) * deltaTimeSeconds;

     x_stanga = 20, y_stanga = -10;// pentru mana stanga
     x_dreapta = -10, y_dreapta = 15;// pentru mana dreapta

     Mat_model *= transform2D::Translate(x_res + X_jucator, y_res+Y_jucator )* transform2D::Rotate(unghi);

     MatLeft_model *= Mat_model* transform2D::Translate(x_stanga, y_stanga)*transform2D::Rotate(unghi);
     
     MatRight_model *= Mat_model* transform2D::Translate(x_dreapta, y_dreapta)* transform2D::Rotate(unghi);
     
     if (ok_inamic1) 
     {
         ok_inamic1 = 0;

         x_inamic1 = x_res + X_jucator + 300;//pozitia initiala a inamicului 1
         y_inamic1 = y_res + Y_jucator + 300;//-||-
     }

     if (ok_inamic2) 
     {
         ok_inamic2 = 0;

         x_inamic2 = x_res + X_jucator + 400;
         y_inamic2 = y_res + Y_jucator + 400;    
     }

     Mat_health *= transform2D::Translate(x_res + X_jucator, y_res + Y_jucator)* transform2D::Translate(100, 300);;

     Mat_health2 *= Mat_health* transform2D::Translate(400, 0);

     Mat_experienta *= transform2D::Translate(x_res + X_jucator, y_res + Y_jucator)* transform2D::Translate(500, 0);
     
     Mat_obstacol1 *= transform2D::Translate(200,900);

     Mat_obstacol2 *= transform2D::Translate(1500,150);

     Mat_obstacol3 *= transform2D::Translate(900, 900);

     Mat_inamic1 *= transform2D::Translate(x_inamic1, y_inamic1)* transform2D::Translate(x_inamicf1, y_inamicf1)* transform2D::Rotate(unghi_inamic1);

     Mat_inamic2 *= transform2D::Translate(x_inamic2, y_inamic2)* transform2D::Translate(x_inamicf2, y_inamicf2)* transform2D::Rotate(unghi_inamic2);

    RenderMesh2D(meshes["Marginea_Health"], shaders["VertexColor"], Mat_health);
    RenderMesh2D(meshes["Health"], shaders["VertexColor"], Mat_health2);

    RenderMesh2D(meshes["Marginea_Exp"], shaders["VertexColor"], Mat_experienta);
    RenderMesh2D(meshes["Exp"], shaders["VertexColor"], Mat_experienta);


    RenderMesh2D(meshes["Obstacol_1"], shaders["VertexColor"], Mat_obstacol1);

    RenderMesh2D(meshes["Obstacol_2"], shaders["VertexColor"], Mat_obstacol2);

    RenderMesh2D(meshes["Obstacol_3"], shaders["VertexColor"], Mat_obstacol3);
    
    RenderMesh2D(meshes["Marginea_mapei"], shaders["VertexColor"], Mat_map);

    RenderMesh2D(meshes["Jucator"], shaders["VertexColor"], Mat_model);

    RenderMesh2D(meshes["Mana"], shaders["VertexColor"], MatLeft_model);

    RenderMesh2D(meshes["Mana"], shaders["VertexColor"], MatRight_model);
    
    if(inamic1_desen)
        RenderMesh2D(meshes["Inamic"], shaders["VertexColor"], Mat_inamic1);
    
    else 
        {
            gen = gen + 45;
            experienta = experienta + 20;

            inamic1_desen = 1;

            x_inamicf1 = 500*sin(gen); //o miscare a inamicului 1
            y_inamicf1 = 500*cos(gen); // 
            
            printf(" your score is: " "%d " , experienta);
        }

    if (inamic2_desen2)
        RenderMesh2D(meshes["Inamic"], shaders["VertexColor"], Mat_inamic2);
    
    else 
        {
            gen = gen + 50;
            experienta = experienta+20;

            inamic2_desen2 = 1;

            x_inamicf2 = 600 * sin(gen);
            y_inamicf2 = 600 * cos(gen);
            
            printf(" your score is: " "%d ", experienta);
        }

    if (time_1 > 0) 
        {
            if (viteza1 == 1) 
                {
                    viteza1 = 0;

                    x_glont1 = x_res + X_jucator;
                    y_glont1 = y_res + Y_jucator;
                    unghi1 = unghi;
                }

            Mat_glont1 *= transform2D::Translate(xrel_glont1, yrel_glont1);
            time_1 -= deltaTimeSeconds;

            x_glont1 += 1000 * cos(unghi1- 8.58) * deltaTimeSeconds;
            y_glont1 += 1000 * sin(unghi1- 8.58) * deltaTimeSeconds;

            if ((y_glont1 + yrel_glont1 > -125) && 
                (y_glont1 + yrel_glont1 < 925) && 
                (x_glont1 + xrel_glont1 < 325) && 
                (x_glont1 + xrel_glont1 > -125))
                    glont1_desen = 0;//+- 50 cat de mare sa fie hitbox ul

            if ((y_glont1 + yrel_glont1 > -120) && 
                (y_glont1 + yrel_glont1 < -35) && 
                (x_glont1 + xrel_glont1 < -450) && 
                (x_glont1 + xrel_glont1 > -820))
                    glont1_desen = 0;

            if ((y_glont1 + yrel_glont1 > -860) && 
                (y_glont1 + yrel_glont1 < -525) && 
                (x_glont1 + xrel_glont1 < 605) && 
                (x_glont1 + xrel_glont1 > 485))
                    glont1_desen = 0;

            if ((x_glont1 + xrel_glont1 < x_inamic1 + x_inamicf1 + 60) && 
                (x_glont1 + xrel_glont1 > x_inamic1 + x_inamicf1 - 60) && 
                (y_glont1 + yrel_glont1 < y_inamic1 + y_inamicf1 + 60) && 
                (y_glont1 + yrel_glont1 > y_inamic1 + y_inamicf1 - 60)) 
                {
                    glont1_desen = 0; 
                    inamic1_desen = 0;    
                }

            if ((x_glont1 + xrel_glont1 < x_inamic2 + x_inamicf2 + 60) && 
                (x_glont1 + xrel_glont1 > x_inamic2 + x_inamicf2 - 60) && 
                (y_glont1 + yrel_glont1 < y_inamic2 + y_inamicf2 + 60) && 
                (y_glont1 + yrel_glont1 > y_inamic2 + y_inamicf2 - 60)) 
                { 
                    glont1_desen = 0; 
                    inamic2_desen2 = 0;    
                }

           Mat_glont1 *= transform2D::Translate(x_glont1,y_glont1);
           Mat_glont1 *= transform2D::Rotate(unghi1 - 8.58);

            if(glont1_desen)
                RenderMesh2D(meshes["Glont"],shaders["VertexColor"],Mat_glont1);
        }

    if (time_1 < 0)     
        {
            viteza1 = 1;
            glont1_desen = 1;
        }

    if (time_2 > 0) 
        {
            if (viteza2 == 1) 
                {
                    viteza2 = 0;

                    xrel_glont2 = x_res + X_jucator;
                    yrel_glont2 = y_res + Y_jucator;
                    unghi2 = unghi;
                }

            Mat_glont2 *= transform2D::Translate(xrel_glont2, yrel_glont2);
            time_2 -= deltaTimeSeconds;
            x_glont2 += 1000 * cos(unghi2 - 8.58) * deltaTimeSeconds;
            y_glont2 += 1000 * sin(unghi2 - 8.58) * deltaTimeSeconds;

            if ((y_glont2 + yrel_glont2 > -120) && 
                (y_glont2 + yrel_glont2 < -35) && 
                (x_glont2 + xrel_glont2 < -450) && 
                (x_glont2 + xrel_glont2 > -820))
                    glont2_desen = 0;

            if ((y_glont2 + yrel_glont2 > -125) && 
                (y_glont2 + yrel_glont2 < 925) && 
                (x_glont2 + xrel_glont2 < 325) &&  
                (x_glont2 + xrel_glont2 > -125)) 
                    glont2_desen = 0;

            if ((y_glont2 + yrel_glont2 > -860) && 
                (y_glont2 + yrel_glont2 < -525) && 
                (x_glont2 + xrel_glont2 < 605) && 
                (x_glont2 + xrel_glont2 > 485))
                    glont2_desen = 0;

            if ((x_glont2 + xrel_glont2 < x_inamic1 + x_inamicf1 + 60) && 
                (x_glont2 + xrel_glont2 > x_inamic1 + x_inamicf1 - 60) && 
                (y_glont2 + yrel_glont2 < y_inamic1 + y_inamicf1 + 60) && 
                (y_glont2 + yrel_glont2 > y_inamic1 + y_inamicf1 - 60))
                {
                    glont2_desen = 0;
                    inamic1_desen = 0;
                }

            if ((x_glont2 + xrel_glont2 < x_inamic2 + x_inamicf2 + 60) && 
                (x_glont2 + xrel_glont2 > x_inamic2 + x_inamicf2 - 60) && 
                (y_glont2 + yrel_glont2 < y_inamic2 + y_inamicf2 + 60) && 
                (y_glont2 + yrel_glont2 > y_inamic2 + y_inamicf2 - 60))
                {
                    glont2_desen = 0;
                    inamic2_desen2 = 0;
                }

           Mat_glont2 *= transform2D::Translate(x_glont2, y_glont2);
           Mat_glont2 *= transform2D::Rotate(unghi2 - 8.58);

            if (glont2_desen)
                RenderMesh2D(meshes["Glont"], shaders["VertexColor"],Mat_glont2);
        }   

    if (time_2 < 0) 
        {
            viteza2 = 1;
            glont2_desen = 1;
        }

    if (time_3> 0) 
        {
            if (viteza3 == 1) 
                {
                    viteza3 = 0;

                    xrel_glont3 = x_res + X_jucator;
                    yrel_glont3 = y_res + Y_jucator;
                    unghi3 = unghi;
                }

            Mat_glont3 *= transform2D::Translate(xrel_glont3, yrel_glont3);
            time_3 -= deltaTimeSeconds;
            x_glont3 += 1000 * cos(unghi3 - 8.58) * deltaTimeSeconds;
            y_glont3 += 1000 * sin(unghi3 - 8.58) * deltaTimeSeconds;

            if ((y_glont3 + yrel_glont3 > -120) &&
                (y_glont3 + yrel_glont3 < -35) && 
                (x_glont3 + xrel_glont3 < -450) && 
                (x_glont3 + xrel_glont3 > -820))
                    glont3_desen = 0;

            if ((y_glont3 + yrel_glont3 > -125) && 
                (y_glont3 + yrel_glont3 < 925) && 
                (x_glont3 + xrel_glont3 < 325) && 
                (x_glont3 + xrel_glont3 > -125))
                    glont3_desen = 0;//+- 60 cat de mare sa fie hitbox ul

            if ((y_glont3 + yrel_glont3 > -860) && 
                (y_glont3 + yrel_glont3 < -525) && 
                (x_glont3 + xrel_glont3 < 605) && 
                (x_glont3 + xrel_glont3 > 485))
                    glont3_desen = 0;

            if ((x_glont3 + xrel_glont3 < x_inamic1 + x_inamicf1 + 60) && 
                (x_glont3 + xrel_glont3 > x_inamic1 + x_inamicf1 - 60) && 
                (y_glont3 + yrel_glont3 < y_inamic1 + y_inamicf1 + 60) && 
                (y_glont3 + yrel_glont3 > y_inamic1 + y_inamicf1 - 60))
                {
                    glont3_desen = 0;
                    inamic1_desen = 0;
                }

            if ((x_glont3 + xrel_glont3 < x_inamic2 + x_inamicf2 + 60) && 
                (x_glont3 + xrel_glont3 > x_inamic2 + x_inamicf2 - 60) && 
                (y_glont3 + yrel_glont3 < y_inamic2 + y_inamicf2 + 60) && 
                (y_glont3 + yrel_glont3 > y_inamic2 + y_inamicf2 - 60))
                {
                    glont3_desen = 0;
                    inamic2_desen2 = 0;
                }

           Mat_glont3 *= transform2D::Translate(x_glont3, y_glont3);
           Mat_glont3 *= transform2D::Rotate(unghi3 - 8.58);

            if (glont3_desen)
                RenderMesh2D(meshes["Glont"], shaders["VertexColor"],Mat_glont3);
        }

    if (time_3 < 0) 
        {
            viteza3 = 1;
            glont3_desen = 1;
        }

    if (time_4 > 0) 
        {
            if (viteza4 == 1) 
                {
                    viteza4 = 0;

                    xrel_glont4 = x_res + X_jucator;
                    yrel_glont4 = y_res + Y_jucator;
                    unghi4 = unghi;
                }

            Mat_glont4 *= transform2D::Translate(xrel_glont4, yrel_glont4);
            time_4 -= deltaTimeSeconds;
            x_glont4 += 1000 * cos(unghi4 - 8.58) * deltaTimeSeconds;
            y_glont4 += 1000 * sin(unghi4 - 8.58) * deltaTimeSeconds;

            if ((y_glont4 + yrel_glont4 > -125) && 
                (y_glont4 + yrel_glont4 < 925) && 
                (x_glont4 + xrel_glont4 < 325) && 
                (x_glont4 + xrel_glont4 > -125))
                    glont4_desen = 0;//+- 50 cat de mare sa fie hitbox ul

            if ((y_glont4 + yrel_glont4 > -860) && 
                (y_glont4 + yrel_glont4 < -525) && 
                (x_glont4 + xrel_glont4 < 605) && 
                (x_glont4 + xrel_glont4 > 485))
                    glont4_desen = 0;

            if ((y_glont4 + yrel_glont4 > -120) && 
                (y_glont4 + yrel_glont4 < -35) && 
                (x_glont4 + xrel_glont4 < -450) && 
                (x_glont4 + xrel_glont4 > -820))
                    glont4_desen = 0;

            if ((x_glont4 + xrel_glont4 < x_inamic1 + x_inamicf1 + 60) && 
                (x_glont4 + xrel_glont4 > x_inamic1 + x_inamicf1 - 60) && 
                (y_glont4 + yrel_glont4 < y_inamic1 + y_inamicf1 + 60) && 
                (y_glont4 + yrel_glont4 > y_inamic1 + y_inamicf1 - 60))
                {
                    glont4_desen = 0;
                    inamic1_desen = 0;
                }

            if ((x_glont4 + xrel_glont4 < x_inamic2 + x_inamicf2 + 60) && 
                (x_glont4 + xrel_glont4 > x_inamic2 + x_inamicf2 - 60) && 
                (y_glont4 + yrel_glont4 < y_inamic2 + y_inamicf2 + 60) && 
                (y_glont4 + yrel_glont4 > y_inamic2 + y_inamicf2 - 60))
                {
                    glont4_desen = 0;
                    inamic2_desen2 = 0;
                }

          Mat_glont4 *= transform2D::Translate(x_glont4, y_glont4);
          Mat_glont4 *= transform2D::Rotate(unghi4 - 8.58);

            if (glont4_desen)
                RenderMesh2D(meshes["Glont"], shaders["VertexColor"], Mat_glont4);
        }

    if (time_4 < 0) 
        {
            viteza4 = 1;
            glont4_desen = 1;
        }
        
    RenderMesh2D(meshes["Mapa"], shaders["VertexColor"], Mat_map);
  
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    localX = mouseX - resolution_x;
    localY = mouseY - resolution_y;
    unghi = 8.58 - atan2(localY, localX);// unghiul playerului , 8.58 o constanta gasita prin incercari care asigura ca playerul se uita unde trebuie; 
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if ((button == GLFW_MOUSE_BUTTON_RIGHT) && 
        (time_1 <= 0) && 
        (time_2 <= 0.8) && 
        (time_3 <= 1.6) && 
        (time_4 <= 2.4))
        {
            time_1 = 3.2;

            x_glont1 = 0;// sa plece glontul din arma nu de la ultima pozitia a glontului 1
            y_glont1 = 0;
        }

    else if ((button == GLFW_MOUSE_BUTTON_RIGHT) && 
            (time_2 <= 0) && 
            (time_3 <= 0.8) && 
            (time_4 <= 1.6) && 
            (time_1 <= 2.4))
            {
                time_2 = 3.2;

                x_glont2 = 0;
                y_glont2 = 0;
            }

    else if ((button == GLFW_MOUSE_BUTTON_RIGHT) && 
            (time_3 <= 0) && 
            (time_4 <= 0.8) && 
            (time_1 <= 1.6) && 
            (time_2 <= 2.4))
            {
                time_3 = 3.2;

                x_glont3 = 0;
                y_glont3 = 0;
            }

    else if ((button == GLFW_MOUSE_BUTTON_RIGHT) && 
            (time_4 <= 0) &&
            (time_1 <= 0.8) && 
            (time_2 <= 1.6) && 
            (time_3 <= 2.4))
            {
                time_4 = 3.2;

                x_glont4 = 0;
                y_glont4 = 0;
            }

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_D)) 
        {
       
            if ((Y_jucator > -475) && 
                (Y_jucator < 550) && 
                (X_jucator < -325) && 
                (X_jucator > -760))

                    X_jucator -= 5;

            if ((Y_jucator > -1225) && 
                (Y_jucator < -900) && 
                (X_jucator < -50) && 
                (X_jucator > -160))
                
                    X_jucator -= 5;
             
            if ((Y_jucator > -475) && 
                (Y_jucator < -375) && 
                (X_jucator < -1100) && 
                (X_jucator > -1460))
                
                    X_jucator -= 5;
           
            if (X_jucator > 350)
                    
                    X_jucator -= 5;//marginea hartii

            X_jucator += 5;

            cam_jucator = glm::vec3(X_jucator, Y_jucator, 50);

            GetSceneCamera()->SetPosition(cam_jucator);//mut camera de pe player
  
        }

    if (window->KeyHold(GLFW_KEY_A)) 
        {
            
            if ((Y_jucator > -1225) && 
                (Y_jucator < -900) && 
                (X_jucator < -40) && 
                (X_jucator > -150))
                    
                    X_jucator += 5;

            if ((Y_jucator > -475) && 
                (Y_jucator < 550) && 
                (X_jucator < -315) && 
                (X_jucator > -750))
                    
                    X_jucator += 5;
       
            if ((Y_jucator > -475) && 
                (Y_jucator < -375) && 
                (X_jucator < -1090) && 
                (X_jucator > -1450))
                
                    X_jucator += 5;

            if (X_jucator < -1625)
                
                    X_jucator += 5;

            X_jucator -= 5;

            cam_jucator = glm::vec3(X_jucator, Y_jucator, 50);

            GetSceneCamera()->SetPosition(cam_jucator);
   
        }

    if (window->KeyHold(GLFW_KEY_W)) 
        {

            
            if ((Y_jucator > -1235) && 
                (Y_jucator < -900) && 
                (X_jucator < -50) && 
                (X_jucator > -150))
                
                    Y_jucator -= 5;

            if ((Y_jucator > -485) && 
                (Y_jucator < 550) && 
                (X_jucator < -325) && 
                (X_jucator > -750))
                    
                    Y_jucator -= 5;

            if ((Y_jucator > -485) && 
                (Y_jucator < -375) && 
                (X_jucator < -1100) && 
                (X_jucator > -1450))
                
                    Y_jucator -= 5;

            if (Y_jucator > 600)
                
                    Y_jucator -= 5;

            Y_jucator += 5;

            cam_jucator = glm::vec3(X_jucator, Y_jucator, 50);

            GetSceneCamera()->SetPosition(cam_jucator);

        }

    if (window->KeyHold(GLFW_KEY_S)) 
        {
    
            if ((Y_jucator > -475) && 
                (Y_jucator < 560) && 
                (X_jucator < -325) && 
                (X_jucator > -750))
                
                    Y_jucator += 5;

            if ((Y_jucator > -1225) && 
                (Y_jucator < -890) && 
                (X_jucator < -50) && 
                (X_jucator > -150))
                    
                    Y_jucator += 5;

            if ((Y_jucator > -475) && 
                (Y_jucator < -365) && 
                (X_jucator < -1100) && 
                (X_jucator > -1450))
                
                    Y_jucator += 5;

            if (Y_jucator < -1300)
                
                    Y_jucator += 5;
     
        Y_jucator -= 5;

        cam_jucator = glm::vec3(X_jucator, Y_jucator, 50);

        GetSceneCamera()->SetPosition(cam_jucator);
        }
}

void Tema1::OnWindowResize(int width, int height) 
{
    resolution_x = width / 2; //rezolutiile
    resolution_y = height / 2;
}
