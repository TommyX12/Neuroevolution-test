#include "engine/includes/utils.h"

namespace Nebula
{
    Vec2D::Vec2D()
    {
        this->x = this->y = 0;
    }

    Vec2D::Vec2D(float64 x, float64 y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2D::~Vec2D()
    {
        //dtor
    }
    
    Vec2D Vec2D::operator+(const Vec2D& b)
    {
        return Vec2D(this->x + b.x, this->y + b.y);
    }
    
    Vec2D Vec2D::operator-(const Vec2D& b)
    {
        return Vec2D(this->x - b.x, this->y - b.y);
    }
    
    Vec2D Vec2D::operator*(float64 m)
    {
        return Vec2D(this->x * m, this->y * m);
    }
    
    Vec2D Vec2D::operator/(float64 m)
    {
        return Vec2D(this->x / m, this->y / m);
    }
    
    Vec2D& Vec2D::operator=(const Vec2D& b)
    {
        this->x = b.x;
        this->y = b.y;
        return *this;
    }
    
    bool Vec2D::operator==(const Vec2D& b)
    {
        return this->x == b.x && this->y == b.y;
    }
    
    Vec2D& Vec2D::operator+=(const Vec2D& b)
    {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }
    
    Vec2D& Vec2D::operator-=(const Vec2D& b)
    {
        this->x -= b.x;
        this->y -= b.y;
        return *this;
    }
    
    Vec2D& Vec2D::operator*=(float64 m)
    {
        this->x *= m;
        this->y *= m;
        return *this;
    }
    
    Vec2D& Vec2D::operator/=(float64 m)
    {
        this->x /= m;
        this->y /= m;
        return *this;
    }
    
    Vec2D& Vec2D::reset()
    {
        this->x = this->y = 0;
        return *this;
    }
    
    float64 Vec2D::distance(const Vec2D& b)
    {
        float64 dx = b.x - this->x;
        float64 dy = b.y - this->y;
        return sqrt(dx*dx + dy*dy);
    }
    
    float64  Vec2D::distanceSq(const Vec2D& b)
    {
        float64 dx = b.x - this->x;
        float64 dy = b.y - this->y;
        return dx*dx + dy*dy;
    }
    
    Vec2D& Vec2D::addDirectional(float64 distance, float64 angle)
    {
        this->x += cos(Convert::rad(angle)) * distance;
        this->y += sin(Convert::rad(angle)) * distance;
        return *this;
    }
    
    float64 Vec2D::length()
    {
        return sqrt(this->x*this->x + this->y*this->y);
    }
    
    float64 Vec2D::lengthSq()
    {
        return this->x*this->x + this->y*this->y;
    }
    
    float64 Vec2D::angle()
    {
        return Convert::deg(atan2(this->y, this->x));
    }
    
    float64 Vec2D::angleTo(const Vec2D& b)
    {
        return Convert::deg(atan2(b.y - this->y, b.x - this->x));
    }
    
    Vec2D& Vec2D::rotate(float64 degree)
    {
        float64 rads = Convert::rad(degree);
        float64 s = sin(rads);
        float64 c = cos(rads);
        float64 xr = this->x * c - this->y * s;
        this->y = this->x * s + this->y * c;
        this->x = xr;
        return *this;
    }
}


/*
class Vec2DConst {
	
	public static var Zero(default, null):Vec2DConst = new Vec2DConst();
    private static var _RadsToDeg:Float = 180 / Math.PI;

    private var _x:Float;
    private var _y:Float;

    public var x(get, set):Float;
    @:noCompletion private function get_x():Float { return _x; }
    @:noCompletion private function set_x(value:Float):Float {
		return value;
	}

    public var y(get, set):Float;
    @:noCompletion private function get_y():Float { return _y; }
    @:noCompletion private function set_y(value:Float):Float {
		return value;
	}
	
	public static function createFromRandDir(distance:Float=1.0):Vec2DConst
    {
        var rads:Float = Math.random() * Math.PI * 2;
        return new Vec2DConst(Math.cos(rads) * distance, Math.sin(rads) * distance);
    }
	
	public static function createFromDir(angle:Float, distance:Float=1.0, radian:Bool=false):Vec2DConst
    {
        var rads:Float = radian ? angle : angle / 180 * Math.PI;
        return new Vec2DConst(Math.cos(rads) * distance, Math.sin(rads) * distance);
    }

    public function new(x:Float = 0, y:Float = 0):Void
    {
        _x = x;
        _y = y;
    }

    public function clone():Vec2D { return new Vec2D(_x, _y); }

    public inline function add(pos:Vec2DConst):Vec2D { return new Vec2D(_x + pos._x, _y + pos._y); }
    public inline function addXY(x:Float, y:Float):Vec2D { return new Vec2D(_x + x, _y + y); }

    public inline function sub(pos:Vec2DConst):Vec2D { return new Vec2D(_x - pos._x, _y - pos._y); }
    public inline function subXY(x:Float, y:Float):Vec2D { return new Vec2D(_x - x, _y - y); }

    public inline function mul(vec:Vec2DConst):Vec2D { return new Vec2D(_x * vec._x, _y * vec._y); }
    public inline function mulXY(x:Float, y:Float):Vec2D { return new Vec2D(_x * x, _y * y); }

    public inline function div(vec:Vec2DConst):Vec2D { return new Vec2D(_x / vec._x, _y / vec._y); }
    public inline function divXY(x:Float, y:Float):Vec2D { return new Vec2D(_x / x, _y / y); }

    public inline function scale(s:Float):Vec2D { return new Vec2D(_x * s, _y * s); }

    public inline function rescale(newLength:Float):Vec2D
    {
        var nf:Float = newLength / Math.sqrt(_x * _x + _y * _y);
        return new Vec2D(_x * nf, _y * nf);
    }

    public inline function normalize():Vec2D
    {
        var nf:Float = 1 / Math.sqrt(_x * _x + _y * _y);
        return new Vec2D(_x * nf, _y * nf);
    }

    public inline function length():Float { return Math.sqrt(_x * _x + _y * _y); }
    public inline function lengthSqr():Float { return _x * _x + _y * _y; }
    public inline function distance(vec:Vec2DConst):Float
    {
        var xd:Float = _x - vec._x;
        var yd:Float = _y - vec._y;
        return Math.sqrt(xd * xd + yd * yd);
    }
    public inline function distanceXY(x:Float, y:Float):Float
    {
        var xd:Float = _x - x;
        var yd:Float = _y - y;
        return Math.sqrt(xd * xd + yd * yd);
    }
    public inline function distanceSqr(vec:Vec2DConst):Float
    {
        var xd:Float = _x - vec._x;
        var yd:Float = _y - vec._y;
        return xd * xd + yd * yd;
    }
    public inline function distanceXYSqr(x:Float, y:Float):Float
    {
        var xd:Float = _x - x;
        var yd:Float = _y - y;
        return xd * xd + yd * yd;
    }

    public inline function equals(vec:Vec2DConst):Bool { return _x == vec._x && _y == vec._y; }
    public inline function equalsXY(x:Float, y:Float):Bool { return _x == x && _y == y; }
    public inline function isNormalized():Bool { return Util.abs((_x * _x + _y * _y)-1) < Vec2D.EpsilonSqr; }
    public inline function isZero():Bool { return _x == 0 && _y == 0; }
    public inline function isNear(vec2:Vec2DConst):Bool { return distanceSqr(vec2) < Vec2D.EpsilonSqr; }
    public inline function isNearXY(x:Float, y:Float):Bool { return distanceXYSqr(x, y) < Vec2D.EpsilonSqr; }
    public inline function isWithin(vec2:Vec2DConst, epsilon:Float):Bool { return distanceSqr(vec2) < epsilon*epsilon; }
    public inline function isWithinXY(x:Float, y:Float, epsilon:Float):Bool { return distanceXYSqr(x, y) < epsilon*epsilon; }
    public inline function isValid():Bool { return !Math.isNaN(_x) && !Math.isNaN(_y) && Math.isFinite(_x) && Math.isFinite(_y); }
    public inline function getDegrees():Float { return getRads() * _RadsToDeg; }
    public inline function getRads():Float { return Math.atan2(_y, _x); }
    public inline function getRadsBetween(vec:Vec2DConst):Float { return Math.atan2(x - vec.x, y - vec.y); }

    public inline function dot(vec:Vec2DConst):Float { return _x * vec._x + _y * vec._y; }
    public inline function dotXY(x:Float, y:Float):Float { return _x * x + _y * y; }

    public inline function crossDet(vec:Vec2DConst):Float { return _x * vec._y - _y * vec._x; }
    public inline function crossDetXY(x:Float, y:Float):Float { return _x * y - _y * x; }

    public inline function rotate(rads:Float):Vec2D
    {
        var s:Float = Math.sin(rads);
        var c:Float = Math.cos(rads);
        return new Vec2D(_x * c - _y * s, _x * s + _y * c);
    }
    public inline function normalRight():Vec2D { return new Vec2D(-_y, _x); }
    public inline function normalLeft():Vec2D { return new Vec2D(_y, -_x); }
    public inline function negate():Vec2D { return new Vec2D( -_x, -_y); }

    public inline function rotateSpinorXY(x:Float, y:Float):Vec2D { return new Vec2D(_x * x - _y * y, _x * y + _y * x); }
    public inline function rotateSpinor(vec:Vec2DConst):Vec2D { return new Vec2D(_x * vec._x - _y * vec._y, _x * vec._y + _y * vec._x); }
    public inline function spinorBetween(vec:Vec2DConst):Vec2D
    {
        var d:Float = lengthSqr();
        var r:Float = (vec._x * _x + vec._y * _y) / d;
        var i:Float = (vec._y * _x - vec._x * _y) / d;
        return new Vec2D(r, i);
    }

    public inline function lerp(to:Vec2DConst, t:Float):Vec2D { return new Vec2D(_x + t * (to._x - _x), _y + t * (to._y - _y)); }

    public inline function slerp(vec:Vec2DConst, t:Float):Vec2D
    {
        var cosTheta:Float = dot(vec);
        var theta:Float = Math.acos(cosTheta);
        var sinTheta:Float = Math.sin(theta);
        if (sinTheta <= Vec2D.Epsilon)
            return vec.clone();
        var w1:Float = Math.sin((1 - t) * theta) / sinTheta;
        var w2:Float = Math.sin(t * theta) / sinTheta;
        return scale(w1).add(vec.scale(w2));
    }

    public inline function reflect(normal:Vec2DConst):Vec2D
    {
        var d:Float = 2 * (_x * normal._x + _y * normal._y);
        return new Vec2D(_x - d * normal._x, _y - d * normal._y);
    }

    public function toString():String { return "[" + _x + ", " + _y + "]"; }

    public function getMin(p:Vec2DConst):Vec2D { return new Vec2D(Util.min(p._x, _x), Util.min(p._y, _y)); }
    public function getMax(p:Vec2DConst):Vec2D { return new Vec2D(Util.max(p._x, _x), Util.max(p._y, _y)); }

}

class Vec2D extends Vec2DConst
{
    
    public static inline var Epsilon:Float = 0.0000001;
    public static inline var EpsilonSqr:Float = Epsilon * Epsilon;

    public function new(x:Float = 0, y:Float = 0) { super(x, y); }

    @:noCompletion override private function set_x(value:Float):Float {
		return _x = value;
	}

    @:noCompletion override private function set_y(value:Float):Float {
		return _y = value;
	}

    public inline function copy(pos:Vec2DConst):Vec2D
    {
        _x = pos._x;
        _y = pos._y;
        return this;
    }
    public inline function copyXY(x:Float, y:Float):Vec2D
    {
        _x = x;
        _y = y;
        return this;
    }
    public inline function zero():Vec2D
    {
        _x = 0;
        _y = 0;
        return this;
    }

    public inline function addSelf(pos:Vec2DConst):Vec2D
    {
        _x += pos._x;
        _y += pos._y;
        return this;
    }
    public inline function addXYSelf(x:Float, y:Float):Vec2D
    {
        _x += x;
        _y += y;
        return this;
    }

    public inline function subSelf(pos:Vec2DConst):Vec2D
    {
        _x -= pos._x;
        _y -= pos._y;
        return this;
    }
    public inline function subXYSelf(x:Float, y:Float):Vec2D
    {
        _x -= x;
        _y -= y;
        return this;
    }

    public inline function mulSelf(vec:Vec2DConst):Vec2D
    {
        _x *= vec._x;
        _y *= vec._y;
        return this;
    }
    public inline function mulXYSelf(x:Float, y:Float):Vec2D
    {
        _x *= x;
        _y *= y;
        return this;
    }
	public inline function mulValueSelf(value:Float):Vec2D
    {
        _x *= value;
        _y *= value;
        return this;
    }

    public inline function divSelf(vec:Vec2DConst):Vec2D
    {
        _x /= vec._x;
        _y /= vec._y;
        return this;
    }
	public inline function divXYSelf(x:Float, y:Float):Vec2D
    {
        _x /= x;
        _y /= y;
        return this;
    }
    public inline function divValueSelf(value:Float):Vec2D
    {
        _x /= value;
        _y /= value;
        return this;
    }

    public inline function scaleSelf(s:Float):Vec2D
    {
        _x *= s;
        _y *= s;
        return this;
    }

    public inline function rescaleSelf(newLength:Float):Vec2D
    {
        var nf:Float = newLength / Math.sqrt(_x * _x + _y * _y);
        _x *= nf;
        _y *= nf;
        return this;
    }

    public inline function normalizeSelf():Vec2D
    {
        var nf:Float = 1 / Math.sqrt(_x * _x + _y * _y);
        _x *= nf;
        _y *= nf;
        return this;
    }

    public inline function rotateSelf(rads:Float):Vec2D
    {
        var s:Float = Math.sin(rads);
        var c:Float = Math.cos(rads);
        var xr:Float = _x * c - _y * s;
        _y = _x * s + _y * c;
        _x = xr;
        return this;
    }
    public inline function normalRightSelf():Vec2D
    {
        var xr:Float = _x;
        _x = -_y;
        _y = xr;
        return this;
    }
    public inline function normalLeftSelf():Vec2D
    {
        var xr:Float = _x;
        _x = _y;
        _y = -xr;
        return this;
    }
    public inline function negateSelf():Vec2D
    {
        _x = -_x;
        _y = -_y;
        return this;
    }

    public inline function rotateSpinorSelf(vec:Vec2DConst):Vec2D
    {
        var xr:Float = _x * vec._x - _y * vec._y;
        _y = _x * vec._y + _y * vec._x;
        _x = xr;
        return this;
    }

    public inline function lerpSelf(to:Vec2DConst, t:Float):Vec2D
    {
        _x = _x + t * (to._x - _x);
        _y = _y + t * (to._y - _y);
        return this;
    }

    public static function swap(a:Vec2D, b:Vec2D):Void
    {
        var x:Float = a._x;
        var y:Float = a._y;
        a._x = b._x;
        a._y = b._y;
        b._x = x;
        b._y = y;
    }
}

*/
