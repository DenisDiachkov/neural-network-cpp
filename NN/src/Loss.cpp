#include "../include/Loss.hpp"

real MSELoss::operator()(Vector diff) const
{	
	return diff.pow(2.0L).mean();
}

Vector MSELoss::derivative(Vector diff) const
{
	return 2 * diff ;
}
