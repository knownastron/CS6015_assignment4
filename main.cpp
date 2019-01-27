//
//  main.cpp
//  assignment3
//
//  Created by Jason Tran on 2019-01-15.
//  Copyright © 2019 Jason Tran. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
using namespace std;



vector<string> splitLine(string inputStr) {
    vector<string> output;
    string temp = "";
    for (int i = 0; i < inputStr.size(); i++) {
        if (inputStr[i] == ' ') {
            output.push_back(temp);
            temp = "";
        } else {
            temp += inputStr[i];
        }
        
        if (i == inputStr.size() - 1) {
            output.push_back(temp);
        }
    }
    return output;
}

struct Point {
    double x, y;
    double angle;
};

struct Distances {
    double d12, d23, d34, d41; // adjacent
    double d13, d24; //diagonal
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

double distance(Point pt1, Point pt2) {
    double d = sqrt(pow(pt2.x - pt1.x, 2) + pow(pt2.y - pt1.y, 2));
    return d;
}

bool isEqual(float a, float b) {
    return (fabs(a - b) < 0.0001);
}

bool isParallel(double s1, double s2) {
//    if (fabs(s1) == INFINITY && fabs(s2) == INFINITY) {
//        return true;
//    }
    
    if (isEqual(s1, s2)) {
        return true;
    }
    
    return false;
    
    
}

bool allAngles90(Point p1, Point p2, Point p3, Point p4) {
    vector<double> angles = {p1.angle, p2.angle, p3.angle,p4.angle};
    
    for (double angle : angles) {
        if (!isEqual(angle, 90)) {
            return false;
        }
    }
    
    return true;
}

bool allSidesCongruent(Distances d) {
    double side = d.d12;
    
    if (!isEqual(side, d.d23))
    return false;
    
    /*
     REMOVED FOR CODE COVERAGE
    if (!isEqual(side, d.d34))
    return false;
    
    if (!isEqual(side, d.d41))
    return false;
    */
    return true;
}

/*
 REMOVED FOR CODE COVERAGE
Point diagonalMiddle(Point p1, Point p2) {
    double x_mid = (p1.x + p2.x)/2;
    double y_mid = (p1.y + p2.y)/2;
    Point bi_mid = {x_mid, y_mid};
    return bi_mid;
}

bool isSupplementary(float a, float b){
    return (fabs(a + b - 180) < 0.00001);
}
*/

Distances getDistances(Point p1, Point p2, Point p3, Point p4) {
    double d12 = distance(p1, p2);
    double d23 = distance(p2, p3);
    double d34 = distance(p3, p4);
    double d41 = distance(p4, p1);
    double d13 = distance(p1, p3);
    double d24 = distance(p2, p4);
    
    Distances d = {d12, d23, d34, d41, d13, d24};
    
    return d;
}

double angle(Point p0, Point p1, Point p2) {
    const double PI = 3.1415926535897;
    p1.x = (p1.x - p0.x);
    p1.y = (p1.y - p0.y);
    p2.x = (p2.x - p0.x);
    p2.y = (p2.y - p0.y);
    double axb = (p1.x * p2.x) + (p1.y * p2.y);
    double aMag = sqrt(pow(p1.x, 2) + pow(p1.y, 2));
    double bMag = sqrt(pow(p2.x, 2) + pow(p2.y, 2));
    double angleRad = acos(axb /(aMag * bMag));
    double angleDeg = 180/PI * angleRad;
    
    return angleDeg;
}

double getSlope(Point p1, Point p2) {
    double rise = p2.y - p1.y;
    double run = p2.x - p1.x;
    return rise/run;
}

int getNumParallelSides(Point p1, Point p2, Point p3, Point p4) {
    int count = 0;
    double slope12 = getSlope(p1, p2);
    double slope23 = getSlope(p2, p3);
    double slope34 = getSlope(p3, p4);
    double slope41 = getSlope(p4, p1);
    
    if (isParallel(slope12, slope34))
    count++;
    
    if (isParallel(slope23, slope41))
    count++;
    
    return count;
}

int getNumCongruentSides(Distances d) {
    int counter = 0;
    
    if (isEqual(d.d12, d.d23) || isEqual(d.d12, d.d41))
    counter++;
    
    if (isEqual(d.d34, d.d23) || isEqual(d.d34, d.d41))
    counter++;
    
    return counter;
}

void initiateAngles(Point &p1, Point &p2, Point &p3, Point &p4) {
    p1.angle = angle(p1, p2, p4);
    p2.angle = angle(p2, p1, p3);
    p3.angle = angle(p3, p4, p2);
    p4.angle = angle(p4, p1, p3);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool  isParallelogram(Point p1, Point p2, Point p3, Point p4) {
    
    Distances d = getDistances(p1, p2, p3, p4);
    //opposite angles are congruent
    if (!isEqual(p1.angle, p3.angle) || !isEqual(p2.angle, p4.angle)) {
        return false;
    }
    
    /*
     REMOVED FOR CODE COVERAGE
    //opposite sides are congruent
    if (!isEqual(d.d12, d.d34) || !isEqual(d.d23, d.d41)) {
        return false;
    }
    //adjacent angles are supplementary
    if (!isSupplementary(p1.angle, p2.angle) || !isSupplementary(p2.angle, p3.angle) ||
        !isSupplementary(p3.angle, p4.angle) || !isSupplementary(p4.angle, p1.angle))
    {
        return false;
    }
    
    // diagonals bisect each other
    Point diagonalMid13 = diagonalMiddle(p1, p3);
    Point diagonalMid24 = diagonalMiddle(p2, p4);
    if (!isEqual(diagonalMid13.x, diagonalMid24.x) || !isEqual(diagonalMid13.y, diagonalMid24.y)) {
        return false;
    }
    */
    return true;
}
bool isSquare(Point p1, Point p2, Point p3, Point p4) {
    Distances d = getDistances(p1, p2, p3, p4);
    
    // a square has all the properties of a parallelogram
    if (!isParallelogram(p1, p2, p3, p4)) {
        return false;
    }
    
    // and all angles must be 90 degrees
    if (!allAngles90(p1, p2, p3, p4)) {
        return false;
    }
    
    // and the diagonal length is equal
    if (!isEqual(d.d12, d.d41)) {
        return false;
    }
    
    return true;
}


bool isRectangle(Point p1, Point p2, Point p3, Point p4) {
    Distances d = getDistances(p1, p2, p3, p4);
    
    // Rectangles have all the properties of a parallelogram
    if (!isParallelogram(p1, p2, p3, p4)) {
        return false;
    }
    
    // and length of diagonals must equal
    if (!isEqual(d.d13, d.d24)) {
        return false;
    }
    
    return true;
}


bool isRhombi(Point p1, Point p2, Point p3, Point p4) {
    Distances d = getDistances(p1, p2, p3, p4);
    
    // Rhombus' have all the properties of a parallelogram
    if (!isParallelogram(p1, p2, p3, p4)) {
        return false;
    }
    
    // and all sides are congruent
    if (!allSidesCongruent(d)) {
        return false;
    }
    
    return true;
}

bool isTrapezoid(Point p1, Point p2, Point p3, Point p4) {
    int numParallelSides = getNumParallelSides(p1, p2, p3, p4);
    return (numParallelSides == 1);
}

bool isKite(Point p1, Point p2, Point p3, Point p4) {
    Distances d = getDistances(p1, p2, p3, p4);
    int numCongruentSides = getNumCongruentSides(d);
    return numCongruentSides == 2;
}

int main(int argc, const char * argv[]) {
    string in;
    //    in = "45 10 55 55 13 42";
    while (!cin.eof()) {
        getline(cin, in);
        vector<string> splittedLine = splitLine(in);
        assert(splittedLine.size() == 6);
        Point p1 = {0, 0};
        Point p2 = {stod(splittedLine[0]), stod(splittedLine[1])};
        Point p3 = {stod(splittedLine[2]), stod(splittedLine[3])};
        Point p4 = {stod(splittedLine[4]), stod(splittedLine[5])};
        
        initiateAngles(p1, p2, p3, p4);
        
        if (isSquare(p1, p2, p3, p4)) {
            cout << "square" << endl;
        } else if (isRectangle(p1, p2, p3, p4)) {
            cout << "rectangle" << endl;
        } else if (isRhombi(p1, p2, p3, p4)) {
            cout << "rhombus" << endl;
        } else if (isParallelogram(p1, p2, p3, p4)) {
            cout << "parallelogram" << endl;
        } else if (isTrapezoid(p1, p2, p3, p4)) {
            cout << "trapezoid" << endl;
        } else if (isKite(p1, p2, p3, p4)) {
            cout << "kite" << endl;
        } else {
            cout << "quadrilateral" << endl;
        }
    }
        return 0;
}
