#include "graphics.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class Point
{
	protected:
		int x, y;
		int color;
	public:
		Point()
		{
			x = 0;
			y = 0;
			color = 0;
		}
		Point(int x, int y)
		{
			this->x = x;
			this->y = y;
			color = 0;
		}
		Point(int x, int y, int color)
		{
			this->x = x;
			this->y = y;
			this->color = color;
		}
		Point(const Point& p1)
		{
			x = p1.x;
			y = p1.y;
			color = p1.color;
		}
		
		void draw();

		
		void move(int dx, int dy)
		{
			x += dx;
			y += dy;
		}
		
		void hide();
		
		void set(int xx, int yy, int cc);
		
		~Point() = default;
};


class Line : public Point
{
	protected:
		int x, y;
		unsigned long length;
		int color;
	public:
		Line()
		{
			x = 0;
			y = 0;
			length = 0;
			color = 0;
		}
		
		Line(int x, int y, int length, int color)
		{
			this->x = x;
			this->y = y;
			this->length =length;
			this->color = color;
		}
		
		Line(const Line& l)
		{
			this->x = l.x;
			this->y = l.y;
			this->color = l.color;
			this->length = l.length;
		}
		
		void draw_x()
		{
			int xx = x;
			for(int i = 0; i < length; ++i)
			{
				txSetPixel(xx++, y, color);
			}
		}
		
		void draw_y(){
			int yy = y;
			for(int i = 0; i < length; ++i)
			{
				txSetPixel(x, yy++, color);
			}
		}
		
		void draw(int i)
		{
			if(i)
				draw_x();
			else
				draw_y();
		
		}
		
		void move(int dx, int dy)
		{
			x += dx;
			y += dy;
		}
		
		void rotate(int angle){
			int yy = y;
			for(int i = 0; i < length; ++i)
			{
				txSetPixel(yy*tan(angle), yy++, color);
			}
		}
		
		void set(int xx, int yy, int cc, int ll)
		{
			x = xx;
			y = yy;
			color = cc;
			length = ll;
		}
		
		void hide(int i)
		{
			int t = color;
			color = 0;
			this->draw(i);
			color = t;
		}
		
		~Line() = default;
};

class Square : public Line
{
	protected:
		int x, y;
		int color;
		unsigned long length;
	public:
		Square(){
			x = 0;
			y = 0;
			color = 0;
			length = 0;
		}
		
		Square(int x, int y, int color, unsigned long length) : Line(x, y, length, color){
			this->x = x;
			this->y = y;
			this->color = color;
			this->length = length;
		}
		
		Square(const Square& s) : Line(s.x, s.y, s.length, s.color)
		{
			this->x = s.x;
			this->y = s.y;
			this->color = s.color;
			this->length = s.length;
		}
		
		void draw()
		{
			draw_x();
			draw_y();
			Line::move(0, length);
			draw_x();
			Line::move(length, -length);
			draw_y();
			Line::move(-length, 0);
		}
		
		void move(int dx, int dy)
		{
			x += dx;
			y += dy;
			Line::move(dx, dy);
		}
		
		void hide()
		{
			int t = color;
			this->color = 0;
			Line::color = 0;
			this->draw();
			this->color = t;
			Line::color = t;
		}
		
		~Square() = default;
};

class MyRectangle : public Square
{
	protected:
		int x, y;
		int color;
		int length_a;
		int length_b;
	public:
		MyRectangle(){
			x = 0;
			y = 0;
			color = 0;
			length_a = 0;
			length_b = 0;
		}
		
		MyRectangle(int x, int y, int color, int length_a, int length_b){
			this->x = x;
			this->y = y;
			this->color = color;
			this->length_a = length_a;
			this->length_b= length_b;
		}
		
		MyRectangle(const MyRectangle& r)
		{
			this->x = r.x;
			this->y = r.y;
			this->color = r.color;
			this->length_a = r.length_a;
			this->length_b= r.length_b;
		}
		
		void draw()
		{
			Line a(x, y, length_a, color);
			Line b(x, y, length_b, color);
			a.draw_x();
			b.draw_y();
			a.move(0, length_b);
			b.move(length_a, 0);
			a.draw_x();
			b.draw_y();
		}
		
		void hide(){
			int t = color;
			this->color = 0;
			this->draw();
			color = t;
		}
		
		void draw_vertical()
		{
			Line a(x, y, length_b, color);
			Line b(x, y, length_a, color);
			a.draw_x();
			b.draw_y();
			a.move(0, length_a);
			b.move(length_b, 0);
			a.draw_x();
			b.draw_y();
		}
		
		void hide_vertical(){
			int t = color;
			this->color = 0;
			this->draw_vertical();
			color = t;
		}
	void rotate()
	{
		static int counter = 0;
		this->hide();
		if(counter % 2 == 0){
			this->hide_vertical();
			this->draw_vertical();
		}
		else{
			this->hide();
			this->draw();
		}
		counter++;
	}
};



int main() {
	int gddriver = DETECT, gmode, errorcode;
    initgraph(&gddriver, &gmode, "");
	MyRectangle r(2, 2, 255, 500, 100);
	r.draw();
	getch();
	r.rotate();
	getch();
	r.rotate();
	getch();
    closegraph();
	return 0;
}
