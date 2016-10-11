#include <iostream>
using namespace WAXING;
using namespace std;

wax::wax(X *x)
{
  size=1;
  field=x;
  wf=new WF;
  
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
  electronlocationvector=new double;
  electronlocationvector=aaa;
  driftlocationvector=new double;
  driftlocationvector=aaa;
}

void wax::UpdateLocation()
{
  electronlocationvector+=electronvelocityvector;
  driftlocationvector+=driftdriftvelocityvector;
  //check area limit
  //if get limit, relocate to closest limit
  UpdateWF();// update wf
}

void wax::UpdateWF()
{

}

void wax::UpdateVelocity()
{

}
