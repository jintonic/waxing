#ifndef WAXING_WAX_H
#define WAXING_WAX_H
#include <X.h>
#include <vector>
#include <WF.h>
namespace WAXING
{
  class wax;

  static const double electric;
  static const double drift;

}
class WAXING::wax
{
  public:
    WF * wf;
  public :
    void wax(X * x);
    virtual ~wax();

    void Initiallocation(double aaa);
    void Update();

  private:
    double * electronlocationvector;
    double * driftlocationvector;
    double * electronvelocityvector;
    double * driftvelocityvector;

    double oneend,anotherend;

    X * field;

    int size;

  private :
    virtual void UpdateVelocity();
    virtual void UpdateLocation();
    virtual void UpdateWF();
}
