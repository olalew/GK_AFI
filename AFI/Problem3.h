#ifndef Problem3_H
#define Problem3_H

#include <iostream>
#include <osg/Matrix>
#include <osg/Vec3>
#include <osg/Quat>

struct Problem3
{
private:
	bool away = false;
	float distanceAway = 0;

	int torus_cube_step = 0;
	bool move_left = false;
public:
	void updateTeapot(osg::Matrix& teapotMatrix, osg::Matrix& cubeMatrix)
	{
		osg::Vec3d pos = teapotMatrix.getTrans();
		static osg::Vec3d p1 = cubeMatrix.getTrans(); //punkt, wzgledem ktorego bedzie tworzona pierwsza czesc osemki
		static osg::Vec3d p2(1.5, 1, 1); //punkt, wzgledem ktorego bedzie tworzona pierwsza czesc osemki

		teapotMatrix *= osg::Matrix::translate(-p1);
		teapotMatrix *= osg::Matrix::rotate(osg::DegreesToRadians(9.f), osg::Vec3d(0, 0, 1));
		teapotMatrix *= osg::Matrix::translate(p1);

		if (away) {
			if (distanceAway >= 1) {
				away = false;
			}
			distanceAway += 0.01;
			teapotMatrix *= osg::Matrix::translate(osg::Vec3d(0, 0, 0.01));
		}
		else {
			if (distanceAway <= -1) {
				away = true;
			}
			distanceAway -= 0.01;
			teapotMatrix *= osg::Matrix::translate(osg::Vec3d(0, 0, -0.01));
		}
	}

	void updateTorus(osg::Matrix& torusMatrix, osg::Matrix& cubeMatrix)
	{
		osg::Vec3d pos = torusMatrix.getTrans();
		osg::Vec3d point = cubeMatrix.getTrans(); // punkt odniesienia
		static double angle = 270; // w stopniach
		osg::Vec3d angleVec; //modyfikator zmieniajacy promien okregu (tworzac efekt elipsy)
		const double step = 1.8; //rozmiar kroku

		angleVec = osg::Vec3d(cos(osg::DegreesToRadians(angle)), 0, 0);

		//obrot wokol wlasnej osi
		torusMatrix *= osg::Matrix::translate(-pos);
		torusMatrix *= osg::Matrix::rotate(osg::DegreesToRadians(step), osg::Vec3d(0, 0, 1));
		torusMatrix *= osg::Matrix::translate(pos);


	//   CIRCLE
		torusMatrix *= osg::Matrix::translate(-point - angleVec); //-angleVec - usun modyfikacje na czas obracania
		torusMatrix *= osg::Matrix::rotate(osg::DegreesToRadians(step), osg::Vec3d(0, 1, 0));
		torusMatrix *= osg::Matrix::translate(point); //nie przywracaj angleVec. zaraz zostanie dodana zaktualizowana wartosc

	//zmiana promienia
		angle = fmod(angle + step, 360);
		angleVec = osg::Vec3d(cos(osg::DegreesToRadians(angle)), 0, 0);
		torusMatrix *= osg::Matrix::translate(angleVec);
		//voila!
	}
};




#endif // Problem3
