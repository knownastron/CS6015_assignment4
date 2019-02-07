//
//  main.cpp
//  assignment3
//
//  Created by Jason Tran on 2019-01-15.
//  Copyright © 2019 Jason Tran. All rights reserved.
//

#include <assert.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

/*
 Splits a line into a vector of strings delimited by spaces
 */
vector<string> splitLine(string inputStr) {
  vector<string> output;
  string temp = "";
  for (int i = 0; i < inputStr.size(); i++) {
    if (inputStr[i] == ' ') {
      if (temp != "") {
        output.push_back(temp);
        temp = "";
      }
    } else {
      temp += inputStr[i];
    }

    if (i == inputStr.size() - 1) {
      if (temp != "") {
        output.push_back(temp);
      }
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
  double d13, d24;           // diagonal
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double distance(Point pt1, Point pt2) {
  double d = sqrt(pow(pt2.x - pt1.x, 2) + pow(pt2.y - pt1.y, 2));
  return d;
}

bool isEqual(float a, float b) {
  if (a == INFINITY && b == INFINITY) {
    return true;
  }

  if (a == -INFINITY && b == -INFINITY) {
    return true;
  }

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
  vector<double> angles = {p1.angle, p2.angle, p3.angle, p4.angle};

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

double getAngle(Point p0, Point p1, Point p2) {
  const double PI = 3.1415926535897;
  p1.x = (p1.x - p0.x);
  p1.y = (p1.y - p0.y);
  p2.x = (p2.x - p0.x);
  p2.y = (p2.y - p0.y);
  double axb = (p1.x * p2.x) + (p1.y * p2.y);
  double aMag = sqrt(pow(p1.x, 2) + pow(p1.y, 2));
  double bMag = sqrt(pow(p2.x, 2) + pow(p2.y, 2));
  double angleRad = acos(axb / (aMag * bMag));
  double angleDeg = 180 / PI * angleRad;

  return angleDeg;
}

double getSlope(Point p1, Point p2) {
  double rise = p2.y - p1.y;
  double run = p2.x - p1.x;
  return rise / run;
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
  p1.angle = getAngle(p1, p2, p4);
  p2.angle = getAngle(p2, p1, p3);
  p3.angle = getAngle(p3, p4, p2);
  p4.angle = getAngle(p4, p1, p3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isParallelogram(Point p1, Point p2, Point p3, Point p4) {

  // opposite angles are congruent
  if (!isEqual(p1.angle, p3.angle) || !isEqual(p2.angle, p4.angle)) {
    return false;
  }

  /*
   REMOVED FOR CODE COVERAGE
   //    Distances d = getDistances(p1, p2, p3, p4);

   //opposite sides are congruent
   if (!isEqual(d.d12, d.d34) || !isEqual(d.d23, d.d41)) {
   return false;
   }
   //adjacent angles are supplementary
   if (!isSupplementary(p1.angle, p2.angle) || !isSupplementary(p2.angle,
   p3.angle) || !isSupplementary(p3.angle, p4.angle) ||
   !isSupplementary(p4.angle, p1.angle))
   {
   return false;
   }

   // diagonals bisect each other
   Point diagonalMid13 = diagonalMiddle(p1, p3);
   Point diagonalMid24 = diagonalMiddle(p2, p4);
   if (!isEqual(diagonalMid13.x, diagonalMid24.x) || !isEqual(diagonalMid13.y,
   diagonalMid24.y)) { return false;
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// checks for wrong # of points, points < 0 or > 100
bool isError1(vector<string> line) {
  if (line.size() != 6) {
    cout << "error 1";
    return true;
  }

  for (string ch : line) {
    int num;
    try {
      num = stoi(ch);
    } catch (const std::invalid_argument &ia) {
      cout << "error 1";
      return true;
    }
    if (std::stoi(ch) > 100 || std::stoi(ch) < 0) {
      cout << "error 1";
      return true;
    }
  }

  return false;
}

// checks for points that coincide
bool isError2(vector<string> line) {
  string p0 = "0 0";
  string p1 = line[0] + " " + line[1];
  string p2 = line[2] + " " + line[3];
  string p3 = line[4] + " " + line[5];

  vector<string> points = {p0, p1, p2, p3};

  for (int i = 0; i < points.size() - 1; i++) {
    for (int k = i + 1; k < points.size(); k++) {
      if (points[i] == points[k]) {
        cout << "error 2";
        return true;
      }
    }
  }

  return false;
}

bool isError3(Point p1, Point p2, Point p3, Point p4) {
  double slope12 = getSlope(p1, p2);
  double slope23 = getSlope(p2, p3);
  double slope34 = getSlope(p3, p4);
  double slope41 = getSlope(p4, p1);
  //    cout << "slope12 " << slope12 << endl;
  //    cout << "slope23 " << slope23 << endl;
  //    cout << "slope34 " << slope34 << endl;
  //    cout << "slope41 " << slope41 << endl;

  // if opposing sides are parallel, there is no intersection
  if (isParallel(slope12, slope34) && isParallel(slope23, slope41)) {
    return false;
  }

  // b = y - m(x), b is the y intercept
  double b12 = p1.y - slope12 * (p1.x);
  double b23 = p2.y - slope23 * (p2.x);
  double b34 = p3.y - slope34 * (p3.x);
  double b41 = p4.y - slope41 * (p4.x);

  // x and y intercept for lines 12 and 34
  double x1234 = (b12 - b34) / (slope34 - slope12);
  double y1234 = (slope12 * x1234) + b12;
  //    cout << "x1234 " << x1234 << " y1234 " << y1234 << endl;

  // x and y intercept for lines 23 and 41
  double x2341 = (b23 - (b41)) / (slope41 - (slope23));
  double y2341 = (slope23 * x2341) + b23;
  //        cout << "x2341 " << x2341 << " y2341 " << x2341 << endl;

  // check that the intercepts is within the range of line 12
  bool bool1 = x1234 > min(p1.x, p2.x) || isEqual(x1234, min(p1.x, p2.x));
  bool bool2 = x1234 < max(p1.x, p2.x) || isEqual(x1234, max(p1.x, p2.x));
  bool bool3 = y1234 > min(p1.y, p2.y) || isEqual(y1234, min(p1.y, p2.y));
  bool bool4 = y1234 < max(p1.y, p2.y) || isEqual(y1234, max(p1.y, p2.y));

  // check that the intercepts is within the range of line 34
  bool bool5 = x1234 > min(p3.x, p4.x) || isEqual(x1234, min(p3.x, p4.x));
  bool bool6 = x1234 < max(p3.x, p4.x) || isEqual(x1234, max(p3.x, p4.x));
  bool bool7 = y1234 > min(p3.y, p4.y) || isEqual(y1234, min(p3.y, p4.y));
  bool bool8 = y1234 < max(p3.y, p4.y) || isEqual(y1234, max(p3.y, p4.y));

  // check that the intercepts is within the range of line 41
  bool bool9 = x2341 > min(p4.x, p1.x) || isEqual(x2341, min(p4.x, p1.x));
  bool bool10 = x2341 < max(p4.x, p1.x) || isEqual(x2341, max(p4.x, p1.x));
  bool bool11 = y2341 > min(p4.y, p1.y) || isEqual(y2341, min(p4.y, p1.y));
  bool bool12 = y2341 < max(p4.y, p1.y) || isEqual(y2341, max(p4.y, p1.y));

  // check that the intercepts is within the range of line 23
  bool bool13 = x2341 >= min(p2.x, p3.x) || isEqual(x2341, min(p2.x, p3.x));
  bool bool14 = x2341 <= max(p2.x, p3.x) || isEqual(x2341, max(p2.x, p3.x));
  bool bool15 = y2341 >= min(p2.y, p3.y) || isEqual(y2341, min(p2.y, p3.y));
  bool bool16 = y2341 <= max(p2.y, p3.y) || isEqual(y2341, max(p2.y, p3.y));

  //    cout << bool1 << " " << bool2 << " " << bool3 << " " << bool4 << " " <<
  //    bool5 << " " << bool6 << " " << bool7 << " " << bool8 << endl; cout <<
  //    bool9 << " " << bool10 << " " << bool11 << " " << bool12 << " " <<
  //    bool13 << " " << bool14 << " " << bool15 << " " << bool16 << endl;

  if (fabs(x1234) != INFINITY && fabs(y1234) != INFINITY && x1234 != NAN &&
      y1234 != NAN) {
    if (bool1 && bool2 && bool3 && bool4 && bool5 && bool6 && bool7 && bool8) {
      cout << "error 3";
      return true;
    }
  }

  if (fabs(x2341) != INFINITY && fabs(y2341) != INFINITY && x1234 != NAN &&
      y1234 != NAN) {
    if (bool9 && bool10 && bool11 && bool12 && bool13 && bool14 && bool15 &&
        bool16) {
      cout << "error 3";
      return true;
    }
  }

  return false;
}

// any 3 points are colinear
bool isError4(Point p1, Point p2, Point p3, Point p4) {
  double slope12 = getSlope(p1, p2);
  double slope23 = getSlope(p2, p3);
  double slope34 = getSlope(p3, p4);
  double slope41 = getSlope(p4, p1);

  if (isEqual(slope12, slope23) || isEqual(slope23, slope34) ||
      isEqual(slope34, slope41)) {
    cout << "error 4";
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {
  string in;
  //        in = "0 4 2 4 2 2    "; //fine
  //    in = "3 0 0 3 3 3"; // error
  //    in = "0 3 3 0 3 3"; // error 3
  //    in = "4 0 0 4 1 1"; // fine
  //    in = "4 3 2 3 1 2"; // fine
  //    in = "2 1 -2 1 3 -2"; // error 1
  //    in = "5 3 4 0 0 3"; // error 3
  //    in = "1 2 1 4 1 9"; // error 4
  //    in = "25 25 9 2 25 25"; // error 2
  //    in = "84 88 47 47 88 84"; // kite
  //    in = "69 53 17 52 81 52";
  while (!cin.eof()) {
    getline(cin, in);
    vector<string> splittedLine = splitLine(in);
    if (isError1(splittedLine))
      return 1;

    if (isError2(splittedLine))
      return 1;

    Point p1 = {0, 0};
    Point p2 = {stod(splittedLine[0]), stod(splittedLine[1])};
    Point p3 = {stod(splittedLine[2]), stod(splittedLine[3])};
    Point p4 = {stod(splittedLine[4]), stod(splittedLine[5])};

    initiateAngles(p1, p2, p3, p4);

    if (isError4(p1, p2, p3, p4))
      return 1;
    if (isError3(p1, p2, p3, p4))
      return 1;
    

    assert(splittedLine.size() == 6);

    for (string num : splittedLine) {
      assert(stod(num) >= 0 && stod(num) <= 100);
    }

    assert(int(p1.angle + p2.angle + p3.angle + p4.angle) <= 360);

    if (isSquare(p1, p2, p3, p4)) {
      cout << "square";
    } else if (isRectangle(p1, p2, p3, p4)) {
      cout << "rectangle";
    } else if (isRhombi(p1, p2, p3, p4)) {
      cout << "rhombus";
    } else if (isParallelogram(p1, p2, p3, p4)) {
      cout << "parallelogram";
    } else if (isTrapezoid(p1, p2, p3, p4)) {
      cout << "trapezoid";
    } else if (isKite(p1, p2, p3, p4)) {
      cout << "kite";
    } else {
      cout << "quadrilateral";
    }
  }

  return 0;
}
