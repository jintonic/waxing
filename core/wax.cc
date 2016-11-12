#include <iostream>
#include "wax.h"
using namespace std;
using namespace WAGE;
using namespace GeFiCa;
using namespace WAXING;
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
    if(holelocationvector[i]<0)isHoleOnBorder=false;
    if(!isElectonOnBorder&&!isHoleOnBorder)return;
  }
  UpdateVelocity();
  UpdateLocation();
  Update();
}

void wax::Initial(double *location,double phi,double phi110,double theta)
{
  electronlocationvector=location;
  holelocationvector=location;
}

void wax::UpdateLocation()
{
  for(int i=0;i<3;i++)
  {
    electronlocationvector[i]+=electronvelocityvector[i];
    holelocationvector[i]+=holevelocityvector[i];
  }
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
  double potential=field->GetPotential(electronlocationvector[0])
    -field->GetPotential(holelocationvector[0]);
  wf->smpl.push_back(potential);
}

#include <math.h> 
void wax::UpdateVelocity()
{
//need some way to find out n-D system 
//to get a correct E
//
  double *Ee=GetEfromfield(electronlocationvector);
  double *Eh=GetEfromfield(holelocationvector);
  TVector3 * vele=ve(Ee);
  TVector3 * vh=vhole(Eh);

   electronvelocityvector[0]=vele->X();
   electronvelocityvector[1]=vele->Y();
   electronvelocityvector[2]=vele->Z();
   holevelocityvector[0]=vh->X();
   holevelocityvector[1]=vh->Y();
   holevelocityvector[2]=vh->Z();
}
double wax::vs (bool Is111,bool Ishole,double E)
{
  //pro:calculat on direction 111or110,hole or electron, electric field E
  //post:velocity
  double miu0,E0,beta,miun;
  if(Is111&&!Ishole)
  {
    miu0=consts[0];
    E0=consts[1];
    beta=consts[2];
    miun=consts[3];
  }
  else if(!Is111&&!Ishole)
  {
    miu0=consts[4];
    E0=consts[5];
    beta=consts[6];
    miun=consts[7];
  }
  if(Is111&&Ishole)
  {
    miu0=consts[8];
    E0=consts[9];
    beta=consts[10];
    miun=consts[11];
  }
  else if(!Is111&&Ishole)
  {
    miu0=consts[12];
    E0=consts[13];
    beta=consts[14];
    miun=consts[15];

  }
  return miu0*E/pow(1+pow(E/E0,beta),1/beta)-miun*E;
}

double wax::A(double E)
{
  //pro: acctual electric field strength??
  //post:A(E)
  TVector3 *E0=new TVector3(1,0,0);//pow(0.5,0.5),pow(0.5,0.5),0)
  double top=vs(false,false,E);
  TVector3* bottom=new TVector3(0,0,0);
  for(int i=1;i<5;i++)
  {
    TRotation* rjj=rj(i);
    TVector3 * Erj=E0->Transform(*rjj)
    bottom+=1/4*Erj/pow(Erj.Dot(E0),0.5);
  }
  double bot=bottom.Unit()*bottom;
  return top/bot;
}



TRotation * wax::rj(int j)
{
  //pro: jth dirtection
  //post : rj
  double mt=1.64*me;
  double ml=0.0819*me;
  TRotation *rj=new TRotation;
  rj->SetXPhi(1/mt);
  rj->SetYPsi(1/ml);
  rj->SetZTheta(1/mt);
  TRotation * Rj1=Rj(j);
  rj=Rj1(j)->Inverse*rj*Rj1;
  return rj;
}


double wax::R(double E,double AE)
{
  //pre:actual Electric vector, result of A(E)
  //post R(E)
  TVector3 *E0=new TVector3(0,pow(2/3,0.5),pow(1/3,0.5));
  double El=E;
  TRotation * rj1=rj(1);
  TRotation * rj2=rj(2);

  double b=(vs(true,false,El)/AE-1)/(3*(Getlengthoftvetor3(E0->Transform(*rj2))/pow(E0->Transform(*rj2).Dot(E0),0.5)-E0->Transform(*rj1).Dot(E0)/pow(E0->Transform(*rj1).Dot(E0),0.5)));
  double a=1-3*b;
  double top=a-b;
  double bottombot=0;
  for(int i=1;i<5;i++)
  {
    bottombot+=pow(E0->Transform(*rj(i)).Dot(E0),0.5);
  }

  double bottom=pow(E0->Transform(*rj(1)).Dot(E0),0.5)/bottombot-b;
  return top/bottom;
}

TRotation * wax::Rj(int j);
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


void wax::readconstsfromfile()
{
  //hardcode first to test
  //will update to read from file later
  double a[16]={42420,25.1,0.87,62,40180,49.3,0.72,589,107270,10,0.58,0,66333,18.1,0.744,0};
  consts=a;
}


TVector3 * wax::vhole(double * E)
{
  double Ev=GetlengthofE(E);
  double vh111=vs(true,true,Ev);
  double vh100=vs(false,true,Ev);
  double vrel=vh111/vh100;
  double k0=9.2652-26.3467*vrel+29.6137*vrel*vrel-12.3689*vrel*vrel*vrel;
  double A=-0.1322*k0+0.41145*k0*k0-0.23657*k0*k0*k0+0.04077*k0*k0*k0*k0;
  double ou=0.006550*k0-0.19946*k0*k0+0.09859*k0*k0*k0-0.01559*k0*k0*k0*k0;

  double sintheta=sin(theta);
  double sin2phi=sin(s*phi);

  double vxp=vh100*(1-A*(pow(sintheta,4)*pow(sin2phi,2)+pow(sin(2*theta),2)));
  double vyp=vh100*ou*(2*pow(sintheta,3)*cos(theta)*pow(sin2phi,2)+sin(4*theta));
  double vzp=vh100*ou*pow(sintheta,3)*sin(4*phi);

  TVector3 * vp=new TVector(vxp,vyp,vzp);

  TRotation * Ro=new TRotation();
  Ro.Rotatez(phi+3.1415926/4+phi110);//need to ask
  Ro.Rotatey(theta);

  return &(vp->Transform(*Ro));
}

TVector3 * wax::ve(double *E)
{
  double lengthofE=GetlengthofE(E);
  TVector3 * E0=GetUnitVector(E);
  double AE=A(lengthofE);
  double RE=R(lengthofE,AE);
  TVector3 *sum=new TVector3();
  for(int i=1;i<5;i++)
  {
    double nj=njchun(RE,E0,i);
    TVector3 *ET=&(E0->Transform(*rj(i)));
    *sum+(*ET*=1/pow(*ET**E0,0.5))*nj;
  }
  return &(*sum*=AE);
}
double wax::njchun(double R,TVector3 * E0,int j)
{
  double top=pow(E0->Transform(*rj(j)).Dot(*E0),0.5);
  double bot=0;
  for(int i=1;i<5;i++)
  {
    bot+=pow(E0->Transform(*rj(i)).Dot(*E0),0.5);
  }
  double nen=0.25;
  return R*(top/bot-nen)+nen;
  
}
  
