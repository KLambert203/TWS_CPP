#include <stack>
#include <math.h>
#include <assert.h>

#include "StackCalculator.h"

void StackCalculator::Clear()
{
	while (!mStack.empty())
	{
		mStack.pop();
	}
}

double StackCalculator::Add()
{
	if (mStack.size() >= 2)
	{
		double lA = PopValue();
		double lB = PopValue();

		mStack.push(lA + lB);

		return mStack.top();
	}
	else 
	{
		throw std::exception("Not enough elements in the stack to add.");
	}
}

double StackCalculator::Cosinus()
{
	if (mStack.size() >= 1)
	{
		double lA = PopValue();

		mStack.push(cos(lA));

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to calculate cosinus.");
	}
}

double StackCalculator::Divide()
{
	if (mStack.size() >= 2)
	{
		double lA = PopValue();
		double lB = PopValue();

		if (lA != 0) { mStack.push(lB / lA); }
		else{ throw std::exception("Can't divide by 0!"); }

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to substract.");
	}
}

double StackCalculator::Modulus()
{
	if (mStack.size() >= 2)
	{
		double lA = PopValue();
		double lB = PopValue();

		mStack.push(fmod(lB, lA));

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to return modulus.");
	}
}

double StackCalculator::Multiply()
{
	if (mStack.size() >= 2)
	{
		double lA = PopValue();
		double lB = PopValue();

		mStack.push(lA * lB);

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to multiply.");
	}
}

double StackCalculator::Sinus()
{
	if (mStack.size() >= 1)
	{
		double lA = PopValue();

		mStack.push(sin(lA));

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to calculate sinus.");
	}
}

double StackCalculator::SquareRoot()
{
	if (mStack.size() >= 1)
	{
		double lA = PopValue();

		mStack.push(sqrt(lA));

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to calculate square root.");
	}
}

double StackCalculator::Substract()
{
	if (mStack.size() >= 2)
	{
		double lA = PopValue();
		double lB = PopValue();

		mStack.push(lB - lA);

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to substract.");
	}
}

double StackCalculator::Tangent()
{
	if (mStack.size() >= 1)
	{
		double lA = PopValue();

		mStack.push(tan(lA));

		return mStack.top();
	}
	else
	{
		throw std::exception("Not enough elements in the stack to calculate tangent.");
	}
}

void StackCalculator::PushValue(double aValue)
{
	assert(NULL != aValue);
	mStack.push(aValue);
}

double StackCalculator::PopValue()
{
	double lValue = mStack.top();
	mStack.pop();

	return lValue;
}