#ifndef WAXING_WAX_H
#define WAXING_WAX_H
#include <X.h>
#include <vector>
namespace WAXING
{
  class wax;

  static const double electric;
  static const double drift;

}
class WAXING::wax
{
  public:
    std::vector<double> wf;
  public :
    void input(const char *path);
    void output(const char *path);

    void Update();

    void Setinilocation(double a);

  private:
    double * electronlocationvector;
    double * driftlocationvector;
    double * electronvelocityvector;
    double * driftvelocityvector;

    double oneend,anotherend;

    X * field;

  private :
    void CalculatevVelocity();
    void Updatelocation();
    void Updateends();
}
