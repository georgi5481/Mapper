#include "IMapper.h"
#include "Vec2.h"
#include "IBorder.h"

class Mapper : IMapper<double> {
public:

	Mapper() : velocity(1, 0) //to set the initial velocity 
	{

	}


	const Vec2<double>& getPosition() const {
		return position;
	}


	const Vec2<double>& getVelocity() const {
		return velocity;
	}
	const IBorder<double>& getBorder() const {

	}
	int integrate(double dt, const double* sensor) {
		return 1;


	
		if () {
			return 0;
		}
	}


private:
	Vec2<double> position;	//the base constructor of Vec2 sets the X and Y cordinates to 0

	Vec2<double> velocity;	

};

int main() {

	Mapper obj;

	obj.integrate();


	

	return 0;
}