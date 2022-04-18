#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/object3D.h"
#include <lab_m1/Tema2/object2D.cpp>


using namespace std;
using namespace m1;
using namespace implemented;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
    // TODO(student): Never forget to initialize class variables!

}


Tema2::~Tema2()
{
}
float translateXP = 1,translateYP = 0,translateZP = 1;
int paindirection = 1;
float RLeg1X = 0, RLeg1Y = 0, RLeg1Z = 0; 
float RArm1X = 0, RArm1Y = 0, RArm1Z = 0;
int Dir = 1, Dir2 = 1;
float XLeg1 = 0, XLeg2 = 0, ZLeg1 = 0, ZLeg2 = 0;
float moveX = 0, moveY = 0, moveZ = 0;
float XHead = 0, ZHead = 0;
float XArm1 = 0, XArm2 = 0, ZArm1 = 0, ZArm2 = 0;
float XTorso = 0, ZTorso = 0;
float posEx[400], posEy[400], posEz[400];
float Pitch = 0, Roll = 0, DFP = 1, AngP = 0;
float DeltaY = 0, DeltaX = 0;
float ProjectX = 0, ProjectZ = 0, ProjectY = 0;
float Pchange = 0;
float PitchNow = Pitch;
float AngPNow = AngP;
float timp = 3;
float Yaw; 
float fire = 0;
int cellwall[2000];
int cellcell[1000];
int cellvisited[1000];
int print = 1;
int Xcoord = 30;
int Zcoord = 30;
int pos[400];
int hpenemy[400];
int enemyhurt[400];
int contor = 0;
float timehurt = 0;
float pain = 0.5;
float maxhp = 10, maxtime = -100;
float upmotionenemy = 1, rightmotionenemy = 1;
glm::vec3 position;
glm::mat4 View, FinalView;
void Tema2::Init()
{
    Mesh* Leg = object3D::CreateCube("Leg", glm::vec3(0, 0, 0), 0.2, 0.6, 0.2 , glm::vec3((float)40/255, (float)235/255, (float)225/255));
    AddMeshToList(Leg);
    Mesh* Head = object3D::CreateCube("Head", glm::vec3(0, 0, 0), 0.2, 0.2, 0.2, glm::vec3((float)230/255, (float)230/255, (float)50/255));
    AddMeshToList(Head);
    Mesh* Torso = object3D::CreateCube("Torso", glm::vec3(0, 0, 0), 0.2, 0.8, 0.65, glm::vec3(0, 0, 1));
    AddMeshToList(Torso);
    Mesh* Arm = object3D::CreateCube("Arm", glm::vec3(0, 0, 0), 0.2, 0.6, 0.2, glm::vec3(0, 1, 1));
    AddMeshToList(Arm);
    Mesh* Floor = object3D::CreateCube("Floor", glm::vec3(0, 0, 0), 2, 0.1, 2, glm::vec3((float)102/255, (float)65/255, (float)33/255));
    AddMeshToList(Floor);
    Mesh* Wall1 = object3D::CreateCube("Wall1", glm::vec3(0, 0, 0), 2, 3, 0.1, glm::vec3(0.5, 0.5, 0.5));
    AddMeshToList(Wall1);
    Mesh* Wall2 = object3D::CreateCube("Wall2", glm::vec3(0, 0, 0), 0.1, 3, 2, glm::vec3(0.5, 0.5, 0.5));
    AddMeshToList(Wall2);
    Mesh* Ceil = object3D::CreateCube("Ceil", glm::vec3(0, 0, 0), 2, 0.1, 2, glm::vec3(1, 1, 1));
    AddMeshToList(Ceil);
    Mesh* Projectile = object3D::CreateCube("Projectile", glm::vec3(0, 0, 0), 0.2, 0.2, 0.2, glm::vec3((float)210/255, (float)40/255, (float)70/255));
    AddMeshToList(Projectile);
    Mesh* Enemy = object3D::CreateCube("Enemy", glm::vec3(0, 0, 0), 0.5, 1.5, 0.5, glm::vec3((float)30 / 255, (float)200 / 255, (float)30 / 255));
    AddMeshToList(Enemy);
    Mesh* Enemy1 = object3D::CreateCube("Enemy1", glm::vec3(0, 0, 0), 0.5, 1.5, 0.5, glm::vec3((float)190 / 255, (float)190 / 255, (float)40 / 255));
    AddMeshToList(Enemy1);
    Mesh* Enemy2 = object3D::CreateCube("Enemy2", glm::vec3(0, 0, 0), 0.5, 1.5, 0.5, glm::vec3((float)190 / 255, (float)30 / 255, (float)190 / 255));
    AddMeshToList(Enemy2);
    Mesh* HpWire = object3D::CreateCube("HpWire", glm::vec3(0, 0, 0), 0.025, 0.005, 0, glm::vec3((float)1, (float)0, (float)0),false);
    AddMeshToList(HpWire);
    Mesh* TimeWire = object3D::CreateCube("TimeWire", glm::vec3(0, 0, 0), -0.025, 0.005, 0, glm::vec3((float)30/255, (float)20/255, (float)200/255), false);
    AddMeshToList(TimeWire);

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    for (int i = 0; i < 2000; i++) {
        cellwall[i] = 1;
    }
    for (int i = 0; i < 1000; i++) {
        cellcell[i] = 0;
        cellvisited[i] = 0;
    }
    int start = glm::rand();
    while (start > Xcoord * Zcoord)start = glm::floor(start * 37 / 49-Xcoord*Zcoord/4);
        if (start < Xcoord * Zcoord / 2)start = glm::floor(start * 57 / 42);
        if (start % 2 != 0)start +=glm::floor( Xcoord * Zcoord / 8);
        else start -= glm::floor(Xcoord * Zcoord / 3);
        while (start < 0)start += Xcoord * Zcoord / 2;
        while (start > Xcoord * Zcoord) start -= Xcoord * Zcoord / 2;
        int finished = 0;
        int cellnumber = 0;
        
        for (int i = 0; i < 400; i++) {
            pos[i] = glm::rand();
            enemyhurt[i] = 0;
        }
        for (int i = 0; i < glm::floor(Xcoord * sqrt(Zcoord))/2; i++) {
            enemyMatrix[i] = glm::mat4(1);
            pos[i] = pos[i] % (Xcoord * Zcoord);
            int height = glm::floor(pos[i] / Zcoord);
            int length = pos[i] - height * Zcoord;
            height = height - Zcoord/2;
            length = length - Xcoord/2;
            enemyMatrix[i] *= transform3D::Translate(height*2, 0, length*2);
            posEx[i] = height * 2;
            posEz[i] = length * 2;
            hpenemy[i] = 3;
        }
        while (finished == 0) {
            cellcell[start] = 1;
            int cellmarked = 0;
            cellvisited[cellnumber] = start;
            int randomnow = glm::rand();
            if (randomnow % 4 == 0) {
                if (start + Xcoord > Xcoord * Zcoord - 1)randomnow += 1;
                if(start+Xcoord<Xcoord*Zcoord)
                if (cellcell[start + Xcoord] == 0) {
                    cellcell[start + Xcoord] = 1;
                    start = start + Xcoord;
                    cellwall[start] = 0;
                    cellnumber += 1;
                    cellmarked = 1;
                }
                else randomnow += 1;
            }
             if ((randomnow % 4 == 1) && (cellmarked == 0)) {
                 if (start + 1 > Xcoord * Zcoord - 1)randomnow += 1;
                 if(start+1<Xcoord*Zcoord)
                     if (cellcell[start + 1] == 0) {
                         if ((start + 1) % Xcoord == 0) {
                             randomnow += 1;
                         }
                         else {
                             cellcell[start + 1] = 1;
                             start = start + 1;
                             int startt = start;
                             int coordinate = Xcoord * Zcoord;
                             while (startt > Xcoord) {
                                 startt -= Xcoord;
                                 coordinate += 1;
                                 cellmarked = 1;
                             }
                             coordinate += Zcoord * startt;
                             cellwall[coordinate] = 0;
                             cellnumber += 1;
                             cellmarked = 1;
                         }
                     }
                     else randomnow += 1;               
            }
             if ((randomnow % 4 == 2) && (cellmarked == 0)) {
                 if (start - Xcoord < 0)randomnow += 1;
                 if(start-Xcoord>-1)
                if (cellcell[start - Xcoord] == 0) {
                    cellcell[start - Xcoord] = 1;
                    start = start - Xcoord;
                    cellwall[start + Xcoord] = 0;
                    cellnumber += 1;
                    cellmarked = 1;
                }
                else randomnow += 1;
            }
             if ((randomnow % 4 == 3) && (cellmarked == 0)) {
                 if (start - 1 < 0)randomnow += 1;
                 if(start-1>-1)
                     if (cellcell[start - 1] == 0) {
                         if (start % Xcoord == 0) {
                             randomnow += 1;
                         }
                         else {
                             cellcell[start - 1] = 1;
                             start = start - 1;
                             int startt = start;
                             int coordinate = Xcoord * Zcoord;
                             while (startt >= Xcoord) {
                                 startt -= Xcoord;
                                 coordinate += 1;
                             }
                             coordinate += Zcoord * (startt+1);
                             cellwall[coordinate] = 0;
                             cellnumber += 1;
                             cellmarked = 1;
                         }
                     }
                     else randomnow += 1;                    
            }
             if ((randomnow % 4 == 0) && (cellmarked == 0)) {
                 if (start + Xcoord > Xcoord * Zcoord - 1)randomnow += 1;
                 if(start+Xcoord<Xcoord*Zcoord)
                if (cellcell[start + Xcoord] == 0) {
                    cellcell[start + Xcoord] = 1;
                    start = start + Xcoord;
                    cellwall[start] = 0;
                    cellnumber += 1;
                    cellmarked = 1;
                }
                else randomnow += 1;
            }
             if ((randomnow % 4 == 1) && (cellmarked == 0)) {
                 if (start + 1 > Xcoord * Zcoord - 1)randomnow += 1;
                 if (start + 1 < Xcoord * Zcoord)
                     if (cellcell[start + 1] == 0) {
                         if ((start + 1) % Xcoord == 0) {
                             randomnow += 1;
                         }
                         else {
                             cellcell[start + 1] = 1;
                             start = start + 1;
                             int startt = start;
                             int coordinate = Xcoord * Zcoord;
                             while (startt > Xcoord) {
                                 startt -= Xcoord;
                                 coordinate += 1;
                                 cellmarked = 1;
                             }
                             coordinate += Zcoord * startt;
                             cellwall[coordinate] = 0;
                             cellnumber += 1;
                             cellmarked = 1;
                         }
                     }
                     else randomnow += 1;
             }
             if ((randomnow % 4 == 2) && (cellmarked == 0)) {
                 if (start - Xcoord < 0)randomnow += 1;
                 if(start-Xcoord>-1)
                if (cellcell[start - Xcoord] == 0) {
                    cellcell[start - Xcoord] = 1;
                    start = start - Xcoord;
                    cellwall[start + Xcoord] = 0;
                    cellnumber += 1;
                    cellmarked = 1;
                }
            }
                if (cellmarked == 0) {
                    cellnumber -= 1;
                    start = cellvisited[cellnumber];
                }
               if (cellnumber == 0)finished = 1;
            }
}


void Tema2::FrameStart()
{
}


void Tema2::Update(float deltaTimeSeconds)
{
    timehurt -= deltaTimeSeconds;

    pain += deltaTimeSeconds * paindirection;
    if (pain > 0.9)paindirection = -1;
    if (pain < 0.1)paindirection = 1;
    Mesh* EnemyHurt = object3D::CreateCubeBroked("EnemyHurt", glm::vec3(0, 0, 0), 0.5, 1.5, 0.5, glm::vec3((float)pain, (float)pain, (float)pain),true,pain);
    AddMeshToList(EnemyHurt);
    maxtime += deltaTimeSeconds;
    if (maxtime > 0) {
        printf("GAME OVER! Out of Time!");
            int p = 1;
        int i = 1 / (p - 1);
    }
    if((translateXP>(Xcoord+2)) || (translateXP<(-Xcoord-2)) || 
        (translateZP>(Zcoord + 2)) || (translateZP < (-Zcoord - 2))) {
        printf("You exited the maze ALIVE and WON!!! CONGRATULATIONS!");
        int p = 1;
        int i = 1 / (p - 1);
    }
    Mesh* HpFull = object3D::CreateCube("HpFull", glm::vec3(0, 0, 0), maxhp*0.0025, 0.005, 0, glm::vec3((float)1, (float)0, (float)0));
    AddMeshToList(HpFull);
    Mesh* TimeFull = object3D::CreateCube("TimeFull", glm::vec3(0, 0, 0), maxtime * 0.00025, 0.005, 0, glm::vec3((float)30/255, (float)20/255, (float)200/255));
    AddMeshToList(TimeFull);
    legMatrix1 = glm::mat4(1);
    legMatrix1 *= transform3D::Translate(translateXP + XLeg1,translateYP,translateZP+ZLeg1);
    legMatrix1 *= transform3D::RotateOX(RLeg1X);
    legMatrix1 *= transform3D::RotateOZ(RLeg1Z);
    legMatrix2 = glm::mat4(1);
    legMatrix2 *= transform3D::Translate(0.25, 0, 0.25);
    legMatrix2 *= transform3D::Translate(translateXP + XLeg2, translateYP, translateZP+ZLeg2);
    legMatrix2 *= transform3D::RotateOX(-RLeg1X);
    legMatrix2 *= transform3D::RotateOZ(-RLeg1Z);
    headMatrix = glm::mat4(1);
    headMatrix *= transform3D::Translate(0.15, -0.1, 0.1);
    headMatrix *= transform3D::Translate(translateXP+XHead, translateYP+1.5, translateZP+ZHead);
    torsoMatrix = glm::mat4(1);
    torsoMatrix *= transform3D::Translate(translateXP, translateYP+0.6, translateZP);
    torsoMatrix *= transform3D::RotateOY(0.785);
    armMatrix1 = glm::mat4(1);
    armMatrix1 *= transform3D::Translate(0.45, 0.15,0.45);
    armMatrix1 *= transform3D::Translate(translateXP + XArm1, translateYP+0.6, translateZP + ZArm1);
    armMatrix1 *= transform3D::RotateOY(0.785);
    armMatrix1 *= transform3D::RotateOX(RArm1X);
    armMatrix1 *= transform3D::RotateOZ(RArm1Z);
    armMatrix2 = glm::mat4(1);
    armMatrix2 *= transform3D::Translate(-0.14, 0.15, -0.14);
    armMatrix2 *= transform3D::Translate(translateXP + XArm2, translateYP+0.6, translateZP + ZArm2);
    armMatrix2 *= transform3D::RotateOY(0.785);
    armMatrix2 *= transform3D::RotateOX(-RArm1X);
    armMatrix2 *= transform3D::RotateOZ(-RArm1Z);
    healthMatrix = glm::mat4(1);
    healthMatrix *= transform3D::Translate(-0.041, 0.025, 49.95);
    timeMatrix = glm::mat4(1);
    timeMatrix *= transform3D::Translate(0.0315, 0.025, 49.95);
    projectile = glm::mat4(1);
    projectile *= transform3D::Translate(translateXP+0.2, (float)translateYP  + 1.8, translateZP+0.2);
    projectile *= transform3D::Translate(ProjectX, ProjectY, ProjectZ);
    for (int i = 0;i< Xcoord;i++)
        for (int j = 0; j < Zcoord; j++) {
            floor[i*Xcoord+j]= glm::mat4(1);
            floor[i * Xcoord + j] *= transform3D::Translate((i-Xcoord/2)*2, -0.15, (j-Zcoord/2)*2);
            wall[i * Xcoord + j] = glm::mat4(1);
            wall[i * Xcoord + j] *= transform3D::Translate((i - Xcoord / 2) * 2, 0, (j - Zcoord / 2) * 2);
            ceil[i * Xcoord + j] = glm::mat4(1);
            ceil[i * Xcoord + j] *= transform3D::Translate((i - Xcoord / 2) * 2, 3, (j - Zcoord / 2) * 2);
         }
   
        if (moveX > 0.038)upmotionenemy = -1;
        if (moveX < -0.038)upmotionenemy = 1;
        if (moveZ > 0.038)rightmotionenemy = -1;
        if (moveZ < -0.038)rightmotionenemy = 1;
        if ((contor == 3) || (contor == 1))
            moveX += 0.001 * upmotionenemy;
        moveZ += 0.001 * rightmotionenemy;
        moveY += 0.015;
        if ((moveX < 0.0001) && (moveX > -0.0001)&&(contor==1)) {
            moveX = 0;
            contor=2;
        }
        else if ((moveZ < 0.0001) && (moveZ > -0.0001) && (contor == 0)) {
                contor = 3;
        }
        if (((moveZ > 0.01) || (moveZ < -0.01)) && (contor == 2))
            contor = 0;
        if (((moveZ > 0.01) || (moveZ < -0.01)) && (contor == 3))
            contor = 1;
       for (int i = 0; i < glm::floor(Xcoord * sqrt(Zcoord))/2; i++) {
        enemyMatrix[i] *= transform3D::Translate(moveX, sin(moveY*8) /30, moveZ);
        posEx[i] += moveX;
        posEy[i] += sin(moveY * 8) / 30;
        posEz[i] += moveZ;
    }
       for (int i = 0; i < glm::floor(Xcoord * sqrt(Zcoord)) / 2; i++) {
           if (((ProjectX + translateXP + 0.2) > (posEx[i] - 0.2)) && ((ProjectX + translateXP + 0.2) < (posEx[i] + 0.5)) &&
               ((ProjectY + translateYP + 1.8) > (posEy[i] - 0.2)) && ((ProjectY + translateYP + 1.8) < (posEy[i] + 1.5)) &&
               ((ProjectZ + translateZP + 0.2) > (posEz[i] - 0.2)) && ((ProjectZ + translateZP + 0.2) < (posEz[i] + 0.5)) &&
               hpenemy[i] > 0)
           {
               hpenemy[i] -= 1;
               timp = -1;
               enemyhurt[i] = 1;
               timehurt = 1.5;
               if (fire <= 0)maxhp -= 1;
           }
           if ((translateXP > (posEx[i] - 0.2)) && (translateXP < (posEx[i] + 0.5)) &&
               (translateYP > (posEy[i] - 0.2)) && (translateYP < (posEy[i] + 1.5)) &&
               (translateZP > (posEz[i] - 0.2)) && (translateZP < (posEz[i] + 0.5)) &&
               hpenemy[i] > 0)
           {
               hpenemy[i] -= 1;
               maxhp -= 1;
               enemyhurt[i] = 1;
               timehurt = 1.5;
               if (maxhp == 0) {
                   printf("GAME OVER!!! Out of Life!");
                   int p = 1;
                   int i = 0 / (p - 1);
                   }
           }
       }
    glm::ivec2 resolution = window->props.resolution;
    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(0, 0, 0, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    RenderMesh(meshes["Leg"], shaders["VertexColor"], legMatrix1);
    RenderMesh(meshes["Leg"], shaders["VertexColor"], legMatrix2);
    RenderMesh(meshes["Head"], shaders["VertexColor"], headMatrix);
    RenderMesh(meshes["Torso"], shaders["VertexColor"], torsoMatrix);
    RenderMesh(meshes["Arm"], shaders["VertexColor"], armMatrix1);
    RenderMesh(meshes["Arm"], shaders["VertexColor"], armMatrix2);
    for (int i = 0; i < Xcoord; i++)
        for (int j = 0; j < Zcoord; j++) {
            RenderMesh(meshes["Floor"], shaders["VertexColor"], floor[i*Xcoord+j]);
            if (cellwall[Xcoord * Zcoord + i * Xcoord + j] == 1)     
            RenderMesh(meshes["Wall1"], shaders["VertexColor"], wall[i * Xcoord + j]);
            if (cellwall[i * Xcoord + j] == 1)
            RenderMesh(meshes["Wall2"], shaders["VertexColor"], wall[i * Xcoord + j]);
            RenderMesh(meshes["Ceil"], shaders["VertexColor"], ceil[i * Xcoord + j]);
        }
    if (fire == 1) {
        if (timp > 0) {
            ProjectX += (sin(PitchNow)) * (sin(AngPNow)) / 15;
            ProjectY -= (cos(PitchNow)) / 15;
            ProjectZ += (sin(PitchNow)) * (cos(AngPNow)) / 15;
            RenderMesh(meshes["Projectile"], shaders["VertexColor"], projectile);
            timp -= deltaTimeSeconds;
            //printf("X / Y / z time are % f, % f, % f %f       ", ProjectX, ProjectY, ProjectZ, timp);
        }
        if (timp < 0) {
            ProjectX = 0;
            ProjectY = 0;
            ProjectZ = 0;
            fire = 0;
        }
    }
    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.
    for (int i = 0; i < glm::floor(Xcoord * sqrt(Zcoord)); i++) {
        if (hpenemy[i] == 3)
            RenderMesh(meshes["Enemy"], shaders["VertexColor"], enemyMatrix[i]);
        if ((hpenemy[i] == 2) && (enemyhurt[i] == 1))
            RenderMesh(meshes["EnemyHurt"], shaders["VertexColor"], enemyMatrix[i]);
        if ((hpenemy[i] == 2) && (enemyhurt[i] == 0))
            RenderMesh(meshes["Enemy1"], shaders["VertexColor"], enemyMatrix[i]);
        if ((hpenemy[i] == 1) && (enemyhurt[i] == 1))
            RenderMesh(meshes["EnemyHurt"], shaders["VertexColor"], enemyMatrix[i]);

        if ((hpenemy[i] == 1) && (enemyhurt[i] == 0))
            RenderMesh(meshes["Enemy2"], shaders["VertexColor"], enemyMatrix[i]);
        if ((hpenemy[i] == 0) && (enemyhurt[i] == 1))
            RenderMesh(meshes["EnemyHurt"], shaders["VertexColor"], enemyMatrix[i]);
        if((enemyhurt[i]==1)&&(timehurt<0))enemyhurt[i]=0;
    }
  auto camera2 = GetSceneCamera();
    camera2->SetPosition(glm::vec3(0, 0, 50));
    camera2->SetRotation(glm::vec3(0, 0, 0));
    camera2->Update();
    GetCameraInput()->SetActive(false);
    glViewport(0, 0, resolution.x , resolution.y);
    RenderMesh(meshes["HpFull"], shaders["VertexColor"], healthMatrix);
    RenderMesh(meshes["HpWire"], shaders["VertexColor"], healthMatrix);
    RenderMesh(meshes["TimeFull"], shaders["VertexColor"], timeMatrix);
    RenderMesh(meshes["TimeWire"], shaders["VertexColor"], timeMatrix);

    
    GetSceneCamera()->Update();
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input

    if (window->KeyHold(GLFW_KEY_W))
    {
        translateZP -= 0.04;

        if (RLeg1Z > 0.4)Dir2 = -1;
        if (RLeg1Z < -0.4)Dir2 = 1;
        if (RArm1Z > 0.4)Dir2 = -1;
        if (RArm1Z < -0.4)Dir2 = 1;
        RLeg1Z += 0.02 * Dir2;
        ZLeg1 -= 0.01 * Dir2;
        ZLeg2 += 0.01 * Dir2;
        RArm1Z += 0.02 * Dir2;
        ZArm1 -= 0.01 * Dir2;
        ZArm2 += 0.01 * Dir2;

        for (int i = Xcoord*Zcoord; i <Xcoord*Zcoord*2; i++) {
            if (cellwall[i] == 1) {
                float height = (glm::floor((float)(i-Xcoord*Zcoord) / (float)Zcoord) - Zcoord / 2) * 2;
                float length = ((i -Xcoord*Zcoord - (height / 2 + Xcoord/2) * Zcoord) - Xcoord/2) * 2;
               
                if (((translateXP >= height) && (translateXP < (height + 2))) && ((translateZP > (length+0.10)) && (translateZP < (length + 0.20))))
                    translateZP += 0.04;

            }

        }
  }
    if (window->KeyHold(GLFW_KEY_S))
    {
        translateZP += 0.04;
        if (RLeg1Z > 0.4)Dir2 = -1;
        if (RLeg1Z < -0.4)Dir2 = 1;
        if (RArm1Z > 0.4)Dir2 = -1;
        if (RArm1Z < -0.4)Dir2 = 1;
        RLeg1Z += 0.02 * Dir2;
        ZLeg1 -= 0.01 * Dir2;
        ZLeg2 += 0.01 * Dir2;
        RArm1Z += 0.02 * Dir2;
        ZArm1 -= 0.01 * Dir2;
        ZArm2 += 0.01 * Dir2;
        for (int i = Xcoord * Zcoord; i < Xcoord * Zcoord * 2; i++) {
            if (cellwall[i] == 1) {
                float height = (glm::floor((float)(i -Xcoord*Zcoord)/ (float)Zcoord) - Zcoord / 2) * 2;
                float length = ((i-Xcoord*Zcoord - (height / 2 + Xcoord/2) * Zcoord) - Xcoord/2) * 2;
               
                 if (((translateXP > height) && (translateXP < (height + 2))) && ((translateZP > (length-0.45)) && (translateZP < (length - 0.35))))
                    translateZP -= 0.04;

            }

        }
  
    }
    if (window->KeyHold(GLFW_KEY_A))
    {
        translateXP -= 0.04;
        if (RLeg1X > 0.4)Dir = -1;
        if (RLeg1X < -0.4)Dir = 1;
        if (RArm1X > 0.4)Dir = -1;
        if (RArm1X < -0.4)Dir = 1;
        RLeg1X += 0.02 * Dir;
        XLeg1 += 0.01 * Dir;
        XLeg2 -= 0.01 * Dir;
        RArm1X += 0.02 * Dir;
        XArm1 += 0.01 * Dir;
        XArm2 -= 0.01 * Dir;


        for (int i = 0; i < Xcoord*Zcoord; i++) {
            if (cellwall[i] == 1) {
                float height = (glm::floor((float)i / (float)Zcoord) - Zcoord / 2) * 2;
                float length = ((i- (height / 2 + Xcoord/2) * Zcoord) - Xcoord/2) * 2;
                if (((translateXP >= height - 0.05) && (translateXP <= (height + 0.05))) && ((translateZP >= length) && (translateZP <= length + 2)))
                    translateXP += 0.04;

            }

        }
    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        translateXP += 0.04;
        if (RLeg1X > 0.4)Dir = -1;
        if (RLeg1X < -0.4)Dir = 1;
        if (RArm1X > 0.4)Dir = -1;
        if (RArm1X < -0.4)Dir = 1;
        RLeg1X += 0.02 * Dir;
        XLeg1 += 0.01 * Dir;
        XLeg2 -= 0.01 * Dir;
        RArm1X += 0.02 * Dir;
        XArm1 += 0.01 * Dir;
        XArm2 -= 0.01 * Dir;

        for (int i = 0; i < Xcoord*Zcoord; i++) {
            if (cellwall[i] == 1) {
                float height = (glm::floor((float)i / (float)Zcoord) - Zcoord / 2) * 2;
                float length = ((i - (height / 2 + Xcoord/2) * Zcoord) - Xcoord/2) * 2;
                    if (((translateXP >= height - 0.55) && (translateXP <= (height - 0.45))) && ((translateZP >= length) && (translateZP <= length + 2)))
                        translateXP -= 0.04;

            }

        }
    }
    
    if (window->KeyHold(GLFW_KEY_B)) {
        printf("X projectile is: %f     ", (ProjectX + translateXP + 0.2));
        for (int i = 0; i < 4; i++)
            printf("X enemy is : %f     ", posEx[i]);

    }
        Pitch -= DeltaY/50;
        DeltaY = 0;
        AngP -= DeltaX/50;
        DeltaX = 0;
        float offsetX = DFP * (sin(Pitch))*(sin(AngP));
        float offsetZ = DFP * (sin(Pitch))*(cos(AngP));
        GetSceneCamera()->SetPosition(glm::vec3( translateXP-offsetX+0.2,(float)translateYP + DFP * (cos(Pitch))+1.8, translateZP -offsetZ+0.2));
        glm::mat4 View = glm::lookAt(glm::vec3 ( (translateXP-offsetX+0.2),(float)translateYP + DFP * (cos(Pitch))+1.8, (translateZP -offsetZ+0.2)), glm::vec3(translateXP+0.2, translateYP + 1.8, translateZP+0.2), glm::vec3 (0,10,0));
        glm::mat4 FinalView = GetSceneCamera()->GetViewMatrix();
        GetSceneCamera()->SetRotation(glm::inverse(View));
    
    


}



void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL) {
        if (DFP > 0.02)DFP = 0.01;
        else DFP = 1;
    }
 

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    DeltaY = deltaY*0.4f;
    DeltaX = deltaX * 1.2f;

  // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if ((button == GLFW_MOUSE_BUTTON_RIGHT)&&(fire==0)) {
        fire = 1;
         PitchNow = Pitch;
         AngPNow = AngP;
         timp = 3;
    }
        
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

    // Treat mouse scroll event
}


void Tema2::OnWindowResize(int width, int height)
{
    // Treat window resize event
}




