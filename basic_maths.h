#ifndef BASIC_MATHS_H
#define BASIC_MATHS_H

template<typename T> T average(T* t, unsigned int n){
	T s(0);
	for(unsigned int i=0;i<n;i++)
		s+=t[i];
	return s/n;
}

#endif
