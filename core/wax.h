#ifndef WAXING_WAX_H
#define WAXING_WAX_H
#include <GeFiCa/X.h>
#include <vector>
#include <WAGE/WF.h>
#include <TRotation.h>
#include <TVector3.h>

using namespace std;
using namespace GeFiCa;
using namespace WAGE;
namespace WAXING
{
  class wax;
}
class WAXING::wax
{
   public:
      WF * wf;
      double theta,phi,phi110;
   public :
      wax(X * x);
      virtual ~wax();

      void Initial(double * location, double phi, double phi110,double theta);
      void Update();
      void Setconsts(TString path);//need more detail

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
      double electronend,holeend;

      X * field;

      int nDimensions;


   private :
      virtual void UpdateVelocity();
      virtual void UpdateLocation();
      virtual void UpdateWF();

      double * GetEfromfield(double *location);

      TVector3 * vhole(double *E);
      TVector3 * ve(double *E);

      double A(double E);
      double R(double E,double AE);

      double njchun(double R,TVector3 *E0i,int j);

      TRotation * Rj(int j);
      TRotation * rj(int j);

      double vs (bool Is111,bool Ishole,double E);

      double GetlengthofE(double *E);
      TVector3 * GetUnitVector(double *E);
      double Getlengthoftvector3(TVector3 * tar)
      {return tar->Dot(tar->Unit());};

      void readconstsfromfile();
};
//rho rhopihi etc need a transform
//xyz only for now
#endif
