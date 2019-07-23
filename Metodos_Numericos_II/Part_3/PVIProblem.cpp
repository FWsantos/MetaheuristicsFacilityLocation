#include "PVIProblem.h"

double PVIProblem::f(double* S){
	// S = (t, Y)
	return  1 - S[0] + 4*S[1];
} 


// PVIProblem::PVIProblem(char* expressao){}

double* PVIProblem::eulerForward(double* S0, double h, double t){
	// cout << S0[0]<<" t";
	// S = (t, Y)
	double S[2], aux[2] , k1, k2;
	for (int i = 0; i < 2; ++i)
		S[i] = S0[i];
	

	// for (int i = 0; i < n; ++i){
	while(S[0] < t){
		k1 = this->f(S);
		// cout << "k "<<k<<endl;
		aux[0] = S[0]+h;
		aux[1] = S[1]+h*k1;

		k2 =this->f(aux);
		S[1] = S[1] + (h/2)*(k1 + k2);
		S[0] = S[0] + h;
		// cout << "t "<< S[0]<<endl;
		// cout << "y "<< S[1]<<endl;
	}
	S0 = S;
	return S0;
}

// VectorXd PVIProblem::f(double t, VectorXd S){
// 	// double a= S(0);
// 	S(0) = 1-t+4*S(0);
// 	// cout <<endl<<"f("<<t<<", "<<a<<") = "<<S(0)<<endl;
// 	return 	S;
// }

VectorXd PVIProblem::f(double t, VectorXd S){
	double x= S(0);
	double y= S(1);
	
	const double m=1+(matricula[0]+matricula[1]+matricula[2]+matricula[3]+matricula[4]+matricula[5])%4;
	const double k = 4;
	const double w = sqrt(k/m);
	const double z = 0.05;
	
	double ft;
	if(t <= 0.5)
		ft = 4*t;
	else
		ft = 4*(1-t);

	double Vt = S(1), Xt = S(0);

	S(0) = Vt;

	S(1) = -ft/m - 2*w*Vt-pow(w,2)*Xt;
	// cout <<endl<<"t = "<<t<<", f("<<x<<", "<<y<<") = "<<S<<endl;

	return S;
}
double PVIProblem::norma(VectorXd X1, VectorXd X2){
	VectorXd R;
	R = X1-X2;
	double r = 0;
	for (int i = 0; i < X1.size(); ++i){
		r = abs(R(i));
	}
	return R.norm();
}
VectorXd PVIProblem::RungeKutta(VectorXd S0, double h, double t, double erro){
	
	VectorXd S = S0;
	VectorXd SOld = 10*S;
	VectorXd k[4];
	double ti = 0;
	
	while(norma(S, SOld) >= erro){
		SOld = S;
			// cout << "t "<< t<<endl;
			// cout << "S "<< S<<endl;


		while(ti <= t){
			// cout<<"cheguei"<<endl;
			k[0] = this->f(ti, S);
			k[1] =this->f(ti+0.5*h, S+0.5*h*k[0]);
			k[2] =this->f(ti+0.5*h, S+0.5*h*k[1]);
			k[3] =this->f(ti+h, S+(h*k[2]));

			S = S + (h/6)*(k[0] + (2*k[1]) + (2*k[2])+k[3]);
			ti = ti + h;
			
		}
		
		h = h/2;
	}

	S0 = S;
	return S0;	
}