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
   double mobility = 
   electronvelocityvector[0] = mobility * field->GetE1(electronlocationvector[0]);
}
