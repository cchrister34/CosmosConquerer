#include "Angle.h"
#include<cmath>
#include <format>

const double Angle::PI = 3.1415926535897932384626433;

Angle::Angle():m_angle(0)
{
}

Angle::Angle(const Angle& angle):m_angle(angle.m_angle)
{
}

Angle::Angle(double degrees): m_angle(degrees)
{
    Normalise();
}

Angle::Angle(float degrees) : m_angle(degrees)
{
    Normalise();
}

Angle::Angle(int degrees) : m_angle(degrees)
{
    Normalise();
}

Angle::Angle(short degrees) : m_angle(degrees)
{
    Normalise();
}

double Angle::difference(const Angle& other)
{
    double answer = other.m_angle - m_angle;
    if (answer > 180) answer = answer - 360;
    return answer;
}

double Angle::value() const
{
    return m_angle;
}

double Angle::radians() const
{
    return m_angle/180*PI;
}

double Angle::offset() const
{
    if (m_angle <= 180) return m_angle;
    else return m_angle - 360;
}

void Angle::setRadians(double radians)
{
    m_angle = radians / PI * 180;
    Normalise();
}

void Angle::setDegrees(double degrees)
{
    m_angle = degrees;
    Normalise();
}

Angle& Angle::operator=(double degrees)
{
    m_angle = degrees;
    Normalise();
    return *this;
}

Angle& Angle::operator=(Angle& other)
{
    m_angle = other.m_angle;
    return *this;
}


Angle& Angle::operator=(float degrees)
{
    m_angle = degrees;
    Normalise();
    return *this;
}

Angle& Angle::operator=(int degrees)
{
    m_angle = degrees;
    Normalise();
    return *this;
}

Angle& Angle::operator=(short degrees)
{
    m_angle = degrees;
    Normalise();
    return *this;
}

Angle Angle::operator+(Angle other) const
{
    return Angle( this->m_angle + other.m_angle);
}

Angle Angle::operator-(Angle other) const
{
    return Angle(this->m_angle - other.m_angle);
}

Angle& Angle::operator+=(Angle add)
{
    m_angle += add.m_angle;
    Normalise();
    return *this;
}

Angle& Angle::operator-=(Angle sub)
{
    m_angle -= sub.m_angle;
    Normalise();
    return *this;
}

Angle Angle::operator*(double mul) const
{
    return Angle(this->m_angle * mul);
}

Angle Angle::operator/(double div) const
{
    return Angle(this->m_angle / div);
}

Angle& Angle::operator*=(Angle mul)
{
    m_angle *= mul.m_angle;
    Normalise();
    return *this;
}

Angle& Angle::operator/=(Angle div)
{
    m_angle /= div.m_angle;
    Normalise();    // Not needed
    return *this;
}

bool Angle::operator==(const Angle& other) const
{
    return other.m_angle==m_angle;
}

Angle Angle::operator-() const
{
    return Angle(360-m_angle);
}

std::string Angle::toString(int decimalPlaces)
{
    if (decimalPlaces < 0) decimalPlaces = 0;
    if (decimalPlaces > 6) decimalPlaces = 6;
    std::string answer = std::to_string(m_angle);
    answer += "000000";
    size_t dot = answer.find('.');
    if (decimalPlaces == 0) --dot;
    answer = answer.substr(0, dot + decimalPlaces+1);

    return answer;
}
