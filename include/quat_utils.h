#ifndef	QUAT_UTILS_H_
#define	QUAT_UTILS_H_

#include <stdio.h>

void
quat_to_mat(double *quat, double mat[3][3])
{
  double w2 = quat[0]*quat[0];
  double i2 = quat[1]*quat[1];
  double j2 = quat[2]*quat[2];
  double k2 = quat[3]*quat[3];
  double twoij = 2.0*quat[1]*quat[2];
  double twoik = 2.0*quat[1]*quat[3];
  double twojk = 2.0*quat[2]*quat[3];
  double twoiw = 2.0*quat[1]*quat[0];
  double twojw = 2.0*quat[2]*quat[0];
  double twokw = 2.0*quat[3]*quat[0];

  mat[0][0] = w2+i2-j2-k2;
  mat[0][1] = twoij-twokw;
  mat[0][2] = twojw+twoik;

  mat[1][0] = twoij+twokw;
  mat[1][1] = w2-i2+j2-k2;
  mat[1][2] = twojk-twoiw;

  mat[2][0] = twoik-twojw;
  mat[2][1] = twojk+twoiw;
  mat[2][2] = w2-i2-j2+k2;
}

void
quat_to_mat_trans(double *quat, double mat[3][3])
{
  double w2 = quat[0]*quat[0];
  double i2 = quat[1]*quat[1];
  double j2 = quat[2]*quat[2];
  double k2 = quat[3]*quat[3];
  double twoij = 2.0*quat[1]*quat[2];
  double twoik = 2.0*quat[1]*quat[3];
  double twojk = 2.0*quat[2]*quat[3];
  double twoiw = 2.0*quat[1]*quat[0];
  double twojw = 2.0*quat[2]*quat[0];
  double twokw = 2.0*quat[3]*quat[0];

  mat[0][0] = w2+i2-j2-k2;
  mat[1][0] = twoij-twokw;
  mat[2][0] = twojw+twoik;

  mat[0][1] = twoij+twokw;
  mat[1][1] = w2-i2+j2-k2;
  mat[2][1] = twojk-twoiw;

  mat[0][2] = twoik-twojw;
  mat[1][2] = twojk+twoiw;
  mat[2][2] = w2-i2-j2+k2;
}

void
print_mat(double m[3][3])
{
  for (int i=0; i<3; ++i)
    printf("%16.8f %16.8f %16.8f\n", m[i][0], m[i][1], m[i][2]);
}

#endif	    /* !QUAT_UTILS_H_ */
