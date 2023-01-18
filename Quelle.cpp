//	https://www.arndt-bruenner.de/mathe/10/
//	parabeltangente.htm#:~:text=Somit%20ergibt%20sich%20f%C3%BCr%20die%20Tangente
//	%20an%20die,jeden%20Punkt%20x%20durch%202ax%20%2B%20b%20gegeben.

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <initializer_list>

class Point
{
private:
	float mX, mY;
public:
	Point() :
		mX{ 0 },
		mY{ 0 }
	{}
	Point(float x, float y) :
		mX{ x },
		mY{ y }
	{}
	Point(Point const& p) :
		mX{ p.mX },
		mY{ p.mY }
	{}
	Point& operator=(Point const& rhs) {
		mX = rhs.mX;
		mY = rhs.mY;
		return *this;
	}
	float x() const
	{
		return mX;
	}
	float y() const
	{
		return mY;
	}
	void set_x(float xx)
	{
		mX = xx;
	}
	void set_y(float yy)
	{
		mY = yy;
	}
	friend std::ostream&
		operator<<(std::ostream& os, Point const& p) {
		return os << "x = " << p.mX << " y = " << p.mY;
	}
};
class Kurve : public Point {
public:
	std::vector<Point> kur;


public:
	Kurve(std::initializer_list<Point> liste) : kur{ liste } {}
	Kurve(Point p) {
		kur.push_back(p);
	}

	std::vector<Point>& get_kur() {
		return kur;
	}
};


class Segment
{
private:
	Point mA, mB;
public:
	Segment(Point A, Point B) :
		mA{ A }, mB{ B }
	{}
	float A() const		// Coefficient A: y = Ax + B
	{
		return (mA.y() - mB.y()) / (mA.x() - mB.x());
		// source: https://calculis.net/droite
					// A completer
	}
	float B() const		// Coefficient B: y = Ax + B
	{
		return mA.y() - A() * mA.x();
		// source: https://calculis.net/droite
					// A completer
	}
	Point intersection(Segment const& other)
	{
		float x = (other.B() - B()) / (A() - other.A());
		// source: https://calculis.net/intersection
		// A completer

		// A completer
		return Point{ x , A() * x + B() };
	}
	std::string equation() const
	{
		return "y = " + std::to_string(A()) + "x + " + std::to_string(B());
	}
};
int main() {
	Point poiA(0, 0);
	Point poiB(2, pow(2, 2));


	Kurve parabole({ 0,0 });
	for (float i = 0; i < 100; i++)
		parabole.kur.push_back({ i * 0.1f,pow(i * 0.1f,2.0f) });
	Point Q;
	float xQ, yQ;
	std::cout << "Bitte den Punkt, aus dem wird Tangente auf Parabel berechnet:   " << std::endl;
	std::cout << "Bitte x: ";
	std::cin >> xQ;
	Q.set_x(xQ);
	std::cout << std::endl;
	std::cout << "Bitte y: ";
	std::cin >> yQ;
	Q.set_y(yQ);
	std::cout << std::endl;


	Kurve parabole_Bsp_1({ 0.0f,0.0f });
	for (float i = -30.0f; i < 100; i++) {
		parabole_Bsp_1.kur.push_back({ i * 0.1f, -3 * pow(i * 0.1f,2.0f) + 2*i*0.1f + 1 });
	}

	// Tangente berechnen , Punkt Q bekant Q(-1,-1), tangente hat Form y = Ax + B , Parabole f(x) = -3x^2 + 2x +1
	// Punkt der Berührung T(xT,yT) , yT = A*xT + B, A ist tangens des Winkels der Tangente A = f'(x) = -6x + 2
	//float xT = 0.0f, yT = 0.0f;
	
	
	// Parabel yT = -3xT^2 + 2xT +1  ; Tangente yT = (-6xT +2) xT + B
	// xT^2 - B/3 + 1/3 = 0

	//  https://www.youtube.com/watch?v=ql_w5paclOs

	float xT1 = -xQ + sqrt(pow(xQ,2.0f) - (1 - yQ + 2 * xQ) / 3);
	float xT2 = -xQ - sqrt(pow(xQ,2.0f) - (1 - yQ + 2 * xQ) / 3);
	//float B1 =(- 6.0f ) * xT1 +2)) * xQ - yQ;    // In diesem fall Q(-1,-1)
	//float B2 =(- 6.0f ) * xT2 +2)) * xQ - yQ; 
	float B1 = yQ + 6.0f * xT1 * xQ - 2 * xQ;    // In diesem fall Q(-1,-1)
	float B2 = yQ + 6.0f * xT2 * xQ - 2 * xQ;
	float A1 = -6.0f * xT1 + 2;
	float A2 = -6.0f * xT2 + 2;
	std::cout << "Das Ergebnis: Tangente1 y = " << A1 << " * x + " << B1 << std::endl;
	std::cout << "Das Ergebnis: Tangente2 y = " << A2 << " * x + " << B2 << std::endl;
	std::cout << "Der Punkt der Berührung der Tangente1 und Parabell ist "
		<< "T1(" << xT1 << ", " << A1 * xT1 + B1 << ")" << std::endl;
	std::cout << "Der Punkt der Berührung der Tangente2 und Parabell ist "
		<< "T1(" << xT2 << ", " << A2 * xT2 + B2 << ")" << std::endl;


	auto it = parabole_Bsp_1.kur.begin();
	while (it != parabole_Bsp_1.kur.end()) {
		std::cout << "parabole " << *it++ << std::endl;

	}

	Kurve hiperbole({ 0,0 });
	for (float i = 0; i < 100; i++)
		hiperbole.kur.push_back({ i * 0.1f,pow(i * 0.1f,.5f) });





	auto it_h = hiperbole.kur.begin();
	while (it_h != hiperbole.kur.end()) {
		std::cout << *it_h++ << std::endl;

	}


	Point pA(3.5f, 4.0f);
	Point pB(-4.0f, 2.0f);
	Point pC(2.0f, -2.0f);
	Point pD(-2.0f, 5.0f);

	Segment Line1(pA, pB);
	std::cout << Line1.equation() << std::endl;
	Segment Line2(pC, pD);
	std::cout << Line2.equation() << std::endl;

	std::cout << Line1.intersection(Line2);	// Point d'intersection des deux lignes droites	
}