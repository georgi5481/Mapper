#include "Mapper.h"

int main() {
	Mapper<double> mapper;
	double array[16][12] = { 
{1,1,1,1,1,1,1,1,1,1,1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1},
{1,1,1,1,1,1,1,1,1,1,1,1}};

	unsigned int realPositionX = 8;
	unsigned int realPositionY = 3;

	bool shouldMap = true;

	realPositionX++;
	
	while (shouldMap) {
		
		double aheadSensor = array[realPositionY - 1][realPositionX];
		double leftSensor = array[realPositionY][realPositionX - 1];
		double downSensor = array[realPositionY + 1][realPositionX];
		double rightSensor = array[realPositionY][realPositionX + 1];

		double arrayPosition[4] = {aheadSensor, leftSensor, downSensor, rightSensor};

		std::cout << mapper.getVelocity().x << " " << mapper.getVelocity().y << '\n';

		int integrateResult = mapper.integrate(0.1, arrayPosition);

		Vec2<double> velocity = mapper.getVelocity();
		bool ifRight = (velocity.x == 1 && velocity.y == 0);	//helping bools telling us where we are going atm.
		bool ifLeft = (velocity.x == -1 && velocity.y == 0);
		bool ifDown = (velocity.x == 0 && velocity.y == -1);
		bool ifUp = (velocity.x == 0 && velocity.y == 1);

		if (ifRight)
		{
			realPositionX++;
		}
		else if (ifLeft)
		{
			realPositionX--;
		}
		else if (ifDown)
		{
			realPositionY++;
		}
		else if (ifUp)
		{
			realPositionY--;
		}


		if (integrateResult == 0) {
			shouldMap = false;
		}
	}

	for (int k = 0; k < (mapper.getBorder()).getCount(); k++ ) {
		std::cout << ((mapper.getBorder())[k]).x << " " << ((mapper.getBorder())[k]).y << '\n';
	}
	return 0;
}