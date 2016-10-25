#ifndef WAXING_WAX_H
#define WAXING_WAX_H
#include <X.h>
#include <vector>
#include <WF.h>
namespace WAXING
{
  class wax;
}
class WAXING::wax
{
  public:
    WF * wf;
  public :
    wax(X * x);
    virtual ~wax();

    void Initiallocation(double aaa);
    void Update();

  private:
    double * electronlocationvector;
    double * holelocationvector;
    double * electronvelocityvector;
    double * holevelocityvector;

    double electronend,holeend;

    X * field;

    int nDimensions;

  private :
    virtual void UpdateVelocity();
    virtual void UpdateLocation();
    virtual void UpdateWF();
}
