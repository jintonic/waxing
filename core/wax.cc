#include <iostream>
using namespace WAXING;
using namespace std;

wax::wax(X *x)
{
  nDimensions=1;
  if (x==NULL) {
     Warning("wax","Pointer to electric field == NULL, quit");
     abort();
  }
  field=x;
  wf=new WF;
  
  holelocationvector=new double[3];
  electronlocationvector=new double[3];
  electronvelocityvector=new double[3];
  holevelocityvector=new double[3];
  for(int i=3;i-->0;)
  {
    holelocationvector[i]=0;
    electronlocationvector[i]=0;
    electronvelocityvector[i]=0;
    holevelocityvector[i]=0;
  }
}
wax::~wax()
{
  delete electronlocationvector;
  delete holelocationvector;
  delete electronvelocityvector;
  delete holevelocityvector;
}
void wax::Update()
{
  bool isElectonOnBorder=true,isHoleOnBorder=true;
  for(int i=0;i<nDimensions;i++)
  {
    if(electronlocationvector[i]<0)isElectonOnBorder=false;
    if(holelocationvetor[i]<0)isHoleOnBorder=false;
    if(!isElectonOnBorder&&!isHoleOnBorder)return;
  }
  UpdareVelocity();
  UpdateLocation();
  Update();
}

void wax::InitialLocation(double aaa)
{
  electronlocationvector[0]=aaa;
  holelocationvector[0]=aaa;
}

void wax::UpdateLocation()
{
  electronlocationvector+=electronvelocityvector;
  holelocationvector+=holevelocityvector;
  if(electronlocationvector[0]>field->GetXEdge(true))
    electronlocationvector[0]=field->GetXEdge(true);
  if(electronlocationvector[0]<field->GetXEdge(false))
    electronlocationvector[0]=field->GetXEdge(false);
  if(holelocationvector[0]>field->GetXEdge(true))
    holelocationvector[0]=field->GetXEdge(true);
  if(holelocationvector[0]<field->GetXEdge(false))
    holelocationvector[0]=field->GetXEdge(false);
  //if get limit, relocate to closest limit
  UpdateWF();// update wf
}

void wax::UpdateWF()
{
  double protential=field->GetPotential(electronlocationvector[0])
    -field->GetPotential(holelocationvector[0]);
  wf->smpl.push_back(potential);
}

void wax::UpdateVelocity()
{
}
#include <math.h>   
double vs (bool Is111,double E);
{
  double miu0,E0,beta,miun;
  if(Is111)
  {
    miu0=consts[0];
    E0=consts[1];
    beta=consts[2];
    miun=costs[3];
  }
  else
  {
    miu0=consts[4];
  else
    E0=consts[5];
    beta=consts[6];
    miun=costs[7];
  }
  return miu0*E/pow(1+pow(E/E0,beta),1/beta)-miun*E;
}

double wax::A(double *E)
{
  TVector3 *E0=new TVector3(pow(0.5,0.5),pow(0.5,0.5),0);
  double top=vs(false,GetlengthofE(E));
  double bottom=0;
  for(int i=1;i<5;i++)
  {
    //1/4*E0*rj(i)
  }
}
TRotation * wax::rj(int j)
{
  double mt=1.64*me;
  double ml=0.0819*me;
  TRotation *rj=ew TRotation;
  rj->SetXPhi(1/mt);
  rj->SetYPsi(1/ml);
  rj->SetZTheta(1/mt);
  TRotation * Rj1=Rj(j;)
  rj=Rj1(j)->Inverse*rj*Rj1;
  return rj;
}


double wax::R(double E)
{
  
}

TRotation * Rj(int j);
{
  //calculate Rotation matrix Rj
  //Rj=Rx'(arccos((2/3)**0.5))Rz(phi110+(j-1)pi/2)
  //double pi=3.1415926;
  double arccosthing=0.615480;
  TRotation * Rj=new TRotation();
  Rj->RotateZ(phi110+(j-1)*pi/2);
  Rj->RotateX(arccosthing);
  return Rj;
}


void readconstsfromfile()
{
  //hardcode first to test
  //will update to read from file later
  consts={42420,25.1,0.87,62,40180,49.3,0.72,589,107270,10,0.58,0,66333,18.1,0.744,0};
}
