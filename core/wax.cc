#include <iostream>
using namespace WAXING;
using namespace std;

wax::wax(X *x)
{
  size=1;
  field=x;
  wf=new WF;
  
  driftlocationvector=new double[3];
  electronlocationvector=new double[3];
  electronvelocityvector=new double[3];
  driftvelocityvector=new double[3];
  for(int i=3;i-->0;)
  {
    driftlocationvector[i]=0;
    electronlocationvector[i]=0;
    electronvelocityvector[i]=0;
    driftvelocityvector[i]=0;
  }
}
wax::~wax()
{
  delete electronlocationvector;
  delete driftlocationvector;
  delete electronvelocityvector;
  delete driftvelocityvector;
}
void wax::Update()
{
  bool check1=true,check2=true;
  for(int i=0;i<size;i++)
  {
    if(electronlocationvector[i]<0)check1=false;
    if(driftlocationvetor[i]<0)check2=false;
    if(!check1&&!check2)return;
  }
  UpdareVelocity();
  UpdateLocation();
  Update();
}

void wax::InitialLocation(double aaa)
{
  electronlocationvector[0]=aaa;
  driftlocationvector[0]=aaa;
}

void wax::UpdateLocation()
{
  electronlocationvector+=electronvelocityvector;
  driftlocationvector+=driftdriftvelocityvector;
  if(electronlocationvector[0]>field->GetXEdge(true))
    electronlocationvector[0]=field->GetXEdge(true);
  if(electronlocationvector[0]<field->GetXEdge(false))
    electronlocationvector[0]=field->GetXEdge(false);
  if(driftlocationvector[0]>field->GetXEdge(true))
    driftlocationvector[0]=field->GetXEdge(true);
  if(driftlocationvector[0]<field->GetXEdge(false))
    driftlocationvector[0]=field->GetXEdge(false);
  //if get limit, relocate to closest limit
  UpdateWF();// update wf
}

void wax::UpdateWF()
{
  double protential=field->GetPotential(electronlocationvector[0])
    -field->GetPotential(driftlocationvector[0]);
  wf->smpl.push_back(potential);
}

void wax::UpdateVelocity()
{

}
