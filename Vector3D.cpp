#include "Vector3D.hpp"

Vector3D::Vector3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::printVector() const
{
    cout << '[' << x << ',' << y << ',' << z << ']' << endl;
}

double Vector3D::magnitude() const
{
    return sqrt(this->dot(*this)); 
}

Vector3D Vector3D::normalize() const
{
    return *this / this->magnitude();
}

double Vector3D::dot(Vector3D other) const
{
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3D Vector3D::cross(Vector3D other) const
{
    return Vector3D(this->y * other.z - this->z * other.y,
                    this->z * other.x - this->x * other.z,
                    this->x * other.y - this->y * other.x);
}

Vector3D Vector3D::rotateX(double angle) const 
{
    double rad = angle * 3.14159265359 / 180.0;
    return Vector3D(x, y * cos(rad) - z * sin(rad), y * sin(rad) + z * cos(rad));
}

Vector3D Vector3D::rotateY(double angle) const 
{
    double rad = angle * 3.14159265359 / 180.0;
    return Vector3D(x * cos(rad) + z * sin(rad), y, -x * sin(rad) + z * cos(rad));
}

Vector3D Vector3D::rotateZ(double angle) const 
{
    double rad = angle * 3.14159265359 / 180.0;
    return Vector3D(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad), z);
}

Vector3D Vector3D::operator+(Vector3D other) const
{
    return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3D Vector3D::operator-(Vector3D other) const
{
    return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3D Vector3D::operator*(double number) const
{
    return Vector3D(this->x * number, this->y * number, this->z * number);
}

Vector3D operator*(double number, const Vector3D& vector)
{
    return vector * number;
}

Vector3D Vector3D::operator/(double number) const
{
    return Vector3D(this->x / number, this->y / number, this->z / number);
}