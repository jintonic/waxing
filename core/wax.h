#ifndef WAXING_WAX_H
#define WAXING_WAX_H
#include <X.h>
#include <vector>
#include <WF.h>
#include <TRotation.h>
#include <TVector3.h>

using namespace std::
namespace WAXING
{
  class wax;
  

  double pi=3.1415926;
  double me=0.511//mev
}
class WAXING::wax
{
  public:
    WF * wf;
  public :
    wax(X * x);
    virtual ~wax();

    void Initial(double * location, double phi, double phi110);
    void Update();
    void Setconsts(TString path)//need more detail

  private:
    double * electronlocationvector;
    double * holelocationvector;
    double * electronvelocityvector;
    double * holevelocityvector;
    double * consts;//4*4
    /*			miu0	E0	beta	miun
     * electron 111	
     * 		100
     * hole	111
     * 		100
    */
    double phi,phi110;
    double electronend,holeend;

    X * field;

    int nDimensions;


  private :
    virtual void UpdateVelocity();
    virtual void UpdateLocation();
    virtual void UpdateWF();
    double A(double E);
    double R(double E);

    TRotation * Rj(int j);
    TRotation * rj(int j);

    double vs (bool Is111);
    void readconstsfromfile();

    double GetlengthofE(double *E);
}
//rho rhopihi etc need a transform
//xyz only for now
