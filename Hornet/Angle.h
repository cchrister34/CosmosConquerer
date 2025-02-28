#pragma once
#include <cmath>
#include <string>

// This is a largely untested class to store an angle in degrees.
// The value of the angle is restriced to [0 to 360).
// This means that 0 is possible 360 is not: 0<=angle<360
// There is a function to provide the shortest angle difference.
// Free casting to/from a double is supported

class Angle
{
private:
    static const double  PI;
    double m_angle;
    void Normalise()
    {
        m_angle = fmod(m_angle, 360.0);
        if (m_angle < 0)
            m_angle += 360.0;
    }
public:
    Angle();
    Angle(const Angle& angle);
    Angle(double degrees);
    Angle(float degrees);
    Angle(int degrees);
    Angle(short degrees);

    // Returns the shortest angle difference between two angles, in range
    // (-180 to +180]
    double difference(const Angle& other);

    // Returns the angle in degrees
    double value() const;
    // Returns the angle in radians
    double radians() const;
    // Returns the angle in the range (-180,+180)
    double offset() const;

    // Converts a value from radians
    void setRadians(double radians);

    // Sets the value in degrees, in range [0,360)
    void setDegrees(double degrees);

    // All assignment operators return values in range [0,360)
    Angle& operator =(Angle& angle);
    Angle& operator =(double degrees);
    Angle& operator =(float degrees);
    Angle& operator =(int degrees);
    Angle& operator =(short degrees);

    // All mathematical operators return values in range [0,360)
    Angle operator +(Angle angle)const;
    Angle operator -(Angle angle)const;
    Angle& operator+=(Angle add);
    Angle& operator-=(Angle sub);
    Angle operator *(double mul)const;
    Angle operator /(double div)const;
    Angle& operator*=(Angle mul);
    Angle& operator/=(Angle div);

    bool operator ==(const Angle& other)const;

    // Returns the angle: 360-angle, in range [0,360)
    Angle operator-()const;

    // Converts the angle to a string, with the specified
    // decimal places
    std::string toString(int decimalPlaces = 6);
};

