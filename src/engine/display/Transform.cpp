#include "engine/includes/display.h"

namespace Nebula
{
    Transform::Transform()
    {
        this->a = 1;
        this->b = 0;
        this->c = 0;
        this->d = 1;

        this->tx = 0;
        this->ty = 0;
        this->tz = 0;

        this->red = 1;
        this->green = 1;
        this->blue = 1;
        this->alpha = 1;
    }

    Transform::~Transform()
    {
        //dtor
    }

    Transform& Transform::combine_global(Transform &child)
    {
        this->a = child.a;
        this->b = child.b;
        this->c = child.c;
        this->d = child.d;

        this->tx = child.tx;
        this->ty = child.ty;
        this->tz = child.tz;

        this->red = child.red;
        this->green = child.green;
        this->blue = child.blue;
        this->alpha = child.alpha;

        return *this;
    }

    Transform& Transform::combine_local(Transform &child, Transform &parent)
	{
		float64 b00 = child.a;
		float64 b01 = child.b;
		float64 b10 = child.c;
		float64 b11 = child.d;
		float64 btx = child.tx;
		float64 bty = child.ty;
		float64 a00 = parent.a;
		float64 a01 = parent.b;
		float64 a10 = parent.c;
		float64 a11 = parent.d;
		float64 atx = parent.tx;
		float64 aty = parent.ty;

		this->a = a00 * b00 + a01 * b10;
		this->b = a00 * b01 + a01 * b11;
		this->c = a10 * b00 + a11 * b10;
		this->d = a10 * b01 + a11 * b11;
		this->tx = btx * a00 + bty * a01 + atx;
		this->ty = btx * a10 + bty * a11 + aty;
		this->tz = child.tz + parent.tz;

        this->red = parent.red * child.red;
        this->green = parent.green * child.green;
        this->blue = parent.blue * child.blue;
		this->alpha = parent.alpha * child.alpha;

		return *this;
	}
}
