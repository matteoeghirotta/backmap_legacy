#ifndef	PARTICLE_H_
#define	PARTICLE_H_

typedef struct particle {
  double pos[3];
  double quat[4];  
  double vel[3];
  double angmom[3];
  int type;
  int mol;
  int atomID;
} particle;


#endif	    /* !PARTICLE_H_ */
