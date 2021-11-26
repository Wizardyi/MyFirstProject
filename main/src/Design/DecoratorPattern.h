/**
	装饰者模式
 */

#pragma once
#include"../share/common.h"


class Shape
{
	public:
		virtual void draw(){

		}

		virtual ~Shape(){

		}
};


class Rectangle : public Shape
{
	public:
		void draw(){
			cout << "Rectangle  draw" << endl;
		}

};

class Circle : public Shape
{
	public:
		void draw(){
			cout << "Circle draw" << endl;
		}
};

class ShapeDecorator : public Shape
{
	public:
		ShapeDecorator(Shape* decoratedShape){
			this->decoratedShape = decoratedShape;
		}


		void draw(){
			decoratedShape->draw();
		}

	protected:
		Shape* decoratedShape;


};


class RedShapeDecorator : public ShapeDecorator
{
	public:
		RedShapeDecorator(Shape* decoratedShape):ShapeDecorator(decoratedShape){
		}

		void draw(){
			decoratedShape->draw();
			setRedBorder(decoratedShape);
		}
	
	private:
		void setRedBorder(Shape* decoratedShape){
			cout << "Border Color: Red" << endl;
		}

};




